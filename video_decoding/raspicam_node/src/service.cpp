#include "uavData.h"
#include "service.h"
#include "Utils.h"
#include "ttalinkUtils.h"

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float64.h"

//uavData *g_puavData = NULL;

uavData_service::uavData_service(ros::NodeHandle *nh, uavData *puavData)
{
    m_uavdata_nh = nh;
    m_puavData = puavData;
}

uavData_service::~uavData_service()
{

}

int uavData_service::proxy()
{	
	doProxy();

	return 0;
}

bool takeoffOrLanding_serverCB1(ttauav_node::takeoffOrLanding::Request  &req,
         ttauav_node::takeoffOrLanding::Response &res)
{
    res.ack = 1;

    ROS_INFO("takeoff or landing server cb ");

//   res.res.moon_year = req.req.year+1;
//   res.res.moon_month = req.req.month+1;
//   res.res.moon_day = req.req.day+1;
//   ROS_INFO("request: year=%d, month=%d, day=%d", req.req.year, req.req.month, req.req.day);
//   ROS_INFO("sending back response: year[%d],month[%d],day[%d]", res.res.moon_year, res.res.moon_month, res.res.moon_day);
  return true;
}

// bool uavData_service::takeoffOrLanding_serverCB(ttauav_node::takeoffOrLanding::Request  &req,
//          ttauav_node::takeoffOrLanding::Response &res)
// {
//     res.ack = 1;

//     ROS_INFO("takeoff or landing server cb ");

//     ttalink_rosuav_ctrl_loop_input_t rosuav_ctrl_loop_input = {0};

//     if(req.takeoffOrLanding == 1)
//     {
//       rosuav_ctrl_loop_input.flight_ctrl_status = ROS_F_GPS_AUTO_TAKE_OFF;
//     }
//     else if(req.takeoffOrLanding == 2)
//     {
//       rosuav_ctrl_loop_input.flight_ctrl_status = ROS_F_GPS_NAVGATION_ALTI_VEL;
//     }

//     ttalinkUtils::rosuav_ctrl_loopinput(this->m_puavData->getDataPort(), TTALINK_FC_ADDRESS, TTALINK_EMBE_ADDRESS, &rosuav_ctrl_loop_input, 0);

// //   res.res.moon_year = req.req.year+1;
// //   res.res.moon_month = req.req.month+1;
// //   res.res.moon_day = req.req.day+1;
// //   ROS_INFO("request: year=%d, month=%d, day=%d", req.req.year, req.req.month, req.req.day);
// //   ROS_INFO("sending back response: year[%d],month[%d],day[%d]", res.res.moon_year, res.res.moon_month, res.res.moon_day);
//   return true;
// }

bool uavData_service::flight_serverCB(ttauav_node::flight::Request  &req,
         ttauav_node::flight::Response &res)
{
  ROS_INFO("flight server cb ");

    res.ack = 1;

    ttalink_rosuav_ctrl_loop_input_t rosuav_ctrl_loop_input = {0};

    rosuav_ctrl_loop_input.flight_ctrl_status = ROS_F_GPS_POS_VEL_ALTI_VEL;

    rosuav_ctrl_loop_input.velN = req.offset[0];
    rosuav_ctrl_loop_input.velE = req.offset[1];
    rosuav_ctrl_loop_input.velD = req.offset[2];

    rosuav_ctrl_loop_input.atti_yaw = req.targetYaw;

    rosuav_ctrl_loop_input.param[0] = req.yawThreshold;
    rosuav_ctrl_loop_input.param[1] = req.posThreshold;

    // rosuav_ctrl_loop_input.targetYaw
    // rosuav_ctrl_loop_input.yawThreshold
    // rosuav_ctrl_loop_input.posThreshold
    
    ttalinkUtils::rosuav_ctrl_loopinput(this->m_puavData->getDataPort(), TTALINK_FC_ADDRESS, TTALINK_EMBE_ADDRESS, &rosuav_ctrl_loop_input, 0);
//   ROS_INFO("request: year=%d, month=%d, day=%d", req.req.year, req.req.month, req.req.day);
//   ROS_INFO("sending back response: year[%d],month[%d],day[%d]", res.res.moon_year, res.res.moon_month, res.res.moon_day);
  return true;
}

int service_init() {
    ros::NodeHandle n;

    ros::ServiceServer service1 = n.advertiseService("takeoffOrLanding", takeoffOrLanding_serverCB1);
    // ros::ServiceServer service1 = m_uavdata_nh->advertiseService("takeoffOrLanding", &uavData_service::takeoffOrLanding_serverCB, this);
    ROS_INFO("Start takeoffOrLanding server");

    // ros::ServiceServer service2 = n.advertiseService("flight", flight_serverCB);
    // ROS_INFO("Start flight server");

    // ros::MultiThreadedSpinner spinner(2);

    // ros::spin();
    //ros::spinOnce();

	return 0;
}

int uavData_service::doProxy()
{
	int64_t now = Utils::getSystemRunTime();
    ros::NodeHandle n;

    service_init();

    // ros::ServiceServer service1 = n.advertiseService("takeoffOrLanding", takeoffOrLanding_serverCB1);
    // // ros::ServiceServer service1 = m_uavdata_nh->advertiseService("takeoffOrLanding", &uavData_service::takeoffOrLanding_serverCB, this);
    // ROS_INFO("Start takeoffOrLanding server");

    // // ros::ServiceServer service2 = m_uavdata_nh->advertiseService("flight", &uavData_service::flight_serverCB, this);
    // // ROS_INFO("Start flight server");

    // // ros::MultiThreadedSpinner spinner(2);

    // // ros::spin();
    // ros::spinOnce();

	return 0;
}

void uavData_service::threadFunc(){
	proxy();
}



