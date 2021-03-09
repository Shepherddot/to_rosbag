//
// Created by liu on 2021/3/9.
//

#ifndef TO_ROSBAG_INCLUDE_TO_ROSBAG_POSE_PARSER_H_
#define TO_ROSBAG_INCLUDE_TO_ROSBAG_POSE_PARSER_H_

#include <string>
#include <vector>
#include <memory>

#include <ros/time.h>
#include <opencv2/core.hpp>

#include "../include/to_rosbag/time_parser.h"

class PoseParser{
 public:
  PoseParser(std::string dataset_path_);

  std::vector<cv::Mat> getPoseList();
  std::vector<ros::Time> getTimeList();

 private:
  std::shared_ptr<TimeParser> tp_ptr_;

  std::vector<ros::Time> time_list_;
  std::vector<cv::Mat> pose_list_;
};

#endif //TO_ROSBAG_INCLUDE_TO_ROSBAG_POSE_PARSER_H_
