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
	PcClient();//val ָ����������json context ָ���߳������Ļ��� socket ָ���߳̽�����Ϣ��socket nMsgCodeָ������code
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