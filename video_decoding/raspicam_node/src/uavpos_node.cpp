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

#include "uavData.h"
#include "publish.h"

#define ALWAYS_WANT_LOGGING
#define VERSION_STRING "v1.2"

#include "ros/ros.h"

int main(int argc, char** argv) {
  ros::init(argc, argv, "uavpos");
  ros::NodeHandle nh_ttauav;

  // The node handle used for topics will be private or public depending on the value of the ~private_topics parameter

  // nh_params.param("skip_frames", skip_frames, 0);

  uavData *m_puavData = new uavData(47141);
  m_puavData->start();

  uavData_publish *m_puavData_publish = new uavData_publish(&nh_ttauav, m_puavData);
  m_puavData_publish->start();

  // std::thread measurement_process();

  //ros::Rate(50);

  ros::spin();
  // close_cam(state_srv);
  // ros::shutdown();
}

#endif  // __arm__ || __aarch64__
