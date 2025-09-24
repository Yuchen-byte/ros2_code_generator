#pragma once
#include "std_msgs/msg/string.hpp"

namespace ns_template
{

  class Template
  {
  public:
    Template();

    ~Template();

    void setData(const std_msgs::msg::String::ConstSharedPtr &msg);
    std_msgs::msg::String::ConstSharedPtr getData();

    bool runAlgorithm();

  private:
    std_msgs::msg::String::ConstSharedPtr current_str_;
  };

} // namespace ns_template
