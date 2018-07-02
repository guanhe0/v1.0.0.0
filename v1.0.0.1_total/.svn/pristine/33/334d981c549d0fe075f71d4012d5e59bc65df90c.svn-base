#pragma once
#include "json\json.h"
#include <json\config.h>
#include "msgDefine.h"
#include "common.h"

class FaceRecgAlarm
{
public:
	FaceRecgAlarm(Json::Value *val, void * context, int nMsgCode);//val 指向接收消息json value，context 线程指向上下文，nMsgCode消息类型
	~FaceRecgAlarm();
	bool FaceRecgAlarmHand();
	bool FaceRecgBroadCast();
	bool UpdateAlarmInfoSet();
	bool ChangeAlarmInfoSet();// (int nMsgID, int npPrsonID, int nOptState, string strOpter);
	bool FaceRecgAlarmResponse(Json::Value *sendValue);
	bool SetReponseMsgHead(Json::Value *dst, Json::Value *src);

private:
	Json::Value *value;
	void *context;
	int nMsgCode;
};
