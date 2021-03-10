//
// Created by liu on 2021/3/9.
//

#include "../include/to_rosbag/pose_parser.h"

#include "../include/to_rosbag/time_parser.h"
#include "../include/to_rosbag/common.h"

#include <nav_msgs/Odometry.h>

#include <opencv2/core/quaternion.hpp>

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

    std::cout << "-- check rotation: " << std::endl << r << std::endl;

    nav_msgs::Odometry odo_msg;
    odo_msg.header.stamp = curr_t;
    odo_msg.header.frame_id = "odom";
    odo_msg.child_frame_id = "base_link";

    cv::Quatf q = cv::Quatf::createFromRotMat(r);

    odo_msg.pose.pose.position.x = north;
    odo_msg.pose.pose.position.y = east;
    odo_msg.pose.pose.position.z = down;

    odo_msg.pose.pose.orientation.w = q.w;
    odo_msg.pose.pose.orientation.x = q.x;
    odo_msg.pose.pose.orientation.y = q.y;
    odo_msg.pose.pose.orientation.z = q.z;

    bag->write("/car/odom", curr_t, odo_msg);
  }

}

