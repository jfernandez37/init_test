cmake_minimum_required(VERSION 3.8)
project(init_test)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


set(THIS_PACKAGE_INCLUDE_DEPENDS
  rclcpp 
  std_msgs
)

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()

#Node 1 executable
add_executable(node_1 src/node_1.cpp)
target_include_directories(node_1 PRIVATE include)
ament_target_dependencies(node_1 ${THIS_PACKAGE_INCLUDE_DEPENDS})

install(TARGETS node_1
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

# #Node 2 executable
add_executable(node_2 src/node_2.cpp)
target_include_directories(node_2 PRIVATE include)
ament_target_dependencies(node_2 ${THIS_PACKAGE_INCLUDE_DEPENDS})

install(TARGETS node_2
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)


install(DIRECTORY 
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
