#pragma once

#include <string>

#define REGISTER_TOPIC_NAME_LOAD(config_name, topic, default_name)     \
  this->declare_parameter<std::string>(config_name, default_name);     \
  if (!this->get_parameter(config_name, topic)) {                      \
    RCLCPP_ERROR(rclcpp::get_logger("load_param"),                      \
                "Did not load %s. Standard value is: %s", config_name, \
                topic.c_str());                                        \
  }

#define REGISTER_DOUBLE_VALUE_LOAD(config_name, value, default_value)   \
  this->declare_parameter<double>(config_name, default_value);          \
  if (!this->get_parameter(config_name, value)) {                       \
    RCLCPP_ERROR(rclcpp::get_logger("load_param"),                       \
                "Did not load %s. Standard value is: %lf", config_name, \
                value);                                                 \
  }

#define REGISTER_INT_VALUE_LOAD(config_name, value, default_value)             \
  this->declare_parameter<int>(config_name, default_value);                    \
  if (!this->get_parameter(config_name, value)) {                              \
    RCLCPP_ERROR(rclcpp::get_logger("load_param"),                              \
                "Did not load %s. Standard value is: %d", config_name, value); \
  }

#define REGISTER_BOOL_VALUE_LOAD(config_name, value, default_value)    \
  this->declare_parameter<bool>(config_name, default_value);           \
  if (!this->get_parameter(config_name, value)) {                      \
    RCLCPP_ERROR(rclcpp::get_logger("load_param"),                      \
                "Did not load %s. Standard value is: %s", config_name, \
                value ? "true" : "false");                             \
  }
