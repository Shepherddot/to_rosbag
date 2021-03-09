//
// Created by liu on 2021/3/9.
//

#ifndef TO_ROSBAG_INCLUDE_TO_ROSBAG_IMAGE_PARSER_H_
#define TO_ROSBAG_INCLUDE_TO_ROSBAG_IMAGE_PARSER_H_

// this class is only for all images and correspond timestamps reading.

#include <vector>
#include <string>

#include <ros/time.h>

#include <opencv2/core.hpp>

class ImageParser {
 public:
  ImageParser(std::vector<std::pair<std::string, std::string>> dataset_path);

  std::vector<std::vector<ros::Time>> getImageTimeList();
  std::vector<std::vector<cv::Mat>> getImageList();

 private:
  std::vector<std::vector<ros::Time>> image_time_list_;
  std::vector<std::vector<cv::Mat>> image_list_;
};

#endif //TO_ROSBAG_INCLUDE_TO_ROSBAG_IMAGE_PARSER_H_
