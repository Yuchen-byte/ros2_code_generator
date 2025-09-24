#include "template/template_handle.hpp"
#include "template/register.hpp"
#include <chrono>
#include <string>

using to_seconds = std::chrono::duration<double>;

namespace ns_template
{

TemplateHandle::TemplateHandle(const std::string& name) : Node(name)
{
  loadParameters();
  subscribeToTopics();
  publishToTopics();
  createTimer();

  template_ = std::make_shared<Template>();
}

TemplateHandle::~TemplateHandle() = default;

void TemplateHandle::loadParameters()
{
  REGISTER_TOPIC_NAME_LOAD("template_subscribe_topic_name",
                           template_subscribe_topic_name_, "/default_topic1")
  REGISTER_TOPIC_NAME_LOAD("template_publish_topic_name",
                           template_publish_topic_name_, "/default_topic2")
  REGISTER_TOPIC_NAME_LOAD("template_scs_topic_name", template_scs_topic_name_,
                           "/default_topic3")

  REGISTER_DOUBLE_VALUE_LOAD("loop_rate", loop_rate_, 100.0)
  REGISTER_DOUBLE_VALUE_LOAD("watch_dog_rate", watch_dog_rate_, 2.0)
  REGISTER_DOUBLE_VALUE_LOAD("visualization_rate", visualization_rate_, 5.0)
  REGISTER_DOUBLE_VALUE_LOAD("watch_dog_timeout", watch_dog_timeout_, 1.0)
}

void TemplateHandle::subscribeToTopics()
{
  templateStateSubscription_ = this->create_subscription<std_msgs::msg::String>(
      template_subscribe_topic_name_, 10,
      [this](const std_msgs::msg::String::ConstSharedPtr& msg)
      { templateStateCallback(msg); });
}

void TemplateHandle::publishToTopics()
{
  templateStatePublisher_ = this->create_publisher<std_msgs::msg::String>(
      template_publish_topic_name_, 10);
  scsPublisher_ = this->create_publisher<robot_msgs::msg::ScsSignal>(
      template_scs_topic_name_, 10);
}

void TemplateHandle::createTimer()
{
  loop_timer_ = this->create_wall_timer(to_seconds(1.0 / loop_rate_),
                                        [this] { LoopTimerCallback(); });
  watch_dog_timer_ = this->create_wall_timer(
      to_seconds(1.0 / watch_dog_rate_), [this] { WatchDogTimerCallback(); });
  visualization_timer_ = this->create_wall_timer(
      to_seconds(1.0 / visualization_rate_), [this] { sendVisualization(); });
}

void TemplateHandle::templateStateCallback(
    const std_msgs::msg::String::ConstSharedPtr& msg)
{
  // Update topic state
  topic_update_states_[template_subscribe_topic_name_].stamp =
      this->get_clock()->now();
  template_->setData(msg);
  RCLCPP_INFO(rclcpp::get_logger("template"), "Receive: %s",
              (*msg).data.c_str());
}

void TemplateHandle::LoopTimerCallback()
{
  if (!template_->runAlgorithm())
    {
      sendScsSignal("Algorithm running failed", true);
    }
  sendMsg();
}

void TemplateHandle::WatchDogTimerCallback()
{
  for (const auto& it : topic_update_states_)
    {
      // Timeout 1 sec
      if (std::fabs(rclcpp::Time(it.second.stamp).seconds() -
                    this->get_clock()->now().seconds()) > watch_dog_timeout_)
        {
          sendScsSignal("Topic " + it.first + " timeout !", true);
        }
    }
}

void TemplateHandle::sendMsg()
{
  if (templateStatePublisher_->get_subscription_count() > 0)
    {
      templateStatePublisher_->publish(*template_->getData());
    }
}

void TemplateHandle::sendVisualization() {}

void TemplateHandle::sendScsSignal(const std::string& msg, bool status)
{
  RCLCPP_ERROR(rclcpp::get_logger("SCS Trigger"), "%s", msg.c_str());
  scs_msg_.header.stamp = this->get_clock()->now();
  scs_msg_.info = msg;
  scs_msg_.status = status;
  scsPublisher_->publish(scs_msg_);
}

}  // namespace ns_template
