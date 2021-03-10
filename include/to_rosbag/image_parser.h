//
// Created by liu on 2021/3/9.
//

#ifndef TO_ROSBAG_INCLUDE_TO_ROSBAG_IMAGE_PARSER_H_
#define TO_ROSBAG_INCLUDE_TO_ROSBAG_IMAGE_PARSER_H_

// this class is only for all images and correspond timestamps reading.

#include <vector>
#include <string>

#include <rosbag/bag.h>

class ImageParser {
 public:
  ImageParser(std::vector<std::pair<std::string, std::string>> dataset_path, std::vector<std::string> topic_name, std::shared_ptr<rosbag::Bag> bag);
};

#endif //TO_ROSBAG_INCLUDE_TO_ROSBAG_IMAGE_PARSER_H_
