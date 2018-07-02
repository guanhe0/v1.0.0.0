#pragma once
#ifndef FACEDETECT_H
#define FACEDETECT_H


#include "json\json.h"
#include <json\config.h>
#include "zmq.hpp"
//#include "zmq.h"
//#include "zmq_utils.h"
//#include "zhelper.h"
//#include <opencv2\core\core.hpp>
//#include <opencv2\highgui\highgui.hpp>
#include <string.h>
#include "server_config.h"
#include "common.h"
class FaceDetect
{
public:
	FaceDetect();
	bool FaceDetectHandle();
	bool FaceDetectSetResponse(Json::Value *value);
	
	bool InitParm(void *context, const int nMsgCode, Json::Value *value,void *soc);
	
	~FaceDetect();
private:
	void *ctx;
	int code;
	Json::Value *val;
	void *socket;
};
DWORD  WINAPI facedt_worker(void * context);
bool facedt_recv2req(Json::Value *val);
extern Json::Value face_dt_init_value;
extern Json::Value facedt_java_change_camera;
extern char *g_facedt_strAliveCheck;
#endif // !FACEDETECT_H