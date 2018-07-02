#include "stdafx.h"
#include "Broadcast.h"
#include "json\json.h"
#include "json\config.h"
#include "server_config.h"
#include "zmq.hpp"
#include "common.h"
//#include "zhelpers.hpp"
using namespace std;

char *g_broadCast_strAliveCheck = NULL;
DWORD  WINAPI broadcast_worker(void * context)
{
	MSG msg;
	Json::Value value;
	Json::Reader reader;
	int len = 0, nMsgType = 0, ret = 0;
	//zmq::socket_t *broad_sk = new zmq::socket_t(context, ZMQ_DEALER);
//	zmq::socket_t *bd = new zmq::socket_t(context, ZMQ_DEALER);
	
	

	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	while (true) {
		while (true)
		{
			if (PeekMessage(&msg, 0, 0, 0, NULL)) {
				memset(&msg, 0, sizeof(msg));
				ret = GetMessage(&msg, NULL, 0, 0);
				if (ret == -1) {
					fprintf(flog, "[%s] [%d]  GetMessage failed error ==== %d \n", __FUNCTION__, __LINE__, GetLastError());
					//fflush(flog);
					continue;
				}
				char * pInfo = (char *)msg.wParam;
				char * lparam = (char *)msg.lParam;

			value.clear();
			//fprintf(flog, " wparam_free_func  free bradcast msg seccuss 11 ", __FUNCTION__, __LINE__);
			if (!parse_queuemsg2_json(pInfo,reader,value,msg,NULL))//parse pInfo2 Json fail
			{				
				continue;
			}
			else
			{
			
				if (msg.message != BROADCAST_ALIVE_CHECK && msg.message > WM_TIMER) {
#ifdef BROADCAST_VALUE_PRINT
					fprintf(flog, "broadcast worker queue msg============== %s", pInfo);
					fflush(flog);
#endif
				}

			}
			//fprintf(flog, " wparam_free_func  free bradcast msg Over 222", __FUNCTION__, __LINE__);
			len = strlen((char *)msg.wParam);
			switch (msg.message)
			{
			case FACE_TELL_RESULT:
#ifdef ALARM_BROADCAST_PRINT
				printf("\n\n\n\n\n");
				printf("************************************\n");
				printf("send face alarm msg out\n");
				printf("************************************\n");
				printf("\n\n\n\n\n");
				fprintf(flog, "broadcast worker recv face tell msg and send it to client ============== %s", pInfo);
				fflush(flog);
#endif
				s_send(broadcast_sk, (char *)msg.wParam);
				break;
			case BROADCAST_ALIVE_CHECK:
				nMsgType = BROADCAST_RETURN_IAM_ALIVE;
				g_broadCast_strAliveCheck = (char *)malloc(strlen(BROADCAST_STILL_ALIVE) + 10);
				memset(g_broadCast_strAliveCheck, 0, strlen(BROADCAST_STILL_ALIVE) + 10);
				strcpy(g_broadCast_strAliveCheck, BROADCAST_STILL_ALIVE);
				if (lpMonitorThreadId != 0) {
					ret = PostThreadMessage(lpMonitorThreadId, nMsgType, (WPARAM)g_broadCast_strAliveCheck, NULL);
					if (!postthreadmessage_check(ret)) {
						fprintf(flog, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);			
						wparam_free(&g_broadCast_strAliveCheck);
					}
				}
				else {
					fprintf(flog, "erroe lpMonitorThreadId ============== %d", lpMonitorThreadId);					
				}				
				break;
			default:
				break;
			}
			fflush(flog);
			//printf(" wparam_free_func  free bradcast msg start 33");
			switch (msg.message) {
			case FACE_TELL_RESULT:
				wparam_free(&pInfo);
				break;
			case BROADCAST_ALIVE_CHECK:
			//	printf( " wparam_free_func  free bradcast msg start********#####");
				wparam_free(&pInfo);
			//	printf(" wparam_free_func  free bradcast msg Over *********!!!!!!");
				//fprintf(flog, " wparam_free_func  free bradcast msg seccuss ", __FUNCTION__, __LINE__);
				break;
			default:
				break;
			}			
		}
	}	
		fprintf(flog, "[%s] [%s] [%d] broadcast worker end timepoint \n", get_system_misecond_time(), __FUNCTION__, __LINE__);
		fflush(flog);
	}
	return 0;
}
