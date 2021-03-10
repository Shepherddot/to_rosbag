//
// Created by liu on 2021/3/9.
//

#include "../include/to_rosbag/image_parser.h"

#include <iostream>

#include <ros/time.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "../include/to_rosbag/common.h"
#include "../include/to_rosbag/time_parser.h"

ImageParser::ImageParser(std::vector<std::pair<std::string, std::string>> dataset_path,
                         std::vector<std::string> topic_name,
                         std::shared_ptr<rosbag::Bag> bag) {
  int cam_num = dataset_path.size();

  for (int path_i = 0; path_i < cam_num; path_i++) {
    auto path = dataset_path[path_i];

    std::ifstream in(path.first);

    std::cout << "-- show image time stamp path: " << path.first << std::endl;

    std::shared_ptr<TimeParser> tp_ptr = std::make_shared<TimeParser>();

    std::string line;
    int image_counter = 0;
    while (std::getline(in, line)) {
      std::stringstream s(line);
      std::string timestamp;
      s >> timestamp;

      std::string image_file_path = path.second + "/" + timestamp + ".png";

      std::cout << "-- image file path: " << image_file_path << " current id: " << std::to_string(image_counter) << std::endl;

      cv::Mat im = cv::imread(image_file_path, cv::IMREAD_UNCHANGED);

      sensor_msgs::Image image_msg;
      Common::imageToRos(im, &image_msg);

      ros::Time curr_t;
      tp_ptr->timestampToRos(timestamp, &curr_t);

      image_msg.header.stamp = curr_t;
      image_msg.header.frame_id = image_counter;

      image_counter++;

      bag->write(topic_name[path_i], curr_t, image_msg);
    } // loop time stamp file

  }

}

