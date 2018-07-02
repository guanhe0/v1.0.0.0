#include "stdafx.h"
#include "monitor.h"
#include "common.h"
#include "WinUser.h"
#define ARE_YOU_OK "are you ok"
#define TIMER_ID_FACE_TELL  1
#define TIMER_ID_TRACK  2
#define TIMER_ID_BROADCAST 3
#define CAMERA_STATUS_QUERY_BROADCAST 4
#define TIMER_ID_SERVER_STATUS 5
#define TIMER_ID_FACEDT	6

//int var define
int timeout_face_tell = 2000;
int timeout_track = 1000;
int timeout_broadcast = 2000;
int timeout_camera_status_timeout = 300000;
int timeout_server_status_timeout = 60000;
int timeout_facedt_timeout = 2000;

//Json value define
static Json::Value monitor_value;
static Json::Value track_value;
static Json::Value camera_status_query;
//char var define
char *MonitorStrThreadMsg = NULL;

//function define
void CALLBACK face_tell_timer_proc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);
void CALLBACK track_timer_proc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);
void CALLBACK broadcast_timer_proc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);
void CALLBACK camera_status_timer_proc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);//相机状态检测
void CALLBACK server_status_timer_proc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);//server status query
void CALLBACK facedt_timer_proc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);//server status query

void CALLBACK facedt_timer_proc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)//server status query
{
	int nMsgType = FACEDT_ALIVE_CHECK;
	int ret = 0, len = 0;

	add_msg2_head(monitor_value);
	//	postthreadmessage_mem_malloc(&malloc_len_pre, &MonitorStrThreadMsg, &monitor_value);
	len = strlen(monitor_value.toStyledString().data());
	char *MonitorStrThreadMsg = (char *)malloc(len + 1);

	memset(MonitorStrThreadMsg, 0, len + 1);
	strcpy(MonitorStrThreadMsg, monitor_value.toStyledString().data());
#ifdef MONITOR_VLAUE_PRINT
//	fprintf(flog_monitor, "[%s] [%s] [%d] broadcast_timer_proc send alive check msg ======== %s\n", __TIME__,__FUNCTION__, __LINE__, MonitorStrThreadMsg);
//	//fflush(flog);
#endif
	if (lpFaceDtThreadId != 0) {
		ret = PostThreadMessage(lpFaceDtThreadId, nMsgType, (WPARAM)MonitorStrThreadMsg, NULL);
		if (!postthreadmessage_check(ret)) {
			fprintf(flog_monitor, "[%s] [%s] [%d] PostThreadMessage failed\n", __TIME__,__FUNCTION__, __LINE__);
			//fflush(flog);
			wparam_free(&MonitorStrThreadMsg);
		}
	}
}
void CALLBACK server_status_timer_proc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)//server status query
{
	//just get server self status
	//send it to java 
	int nMsgType = SERVER_STATUS_PUSH;
	int ret = 0,len = 0;
	DWORD dwTotalRecv1 = 0, dwTotalSend1 = 0;
	DWORD maxNetData = 0;
	DWORD mem_total = 0, mem_avail = 0,mem_used = 0;
	Json::Value ServerStatus, msgBody, MonitorList, dataPush, dataRequest, atom_status;

	

	GetSysNetworkFlowByMidTable(dwTotalRecv1, dwTotalSend1);
	maxNetData = dwTotalRecv1 > dwTotalSend1 ? dwTotalRecv1 : dwTotalSend1;
	GetSysMemUseStatus(mem_total, mem_avail);
	mem_used = mem_total - mem_avail;
	SetMsgHead(&ServerStatus, NULL, JSONMSGTYPE_REQUEST, JSONMSGCODE_SERVER_MONITOR_SERVER);
	atom_status["serverId"] = "server01";
	atom_status["currentTime"] = ServerStatus["msgHead"]["timestamp"];
	atom_status["memory"] = int(mem_used);
	atom_status["networkFlow"] = (int)maxNetData;
	MonitorList[0] = atom_status;
	dataPush["MonitorList"] = MonitorList;
	msgBody["dataPush"] = dataPush;
	msgBody["dataRequest"] = {};
	msgBody["dataRequest"]["code"] = 0;
	ServerStatus["msgBody"] = msgBody;
	add_msg2_head(ServerStatus);

	len = strlen(ServerStatus.toStyledString().data());
	char *MonitorStrThreadMsg = (char *)malloc(len + 1);
	memset(MonitorStrThreadMsg, 0, len + 1);
	strcpy(MonitorStrThreadMsg, ServerStatus.toStyledString().data());



	if (lpJavaThreadId != 0) {
		ret = PostThreadMessage(lpJavaThreadId, nMsgType, (WPARAM)MonitorStrThreadMsg, NULL);
		if (!postthreadmessage_check(ret)) {
			fprintf(flog_monitor, "[%s] [%s] [%d] PostThreadMessage failed\n", __TIME__,__FUNCTION__, __LINE__);
			//fflush(flog);
			wparam_free(&MonitorStrThreadMsg);
		}
		else{
#ifdef MONITOR_VLAUE_PRINT
			fprintf(flog_monitor, "[%s] [%s] [%d] server_status_timer_proc send  msg to java ======== %s\n", __TIME__,__FUNCTION__, __LINE__, MonitorStrThreadMsg);
			//fflush(flog);
#endif
		}
	}


}

void CALLBACK broadcast_timer_proc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)//广播线程心跳检测

{

	int nMsgType = BROADCAST_ALIVE_CHECK;		
	int ret = 0,len = 0;
	
	add_msg2_head(monitor_value);
//	postthreadmessage_mem_malloc(&malloc_len_pre, &MonitorStrThreadMsg, &monitor_value);
	len = strlen(monitor_value.toStyledString().data());
	char *MonitorStrThreadMsg = (char *)malloc(len + 1);

	memset(MonitorStrThreadMsg, 0, len + 1);
	strcpy(MonitorStrThreadMsg, monitor_value.toStyledString().data());
#ifdef MONITOR_VLAUE_PRINT
	//fprintf(flog_monitor, "[%s] [%s] [%d] broadcast_timer_proc send alive check msg ======== %s\n", __TIME__,__FUNCTION__, __LINE__, MonitorStrThreadMsg);
	////fflush(flog);
#endif
	if (lpBroadCastThreadId != 0) {
		ret = PostThreadMessage(lpBroadCastThreadId, nMsgType, (WPARAM)MonitorStrThreadMsg, NULL);
		if (!postthreadmessage_check(ret)) {
			fprintf(flog_monitor, "[%s] [%s] [%d] PostThreadMessage failed\n", __TIME__,__FUNCTION__, __LINE__);
			//fflush(flog);
			wparam_free(&MonitorStrThreadMsg);
		}
	}	
}
char *tmpStr = NULL;
void CALLBACK face_tell_timer_proc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)//人脸识别线程心跳检测
{

	int nMsgType = FACETELL_ALIVE_CHECK;	
	int ret = 0,len = 0;

	
	add_msg2_head(monitor_value);
	len = strlen(monitor_value.toStyledString().data());
	char *MonitorStrThreadMsg = (char *)malloc(len + 1);

	memset(MonitorStrThreadMsg, 0, len + 1);
	strcpy(MonitorStrThreadMsg, monitor_value.toStyledString().data());

#ifdef MONITOR_VLAUE_PRINT
	//fprintf(flog_monitor, "[%s] [%s] [%d] face_tell_timer_proc send alive check msg ======== %s\n", __TIME__,__FUNCTION__, __LINE__, MonitorStrThreadMsg);
	////fflush(flog);
#endif
#if 0
	if (tmpStr != NULL) {
		free(tmpStr);
		tmpStr = NULL;
	}
	
	tmpStr = (char *)malloc(strlen(monitor_value.toStyledString().data()));
#endif 
	if (lpFaceTellThreadId != 0) {
		ret = PostThreadMessage(lpFaceTellThreadId, nMsgType, (WPARAM)MonitorStrThreadMsg, NULL);
	//	ret = PostThreadMessage(lpFaceTellThreadId, nMsgType, (WPARAM)tmpStr, NULL);
		if (!postthreadmessage_check(ret)) {
			fprintf(flog_monitor, "[%s] [%s] [%d] PostThreadMessage failed\n", __TIME__,__FUNCTION__, __LINE__);
			//fflush(flog);
			wparam_free(&MonitorStrThreadMsg);
		}
		else {
			//fprintf(flog_monitor, "[%s] [%s] [%d] tmpStr ======== %x\n", __TIME__,__FUNCTION__, __LINE__, tmpStr);
			////fflush(flog);
		}
	}

/////////////////java alive check
	nMsgType = JAVA_ALIVE_CHECK;
	ret = 0; len = 0;
	add_msg2_head(monitor_value);
	len = strlen(monitor_value.toStyledString().data());
	char *java_check_str = (char *)malloc(len + 1);
	memset(java_check_str, 0, len + 1);
	strcpy(java_check_str, monitor_value.toStyledString().data());
	if (lpJavaThreadId != 0) {
		ret = PostThreadMessage(lpJavaThreadId, nMsgType, (WPARAM)java_check_str, NULL);
		//	ret = PostThreadMessage(lpFaceTellThreadId, nMsgType, (WPARAM)tmpStr, NULL);
		if (!postthreadmessage_check(ret)) {
			fprintf(flog, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
			//fflush(flog);
			wparam_free(&java_check_str);
		}
		else {
			//fprintf(flog, "[%s] [%d] tmpStr ======== %x\n", __FUNCTION__, __LINE__, tmpStr);
			////fflush(flog);
		}
	}
/////////////////client alive check
	nMsgType = CLIENT_ALIVE_CHECK;
	ret = 0; len = 0;
	add_msg2_head(monitor_value);
	len = strlen(monitor_value.toStyledString().data());
	char *client_check_str = (char *)malloc(len + 1);
	memset(client_check_str, 0, len + 1);
	strcpy(client_check_str, monitor_value.toStyledString().data());
	if (lpClientThreadId != 0) {
		ret = PostThreadMessage(lpClientThreadId, nMsgType, (WPARAM)client_check_str, NULL);		
		if (!postthreadmessage_check(ret)) {
			fprintf(flog, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
			//fflush(flog);
			wparam_free(&client_check_str);
		}
		else {
			//fprintf(flog, "[%s] [%d] tmpStr ======== %x\n", __FUNCTION__, __LINE__, tmpStr);
			////fflush(flog);
		}
	}
}
void CALLBACK track_timer_proc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)//跟踪线程心跳检测
{

	int nMsgType = TRACK_ALIVE_CHECK;		
	int ret = 0,len = 0;

	//
	//
	g_system_date = get_system_date();
	add_msg2_head(track_value);
	len = strlen(track_value.toStyledString().data());
	char *MonitorStrThreadMsg = (char *)malloc(len + 1);
	memset(MonitorStrThreadMsg, 0, len + 1);
	strcpy(MonitorStrThreadMsg, track_value.toStyledString().data());

#ifdef MONITOR_VLAUE_PRINT
	//fprintf(flog_monitor, "[%s] [%s] [%d] track_timer_proc send alive check msg ======== %s\n", __TIME__,__FUNCTION__, __LINE__, MonitorStrThreadMsg);
	////fflush(flog);
#endif
	if (lpTrackThreadId != 0) {
		ret = PostThreadMessage(lpTrackThreadId, nMsgType, (WPARAM)MonitorStrThreadMsg, NULL);
		if (!postthreadmessage_check(ret)) {
			fprintf(flog_monitor, "[%s] [%s] [%d] PostThreadMessage failed\n", __TIME__,__FUNCTION__, __LINE__);
			//fflush(flog);
			wparam_free(&MonitorStrThreadMsg);
		}
	}
}
void CALLBACK camera_status_timer_proc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)//相机状态检测
{
	int nMsgType = CAMERA_STATUS_CHECK;
	int ret = 0,len = 0;

	
	add_msg2_head(camera_status_query);
	len = strlen(camera_status_query.toStyledString().data());
	char *MonitorStrThreadMsg = (char *)malloc(len + 1);
	memset(MonitorStrThreadMsg, 0, len + 1);
	strcpy(MonitorStrThreadMsg, camera_status_query.toStyledString().data());
#ifdef MONITOR_VLAUE_PRINT
	//fprintf(flog_monitor, "[%s] [%s] [%d] camera_status_timer_proc send query msg to rtsp ======== %s\n", __TIME__,__FUNCTION__, __LINE__, MonitorStrThreadMsg);
	////fflush(flog);
#endif
#ifdef CAMERA_STATUS_REQ
	if (lpRtspThreadId != 0) {
		ret = PostThreadMessage(lpRtspThreadId, nMsgType, (WPARAM)MonitorStrThreadMsg, NULL);
		if (!postthreadmessage_check(ret)) {
			fprintf(flog_monitor, "[%s] [%s] [%d] PostThreadMessage failed\n", __TIME__,__FUNCTION__, __LINE__);
			//fflush(flog);
			wparam_free(&MonitorStrThreadMsg);
		}
	}
#endif
}
DWORD  WINAPI monitor_worker(void * context)
{
	point_empty_check(context);
	fprintf(flog_monitor, "[%s] [%s] [%d] monitor begin to run\n", __TIME__,__FUNCTION__, __LINE__);
	//fflush(flog);

	MSG msg;
	DWORD begin = 0, end = 0;
	int ret = 0, nMsgType,malloc_len_pre = 0,track_len_pre = 0,broad_cast_pre = 0;
	Json::Reader reader;
//	Json::Value monitor_value,track_value;
	std::ifstream in;
	char *strThreadMsg = NULL,*str_track_thread_msg = NULL,*str_broadcast_thread_msg = NULL;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

	in.open("server_send_alive_check.json", std::ios::binary);
	json_open_check(&in);
	json_parse2_value(&in, &monitor_value);

	in.close();
	in.open("server_send_track_alive_check.json", std::ios::binary);
	if (!json_open_check(&in)) {
		fprintf(flog_monitor, "[%s] [%s] [%d] open file failed\n", __TIME__,__FUNCTION__, __LINE__);
		//fflush(flog);
	}
	json_parse2_value(&in, &track_value);

	//open camera status query
	in.close();
	in.open("server_send_camera_status_query.json", std::ios::binary);
	if (!json_open_check(&in)) {
		fprintf(flog_monitor, "[%s] [%s] [%d] open file failed\n", __TIME__,__FUNCTION__, __LINE__);
		//fflush(flog);
	}
	json_parse2_value(&in, &camera_status_query);

//	int len_value = strlen((char *)monitor_value.toStyledString().data());
	fprintf(flog_monitor, "[%s] [%s] [%d] monitor begin to run,start face_tell_timer\n", __TIME__,__FUNCTION__, __LINE__);
	//fflush(flog);

	
	Sleep(10000);//must not remove
	//face tell face_tell_timer
	UINT_PTR face_tell_timer = -1;
	face_tell_timer =  SetTimer(NULL, TIMER_ID_FACE_TELL, timeout_face_tell, (TIMERPROC)face_tell_timer_proc);
	if (face_tell_timer == 0) {
		//failed
	}

	//track track_timer
	UINT_PTR track_timer = -1;
	track_timer = SetTimer(NULL, TIMER_ID_TRACK, timeout_track, (TIMERPROC)track_timer_proc);
	if (track_timer == 0) {
		//failed
	}

	//face tell face_tell_timer
	UINT_PTR broadcast_timer = -1;
	broadcast_timer = SetTimer(NULL, TIMER_ID_BROADCAST, timeout_broadcast, (TIMERPROC)broadcast_timer_proc);
	if (broadcast_timer == 0) {
		//failed
	}

//	camera status query cmd to rtsp
	UINT_PTR camera_status_query_timer = -1;
	camera_status_query_timer = SetTimer(NULL, CAMERA_STATUS_QUERY_BROADCAST, timeout_camera_status_timeout, (TIMERPROC)camera_status_timer_proc);
	if (camera_status_query_timer == 0) {
		//failed
	}

	UINT_PTR server_status_timer = -1;
	server_status_timer = SetTimer(NULL, TIMER_ID_SERVER_STATUS, timeout_server_status_timeout, (TIMERPROC)server_status_timer_proc);
	if (server_status_timer == 0) {
		//failed
	}
	
	//face dt alive check
	UINT_PTR facedt_timer = -1;
	facedt_timer = SetTimer(NULL, TIMER_ID_FACEDT, timeout_facedt_timeout, (TIMERPROC)facedt_timer_proc);
	if (facedt_timer == 0) {
		//failed
	}
	while (true) {
	while (true)
	{
		
		if (PeekMessage(&msg, 0, 0, 0, NULL))
		{
			memset(&msg, 0, sizeof(msg));
			ret = GetMessage(&msg, NULL, 0, 0);
			if (ret == -1) {
				fprintf(flog_monitor, "[%s] [%s] [%d]  GetMessage failed error ==== %d \n", __TIME__,__FUNCTION__, __LINE__, GetLastError());				
				continue;
			}

			char * pInfo = (char *)msg.wParam;
			char *lParam = (char *)msg.lParam;


			switch (msg.message)
			{
			case WM_TIMER:
				DispatchMessage(&msg);
				break;
			case FACETELL_RETURN_IAM_ALIVE:				

				fprintf(flog_monitor,"[%s] [%s] [%d] face tell still alive \n",__TIME__, __FUNCTION__, __LINE__);
			//	fprintf(flog, "[%s] [%d] face tell still alive \n", __FUNCTION__, __LINE__);								
				break;
			case TRACK_RETURN_IAM_ALIVE:				
				fprintf(flog_monitor,"[%s] [%s] [%d] track still alive \n", __TIME__, __FUNCTION__, __LINE__);
			//	fprintf(flog, "[%s] [%d] track still alive \n", __FUNCTION__, __LINE__);				
				break;
			case BROADCAST_RETURN_IAM_ALIVE:				
				fprintf(flog_monitor,"[%s] [%s] [%d] broadcast still alive \n",__TIME__, __FUNCTION__, __LINE__);
			//	fprintf(flog, "[%s] [%d] broadcast still alive \n", __FUNCTION__, __LINE__);				

				break;
			case FACEDT_RETURN_IAM_ALIVE:				
				fprintf(flog_monitor,"[%s] [%s] [%d] facedt still alive \n", __TIME__,__FUNCTION__, __LINE__);
			//	fprintf(flog, "[%s] [%d] facedt still alive \n", __FUNCTION__, __LINE__);				
				break;
			case JAVA_RETURN_IAM_ALIVE:
				fprintf(flog_monitor,"[%s] [%s] [%d] java still alive \n", __TIME__, __FUNCTION__, __LINE__);
				break;
			case CLIENT_RETURN_IAM_ALIVE:
				fprintf(flog_monitor,"[%s] [%s] [%d] client still alive \n", __TIME__, __FUNCTION__, __LINE__);
				break;
			default:
				fprintf(flog_monitor, "[%s] [%d] unkown ms type\n", __FUNCTION__, __LINE__);
				break;
			}

			switch (msg.message)
			{
			case FACETELL_RETURN_IAM_ALIVE:								
			case TRACK_RETURN_IAM_ALIVE:								
			case BROADCAST_RETURN_IAM_ALIVE:
			case FACEDT_RETURN_IAM_ALIVE:
			case JAVA_RETURN_IAM_ALIVE:
			case CLIENT_RETURN_IAM_ALIVE:
				wparam_free(&pInfo);
				break;
			default:
				break;
			}
			fflush(flog);
		}		
		}
	}
//	MessageBox(NULL, (LPCTSTR)"monitor_worker exit ", (LPCTSTR)"title", MB_OK);
	KillTimer(NULL,face_tell_timer);
	KillTimer(NULL, track_timer);
	KillTimer(NULL, broadcast_timer);
	return 0;
}
