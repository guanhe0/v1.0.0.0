#pragma once
#include "json\json.h"
#include "json\config.h"
#include "zmq.h"
//#include "zmq_utils.h"
#include "common.h"
#include "server_config.h"
class ReqRepForJava
{
public:
	ReqRepForJava();
	~ReqRepForJava();
	bool ReqDataFromJava(int mode, Json::Value *pj, Json::Value *pr);
	bool RecvDataFromJava(int mode, Json::Value *pj);	
private:

};
DWORD  WINAPI java_worker(void * context);
bool trans_query_reslut2_client(int *len_pre, char **strTmp, Json::Value *val, int ThreadId, int nMsgType);
bool jthread_request2_other(int msg_type, DWORD  thread, Json::Value &value, char **str_tmp, void *param);
void CALLBACK java_change_camera_timer_pro(UINT wTimerID, UINT nMsg, DWORD dwUser, DWORD dwl, DWORD dw2);
bool java_change_camera_result_collect(int req_pre, Json::Value &value, Json::Value &responseValue,void *para);

