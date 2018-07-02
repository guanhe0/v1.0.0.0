#pragma once
#ifndef __COMMON_DEFINE1__
#define __COMMON_DEFINE1__
#include "zmq.hpp"
//#include "zmq_utils.h"
#include "json\json.h"
#include <json\config.h>
#include "time.h"
//#include "SimpleLog.h"
#include "Conversation2Java.h"
#include "msgDefine.h"
#include "server_config.h"
#include "Psapi.h"
#include <string>
#include <set>
#include <fstream>
using namespace std;
#define PC_CLIENT_VER_LEN 40
#define USER_NAME_LEN 40
#define USER_PWD_LEN 40
#define SERVER_IP_LEN 16
#define PC_CLIENT_START 4000
#define PC_CLIENT_END	4999
#define FACEDETECTED_SART 30000
#define FACEDETECTED_END 30999
#define IP_LEN_MAX 16
#define JAVA_CONNECT_ADDR_LEN 50
#define VALUE2STR_LEN_MAX 9999
#define MSGID_LEN_MAX 64
#define CLIENT_REQUEST_TIMEOUT 5


#define BROADCAST_PROTO "tcp"
#define FACETELL_STILL_ALIVE "face tell still alive"
#define FACEDT_STILL_ALIVE "face dt still alive"
#define BROADCAST_STILL_ALIVE "broadcast still alive"
#define TRACK_STILL_ALIVE "track still alive"
#define PROTE_ADDR_LEN 40
#define NEW_CLIENT_URL_LEN 200
#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}
bool getServerIP(void *pServerIP);
string getTimeStamp();
extern char strJavaIP[IP_LEN_MAX];
extern char strNewClientVer[PC_CLIENT_VER_LEN];
extern char strnewClientUrl[NEW_CLIENT_URL_LEN];
extern char strUserName[USER_NAME_LEN];
extern char strPwd[USER_PWD_LEN];

extern int nClientPort;
extern int nFaceDetectPort;
extern int nTrackInitPort;
extern char strServerIP[IP_LEN_MAX];
extern char strRtspIP[IP_LEN_MAX];
extern char strFaceDtIP[IP_LEN_MAX];
extern char strTrackInitIP[IP_LEN_MAX];
extern char strFaceTellIP[IP_LEN_MAX];
extern char strFaceTrackIP[IP_LEN_MAX];
extern char strShapeIP[IP_LEN_MAX];
extern char strBroadCastAddr[60];
extern FILE * debugfile;
extern long long nAlarmPad;
extern int nFaceDetectBroadCast;
extern char strJavaRequestAddr[100];
extern char strListen[LISTEN_ADDR_LEN];
extern char strJavaListen[LISTEN_ADDR_LEN];
extern char strJavaInitListen[LISTEN_ADDR_LEN];

extern int nListenJavaTimeout;
extern int nBroadCastPort;
extern char strJsonNum[24];
extern FILE *flog;
extern FILE *flog_client;
extern FILE *flog_java;
extern FILE *flog_facedt;
extern FILE *flog_facetell;
extern FILE *flog_main;
extern FILE *flog_monitor;
extern FILE *flog_search;
extern FILE *flog_media;
extern FILE *flog_shape;
extern FILE *flog_facesearch;
extern FILE *flog_change_camera;
extern FILE *flog_client_tree;
extern FILE *flog_pic_in;
extern FILE *flog_track;
extern FILE *flog_track_init;
extern FILE *flog_one_vs_one;
extern Json::Value picture_list;
extern long long face_tell_num;
extern long long face_dt_num;
extern int g_facedt_faceminisize;
extern float g_facedt_faceminquality;
#define CLIENT_VALUE_PRINT
#define PC_REQUEST_CONTROLL
#define CLIENT_LINK_TEST
#if 0
#define STEP_PRINT



#define CLIENT_VALUE_PRINT
#define TELL_VAUE_PRINT
//#define CLIENT_MULTI_CLIENT_LOGIN

#define TELL_STEP_PRINT
//#define FD_STEP_PRINT
//#define FD_VALUE_PRINT
//#define SEARCH_VALUE_PRINT
//#define COMMON_VALUE_PRINT
//#define JAVA_STEP_PRINT

//#define MAIN_STEP_PRINT
#define MAIN_LOG_PRINT

#define SHAPE_STEP_PRINT
#define SHAPE_VALUE_PRINT
//#define MONITOR_VLAUE_PRINT
#define SHAPE_DEBUG
#define POST_THREAD_MESSAGE_OPEN
//#define RTSP_STEP_PRINT
#define RTSP_VALUE_PRINT
#define BROADCAST_VALUE_PRINT
#define TRACK_VALUE_PRINT
//#define FACETELL_RATE
#define RTSP_STEP_PRINT
//#define GET_CAMERA_STATUS_FROM_JSON_FILE
//#define FACE_DT2_RTSP
#define PC_REQUEST_CONTROLL
#endif
#define ALARM_INFO_PRINT
#define ALARM_BROADCAST_PRINT
/////////////////////////////////////////////////
#define FD_STEP_PRINT
#define SEARCH_PIC_WITH_PIC
#define GET_IP_FROM_JAVA
#define DEBUG 
#define LINK_DEBUG
#define EMPTY_MSG_DEBUG
#define JAVA_VALUE_PRINT
#define FD_VALUE_PRINT
#define CAMERA_STATUS_REQ
#define SEARCH_VALUE_PRINT
#define FACE_SEARCH_PRINT
#define PIC_WITH_PIC_PRINT
//#define PICS_IN_LIB_PRINT
#define PERSON_TRACK_PRINT
#define CLIENT_ONE_VS_ONE
extern class FrontendMsg//router 模式收发数据
{
public:
	FrontendMsg(void *ctx, void *w);
	~FrontendMsg();
	bool RecvFrontendMsg(zmq_msg_t * msg_recv);//½ÓÊÕÒ»¸ö¿ÕÏûÏ¢Ìå£¬Í¨¹ý³ÉÔ±º¯ÊýÌî³ä
	bool SendOuterMsg(char *val);
	char *get_identity();
	bool set_identity(char *id);
	bool set_pic_num(int n);
	int get_pic_num();
	int add_back_pic_num();
	bool backpiclist_append(Json::Value *val);
	bool get_backpiclist(Json::Value *val);
	bool delete_backpiclist();	
	
private:
	void *context;
	void *worker;
	zmq_msg_t msg_recv;
	//	zmq_msg_t msg_send;
	char identity[IDENTITY_STR_LEN];
	int nPicNumber;//文件夹图片入库图片数量
	int nPicCount;//图片计数器
	Json::Value backPicList;
};
 class DealerModeSendRecv//router 收发数据
{
public:
	DealerModeSendRecv(void *ctx, void * sock);
	~DealerModeSendRecv();

	bool SendDealerMsg(char *val);
private:
	void *context;
	void *socket;
	zmq_msg_t msg_recv;
	zmq_msg_t msg_send;
	char identity[IDENTITY_STR_LEN];
};
extern struct stAlarmInfo
{
	//	string strPersonName;
	unsigned int unMsgID;
	unsigned int unpersonID;
	long long unFirstTime;
	unsigned int unCamID;
	long long unWarnTime;
	//	unsigned int nWarnDegree;
	//	float similarity;
	unsigned short usoptState;
	string strOptStaff;
	//	float belief;
	bool operator <	(const stAlarmInfo & a) const
	{
		return a.unpersonID < unpersonID;
	}
};
bool SetMsgHead(Json::Value *dst, Json::Value *src, int msgType, int msgCode);

extern set<stAlarmInfo> AlarmInfoSet;

extern DWORD lpClientThreadId;
extern DWORD lpJavaThreadId;

extern DWORD lpFaceTellThreadId;
extern DWORD lpRtspThreadId;
extern DWORD lpTrackThreadId;
extern DWORD lpShapeThreadId;
extern DWORD lpPicSearchThreadId;
extern DWORD lpFaceDtThreadId;
extern DWORD lpBroadCastThreadId;
extern DWORD lpMonitorThreadId;
extern void *frontend;
extern void *broadcast_sk;
extern void *java_sk;
extern void *java_sk_dealer;
extern void *face_dt_sk;
extern void *face_tl_sk;
extern void *rtsp_sk;
extern void *track_sk;
extern void *shape_sk;
extern void *search_sk;
extern void *pic_data_update_sk;
extern int zmq_poll_timeout;
extern int monitor_time;
extern HANDLE m_facetell_mutex;
extern HANDLE g_client_msg_map_mutex;
extern HANDLE g_client_request_mutex;
extern HANDLE g_alarminfoset_mutex;
extern HANDLE g_picsearch_muxtex;
char * Json2Char(Json::Value *src);
bool SetReqMsgHead(Json::Value *dst, int msgCode);
extern struct java_identity_s
{
	void *context;
	char identity[IDENTIFY_BUFFER_SIZE];
};
extern struct time_event_s {
	FrontendMsg *m;
	Json::Value *val;

};
extern struct facetell_para {
//	int facelibid;
	std::vector<int> facelibid;
	float minalarmthreshold;
	int	facceoutnumber;
};
#endif
//printf("[%s] [%d] recv msg ==== %s\n",__FUNCTION__,__LINE__, (char *)zmq_msg_data(&msg_recv));
void debug_print(char *str);
//bool charArray2intArray(const char * src, int *dst);
int zmq_send_check(int len);
void json_parse_fail();
bool point_empty_check(void *p);
bool postthreadmessage_check(int ret);
bool postthreadmessage_mem_malloc(char **p_str, Json::Value *p_value);
bool json_open_check(ifstream *in);
bool json_parse2_value(ifstream *in, Json::Value *p_val);

void run_into_exception();
int get_json_number(char * num);
void print_info2_file();
bool thread_create_check(HANDLE l);
extern HANDLE m_facetell_mutex;
extern bool face_tell_connect_builded;
extern LPCTSTR facetell_mutex_name;
extern LPCTSTR clientmap_mutex_name;
extern  LPCTSTR client_request_mutex_name;
extern LPCTSTR face_tell_alarminfoset_mutex_name;
extern LPCTSTR pic_search_data_mutex_name;
extern bool GetSysNetworkFlowByMidTable(DWORD &dwbpsRecv, DWORD &dwbpsSend);
extern bool GetSysMemUseStatus(DWORD &total, DWORD & avail);
extern Json::Value analyser_strategy_value;
extern void wparam_free(char **p);
extern bool add_msg2_head(Json::Value &value);
extern Json::Value g_cameralist;
extern Json::Value g_clusterlist;
extern bool json_write2_file(Json::Value & value, std::ofstream &file);
extern bool trans_msg2_another_thread(int nMsgType, Json::Value *val, DWORD ThreadId,char **msgStr,void *para);
extern bool parse_queuemsg2_json(char * pInfo, Json::Reader &reader, Json::Value &value, MSG &msg, void *para);
extern char *g_common_str_client;
extern char *g_common_str_java;
extern char *g_common_str_facedt;
extern char *g_common_str_facetell;
extern char *g_common_str_search;
extern char *g_common_str_shape;
extern char *g_common_str_track;
extern char *g_common_str_rtsp;

extern Json::Value g_cluster_start_items;
extern Json::Value g_cameraadd_attach_para;
extern map<int, struct facetell_para>g_cameraid_map2_facetell_para;

extern map <int, std::string > g_mapmsgclient;
extern bool g_client_alive;
extern int s_send(void *socket, char *string);
extern int s_sendmore(void *socket, char *string);
extern Json::Value g_change_camera_value;
extern MSG java_msg;
extern int g_face_search_index;
extern string g_system_date;
extern string get_system_date();
extern map<int, Json::Value>g_pic_search_data;
extern vector<string> g_ip_config_vec;
const char* StringToConstCharX(string str);

string Gb2312ToUtf_8(const char* gb2312);

string Gb2312ToUtf_8_EX(string gb2312);
extern Json::Value TransUnicodeStringtoUTF8(Json::Value unicodeValue);
extern const char* get_system_misecond_time();