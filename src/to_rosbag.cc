//
// Created by liu on 2021/3/9.
//

#include "../include/to_rosbag/to_rosbag.h"

ToRosBag::ToRosBag(std::string bag_path, std::string dataset_path) {
  bag_ = std::make_shared<rosbag::Bag>();
  bag_->open(bag_path, rosbag::bagmode::Write);

  toParserImage(dataset_path);
  toParserPose(dataset_path);
}

void ToRosBag::toParserImage(std::string dataset_path) {
  std::string left_topic_name = "/mono_left";
  std::string rear_topic_name = "/mono_rear";
  std::string righ_topic_name = "/mono_right";

  std::vector<std::pair<std::string, std::string>> image_path_list;
  // image_path_list.emplace_back(dataset_path + left_cam_base_name + ".timestamp", dataset_path + left_cam_base_name);
  image_path_list.emplace_back(dataset_path + rear_topic_name + ".timestamps", dataset_path + rear_topic_name);
  // image_path_list.emplace_back(dataset_path + righ_cam_base_name + ".timestamp", dataset_path + righ_cam_base_name);

  std::vector<std::string> image_topic_list;
  // image_topic_list.emplace_back(left_topic_name);
  image_topic_list.emplace_back(rear_topic_name);
  // image_topic_list.emplace_back(righ_topic_name);

  std::cout << " -- check image time stamp file: " << dataset_path + rear_topic_name + ".timestamps" << std::endl;
  std::cout << " -- check image path: " << dataset_path + rear_topic_name << std::endl;

  ip_ptr_ = std::make_shared<ImageParser>(image_path_list, image_topic_list, bag_);
}

void ToRosBag::toParserPose(std::string dataset_path) {
  pp_ptr_ = std::make_shared<PoseParser>(dataset_path, bag_);
}

