#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include <chrono>

using namespace std::chrono_literals;


/**
 * @brief A class that implements a publisher object to print a string.
 * 
 */
class SimplePublisher : public rclcpp::Node
{
public:
  /**
   * @brief Construct a new Simple Publisher object and create timer function.
   * 
   */
  SimplePublisher() : Node("simple_publisher"), counter_(0)
  {
    pub_ = create_publisher<std_msgs::msg::String>("chatter", 10);
    timer_ = create_wall_timer(1s, std::bind(&SimplePublisher::timerCallback, this));
    RCLCPP_INFO(get_logger(), "Publishing at 1 Hz");
  }

  /**
   * @brief A callback function that prints a string that uses a incrementing
   * counter variable.
   */
  void timerCallback()
  {
    auto message = std_msgs::msg::String();
    message.data = "Hello ROS 2 - counter:" + std::to_string(counter_++);
    pub_->publish(message);
  }


private:
  // private variables
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  unsigned int counter_;
};


int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<SimplePublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}