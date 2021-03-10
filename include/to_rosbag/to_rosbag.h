//
// Created by liu on 2021/3/9.
//

#ifndef TO_ROSBAG_INCLUDE_TO_ROSBAG_TO_ROSBAG_H_
#define TO_ROSBAG_INCLUDE_TO_ROSBAG_TO_ROSBAG_H_

#include <string>

#include <rosbag/bag.h>

#include "image_parser.h"
#include "pose_parser.h"

class ToRosBag {
 public:
  ToRosBag(std::string bag_path, std::string dataset_path);

 private:
  void toParserImage(std::string dataset_path);
  void toParserPose(std::string dataset_path);

  std::shared_ptr<rosbag::Bag> bag_;

  std::shared_ptr<ImageParser> ip_ptr_;
  std::shared_ptr<PoseParser> pp_ptr_;
};

#endif //TO_ROSBAG_INCLUDE_TO_ROSBAG_TO_ROSBAG_H_
