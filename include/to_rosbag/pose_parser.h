//
// Created by liu on 2021/3/9.
//

#ifndef TO_ROSBAG_INCLUDE_TO_ROSBAG_POSE_PARSER_H_
#define TO_ROSBAG_INCLUDE_TO_ROSBAG_POSE_PARSER_H_

#include <string>
#include <vector>
#include <memory>

#include <ros/time.h>
#include <rosbag/bag.h>

#include <opencv2/core.hpp>

class PoseParser{
 public:
  PoseParser(std::string dataset_path, std::shared_ptr<rosbag::Bag> bag);
};

#endif //TO_ROSBAG_INCLUDE_TO_ROSBAG_POSE_PARSER_H_
