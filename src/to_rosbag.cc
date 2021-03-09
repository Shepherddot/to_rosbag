//
// Created by liu on 2021/3/9.
//

#include "../include/to_rosbag/to_rosbag.h"

#include <nav_msgs/Odometry.h>

#include <opencv2/core/quaternion.hpp>

#include "../include/to_rosbag/common.h"

const int kCamNum = 3;

ToRosBag::ToRosBag(std::string bag_path, std::string dataset_path) {
  bag_.open(bag_path, rosbag::bagmode::Write);

  toParserImage(dataset_path);
  toParserPose(dataset_path);
}

void ToRosBag::toParserImage(std::string dataset_path) {
  std::string left_cam_base_name = "/mono_left";
  std::string rear_cam_base_name = "/mono_rear";
  std::string righ_cam_base_name = "/mono_right";

  std::vector<std::pair<std::string, std::string>> image_path_list;
  for (int i = 0; i < kCamNum; i++) {
    image_path_list.emplace_back(dataset_path + left_cam_base_name + ".timestamp", dataset_path + left_cam_base_name);
    image_path_list.emplace_back(dataset_path + rear_cam_base_name + ".timestamp", dataset_path + rear_cam_base_name);
    image_path_list.emplace_back(dataset_path + righ_cam_base_name + ".timestamp", dataset_path + righ_cam_base_name);
  }

  ip_ptr_ = std::make_shared<ImageParser>(image_path_list);

  std::vector<std::vector<ros::Time>> time_list = ip_ptr_->getImageTimeList();
  std::vector<std::vector<cv::Mat>> image_list = ip_ptr_->getImageList();

  for (int cam_i = 0; cam_i < kCamNum; cam_i++) {
    std::vector<ros::Time> cam_time_list = time_list[cam_i];
    std::vector<cv::Mat> cam_image_list = image_list[cam_i];

    for (int i = 0; i < cam_time_list.size(); i++) {
      sensor_msgs::Image image_msg;
      imageToRos(cam_image_list[i], &image_msg);
      image_msg.header.stamp = cam_time_list[i];
      image_msg.header.frame_id = i;

      bag_.write(left_cam_base_name, cam_time_list[i], image_msg);
    }
  }

}

void ToRosBag::toParserPose(std::string dataset_path) {
  pp_ptr_ = std::make_shared<PoseParser>(dataset_path);

  std::vector<ros::Time> time_list = pp_ptr_->getTimeList();
  std::vector<cv::Mat> pose_list = pp_ptr_->getPoseList();

  for (int i = 0; i < time_list.size(); i++) {
    nav_msgs::Odometry odo_msg;
    odo_msg.header.stamp = time_list[i];
    odo_msg.header.frame_id = "odom";
    odo_msg.child_frame_id = "base_link";

    cv::Mat pose = pose_list[i];
    cv::Mat r = pose.rowRange(0, 3).colRange(0, 3);
    cv::Quatf q;
    q.createFromRotMat(r);
    cv::Mat t = pose.col(3).rowRange(0, 3);

    odo_msg.pose.pose.position.x = t.at<float>(0);
    odo_msg.pose.pose.position.y = t.at<float>(1);
    odo_msg.pose.pose.position.z = t.at<float>(2);

    odo_msg.pose.pose.orientation.w = q.w;
    odo_msg.pose.pose.orientation.x = q.x;
    odo_msg.pose.pose.orientation.y = q.y;
    odo_msg.pose.pose.orientation.z = q.z;

    bag_.write("/car/odom", time_list[i], odo_msg);
  }
  
}

