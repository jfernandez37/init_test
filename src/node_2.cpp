#include <init_test/node_2.hpp>


Node2::Node2()
{
  if(!rclcpp::ok()){
    rclcpp::init(0,nullptr);
    std::cout <<  "node 2 init ran" << std::endl;
  }
  else{
    std::cout <<  "node 2 init did not run" << std::endl;
  }
  
  _ros_node_2 = rclcpp::Node::make_shared("node_2_node");
  executor_2_ = std::make_shared<rclcpp::executors::MultiThreadedExecutor>();
  executor_2_->add_node(_ros_node_2);

  auto spin = [this](){
    while(rclcpp::ok()){
      executor_2_->spin_once();
    }
  };

  thread_executor_2_spin_ = std::thread(spin);

  // Publisher
  this->node2_publisher_ = this->_ros_node_2->create_publisher<std_msgs::msg::String>("node2/msg", 10);
  node2_timer_ = _ros_node_2->create_wall_timer(std::chrono::duration<double>(3), std::bind(&Node2::node_2_callback, this));
}
 
Node2::~Node2()
{
  executor_2_->cancel();
  thread_executor_2_spin_.join();
}

void Node2::node_2_callback() const{
  std_msgs::msg::String node_2_msg = std_msgs::msg::String();
  node_2_msg.data = "node_2";
  node2_publisher_->publish(node_2_msg);
}

int main(int argc, char *argv[])
{
  auto node_2 = std::make_shared<Node2>();
}