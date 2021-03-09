//
// Created by liu on 2021/3/9.
//

#include "../include/to_rosbag/image_parser.h"

#include <fstream>
#include <sstream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "../include/to_rosbag/time_parser.h"

ImageParser::ImageParser(std::vector<std::pair<std::string, std::string>> dataset_path) {
  int cam_num = dataset_path.size();

  for (int path_i = 0; path_i < cam_num; path_i++) {
    auto path = dataset_path[path_i];

    std::ifstream in(path.first);

    std::vector<uint64_t> time_list;
    std::string line;
    while (std::getline(in, line)) {
      std::stringstream s(line);
      uint64_t timestamp;
      s >> timestamp;
      time_list.push_back(timestamp);
    }

    std::shared_ptr<TimeParser> tp_ptr = std::make_shared<TimeParser>(time_list);
    image_time_list_.push_back(tp_ptr->getTimeList());

    std::vector<std::string> image_paths;
    cv::glob(path.second, image_paths);
    std::sort(image_paths.begin(), image_paths.end());

    for (auto certain_im = image_paths.begin(); certain_im != image_paths.end(); certain_im++) {
      cv::Mat im = cv::imread(*certain_im, cv::IMREAD_UNCHANGED);
      image_list_[path_i].push_back(im);
    }

  }

}

std::vector<std::vector<ros::Time>> ImageParser::getImageTimeList() {
  return image_time_list_;
}

std::vector<std::vector<cv::Mat>> ImageParser::getImageList() {
  return image_list_;
}

