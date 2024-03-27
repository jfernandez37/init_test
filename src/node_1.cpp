#include <init_test/node_1.hpp>
#include <init_test/node_2.hpp>


Node2::Node2()
{
  node_2_context_ = rclcpp::Context::make_shared();
  node_2_context_2_ = rclcpp::Context::make_shared();
  if (!rclcpp::ok(node_2_context_2_)){
    node_2_context_2_->init(0, nullptr);
    std::cout <<  "node 2 init ran" << std::endl;
  }
  else{
    std::cout <<  "node 2 init did not run" << std::endl;
  }

  rclcpp::NodeOptions node_options = rclcpp::NodeOptions();
  
  node_options.context(node_2_context_2_);
  _ros_node_2 = rclcpp::Node::make_shared("node_2_node", node_options);

  std::cout << node_2_context_2_->is_valid() << std::endl;
  
  // if(!rclcpp::ok()){
  //   rclcpp::init(0,nullptr);
  //   std::cout <<  "node 2 init ran" << std::endl;
  // }
  // else{
  //   std::cout <<  "node 2 init did not run" << std::endl;
  // }
  
  // _ros_node_2 = rclcpp::Node::make_shared("node_2_node");


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

  auto node_2 = std::make_shared<Node2>();

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
  auto node_1 = std::make_shared<Node1>();
}