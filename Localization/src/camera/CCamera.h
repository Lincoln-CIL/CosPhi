/*
 * File name: CCamera.h
 * Author:    Tom Krajnik
 */

#ifndef __CWEBCAMERA_H__
#define __CWEBCAMERA_H__

#include "CRawImage.h" 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cmath.h"
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <CTimer.h>

//---START--ROS---
#ifdef USE_ROS
#include <ros/package.h>
#include <image_transport/image_transport.h>
#endif
//---END--ROS---

//---START--OPENCV---
#ifdef USE_OPENCV
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#endif
//---END--OPENCV---

extern "C" {
#include "v4l2uvc.h"
}

//-----------------------------------------------------------------------------
// Class CCamera
//-----------------------------------------------------------------------------
//! A CCamera class
/*! class to represent robot's camera
 */

typedef enum{
	CT_UNKNOWN,
	CT_WEBCAM,
	CT_FILELOADER,
	CT_VIDEOLOADER,
	CT_ROS_CAM,
	CT_OPENCV,
	CT_NUMBER
}ECameraType;

class CCamera
{

	public:

	CCamera();
	int init(const char *deviceName,int *wi,int *he,bool saveI);
	~CCamera();
	int renewImage(CRawImage* image,bool a);
	int initFileLoader(const char *deviceName,int *wi,int *he);
	void setGain(int value);
	int getGain();
	void setContrast(int value);
	int getContrast();

	void changeExposition(int value);
	void changeBrightness(int value);
	void changeGain(int value);
	void changeContrast(int value);
	void setExposition(int value);
	int getExposition();
	
	void setBrightness(int value);
	int getBrightness();
	int setDeviceAutoExposure(const int val);
	int setDeviceWhiteBalanceAuto(const int val);
	int setDeviceWhiteTemperature(const int value);
	int getDeviceWhiteTemperature();
	int fileNum;		
	ECameraType cameraType;

	bool running;
	bool stop;

	int saveConfig(const char* filename);
	int loadConfig(const char* filename);
	char directory[1000];
	private:
	int getDeviceGain();
	int getDeviceContrast();
	int getDeviceExposition();
	int getDeviceBrightness();
	int getDeviceSharpness();

	int setDeviceExposition(int value);
	int setDeviceSharpness(const int value);
	int setDeviceGain(const int value);
	int setDeviceContrast(const int value);
	int setDeviceBrightness(const int value);
	int getParamInfo(const int paramType, int &min, int &max, int &default_val);
	
	int exposition;
	int brightness;
	int gain;
	int format;
	int contrast;

	bool autoexposure;
	struct vdIn *videoIn;
	int width, height;
	char avifilename[100];
	CTimer globalTimer;
	bool save,readNextFrame;
	avi_t *aviFile; 
	char *aviBuffer1; 
	unsigned char *aviBuffer2; 
#ifdef USE_OPENCV
	cv::VideoCapture *openCVDevice;
#endif
};
#endif
/* end of CCamera.h */
