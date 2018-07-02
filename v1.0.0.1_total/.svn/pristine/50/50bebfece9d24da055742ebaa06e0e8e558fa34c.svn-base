#pragma once
#ifndef PC_CLIENT_H
#define PC_CLIENT_H


#include "json\json.h"
#include <json\config.h>
#include "msgDefine.h"
#include "common.h"
#include "server_config.h"

class PcClient
{
public:
	PcClient();//val 指向请求数据json context 指向线程上下文环境 socket 指向线程接收消息的socket nMsgCode指向请求code
	~PcClient();
	
	
	
	
	
	
	bool CameraArrayAppend(Json::Value *dst, Json::Value *src);
	bool DistricArrayAppend(Json::Value *dst, Json::Value *src);
	bool EaraArrayAppend(Json::Value *dst, Json::Value *src);
	bool CameraListToJson(Json::Value *dst, Json::Value *src,int len);
	
	
private:
	int nJsonMsgCode;
	Json::Value *pValue;
	int nResponse;
	void * pContext;
	int nRequestId;	
};
DWORD  WINAPI client_worker(void * context);
bool trans_query_msg2_java(Json::Value *val, Json::Value *request);

#endif // !PC_CLIENT_H