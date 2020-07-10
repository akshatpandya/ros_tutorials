cmake_minimum_required(VERSION 2.8.3)
project(ros_tutorials)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation	
)

add_message_files(
   FILES
   file_entry.msg
   population_msg.msg
 )

add_service_files(
FILES
edit_field.srv
)

generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
)

include_directories(
include ${catkin_INCLUDE_DIRS}
)

add_executable(population_node src/population_node.cpp)
target_link_libraries(population_node ${catkin_LIBRARIES})
add_dependencies(population_node ${catkin_EXPORTED_TARGETS})

add_executable(client_node src/client_node.cpp)
target_link_libraries(client_node ${catkin_LIBRARIES})
add_dependencies(client_node ${catkin_EXPORTED_TARGETS})

catkin_install_python(PROGRAMS scripts/client_node.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

catkin_install_python(PROGRAMS scripts/server_node.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)