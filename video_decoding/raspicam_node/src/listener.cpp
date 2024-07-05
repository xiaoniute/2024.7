/*
Copyright (c) 2013, Broadcom Europe Ltd
Copyright (c) 2013, James Hughes
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef __x86_64__

#include <stdio.h>

int main(int argc, char** argv) {
  (void)fprintf(stderr, "The raspicam_node for the x86/64 architecture is a fake!\n");
  return 1;
}

#endif  // __x86_64__

#if defined(__arm__) || defined(__aarch64__)

// We use some GNU extensions (basename)
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <memory>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float64.h"
#include "ttauav_node/uavdata.h"

void chatterCallback(const ttauav_node::uavdata::ConstPtr& msg)
{
    //ROS_INFO("I heard:[%s]", msg->data.c_str());
    ROS_INFO("I heard:[%f]", msg->latit);
    ROS_INFO("I heard:[%f]", msg->longi);

    ROS_INFO("I heard:[%f]", msg->quat[0]);
    ROS_INFO("I heard:[%f]", msg->quat[1]);
    ROS_INFO("I heard:[%f]", msg->quat[2]);
    ROS_INFO("I heard:[%f]", msg->quat[3]);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "listener");
  ros::NodeHandle nh_listener;

  // The node handle used for topics will be private or public depending on the value of the ~private_topics parameter

  // nh_params.param("skip_frames", skip_frames, 0);

  ros::Subscriber sub = nh_listener.subscribe("uavdata", 1000, chatterCallback);

  // std::thread measurement_process();

  //ros::Rate(50);

  ros::spin();
  // close_cam(state_srv);
  // ros::shutdown();
}

#endif  // __arm__ || __aarch64__
