#include "uavData.h"
//#include "service.h"
#include "Utils.h"
#include "ttalinkUtils.h"

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float64.h"

#include "ttauav_node/gimbalControl.h"
#include "ttauav_node/takeoffOrLanding.h"
#include "ttauav_node/flightByOffset.h"
#include "ttauav_node/flightByVel.h"

#include "uavData.h"

uavData *m_puavData = NULL;

bool takeoffOrLanding_serverCB1(ttauav_node::takeoffOrLanding::Request  &req,
         ttauav_node::takeoffOrLanding::Response &res)
{
    res.ack = 1;

    ROS_INFO("takeoff or landing server cb ");

    res.ack = 1;

    ttalink_rosuav_ctrl_loop_input_t rosuav_ctrl_loop_input = {0};

    if(req.takeoffOrLanding == 1)
    {
      rosuav_ctrl_loop_input.flight_ctrl_status = ROS_F_GPS_AUTO_TAKE_OFF;

      ROS_INFO("request: takeoff ");
    }
    else if(req.takeoffOrLanding == 2)
    {
      rosuav_ctrl_loop_input.flight_ctrl_status = ROS_F_GPS_NAVGATION_ALTI_VEL;

      ROS_INFO("request: landing ");
    }

    if(m_puavData)
    {
      ttalinkUtils::rosuav_ctrl_loopinput(m_puavData->getDataPort(), TTALINK_FC_ADDRESS, TTALINK_EMBE_ADDRESS, &rosuav_ctrl_loop_input, 0);
    }
//   res.res.moon_year = req.req.year+1;
//   res.res.moon_month = req.req.month+1;
//   res.res.moon_day = req.req.day+1;
//   ROS_INFO("request: year=%d, month=%d, day=%d", req.req.year, req.req.month, req.req.day);
//   ROS_INFO("sending back response: year[%d],month[%d],day[%d]", res.res.moon_year, res.res.moon_month, res.res.moon_day);

  return true;
}

bool flightByOffset_serverCB(ttauav_node::flightByOffset::Request  &req,
         ttauav_node::flightByOffset::Response &res)
{
    res.ack = 1;

    ROS_INFO("flight offset server cb ");

    ttalink_rosuav_ctrl_loop_input_t rosuav_ctrl_loop_input = {0};

    rosuav_ctrl_loop_input.flight_ctrl_status = ROS_F_GPS_POS_VEL;

    rosuav_ctrl_loop_input.velN = req.offset[0];
    rosuav_ctrl_loop_input.velE = req.offset[1];
    rosuav_ctrl_loop_input.velD = req.offset[2];

    rosuav_ctrl_loop_input.atti_yaw = req.targetYaw;

    rosuav_ctrl_loop_input.param[0] = req.yawThreshold;
    rosuav_ctrl_loop_input.param[1] = req.posThreshold;

    // rosuav_ctrl_loop_input.targetYaw
    // rosuav_ctrl_loop_input.yawThreshold
    // rosuav_ctrl_loop_input.posThreshold

    ROS_INFO("request: targetYaw:%f ", req.targetYaw);
    
    ttalinkUtils::rosuav_ctrl_loopinput(m_puavData->getDataPort(), TTALINK_FC_ADDRESS, TTALINK_EMBE_ADDRESS, &rosuav_ctrl_loop_input, 0);
//   ROS_INFO("request: year=%d, month=%d, day=%d", req.req.year, req.req.month, req.req.day);
  return true;
}

bool flightByVel_serverCB(ttauav_node::flightByVel::Request  &req,
         ttauav_node::flightByVel::Response &res)
{
    res.ack = 1;

    ROS_INFO("flight vel server cb ");

    ttalink_rosuav_ctrl_loop_input_t rosuav_ctrl_loop_input = {0};

    rosuav_ctrl_loop_input.flight_ctrl_status = ROS_F_GPS_POS_VEL_ALTI_VEL;

    rosuav_ctrl_loop_input.velN = req.vel_n;
    rosuav_ctrl_loop_input.velE = req.vel_e;
    rosuav_ctrl_loop_input.velD = req.vel_d;

    rosuav_ctrl_loop_input.atti_yaw = req.targetYaw;

    rosuav_ctrl_loop_input.param[0] = req.fly_time;

    // rosuav_ctrl_loop_input.targetYaw
    // rosuav_ctrl_loop_input.yawThreshold
    // rosuav_ctrl_loop_input.posThreshold

    ROS_INFO("request: targetYaw:%f ", req.targetYaw);
    
    ttalinkUtils::rosuav_ctrl_loopinput(m_puavData->getDataPort(), TTALINK_FC_ADDRESS, TTALINK_EMBE_ADDRESS, &rosuav_ctrl_loop_input, 0);
//   ROS_INFO("request: year=%d, month=%d, day=%d", req.req.year, req.req.month, req.req.day);
  return true;
}

bool gimbalControl_serverCB(ttauav_node::gimbalControl::Request  &req,
         ttauav_node::gimbalControl::Response &res)
{
    res.ack = 1;

    ROS_INFO("gimbal control server cb ");

    // rosuav_ctrl_loop_input.targetYaw
    // rosuav_ctrl_loop_input.yawThreshold
    // rosuav_ctrl_loop_input.posThreshold

    ROS_INFO("request: pitch:%f , roll:%f, yaw:%f", req.pitch, req.roll, req.yaw);
    
    //ttalinkUtils::rosuav_ctrl_loopinput(m_puavData->getDataPort(), TTALINK_FC_ADDRESS, TTALINK_EMBE_ADDRESS, &rosuav_ctrl_loop_input, 0);

    ttalinkUtils::SendGeneralCommand(m_puavData->getDataPort(), TTALINK_PTZ_ADDRESS, TTALINK_EMBE_ADDRESS
    , 11223344, 0, 109, req.pitch, req.roll, req.yaw,0,0,0,0);

    return true;
}


int main(int argc, char** argv) {
  ros::init(argc, argv, "service");
    ros::NodeHandle n;

    m_puavData = new uavData(47142);
    m_puavData->start();

    ros::ServiceServer service1 = n.advertiseService("takeoffOrLanding", takeoffOrLanding_serverCB1);
    // ros::ServiceServer service1 = m_uavdata_nh->advertiseService("takeoffOrLanding", &uavData_service::takeoffOrLanding_serverCB, this);
    ROS_INFO("Start takeoffOrLanding server");

    ros::ServiceServer service2 = n.advertiseService("flightByOffset", flightByOffset_serverCB);
    ROS_INFO("Start flightByOffset server");

    ros::ServiceServer service3 = n.advertiseService("flightByVel", flightByVel_serverCB);
    ROS_INFO("Start flightByVel server");

    ros::ServiceServer service4 = n.advertiseService("gimbalControl", gimbalControl_serverCB);
    ROS_INFO("Start gimbalControl server");

    ros::MultiThreadedSpinner spinner(4);

    ros::spin();
    //ros::spinOnce();

	return 0;
}




