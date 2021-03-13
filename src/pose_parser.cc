//
// Created by liu on 2021/3/9.
//

#include "../include/to_rosbag/pose_parser.h"

#include "../include/to_rosbag/time_parser.h"
#include "../include/to_rosbag/common.h"

#include <nav_msgs/Odometry.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <opencv2/core/quaternion.hpp>
#include <opencv2/core/eigen.hpp>

#include "../thirdparty/fast-cpp-csv-parser/csv.h"

PoseParser::PoseParser(std::string dataset_path, std::shared_ptr<rosbag::Bag> bag) {
  std::string pose_path = dataset_path + "/rtk.csv";

  std::cout << "-- check pose file path: " << pose_path << std::endl;

  io::CSVReader<7> in(pose_path);
  in.read_header(io::ignore_extra_column, "timestamp", "northing", "easting", "down", "roll", "pitch", "yaw");
  std::string timestamp;
  float north;
  float east;
  float down;
  float roll;
  float pitch;
  float yaw;

  std::shared_ptr<TimeParser> tp_ptr = std::make_shared<TimeParser>();

  while (in.read_row(timestamp, north, east, down, roll, pitch, yaw)) {
    ros::Time curr_t;
    tp_ptr->timestampToRos(timestamp, &curr_t);

    cv::Point3f euler;
    euler.x = roll;
    euler.y = pitch;
    euler.z = yaw;

    cv::Mat r = cv::Mat::eye(3, 3, CV_32FC1);
    Common::rpyToRotMat(euler, r);

    cv::Mat transform = cv::Mat::eye(4, 4, CV_32FC1);
    r.copyTo(transform.rowRange(0, 3).colRange(0, 3));
    cv::Mat t = (cv::Mat_<float>(3, 1) << north, east, down);
    t.copyTo(transform.col(3).rowRange(0, 3));

    Eigen::AngleAxisf rollAngle(Eigen::AngleAxisf(0, Eigen::Vector3f::UnitX()));
    Eigen::AngleAxisf pitchAngle(Eigen::AngleAxisf(0, Eigen::Vector3f::UnitY()));
    Eigen::AngleAxisf yawAngle(Eigen::AngleAxisf(-(CV_PI / 2), Eigen::Vector3f::UnitZ()));

    Eigen::Matrix3f modify_rot;
    modify_rot = yawAngle * pitchAngle * rollAngle;

    cv::Mat cv_rot;
    cv::eigen2cv(modify_rot, cv_rot);

    cv::Mat cv_modify_rot = cv::Mat::eye(4, 4, CV_32FC1);
    cv_rot.copyTo(cv_modify_rot.rowRange(0, 3).colRange(0, 3));

    transform = transform * cv_modify_rot;

    if (is_this_start_) {
      start_point_ = transform.clone();
      is_this_start_ = false;
    }

    cv::Mat odom_transform = start_point_.inv() * transform;

    nav_msgs::Odometry odo_msg;
    odo_msg.header.stamp = curr_t;
    odo_msg.header.frame_id = "odom";
    odo_msg.child_frame_id = "base_link";

    Eigen::Matrix3f e_rot;
    cv::cv2eigen(odom_transform.colRange(0, 3).rowRange(0, 3), e_rot);
    Eigen::Quaternionf q(e_rot);

    odo_msg.pose.pose.position.x = odom_transform.col(3).at<float>(0);
    odo_msg.pose.pose.position.y = odom_transform.col(3).at<float>(1);
    odo_msg.pose.pose.position.z = odom_transform.col(3).at<float>(2);

    odo_msg.pose.pose.orientation.w = q.w();
    odo_msg.pose.pose.orientation.x = q.x();
    odo_msg.pose.pose.orientation.y = q.y();
    odo_msg.pose.pose.orientation.z = q.z();

    std::ofstream pose_file;
    pose_file.open("/home/liu/traj.txt", std::ios::app);
    pose_file << std::fixed << std::setprecision(6) << curr_t.toSec() << " " << odom_transform.col(3).at<float>(0) << " "
              << odom_transform.col(3).at<float>(1) << " " << odom_transform.col(3).at<float>(2) << " " << q.x() << " " << q.y() << " " << q.z()
              << " " << q.w() << "\n";

    bag->write("/car/odom", curr_t, odo_msg);
  }

}

