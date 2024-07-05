#pragma once
#include <stdint.h>
#include <string>
#include "Thread.h"
#include "uavData.h"

#include "ros/ros.h"
#include "ttauav_node/flight.h"
#include "ttauav_node/takeoffOrLanding.h"

class uavData_service : public Thread
{
public:
    uavData_service(ros::NodeHandle *nh, uavData *puavData);
    virtual ~uavData_service();

public:
    int proxy();

protected:
    int doProxy();
	void threadFunc();

private:
bool takeoffOrLanding_serverCB(ttauav_node::takeoffOrLanding::Request  &req,
         ttauav_node::takeoffOrLanding::Response &res);
bool flight_serverCB(ttauav_node::flight::Request  &req,
         ttauav_node::flight::Response &res);

private:
    ros::NodeHandle *m_uavdata_nh;
    uavData *m_puavData;

};

