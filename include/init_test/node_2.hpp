#ifndef INIT_TEST__NODE_2_HPP_
#define INIT_TEST__NODE_2_HPP_

#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/string.hpp>

#include <thread>
#include <chrono>
#include <functional>
#include <memory>
#include <string>

class Node2{
    public: Node2();
    public: ~Node2();
      void node_2_callback() const;
    private:
      rclcpp::Node::SharedPtr _ros_node_2;
      rclcpp::executors::MultiThreadedExecutor::SharedPtr executor_2_;
      std::thread thread_executor_2_spin_;

      rclcpp::Context::SharedPtr node_2_context_;
      rclcpp::Context::SharedPtr node_2_context_2_;

      rclcpp::TimerBase::SharedPtr node2_timer_;
      rclcpp::Publisher<std_msgs::msg::String>::SharedPtr node2_publisher_;
};

#endif

