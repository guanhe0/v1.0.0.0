#pragma once
#include "json\json.h"
#include <json\config.h>
#include "zmq.hpp"
//#include "zmq_utils.h"
//#include "zmq.h"
//#include "zhelper.h"
class FaceTell {
public:
	FaceTell(void *sok);
	~FaceTell();
	bool FaceMsgFill(Json::Value *src,Json::Value *ret);//人脸检测数据转人脸识别请求
//	DWORD WINAPI FaceTellMsgThread(void * context);
	
//	bool InitParam(void *ctx, void *sock);
private:
	
	
	void *ctx;
	void *dealer_sok;//while 循环执行会导致不断初始化和创建dealer_sok
};
DWORD  WINAPI facetell_worker(void * context);
bool facetell_connect_status_update();
extern char *g_facetell_strAliveCheck;