#include "stdafx.h"
#include "common.h"
#include<winsock2.h>
#include <IPHlpApi.h>
#include <time.h>
#include <sys/timeb.h>
#pragma comment(lib, "ws2_32.lib")

#pragma comment(lib, "IPHlpApi.lib")

const char* StringToConstCharX(string str)
{
	char* c;
	const int len = (const int)(str.length());
	c = new char[len + 1];
	strcpy(c, str.c_str());
	return c;

}

string Gb2312ToUtf_8(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr)
	{
		delete[] wstr;
		wstr = NULL;
	}
	string resStr = "";
	resStr = str;
	if (str)
	{
		delete[] str;
		str = NULL;
	}
	return resStr;
}
Json::Value TransUnicodeStringtoUTF8(Json::Value unicodeValue)
{
	string strSrc = unicodeValue.asCString();
	return( Json::Value(strSrc.c_str()));

}
string Gb2312ToUtf_8_EX(string gb2312)
{
	const char* utf_81 = StringToConstCharX(gb2312);
	string strValue = Gb2312ToUtf_8(utf_81);
	if (utf_81) delete[] utf_81;
	return strValue;
}

HANDLE m_facetell_mutex;
HANDLE g_client_msg_map_mutex;
HANDLE g_client_request_mutex;
HANDLE g_alarminfoset_mutex;
HANDLE g_picsearch_muxtex;
LPCTSTR facetell_mutex_name = (LPCTSTR)"facetell_mutex_name";
LPCTSTR clientmap_mutex_name = (LPCTSTR)"clientmap_mutex_name";
LPCTSTR client_request_mutex_name = (LPCTSTR)"client_request_mutex_name";
LPCTSTR face_tell_alarminfoset_mutex_name = (LPCTSTR)"face_tell_alarminfoset_mutex_name";
LPCTSTR pic_search_data_mutex_name = (LPCTSTR)"pic_search_data_mutex_name";
bool face_tell_connect_builded = false;
Json::Value g_cameralist;
Json::Value g_clusterlist;
Json::Value g_cluster_start_items;
bool getServerIP(void *pServerIP)//16
{
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		return false;
	}
	else
	{
		char hostname[256];
		ret = gethostname(hostname, sizeof(hostname));
		if (ret == SOCKET_ERROR)
		{
			return false;
		}
		else
		{
			HOSTENT* host = gethostbyname(hostname);
			if (host == NULL)
			{
				return false;
			}
			else
			{

				strcpy((char*)pServerIP, inet_ntoa(*(in_addr*)host->h_addr));
				return true;
			}
		}
	}
}
char*G2U(const char* gb2312)
{
int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
wchar_t* wstr = new wchar_t[len+1];
memset(wstr, 0, len+1);
MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
char* str = new char[len+1];
memset(str, 0, len+1);
WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
if(wstr) delete[] wstr;
return str;
}
string getTimeStamp()
{
	string result;
	//SYSTEMTIME sys;
	//
	//GetLocalTime(&sys);
	//result = to_string(sys.wYear) + to_string(sys.wMonth) + to_string(sys.wDay) + to_string(sys.wHour) + to_string(sys.wMinute) + to_string(sys.wSecond * 1000 + sys.wMilliseconds);

	long long time_last;
	time_last = time(NULL);
	struct timeb t1;
	ftime(&t1);
	time_last = t1.time * 1000 + t1.millitm;
	result = to_string(time_last);
	//	fprintf(flog, "[%s] [%s] [%d] result timestamp  ===== %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)result.c_str());
	return result;
}

extern char strJavaIP[IP_LEN_MAX] = { "192.168.1.105" };
extern char strServerIP[IP_LEN_MAX] = { 0 };
char strRtspIP[IP_LEN_MAX] = { 0 };
char strFaceDtIP[IP_LEN_MAX] = { 0 };
char strTrackInitIP[IP_LEN_MAX] = { 0 };
char strFaceTellIP[IP_LEN_MAX] = { 0 };
char strFaceTrackIP[IP_LEN_MAX] = { 0 };
char strShapeIP[IP_LEN_MAX] = { 0 };
extern char strJavaRequestAddr[100] = { 0 };
char strNewClientVer[PC_CLIENT_VER_LEN] = { "v1.0.1" };
char strnewClientUrl[NEW_CLIENT_URL_LEN] = { 0 };
char strUserName[USER_NAME_LEN] = { "admin" };
char strPwd[USER_PWD_LEN] = { "admin" };
char strListen[LISTEN_ADDR_LEN] = { 0 };
char strJavaListen[LISTEN_ADDR_LEN] = { 0 };
char strJavaInitListen[LISTEN_ADDR_LEN] = { 0 };
char strBroadCastAddr[60] = { 0 };
char strJsonNum[24] = { 0 };

FILE *flog = NULL;

FILE *flog_client = NULL;
FILE *flog_java = NULL;
FILE *flog_facedt = NULL;
FILE *flog_facetell = NULL;
FILE *flog_main = NULL;
FILE *flog_monitor = NULL;
FILE *flog_search = NULL;
FILE *flog_media = NULL;
FILE *flog_shape = NULL;
FILE *flog_facesearch = NULL;
FILE *flog_change_camera = NULL;
FILE *flog_client_tree = NULL;
FILE *flog_pic_in = NULL;
FILE *flog_track = NULL;
FILE *flog_track_init = NULL;
FILE *flog_one_vs_one = NULL;

extern FILE * debugfile = NULL;
int nClientPort = 6001;
int nFaceDetectPort = 5556;
int nTrackInitPort = 5004;
long long nAlarmPad = 9000;
int nFaceDetectBroadCast = 5557;
int nListenJavaTimeout = 100;
int nBroadCastPort = 5559;

void *frontend = NULL;
void *broadcast_sk = NULL;
void *java_sk = NULL;
void *java_sk_dealer = NULL;
void *face_dt_sk = NULL;
void *face_tl_sk = NULL;
void *rtsp_sk = NULL;
void *track_sk = NULL;
void *shape_sk = NULL;
void *search_sk = NULL;
void *pic_data_update_sk = NULL;

int zmq_poll_timeout = 5;
int monitor_time = 2000;

char *g_common_str_java = NULL;
char *g_common_str_facedt = NULL;
char *g_common_str_facetell = NULL;
char *g_common_str_search = NULL;
char *g_common_str_shape = NULL;
char *g_common_str_track = NULL;
char *g_common_str_rtsp = NULL;
char *g_common_str_client = NULL;

FrontendMsg::FrontendMsg(void *ctx, void *w)
{
	if (ctx == NULL || w == NULL) {
		printf("point is NULL\n");
		getchar();
		return;
	}
	context = ctx;
	worker = w;
	memset(identity, 0, IDENTITY_STR_LEN);
	nPicNumber = 0;
	nPicCount = 0;
}
FrontendMsg::~FrontendMsg()
{

}
char *FrontendMsg::get_identity()
{
	return identity;
}
bool FrontendMsg::set_identity(char *id)
{
	if (id == NULL) {
		printf("[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "get identity failed");
		fprintf(flog,"[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "get identity failed");
		//fflush(flog);
		getchar();
		return false;
	}
	int len = strlen(id);
	if (len < IDENTITY_STR_LEN) {
		strcpy(identity, id);
	}
	else {
		printf("[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "identity str is length out");
		fprintf(flog,"[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "identity str is length out");
		getchar();
		return false;
	}
	return true;
}
bool FrontendMsg::set_pic_num(int n)
{
	if (n <= 0) {
		return false;
	}
	nPicNumber = n;
	nPicCount = 0;//图片计数器清0
	return true;
}
int FrontendMsg::add_back_pic_num()
{
	nPicCount++;
	return nPicCount;
}
int FrontendMsg::get_pic_num()
{
	return nPicNumber;
}
bool FrontendMsg::backpiclist_append(Json::Value *val)
{
	point_empty_check(val);
	backPicList.append((*val));

//	printf("[%s] [%d] backPicList == %s \n", __FUNCTION__, __LINE__, (char *)backPicList.toStyledString().data());

	return true;
}
bool FrontendMsg::get_backpiclist(Json::Value *val)
{
	point_empty_check(val);
	(*val) = backPicList;
	return true;
}
//hsj
bool  FrontendMsg::delete_backpiclist()
{
	backPicList.clear();
	nPicCount = 0;
	nPicNumber = 0;
	return true;
}
bool FrontendMsg::RecvFrontendMsg(zmq_msg_t *msg_recv)
{
	zmq_msg_init(msg_recv);
	int len = zmq_msg_recv(msg_recv, worker, 0);
	if (len == -1) {
		printf("receive front msg identity failed\n");
		getchar();
		return false;
	}
	memset(identity, 0, IDENTITY_STR_LEN);
	strncpy(identity, (char *)zmq_msg_data(msg_recv), len);
#ifdef COMMON_VALUE_PRINT
	printf("ident ========== %s len ==== %d \n", identity, len);
#endif

	char result[100];
	memset(result, 0, 100);
	len = zmq_msg_recv(msg_recv, worker, 0);
	if (len == -1) {
#ifdef COMMON_STEP_PRINT
		printf("[%s] [%d] recv msg failed %s\n", __FUNCTION__, __LINE__);
		
#endif
		return false;
		
	}
	else
	{
		strncpy(result, (char *)zmq_msg_data(msg_recv), len);
	}
#ifdef COMMON_VALUE_PRINT
	printf("empty ========== %s\n\n", result);
#endif

//	zmq_msg_init(msg_recv);
	len = zmq_msg_recv(msg_recv, worker, 0);
	if (len == -1) {
#ifdef COMMON_STEP_PRINT
		printf("[%s] [%d] recv msg failed\n", __FUNCTION__, __LINE__);
#endif
		return false;
	}
#ifdef COMMON_VALUE_PRINT
	printf("content ========== %s\n\n", (char *)zmq_msg_data(msg_recv));
#endif
	return true;
}
bool FrontendMsg::SendOuterMsg(char *val)
{
	if (val == NULL) {
		return false;
	}
	else {
#ifdef COMMON_VALUE_PRINT
		printf("[%s] [%d] %s ===== %d\n", __FUNCTION__, __LINE__, "SendOuterMsg", val);
#endif
	}
	int len = strlen(identity);
	if (len <= 0)
	{
#ifdef COMMON_STEP_PRINT
		printf("[%s] [%d] identity is empty ==== \n", __FUNCTION__, __LINE__);
#endif
		return false;
	}
	//	strcpy(identity, "1234-5678");
	char empty[] = { "" };
#ifdef COMMON_VALUE_PRINT
	printf("send identity ============ %s\n", identity);
#endif
//	zmq_send(worker, identity, strlen(identity), ZMQ_SNDMORE);
	s_sendmore(worker, identity);
	//zmq_send(worker, "", 0, ZMQ_SNDMORE);
	s_sendmore(worker, empty);
#ifdef COMMON_VALUE_PRINT
		printf("[%s] [%d] val === %s\n", __FUNCTION__, __LINE__, val);
#endif
//	zmq_send(worker, val, strlen(val), 0);		

	s_send(worker, val);
	
}
DealerModeSendRecv::DealerModeSendRecv(void *ctx, void * sock)
{
	context = ctx;
	socket = sock;
}
DealerModeSendRecv::~DealerModeSendRecv()
{}
bool DealerModeSendRecv::SendDealerMsg(char *val)
{
	if (val == NULL) {
		return false;
	}
	int len = 0;
	//len = zmq_send(socket, "", 0, ZMQ_SNDMORE);
	//zmq_send_check(len);
	//len = zmq_send(socket, val, strlen(val) + 1, 0);
	//zmq_send_check(len);
	zmq_msg_t msg;
	zmq_msg_init_size(&msg, 0);
	memcpy(zmq_msg_data(&msg), "", 0);
	len = zmq_msg_send(&msg, socket, ZMQ_SNDMORE);
	
	zmq_msg_init_size(&msg, strlen(val));
	memcpy(zmq_msg_data(&msg), val, strlen(val));
	len = zmq_msg_send(&msg, socket, 0);
	zmq_msg_close(&msg);
	if (len) {
		return true;
	}
	else {
		return false;
	}

}

bool SetMsgHead(Json::Value *dst, Json::Value *src, int msgType, int msgCode)//注意dst 为最外层
{
	if (dst == NULL) {
		printf("point is NULL");
		getchar();
		return false;
	}
	SYSTEMTIME time;
	Json::Value msgHead;
	Json::Value reValue;
	//getTimeStamp(&time);
	
	//(*src)["msgHead"]["timestamp"].toStyledString().data();
	if (src != NULL) {
		if (!(*src)["msgHead"]["timestamp"].isNull()) {
//			fprintf(flog, "[%s] [%d] src timestamp  ===== %s\n", __FUNCTION__, __LINE__, (char *)(*src)["msgHead"]["timestamp"].toStyledString().data());
		}

		msgHead["requestID"] = (*src)["msgHead"]["requestID"];
		msgHead["boundID"] = (*src)["msgHead"]["boundID"];
		msgHead["serverIP"] = strServerIP;
		msgHead["authorization"] = (*src)["msgHead"]["authorization"];
		msgHead["timestamp"] = (*src)["msgHead"]["timestamp"]; //time;
#ifdef DEBUG
		if (!(*src)["msgHead"]["clientIP"].isNull()) {
		//	printf("[%s] [%d] src ip ===== %s\n", __FUNCTION__, __LINE__, (*src)["msgHead"]["clientIP"].toStyledString().data());
		}
#endif // DEBUG
		if (!(*src)["msgHead"]["clientIP"].isNull()) {
			msgHead["clientIP"] = (*src)["msgHead"]["clientIP"];
		}
	}
	else {
		msgHead["requestID"] = 0;
		msgHead["boundID"] = rand();
		msgHead["serverIP"] = strServerIP;
		msgHead["authorization"] = 0;
		msgHead["timestamp"] = getTimeStamp();
		if (!msgHead["timestamp"].isNull()) {
		//	fprintf(flog, "[%s] [%d] src timestamp  ===== %s\n", __FUNCTION__, __LINE__, (char *)msgHead["timestamp"].toStyledString().data());
		}
	}

	msgHead["msgType"] = msgType;// (*src)["msgHead"]["msgType"];
	msgHead["msgCode"] = msgCode;// (*src)["msgHead"]["msgCode"];
	reValue["msgHead"] = msgHead;
	(*dst) = reValue;
	if (!(*dst)["msgHead"]["timestamp"].isNull()) {
//		fprintf(flog, "[%s] [%d] new  getTimeStamp  ===== %s\n", __FUNCTION__, __LINE__, (char *)(*dst)["msgHead"]["timestamp"].toStyledString().data());
	}
	//fflush(flog);
	return true;
}
set<stAlarmInfo> AlarmInfoSet;

DWORD lpClientThreadId = 0;
DWORD lpJavaThreadId = 0;

DWORD lpFaceTellThreadId = 0;
DWORD lpRtspThreadId = 0;
DWORD lpTrackThreadId = 0;
DWORD lpFaceDtThreadId = 0;
DWORD lpShapeThreadId = 0;
DWORD lpPicSearchThreadId = 0;
DWORD lpBroadCastThreadId = 0;
DWORD lpMonitorThreadId = 0;

char * Json2Char(Json::Value *src)
{
	if (src == NULL) {
		return NULL;
	}
	char *str = NULL;
	int len = strlen((*src).toStyledString().data());
	str = (char *)malloc(len + 1);
	memset(str, 0, len + 1);
	memcpy(str, (char *)(*src).toStyledString().data(), len);
	if (str != NULL) {
		return str;
	}
	else {
		return NULL;
	}
}
//bool SetReqMsgHead(Json::Value *dst, int msgCode,char *remoteIP,int nMsgType)
bool SetReqMsgHead(Json::Value *dst, int msgCode)
{
	if (dst == NULL) {
		return false;
	}
//	time_t time;
	Json::Value Ret;
	Json::Value msgHead;
//	getTimeStamp(&time);
	msgHead["requestID"] = "";
	msgHead["boundID"] = "";
	msgHead["authorization"] = "";
	msgHead["timestamp"] = getTimeStamp();
	msgHead["clientIP"] = strJavaIP;
	msgHead["serverIP"] = strServerIP;
	msgHead["msgType"] = JSONMSGTYPE_REQUEST;
	msgHead["msgCode"] = msgCode;
	Ret["msgHead"] = msgHead;
	(*dst) = Ret;
	return true;
}
void debug_print(char *str)
{
	if (str != NULL)
		printf("[%s] [%d] recv msg ==== %s\n", __FUNCTION__, __LINE__, (char *)str);
}
int zmq_send_check(int len)
{
	if (len < 0) {
		printf("zmq send msg failed");
		getchar();
#ifdef  COMMON_STEP_PRINT
		printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, (char *)"zmq send msg failed");
#endif //  COMMON_STEP_PRINT
		getchar();
		return - 1;
	}
}
void json_parse_fail()
{
	//SL_LOG("json parse file failed");
	//fprintf(flog,"[%s] [%d] %s\n", __FUNCTION__, __LINE__, (char *)"json parse file failed");
	////fflush(flog);
#ifdef  COMMON_STEP_PRINT
	printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, (char *)"json parse file failed");
#endif //  COMMON_STEP_PRINT
	getchar();
}
bool point_empty_check(void *p)
{
	if (p == NULL) {
		printf("point is empty");
		getchar();
#ifdef  COMMON_STEP_PRINT
		printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, (char *)"point is empty");
#endif 		
		return false;
	}
	return true;
}
bool postthreadmessage_check(int ret)
{
	if (ret == 0) {
		printf("postthreadmessage failed");
		
		printf("[%s] [%d] GetLastError == %d\n", __FUNCTION__, __LINE__, GetLastError());
		fprintf(flog,"[%s] [%d] GetLastError == %d\n", __FUNCTION__, __LINE__, GetLastError());
		getchar();
		//fflush(flog);
		return false;
	}
	return true;
}
bool postthreadmessage_mem_malloc(char **p_str,Json::Value *p_value)//must not use if not necessery
{
	point_empty_check(p_str);
	point_empty_check(p_value);

	
	int len = strlen((char *)(*p_value).toStyledString().data());
	(*p_str) = (char *)malloc(len + 100);
	memset((*p_str), 0, len + 100);
	
//	strncpy((*p_str), (*p_value).toStyledString().data(), len);
	memcpy((*p_str), (*p_value).toStyledString().data(), len);
	return true;
}
bool json_open_check(ifstream *in)
{
	if (!(*in).is_open()) {		
		getchar();
		return false;
	}
	return true;
}
bool json_parse2_value(ifstream *in, Json::Value *p_val)
{
	Json::Reader reader;

	if (reader.parse((*in), (*p_val)))
	{
	//	printf("serip ==== %s \n", value["msgHead"]["serverIP"].toStyledString().data());
	}
	else
	{
		printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, "json file format error");
		fprintf(flog,"[%s] [%d] %s\n", __FUNCTION__, __LINE__, "json file format error");		
		return false;
	}
	return true;
}
void run_into_exception()
{
	//printf("[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
	//fprintf(flog,"[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
	////fflush(flog);
	getchar();
}
int get_json_number(char * num)
{
	int ret = 0;
	point_empty_check(num);
	memset(strJsonNum, 0, sizeof(strJsonNum));
	strcpy(strJsonNum, num);
	ret = atoi(strJsonNum);
	return ret;
}
void print_info2_file()
{
	
}
bool thread_create_check(HANDLE l)
{
	if (l == false) {
		fprintf(flog, "create java worker failed\n");
		//fflush(flog);
		return false;
	}
	return true;
}
//printf("[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");aa
bool GetStatisticOfSysNetworkFlow(DWORD &dwbitTotalRecv, DWORD &dwbitTotalSend)
{
	/*获取MIB-II接口表大小*/
	DWORD dwBufferLen = 0;
	GetIfTable(NULL, &dwBufferLen, 0);

	/*创建MIB-II接口表*/
	PMIB_IFTABLE pMibIfTable = (MIB_IFTABLE*)malloc(dwBufferLen);

	/*获取MIB-II接口表*/
	DWORD dwRet = GetIfTable(pMibIfTable, &dwBufferLen, 0);
	if (NO_ERROR != dwRet)
	{
	//	std::cout << "GetIfTable != NO_ERROR, ErrorCode=" << dwRet << std::endl;
		printf("[%s] [%d] GetIfTable != NO_ERROR, ErrorCode= %d\n", __FUNCTION__, __LINE__, dwRet);
		free(pMibIfTable);
		return false;
	}

	dwbitTotalRecv = dwbitTotalSend = 0;

	/*多网卡*/

	for (int i = 0; i != pMibIfTable->dwNumEntries; ++i)//端口数
	{
		//		if (pMibIfTable->table[i].dwType <= 23 && pMibIfTable->table[i].dwType != MIB_IF_TYPE_LOOPBACK)
		if (pMibIfTable->table[i].dwType <= 23)
			//		if(pMibIfTable->table[i].dwType == MIB_IF_TYPE_ETHERNET)
		{
			dwbitTotalRecv += pMibIfTable->table[i].dwInOctets;
			dwbitTotalSend += pMibIfTable->table[i].dwOutOctets;
		}
	}
	dwbitTotalRecv = dwbitTotalRecv / (1024 * 1024);
	dwbitTotalSend = dwbitTotalSend / (1024 * 1024);
	/*Byte转bit*/
	//dwbitTotalRecv *= 8;
	//dwbitTotalSend *= 8;
	//	cout << "dwbitTotalRecv = " << dwbitTotalRecv << "dwbitTotalSend == " << dwbitTotalSend << endl;
	free(pMibIfTable);
	return true;
}
bool GetSysNetworkFlowByMidTable(DWORD &dwbpsRecv, DWORD &dwbpsSend)
{
	DWORD dwTotalRecv1 = 0, dwTotalSend1 = 0;
	if (!GetStatisticOfSysNetworkFlow(dwTotalRecv1, dwTotalSend1))
	{
		printf("GetStatisticOfSysNetworkFlow == false\n");
		return false;
	}
	return true;
}
bool GetSysMemUseStatus(DWORD &total, DWORD & avail)
{
	int nMB = 1024 * 1024;
	PERFORMANCE_INFORMATION stPerformance = { 0 };
	int cb = sizeof(stPerformance);

	GetPerformanceInfo(&stPerformance, cb);
	int nPageSize = stPerformance.PageSize;
	INT64 i64PhyTotal = (INT64)stPerformance.PhysicalTotal * nPageSize / nMB;
	INT64 i64PhyAvail = (INT64)stPerformance.PhysicalAvailable * nPageSize / nMB;
	total = i64PhyTotal;
	avail = i64PhyAvail;
	return true;
}
Json::Value analyser_strategy_value;
void wparam_free(char **p)
{
	if (p != NULL) {
		free(*p);
		*p = NULL;
	}
}
bool add_msg2_head(Json::Value &value)
{
	int requestID = value["msgHead"]["requestID"].asInt();
	if (requestID == 0)
	{
		value["msgHead"]["requestID"] = rand();
	}
	return true;
}
bool json_write2_file(Json::Value & value, std::ofstream &file)//1 file open 2 open check 
{
	file << value.toStyledString() << endl;
	file.close();
	return true;
}
bool parse_queuemsg2_json(char * pInfo, Json::Reader &reader,Json::Value &value, MSG &msg, void *para)
{
	if (pInfo == NULL) {
		return false;
	}
	int alive_msg = 0;

	if (para != NULL) {
		alive_msg = *((int *)para);
	}
	
	if (msg.message > WM_USER && msg.message != alive_msg) {
		if (reader.parse(pInfo, value)) {
			return true;
		}
		else {			
			wparam_free(&pInfo);//self define msg pInfo
			return false;
		}
	}
	return true;
}
bool trans_msg2_another_thread(int nMsgType, Json::Value *val, DWORD ThreadId, char **msgStr, void *para)
{
	if (val == NULL || nMsgType <= 0 || ThreadId <= 0 || msgStr == NULL) {
		return false;
	}
	/*CUIIJIANHUA + 1v1 + CHANGE + ADD*/
	if (nMsgType == CLIENT_GET_FACE_CHECKIN)
	{
		(*val)["msgBody"]["dataPush"]["imgFirstURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["dataPush"]["imgFirstURL"].asString());
		(*val)["msgBody"]["dataPush"]["imgSecondURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["dataPush"]["imgSecondURL"].asString());	
    }
	else if (nMsgType == FACEDT_GET_FACE_CHECKIN)
	{
		//string ff = (*val)["msgBody"]["dataSend"]["img1"]["imgFirstURL"].asString();
		(*val)["msgBody"]["dataSend"]["img1"]["RoiURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["dataSend"]["img1"]["RoiURL"].asString());
		(*val)["msgBody"]["dataSend"]["img1"]["imgFirstURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["dataSend"]["img1"]["imgFirstURL"].asString());
		(*val)["msgBody"]["dataSend"]["img1"]["imgSrcURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["dataSend"]["img1"]["imgSrcURL"].asString());

		(*val)["msgBody"]["dataSend"]["img2"]["RoiURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["dataSend"]["img2"]["RoiURL"].asString());
		(*val)["msgBody"]["dataSend"]["img2"]["imgSecondURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["dataSend"]["img2"]["imgSecondURL"].asString());
		(*val)["msgBody"]["dataSend"]["img2"]["imgSrcURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["dataSend"]["img2"]["imgSrcURL"].asString());
	}

	else if (nMsgType == CLIENT_FACE_SEARCH)
	{
		string ff = (*val)["msgBody"]["data"]["imgURL"].asString();
		(*val)["msgBody"]["data"]["imgURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["data"]["imgURL"].asString());
	}
	
	else if (nMsgType == FACEDT_FACE_SEARCH_SUCCESS)
	{
		//string vvvv = (*val).toStyledString();	
		int nSize = (*val)["msgBody"]["data"]["FaceInfoArray"].size();
		for (int i = 0; i < nSize; i++)
		{
			//string dddd = (*val)["msgBody"]["data"]["FaceInfoArray"][i]["RoiURL"].asString();
			(*val)["msgBody"]["data"]["FaceInfoArray"][i]["RoiURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["data"]["FaceInfoArray"][i]["RoiURL"].asString());
		}
		//string dddd1 = (*val)["msgBody"]["data"]["imgURL"].asString();
		(*val)["msgBody"]["data"]["imgURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["data"]["imgURL"].asString());	
	}
	else if (nMsgType == CLIENT_USING_IMG_CHECKIN_IMG)
	{
		(*val)["msgBody"]["dataPush"]["imgURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["dataPush"]["imgURL"].asString());
	}
	else if(nMsgType==FACETELL_RETURN_FACE_SEARCH_RESULT)//1vsN返回消息
	{
		string str = (*val).toStyledString();
		for (int i=0;i<(*val)["msgBody"]["data"]["matchInfoArray"].size();i++)
		{
			if (!(*val)["msgBody"]["data"]["matchInfoArray"][i]["imgUrl"].isNull())
			{
				(*val)["msgBody"]["data"]["matchInfoArray"][i]["imgUrl"] = 
					Gb2312ToUtf_8_EX((*val)["msgBody"]["data"]["matchInfoArray"][i]["imgUrl"].asString());
			}
			if (!(*val)["msgBody"]["data"]["matchInfoArray"][i]["name"].isNull())
			{
				(*val)["msgBody"]["data"]["matchInfoArray"][i]["name"] =
					Gb2312ToUtf_8_EX((*val)["msgBody"]["data"]["matchInfoArray"][i]["name"].asString());
			}
		}
		
	}
	/*END*/
	int ret = 0;
	postthreadmessage_mem_malloc(msgStr, val);

	ret = PostThreadMessage(ThreadId, nMsgType, (WPARAM)(*msgStr), NULL);
	if (!postthreadmessage_check(ret)) {
		fprintf(flog, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
		//fflush(flog);
		wparam_free(msgStr);
		return false;
	}
	else {
#ifdef 	RTSP_VALUE_PRINT
		//fprintf(flog, "[%s] [%d]   rtsp send msg to java ========= %s\n", __FUNCTION__, __LINE__, (char *)g_common_str_tmp);
		////fflush(flog);
#endif
	}
	return true;
}
Json::Value g_cameraadd_attach_para;
map<int, struct facetell_para>g_cameraid_map2_facetell_para;
map <int, std::string > g_mapmsgclient;
bool g_client_alive = false;
int s_send(void *socket, char *string)
{
	zmq_msg_t msg;
	zmq_msg_init_size(&msg, strlen(string));
	memcpy(zmq_msg_data(&msg), string, strlen(string));
	int size = zmq_msg_send(&msg, socket, 0);
	zmq_msg_close(&msg);
	if (size) {
		return true;
	}
	else {
		return false;
	}
}
int s_sendmore(void *socket, char *string)
{
	zmq_msg_t msg;
	zmq_msg_init_size(&msg, strlen(string));
	memcpy(zmq_msg_data(&msg), string, strlen(string));
	int size = zmq_msg_send(&msg, socket, ZMQ_SNDMORE);
	zmq_msg_close(&msg);
	if (size) {
		return true;
	}
	else {
		return false;
	}
}
Json::Value g_change_camera_value;
MSG java_msg;
int g_face_search_index = 0;
string g_system_date;
string get_system_date()
{
	string result;
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	result = to_string(sys.wYear) + to_string(sys.wMonth) + to_string(sys.wDay);
	return result;
}
const char * get_system_misecond_time()
{
	string res;
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	res = to_string(sys.wYear) + to_string(sys.wMonth) + to_string(sys.wDay) + to_string(sys.wHour) + to_string(sys.wMinute) + \
		to_string(sys.wSecond) + to_string(sys.wMilliseconds);
	return res.c_str();
}
map<int, Json::Value>g_pic_search_data;
vector<string> g_ip_config_vec = {
	"data_update_ip",
	"facedt_ip",
	"facetell_ip",
	"java_ip",
	"nAlarmPad",
	"rtsp_ip",
	"search_ip",
	"shape_ip",
	"track_ip",
	"video_save_url"
};