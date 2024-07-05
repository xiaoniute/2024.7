cmake_minimum_required(VERSION 3.1)
project(ttauav_node)


set(CMAKE_CXX_STANDARD 14) # use C++14
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed")  # https://github.com/raspberrypi/userland/issues/178

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  compressed_image_transport
  roscpp
  std_msgs
  message_generation
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES arm*) 

ENDIF()


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

#######################################
## Declare ROS messages and services ##
#######################################

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  uavdata.msg
)

## Generate services in the 'srv' folder
add_service_files(
  FILES
  takeoffOrLanding.srv
  flightByOffset.srv
  flightByVel.srv
  gimbalControl.srv
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

#add dynamic reconfigure api
generate_dynamic_reconfigure_options(

)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
   INCLUDE_DIRS include
#  LIBRARIES raspicam
#  CATKIN_DEPENDS compressed_image_transport roscpp std_msgs
#  DEPENDS system_lib
   CATKIN_DEPENDS message_runtime std_msgs roscpp
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include
  ${catkin_INCLUDE_DIRS}
  /opt/vc/include
  /opt/vc/include/interface/vcos/pthreads
  /opt/vc/include/interface/vmcs_host/linux
  src/utils
  src/proxy_src
  src/ttalink
)

add_compile_options(-Wall -Wuseless-cast -Wformat-nonliteral)

aux_source_directory(src/proxy_src PROXY_SRCS)
add_library(proxy ${PROXY_SRCS})

aux_source_directory(src/utils UTILS_SRCS)
add_library(utils ${UTILS_SRCS})

## Declare a cpp executable
add_executable(uavdata src/ttauav_node.cpp src/uavData.cpp src/publish.cpp )
add_dependencies(uavdata ttauav_node_generate_messages_cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(uavdata
  ${catkin_LIBRARIES}
  ${RPI_LIBRARIES} 
  utils
  proxy
)

## Declare a cpp executable
# add_executable(uavpos src/uavpos_node.cpp src/uavData.cpp src/publish.cpp)
# add_dependencies(uavpos ttauav_node_generate_messages_cpp)

# ## Specify libraries to link a library or executable target against
# target_link_libraries(uavpos
#   ${catkin_LIBRARIES}
#   ${RPI_LIBRARIES} 
#   utils
#   proxy
# )

add_executable(listener src/listener.cpp)
add_dependencies(listener ttauav_node_generate_messages_cpp)

target_link_libraries(listener
  ${catkin_LIBRARIES}
  ${RPI_LIBRARIES}
)

add_executable(service src/service_test.cpp src/uavData.cpp )
add_dependencies(service ttauav_node_generate_messages_cpp)

target_link_libraries(service
  ${catkin_LIBRARIES}
  ${RPI_LIBRARIES} 
  utils
  proxy
)


add_executable(service_client src/serviceClient.cpp)
add_dependencies(service_client ttauav_node_generate_messages_cpp)

target_link_libraries(service_client
  ${catkin_LIBRARIES}
  ${RPI_LIBRARIES}
)


#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
install(TARGETS uavdata listener service service_client
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

# Mark other files for installation (e.g. launch and bag files, etc.)
install(DIRECTORY
  launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)


