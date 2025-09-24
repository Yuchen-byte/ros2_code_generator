#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "template/template.hpp"

#include "robot_msgs/msg/scs_signal.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/header.hpp"

namespace ns_template
{

  class TemplateHandle : public rclcpp::Node
  {
  public:
    explicit TemplateHandle(const std::string &name);

    ~TemplateHandle();

  private:
    /* Initialize interface */
    void loadParameters();
    void subscribeToTopics();
    void publishToTopics();
    void createTimer();

    /* Subscribe Callback */
    void templateStateCallback(const std_msgs::msg::String::ConstSharedPtr &msg);

    /* Timer Callback */
    void LoopTimerCallback();
    void WatchDogTimerCallback();

    /* Send Messages */
    void sendMsg();
    void sendVisualization();
    void sendScsSignal(const std::string &msg, bool state);

    /* Interface variable */
    // Topic name
    std::string template_subscribe_topic_name_;
    std::string template_publish_topic_name_;
    std::string template_scs_topic_name_;

    // Timer
    rclcpp::TimerBase::SharedPtr loop_timer_;
    rclcpp::TimerBase::SharedPtr watch_dog_timer_;
    rclcpp::TimerBase::SharedPtr visualization_timer_;

    // Timer rate
    double loop_rate_;
    double watch_dog_rate_;
    double visualization_rate_;

    // Watch dog timeout
    double watch_dog_timeout_;

    // Topic update states
    std::unordered_map<std::string, std_msgs::msg::Header> topic_update_states_;
    robot_msgs::msg::ScsSignal scs_msg_;

    // Subscription
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr templateStateSubscription_;

    // Publisher
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr templateStatePublisher_;
    rclcpp::Publisher<robot_msgs::msg::ScsSignal>::SharedPtr scsPublisher_;

    // Other variable
    std::shared_ptr<Template> template_;
  };

} // namespace ns_template
