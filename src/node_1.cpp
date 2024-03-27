#include <init_test/node_1.hpp>


Node1::Node1()
{
  // conveyor_context = rclcpp::Context::make_shared();
  // if (!rclcpp::ok(conveyor_context)){
  //   conveyor_context->init(0, nullptr);
  //   rclcpp::init(0,nullptr);
  // }

  // rclcpp::NodeOptions node_options = rclcpp::NodeOptions();
  
  // node_options.context(conveyor_context);

  // std::string node_name = "conveyor_ros_node";
  if(!rclcpp::ok()){
    rclcpp::init(0,nullptr);
    std::cout <<  "node 1 init ran" << std::endl;
  }
  else{
    std::cout <<  "node 1 init did not run" << std::endl;
  }
  
  _ros_node = rclcpp::Node::make_shared("node_1_node");
  executor_ = std::make_shared<rclcpp::executors::MultiThreadedExecutor>();
  executor_->add_node(_ros_node);

  auto spin = [this](){
    while(rclcpp::ok()){
      executor_->spin_once();
    }
  };

  thread_executor_spin_ = std::thread(spin);

  // Publisher
  this->node1_publisher_ = this->_ros_node->create_publisher<std_msgs::msg::String>("node1/msg", 10);
  node1_timer_ = _ros_node->create_wall_timer(std::chrono::duration<double>(3), std::bind(&Node1::node_1_callback, this));
  
}
 
Node1::~Node1()
{
  executor_->cancel();
  thread_executor_spin_.join();
}

void Node1::node_1_callback() const{
  std_msgs::msg::String node_1_msg = std_msgs::msg::String();
  node_1_msg.data = "node_1";
  node1_publisher_->publish(node_1_msg);
}

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  auto node_1 = std::make_shared<Node1>();
}