#ifndef INIT_TEST__NODE_1_HPP_
#define INIT_TEST__NODE_1_HPP_

#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/string.hpp>

#include <thread>
#include <chrono>
#include <functional>
#include <memory>
#include <string>

class Node1{
    public: Node1();
    public: ~Node1();
      void node_1_callback() const;
    private:
      rclcpp::Node::SharedPtr _ros_node;
      rclcpp::executors::MultiThreadedExecutor::SharedPtr executor_;
      std::thread thread_executor_spin_;

      rclcpp::TimerBase::SharedPtr node1_timer_;
      rclcpp::Publisher<std_msgs::msg::String>::SharedPtr node1_publisher_;
};

#endif

