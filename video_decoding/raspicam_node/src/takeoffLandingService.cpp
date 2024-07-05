#include "ros/ros.h"
#include "ttauav_node/takeoffOrLanding.h"

//服务回调函数
bool serverCB(ttauav_node::takeoffOrLanding::Request  &req,
         ttauav_node::takeoffOrLanding::Response &res)
{
//   res.res.moon_year = req.req.year+1;
//   res.res.moon_month = req.req.month+1;
//   res.res.moon_day = req.req.day+1;
//   ROS_INFO("request: year=%d, month=%d, day=%d", req.req.year, req.req.month, req.req.day);
//   ROS_INFO("sending back response: year[%d],month[%d],day[%d]", res.res.moon_year, res.res.moon_month, res.res.moon_day);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "flightcontrol_node");
  ros::NodeHandle n;

  //向ROS Master注册服务
  ros::ServiceServer service = n.advertiseService("takeoffOrLanding", serverCB);
  ROS_INFO("Start takeoffOrLanding server");
  ros::spin();

  return 0;
}

