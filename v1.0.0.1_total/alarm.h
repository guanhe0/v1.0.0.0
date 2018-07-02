#pragma once
#include "json\json.h"
#include <json\config.h>
#include "msgDefine.h"
#include "common.h"

class FaceRecgAlarm
{
public:
	FaceRecgAlarm(Json::Value *val, void * context, int nMsgCode);//val ָ�������Ϣjson value��context �߳�ָ�������ģ�nMsgCode��Ϣ����
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
