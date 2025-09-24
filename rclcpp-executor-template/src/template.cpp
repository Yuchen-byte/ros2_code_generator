#include "template/template.hpp"

namespace ns_template
{

Template::Template()
{
  current_str_ = std::make_shared<std_msgs::msg::String>();
}

Template::~Template() = default;

void Template::setData(const std_msgs::msg::String::ConstSharedPtr &msg)
{
  current_str_ = msg;
}

std_msgs::msg::String::ConstSharedPtr Template::getData()
{
  return current_str_;
}

bool Template::runAlgorithm()
{
  return true;
}

} // namespace ns_template
