// mmserver.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//#include "zmq.h"
//#include "zmq_utils.h"
#include "zmq.hpp"
//#include "zhelper.h"
#include "json\json.h"
#include <json\config.h>
#include "common.h"
//#include "SimpleLog.h"
#include "server_config.h"
#include "msgDefine.h"
#include "alarm.h"
#include "pc_client.h"
#include "FaceDetect.h"
#include "FaceTell.h"
#include "Conversation2Java.h"
#include "rtspServer.h"
#include "PersonTrack.h"
#include "Broadcast.h"
#include "ShapeAnalysis.h"
#include "TrackServer.h"
#include "monitor.h"
#include "pic_search.h"
#include <fstream>
std::string g_ip_info_req_json = "server_send_java_connect_req.json";
std::string g_cluster_info_req_json = "server_send_cluster_info_req.json";
std::string g_java_change_camera_json = "server_send_change_camera_req.json";
int g_poll_timeout2_java = 1000;
bool bIsGetIpServerInfo;

bool java_send_change_camera_info(Json::Value &value);
bool set_face_dt_init_req_json(Json::Value *pVal)
{
	if (pVal == NULL) {
		fprintf(flog,"[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "pVal is NULL");
		fflush(flog);
		getchar();
		return false;
	}
	Json::Reader reader;
	Json::Value value, dataRequest;
	std::ifstream in;
	char jsonFilePath[255] = { 0 };
	int len = 0;
	char *strTmp = NULL;
	
	in.open(strMsgHeadFile, std::ios::binary);
	if (!in.is_open()) {
		printf("file open failed");
		getchar();
		fprintf(flog,"[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "file open failed");
		fflush(flog);
		getchar();
		return -1;
	}
	if (reader.parse(in, value)) {
		len = strlen((char *)value.toStyledString().data());
		strTmp = (char *)malloc(len + 1);
		memset(strTmp, 0, len + 1);
		memcpy(strTmp, (char*)value.toStyledString().data(), len);
	}
	else {
		//SL_LOG("file parse failed");
		fprintf(flog,"[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "file parse failed");
		fflush(flog);
		getchar();
		return -1;
	}
	//value["msgHead"]["serverIP"] = strServerIP;
	//value["msgHead"]["JavaIP"] = strJavaIP;
	SetReqMsgHead(&value, JSONMSGCODE_FACEDETECTION_INIT_IN);
	dataRequest["FaceDetectorPathDir"] = "";
	dataRequest["PointDetectorPathDir"] = "";
	dataRequest["thresh1"] = "";
	dataRequest["thresh2"] = "";
	dataRequest["thresh3"] = "";
	dataRequest["RoiSavaPathDir"] = "";
	dataRequest["SrcSavaPathDir"] = "";
	dataRequest["SeverNum"] = "";
	dataRequest["threadNum"] = "";
	dataRequest["FaceScore"] = "";
	dataRequest["code"] = "";
	value["dataRequest"] = dataRequest;
	value["dataPush"] = "";
	(*pVal) = value;
	return true;
}
bool init_envale_with_java_info(Json::Value &value)//value is the cluster value from java
{
	Json::Reader reader;
	std::ifstream in_read;
	std::ofstream in_write;
	Json::Value serverList, envalue;

	in_read.open(g_envalue_file, std::ios::binary);
	if (!in_read.is_open()) {
		return false;
	}

	if (!reader.parse(in_read, envalue)) {
		return false;
	}



	int i = 0, len = 0, cluster_type = 0, port = 0;
	char str_type[10] = { 0 }, str_ip[IP_LEN_MAX] = { 0 }, str_port[10] = { 0 };
	len = value.size();
	for (i = 0; i < len; i++) {
		strcpy(str_type, value[i]["clusterType"].toStyledString().data());
		cluster_type = atoi(str_type);
		if (cluster_type == FACE_DETECTION) {//face detection			
			if (value[i].isMember("serverList")) {
				if (value[i]["serverList"].size()) {
					serverList = value[i]["serverList"][0];
					strcpy(str_ip, serverList["severIP"].asCString());
					envalue["facedt_ip"] = str_ip;//face_dt ip
					strcpy(str_port, serverList["severPort"].toStyledString().data());
					port = atoi(str_port);
					nFaceDetectPort = port;//port
				}
			}
		}
		else if (cluster_type == FACE_TELL) {//face tell 
			if (value[i].isMember("serverList")) {
				if (value[i]["serverList"].size()) {
					serverList = value[i]["serverList"][0];
					strcpy(str_ip, serverList["severIP"].asCString());
					envalue["facetell_ip"] = str_ip;//face_tell ip
					strcpy(str_port, serverList["severPort"].toStyledString().data());
					port = atoi(str_port);
					nFaceTell = port;//port	
				}
			}
		}
		else if (cluster_type == HUMAN_SHAPE) {//human shape
			if (value[i].isMember("serverList")) {
				serverList = value[i]["serverList"][0];
				strcpy(str_ip, serverList["severIP"].asCString());
				envalue["shape_ip"] = str_ip;//shape_ip
				strcpy(str_port, serverList["severPort"].toStyledString().data());
				port = atoi(str_port);
				nShapePort = port;//port			
			}
		}
		else if (cluster_type == RTSP_SERVER) {//rtsp
			if (value[i].isMember("serverList")) {
				if (value[i]["serverList"].size()) {
					serverList = value[i]["serverList"][0];
					strcpy(str_ip, serverList["severIP"].asCString());
					envalue["rtsp_ip"] = str_ip;//shape_ip
					strcpy(str_port, serverList["severPort"].toStyledString().data());
					port = atoi(str_port);
					nRtspServer = port;//port		
				}
			}
		}
		else if (cluster_type == HUMAN_TRACK) {
			if (value[i].isMember("serverList")) {
				if (value[i]["serverList"].size()) {
					serverList = value[i]["serverList"][0];
					strcpy(str_ip, serverList["severIP"].asCString());
					envalue["track_ip"] = str_ip;//shape_ip
					strcpy(str_port, serverList["severPort"].toStyledString().data());
					port = atoi(str_port);
					nFaceTrackPort = port;//port
					strcpy(strTrackInitIP, str_ip);
				}
			}
		}	
		else if (cluster_type == PIC_SEARCH) {
			if (value[i].isMember("serverList")) {
				if (value[i]["serverList"].size()) {
					serverList = value[i]["serverList"][0];
					strcpy(str_ip, serverList["severIP"].asCString());
					envalue["search_ip"] = str_ip;//search_ip
					strcpy(str_port, serverList["severPort"].toStyledString().data());
					port = atoi(str_port);
				//	nSearchPort = port;//port
					
				}
			}
		}
	}
///////nAlarmPad
	nAlarmPad = envalue["nAlarmPad"].asInt64();
	///////
#ifdef GET_IP_FROM_JAVA
	in_read.close();

	in_write.open(g_envalue_file, std::ios::binary);
	if (!in_write.is_open()) {
		return false;
	}
	in_write << envalue.toStyledString() << endl;
	in_write.close();
#endif
////////////debug
	in_read.open(g_envalue_file, std::ios::binary);
	if (!in_read.is_open()) {
		return false;
	}

	if (!reader.parse(in_read, envalue)) {
		return false;
	}
	fprintf(flog,"envalue ================= %s\n", (char *)envalue.toStyledString().data());
	fflush(flog);
/////////////
	return true;
}
bool cameraid_map2_facetell_para(Json::Value &value)
{
	int i,j,camid = 0;
	int len = value.size();
	Json::Value camera;
	struct facetell_para para;
	Json::Value *pFaceLibIdList = NULL;
	int lib_size = 0;
	
	for (i = 0; i < len; i++) {
		camera = value[i];
		pFaceLibIdList = &camera["facelibIds"];
		camid = camera["camID"].asInt();
		
	//	para.facelibid = camera["FaceLibId"].asInt();
		
		lib_size = (*pFaceLibIdList).size();
		
		para.facelibid.clear();
		for (j = 0; j < lib_size; j++) {
			para.facelibid.push_back((*pFaceLibIdList)[j].asInt());
		}
		para.minalarmthreshold = camera["minAlarmThreshold"].asFloat();
		para.facceoutnumber = camera["facceOutNumber"].asInt();
		g_cameraid_map2_facetell_para.insert(make_pair(camid,para));
	}
	return true;
}
bool get_info_from_java1(void *context, java_identity_s *js)
{
	if (context == NULL || js == NULL) {
		fprintf(flog, "[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "context is NULL");
		fflush(flog);
		getchar();
		return false;
	}
	js->context = context;
	zmq_msg_t msg_recv;
	Json::Value value;
	Json::Value ip_info_req_value, cluster_info_req_value, java_change_camera_req_value;
	Json::Reader reader;
	int ret = 0;
	int nJsonMsgCode;
	
	//send ip info req
	std::ifstream in;
//	in.open(g_ip_info_req_json, std::ios::binary);
	in.open("server_send_java_connect_req.json", std::ios::binary);
//	in.open("track_addrbak.json", std::ios::binary);
	if (!in.is_open()) {
		printf("[%s] [%d]  open g_ip_info_req_json failed \n", __FUNCTION__, __LINE__);
		getchar();
		return -1;
	}
	if (!reader.parse(in, ip_info_req_value)) {
		printf("[%s] [%d]  parse g_ip_info_req_json failed\n", __FUNCTION__, __LINE__);
		getchar();
		return -1;
	}
//	int len_req = strlen((char *)ip_info_req_value.toStyledString().data());
	bool result = false;
	DealerModeSendRecv dealer(context, java_sk_dealer);
	result = dealer.SendDealerMsg((char *)ip_info_req_value.toStyledString().data());
	if (!result) {
		//failed
	}

	char bind_port[10] = { 0 };
	zmq_pollitem_t items[] = { { java_sk_dealer,0,ZMQ_POLLIN,0 } };
	std::ofstream file_camera_list;
	bool flag_ip = true;
	printf("\nget ip info frome java\n");
	while (flag_ip)
	{
		zmq_poll(items, 1, g_poll_timeout2_java);
		if (items[0].revents & ZMQ_POLLIN) {
			zmq_msg_init(&msg_recv);
			zmq_msg_recv(&msg_recv, java_sk_dealer, 0);

			ret = zmq_msg_recv(&msg_recv, java_sk_dealer, 0);
			
			value.clear();
			nJsonMsgCode = 0;
			string str = (char *)zmq_msg_data(&msg_recv);
			if (ret&&reader.parse(str, value)) {
				nJsonMsgCode = value["msgHead"]["msgCode"].asInt();
				fprintf(flog, "[%s] [%d] recv msg from java ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
				switch (nJsonMsgCode)
				{
				case JSONMSGCODE_JAVA_SEND_IP_INFO:
					if (value["msgBody"]["dataPush"].isMember("javaIP")) {
						strcpy(strJavaIP, value["msgBody"]["dataPush"]["javaIP"].toStyledString().data());
					}
					if (value["msgBody"]["dataPush"].isMember("javaPort")) {
						strcpy(bind_port, value["msgBody"]["dataPush"]["javaPort"].asCString());
						nListJava = atoi(bind_port);
					}
					if (value["msgBody"]["dataPush"].isMember("cameraList")) {
						g_cameralist = value["msgBody"]["dataPush"]["cameraList"];
						file_camera_list.open("g_camera_list.json", std::ios_base::out);
						if (!file_camera_list.is_open()) {
							fprintf(flog, "[%s] [%d] %s\n", __FUNCTION__, __LINE__, "g_camera_list.json open failed");
							fflush(flog);
							printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, "g_camera_list.json open failed");
						}
#ifdef MAIN_STEP_PRINT						
						fprintf(flog, "[%s] [%d] g_cameralist ===== %s\n", __FUNCTION__, __LINE__, (char *)g_cameralist.toStyledString().data());
						fflush(flog);
#endif
						json_write2_file(g_cameralist, file_camera_list);//save cameralist2 json file
						cameraid_map2_facetell_para(g_cameralist);//camera id map2 face tell para
						file_camera_list.close();
					}
					flag_ip = false;
					break;
				default:
					break;
				}
			}
		}
		printf(".");
	}//end of get ip info
	in.close();
	in.open(g_cluster_info_req_json, std::ios::binary);
	if (!in.is_open()) {
		printf("[%s] [%d]  open g_cluster_info_req_json failed\n", __FUNCTION__, __LINE__);
		getchar();
		return -1;
	}
	if (!reader.parse(in, cluster_info_req_value)) {
		printf("[%s] [%d]  parse g_cluster_info_req_json failed \n", __FUNCTION__, __LINE__);
		getchar();
		return -1;
	}
	result = dealer.SendDealerMsg((char *)cluster_info_req_value.toStyledString().data());
	if (!result) {
		//failed
	}

	bool flag_cluster = true;
	Json::Value clusterChangeList;
	printf("\nget cluster info from java\n");
	while (flag_cluster)
	{
		zmq_poll(items, 1, g_poll_timeout2_java);
		if (items[0].revents & ZMQ_POLLIN) {
			zmq_msg_init(&msg_recv);
			zmq_msg_recv(&msg_recv, java_sk_dealer, 0);

			ret = zmq_msg_recv(&msg_recv, java_sk_dealer, 0);
			value.clear();
			nJsonMsgCode = 0;
			string str = (char *)zmq_msg_data(&msg_recv);
			if (ret&&reader.parse(str, value)) {
				nJsonMsgCode = value["msgHead"]["msgCode"].asInt();
				fprintf(flog, "[%s] [%d] recv msg from java ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
				switch (nJsonMsgCode)
				{
				case JSONMSGCODE_JAVA_START_SERVER_ITEMS:
					if (value["msgBody"]["dataPush"].isMember("clusterChangeList")) {
						clusterChangeList = value["msgBody"]["dataPush"]["clusterChangeList"];
					}
					init_envale_with_java_info(clusterChangeList);
					g_cluster_start_items.clear();
					g_cluster_start_items = value;
					flag_cluster = false;
					break;
				default:
					break;
				}
			}
		}
		printf(".");
	}//end of get cluster info
	in.close();
	in.open(g_java_change_camera_json, std::ios::binary);
	if (!in.is_open()) {
		printf("[%s] [%d]  open g_java_change_camera_json failed\n", __FUNCTION__, __LINE__);
		getchar();
		return -1;
	}
	if (!reader.parse(in, java_change_camera_req_value)) {
		printf("[%s] [%d]  parse g_java_change_camera_json failed\n", __FUNCTION__, __LINE__);
		getchar();
		return -1;
	}
	result = dealer.SendDealerMsg((char *)java_change_camera_req_value.toStyledString().data());
	if (!result) {
		//failed
	}

	bool flag_change_camera = true;
	//g_change_camera_value
	printf("\nget change camera info from java\n");
	while (flag_change_camera)
	{
		zmq_poll(items, 1, g_poll_timeout2_java);
		if (items[0].revents & ZMQ_POLLIN) {
			zmq_msg_init(&msg_recv);
			zmq_msg_recv(&msg_recv, java_sk_dealer, 0);

			ret = zmq_msg_recv(&msg_recv, java_sk_dealer, 0);
			value.clear();
			nJsonMsgCode = 0;
			string str = (char *)zmq_msg_data(&msg_recv);
			if (ret&&reader.parse(str, value)) {
				nJsonMsgCode = value["msgHead"]["msgCode"].asInt();
				fprintf(flog, "[%s] [%d] recv msg from java ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
				switch (nJsonMsgCode)
				{
				case JSONMSGCODE_JAVA_CHANGE_CAMERA:
					g_change_camera_value.clear();
					g_change_camera_value = value;
					flag_change_camera = false;
					break;
				default:
					break;
				}
			}
		}
		printf(".");
	}
	//end of get change camera info from java
	zmq_close(java_sk_dealer);
}

bool main_envalue_check(Json::Value &value)
{
	int i,len = 0;
	len = g_ip_config_vec.size();	
	for (i = 0; i < len; i++) {
	//	printf("value == %s\n", g_ip_config_vec[i].c_str());
		if (!value.isMember(g_ip_config_vec[i].c_str())) {
			printf("%s\n", g_ip_config_vec[i].c_str());
			printf("is not set\n");
			return false;
		}
	}
	printf("envalue check success\n");	
	return true;
}
bool main_some_server_check()
{
	BOOL bExist = FALSE;
	HANDLE hMutex = ::CreateMutex(NULL, TRUE, L"face_mtserver");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		bExist = TRUE;
	}
	if (hMutex)
	{
		::ReleaseMutex(hMutex);
	}
	if (bExist)
	{
		return false;
	}
	return true;
}
int main()
{
	if (!main_some_server_check()) {
		printf("mtserver already in running press any key to exit\n");
		getchar();
		return -1;
	}
	//context create
	void *context = zmq_ctx_new();
	HANDLE java;
	HANDLE client_hd;
	HANDLE broadcast_hd;
	int nconnect_status = 0;
	HANDLE face_dt_hd, face_tl_hd,rtsp_hd, shape_hd, track_hd,monitor_hd, search_hd;
	char identity[IDENTIFY_BUFFER_SIZE];
	Json::Value env_value;
	Json::Reader reader;
	

	java_identity_s java_thread_para;
	srand(time(NULL));

	//facetell 状态互斥变量创建
	//printf("facetell_mutex_name == %s\n", facetell_mutex_name);
	m_facetell_mutex = CreateMutex(NULL,false, facetell_mutex_name);
	//HANDLE g_client_msg_map_mutex;
	g_client_msg_map_mutex = CreateMutex(NULL, false, clientmap_mutex_name);
	g_client_request_mutex = CreateMutex(NULL, false, client_request_mutex_name);
	//face_tell_alarminfoset_mutex_name
	g_alarminfoset_mutex = CreateMutex(NULL, false, face_tell_alarminfoset_mutex_name);
//	assert(m_facetell_mutex != 0);
	g_picsearch_muxtex = CreateMutex(NULL, false, pic_search_data_mutex_name);
	//log file open
	flog = fopen("log\\logfile1.txt", "w");
	flog_client = fopen("log\\log_client.txt", "w");
	flog_java = fopen("log\\log_java.txt", "w");
	flog_facedt = fopen("log\\log_facedt.txt", "w");
	flog_facetell = fopen("log\\log_facetell.txt", "w");
	flog_main = fopen("log\\log_main.txt", "w");
	flog_monitor = fopen("log\\log_monitor.txt", "w");
	flog_search = fopen("log\\log_search.txt", "w");
	flog_media = fopen("log\\log_media.txt", "w");
	flog_shape = fopen("log\\log_shape.txt", "w");
	flog_facesearch = fopen("log\\log_facesearch.txt", "w");
	flog_change_camera = fopen("log\\log_change_camera.txt", "w");
	flog_client_tree = fopen("log\\log_client_tree.txt", "w");
	flog_pic_in = fopen("log\\log_pic_in.txt", "w");
	flog_track = fopen("log\\log_track.txt", "w");
	flog_track_init = fopen("log\\log_track_init.txt", "w");
	flog_one_vs_one = fopen("log\\log_one_vs_one.txt", "w");

	if (!point_empty_check(flog_main)) {
		return -1;
	 }

	//socket create 
	frontend = zmq_socket(context, ZMQ_ROUTER);
	broadcast_sk = zmq_socket(context, ZMQ_PUB);
	java_sk = zmq_socket(context, ZMQ_ROUTER);
	java_sk_dealer = zmq_socket(context, ZMQ_DEALER);
	face_dt_sk = zmq_socket(context, ZMQ_DEALER);
	face_tl_sk = zmq_socket(context, ZMQ_DEALER);
	rtsp_sk = zmq_socket(context, ZMQ_DEALER);
	track_sk = zmq_socket(context, ZMQ_DEALER);
	shape_sk = zmq_socket(context, ZMQ_DEALER);
	search_sk = zmq_socket(context, ZMQ_DEALER);
	pic_data_update_sk = zmq_socket(context, ZMQ_DEALER);

	getServerIP(strServerIP);
	strcpy(strRtspIP, strServerIP);//rtsp ip，默认本地ip
	strcpy(strFaceDtIP, strServerIP);//fd ip，默认本地ip
	strcpy(strFaceTellIP, strServerIP);// fl ip，默认本地ip
	strcpy(strFaceTrackIP, strServerIP);//ft ip，默认本地ip
	strcpy(strJavaIP, strServerIP);//java ip，默认本地ip


//////////////////////
	std::ifstream in;
	in.open(g_envalue_file, std::ios::binary);
	json_open_check(&in);
	json_parse2_value(&in, &env_value);
	fprintf(flog, "get java ip from env_value == %s\n", (char *)env_value.toStyledString().data());
	fflush(flog);
	if (!main_envalue_check(env_value)) {
		printf("[%s] [%d] env_value check failed\n", __FUNCTION__, __LINE__);
		getchar();
		return -1;
	}

	sprintf(strJavaInitListen, "%s%s%s%s%d", LISTEN_PROTO, "://", env_value["java_ip"].asCString(), ":", nListJavaInit);
	memset(identity, 0, IDENTIFY_BUFFER_SIZE);
	sprintf(identity, "%04X-%04X", rand() % (0x10000), rand() % (0x10000));
	zmq_setsockopt(java_sk_dealer, ZMQ_IDENTITY, identity, strlen(identity));
	nconnect_status = zmq_connect(java_sk_dealer, strJavaInitListen);
//////////////////////
	//java connect addr
	sprintf(strJavaListen, "%s%s%s%s%d", LISTEN_PROTO, "://", strServerIP, ":", nListJava);
	
	zmq_bind(java_sk, strJavaListen);
	fprintf(flog, "strServerIP == %s 11strJavaListen === %s\n", strServerIP,strJavaListen);
	fflush(flog);

	get_info_from_java1(context,&java_thread_para);
//	std::ifstream in;
	in.close();
	in.open(g_envalue_file, std::ios::binary);
	json_open_check(&in);
	json_parse2_value(&in, &env_value);
	fprintf(flog, "env_value == %s\n", (char *)env_value.toStyledString().data());
	fflush(flog);

	fprintf(flog, "env_value after get_info_from_java == %s\n", (char *)env_value.toStyledString().data());
	fflush(flog);
	java = CreateThread(NULL, 0, java_worker, &java_thread_para, 0, &lpJavaThreadId);
	if (!thread_create_check(java))return -1;
	fprintf(flog, "strJavaListen === %s\n", strJavaListen);
	fflush(flog);

	//Sleep(5000);
	// 生成本机监听地址 针对客户端
	//msg code map init

	msg_code_map_init();
	
	sprintf(strListen, "%s%s%s%s%d", LISTEN_PROTO, "://", strServerIP, ":", nClientPort);
	zmq_bind(frontend, strListen);
	client_hd = CreateThread(NULL, 0, client_worker, context, 0, &lpClientThreadId);
	if (!thread_create_check(client_hd))return -1;
	fprintf(flog, "strListen === %s\n", strListen);
	fflush(flog);
#ifdef MAIN_STEP_PRINT
	fprintf(flog,"lpClientThreadId === %d\n", lpClientThreadId);
	fflush(flog);
#endif


	//广播地址
	sprintf(strBroadCastAddr, "%s%s%s%s%d", LISTEN_PROTO, "://", strServerIP, ":", nBroadCastPort);
	zmq_bind(broadcast_sk, strBroadCastAddr);
	broadcast_hd = CreateThread(NULL, 0, broadcast_worker, context, 0, &lpBroadCastThreadId);
	if (!thread_create_check(broadcast_hd))return -1;
	fprintf(flog,"lpBroadCastThreadId === %d\n", lpBroadCastThreadId);
	fprintf(flog, "strBroadCastAddr === %s\n", strBroadCastAddr);
	fflush(flog);

	//facetell connect addr
#ifdef  LINK_DEBUG
	sprintf(strFaceTell, "%s%s%s%s%d", LISTEN_PROTO, "://", env_value["facetell_ip"].asCString(), ":", nFaceTell);
#else
	sprintf(strFaceTell, "%s%s%s%s%d", LISTEN_PROTO, "://", strFaceTellIP, ":", nFaceTell);	
#endif
#ifdef MAIN_STEP_PRINT
	fprintf(flog,"face tell connect addr ========== %s\n", strFaceTell);
	fflush(flog);
#endif

	memset(identity, 0, IDENTIFY_BUFFER_SIZE);
	sprintf(identity, "%04X-%04X", rand() % (0x10000), rand() % (0x10000));
#ifdef MAIN_STEP_PRINT
	fprintf(flog,"set face_tell identity === %s \n", identity);
	fprintf(flog, "strFaceTell === %s \n", strFaceTell);
	fflush(flog);
#endif

	zmq_setsockopt(face_tl_sk, ZMQ_IDENTITY, identity, strlen(identity));

	nconnect_status = zmq_connect(face_tl_sk, strFaceTell);
	fprintf(flog, "face tell nconnect_status === %d \n", nconnect_status);
	fflush(flog);
	face_tl_hd = CreateThread(NULL, 0, facetell_worker, context, 0, &lpFaceTellThreadId);
	if (!thread_create_check(face_tl_hd))return -1;


	//facedetect connect addr
#ifdef LINK_DEBUG
	sprintf(strFaceDetect, "%s%s%s%s%d", LISTEN_PROTO, "://", env_value["facedt_ip"].asCString(), ":", nFaceDetectPort);
#else
	sprintf(strFaceDetect, "%s%s%s%s%d", LISTEN_PROTO, "://", strFaceDtIP, ":", nFaceDetectPort);
#endif
#ifdef  MAIN_STEP_PRINT
	fprintf(flog,"face dt connect addr ========== %s\n", strFaceDetect);
	fflush(flog);
#endif

	memset(identity, 0, IDENTIFY_BUFFER_SIZE);
	sprintf(identity, "%04X-%04X", rand()%(0x10000), rand()%(0x10000));	
#ifdef  MAIN_STEP_PRINT
	fprintf(flog,"set face_dt identity === %s \n", identity);
	fflush(flog);
#endif

	zmq_setsockopt(face_dt_sk, ZMQ_IDENTITY, identity, strlen(identity));
	nconnect_status = zmq_connect(face_dt_sk, strFaceDetect);
	fprintf(flog, "face dt  nconnect_status === %d \n", nconnect_status);
	fflush(flog);
	face_dt_hd = CreateThread(NULL, 0, facedt_worker, context, 0, &lpFaceDtThreadId);
	if (!thread_create_check(face_dt_hd))return -1;


//rtsp server
#ifdef LINK_DEBUG
	sprintf(strRtspSever, "%s%s%s%s%d", LISTEN_PROTO, "://", env_value["rtsp_ip"].asCString(), ":", nRtspServer);
#else
	sprintf(strRtspSever, "%s%s%s%s%d", LISTEN_PROTO, "://", "192.168.1.232", ":", nRtspServer);
#endif
	
#ifdef MAIN_STEP_PRINT
	fprintf(flog,"strRtspSever connect addr ============ %s\n", strRtspSever);
	fflush(flog);
#endif

	memset(identity, 0, IDENTIFY_BUFFER_SIZE);
	sprintf(identity, "%04X-%04X", rand() % (0x10000), rand() % (0x10000));
#ifdef MAIN_STEP_PRINT
	fprintf(flog,"set rtspServer identity === %s \n", identity);
	fflush(flog);
#endif

	zmq_setsockopt(rtsp_sk, ZMQ_IDENTITY, identity, strlen(identity));
	nconnect_status = zmq_connect(rtsp_sk, strRtspSever);
	fprintf(flog, "rtsp  nconnect_status === %d \n", nconnect_status);
	fflush(flog);
	rtsp_hd = CreateThread(NULL, 0, rtsp_worker, context, 0, &lpRtspThreadId);
	if (!thread_create_check(rtsp_hd))return -1;

	zmq_bind(broadcast_sk, strBroadCastAddr);


//track server
	if (env_value.isMember("track_ip")) {
		sprintf(strTrack, "%s%s%s%s%d", LISTEN_PROTO, "://", env_value["track_ip"].asCString(), ":", nFaceTrackPort);
	}
	else {
		printf("[%s] [%d] track ip addr not set\n", __FUNCTION__, __LINE__);
		fprintf(flog, "[%s] [%d] track ip addr not set\n", __FUNCTION__, __LINE__);
		fflush(flog);
		getchar();
		return -1;
	}
	fprintf(flog, "[%s] [%d] strTrack ==== %s\n", __FUNCTION__, __LINE__, strTrack);
	fflush(flog);
	memset(identity, 0, IDENTIFY_BUFFER_SIZE);
	sprintf(identity, "%04X-%04X", rand() % (0x10000), rand() % (0x10000));
	zmq_setsockopt(track_sk, ZMQ_IDENTITY, identity, strlen(identity));
	track_hd = CreateThread(NULL, 0, TrackWorker, context, 0, &lpTrackThreadId);
	if (!thread_create_check(track_hd))return -1;
//shape server
#ifdef LINK_DEBUG
	sprintf(strShape, "%s%s%s%s%d", LISTEN_PROTO, "://", env_value["shape_ip"].asCString(), ":", nShapePort);
#else
	sprintf(strShape, "tcp://192.168.1.154:6004");// "tcp://192.168.1.143:5556");
#endif
#ifdef  MAIN_STEP_PRINT
	fprintf(flog,"shape connect addr ========== %s\n", strShape);
	fflush(flog);
#endif

	memset(identity, 0, IDENTIFY_BUFFER_SIZE);
	sprintf(identity, "%04X-%04X", rand() % (0x10000), rand() % (0x10000));
#ifdef  MAIN_STEP_PRINT
	fprintf(flog,"set shape identity === %s \n", identity);
	fflush(flog);
#endif

	zmq_setsockopt(shape_sk, ZMQ_IDENTITY, identity, strlen(identity));
	nconnect_status = zmq_connect(shape_sk, strShape);
	fprintf(flog, "shape  nconnect_status === %d \n", nconnect_status);
	fflush(flog);
	shape_hd = CreateThread(NULL, 0, shape_worker, context, 0, &lpShapeThreadId);
	if (!thread_create_check(shape_hd))return -1;

//search_pic_with_pic

	sprintf(strSearchPic, "%s%s%s%s%d", LISTEN_PROTO, "://", env_value["search_ip"].asCString(), ":", nSearchPort);
	memset(identity, 0, IDENTIFY_BUFFER_SIZE);
	sprintf(identity, "%04X-%04X", rand() % (0x10000), rand() % (0x10000));

	zmq_setsockopt(search_sk, ZMQ_IDENTITY, identity, strlen(identity));
	nconnect_status = zmq_connect(search_sk, strSearchPic);
	fprintf(flog, "search  nconnect_status === %d strSearchPic == %s\n", nconnect_status, strSearchPic);
	fflush(flog);
	search_hd = CreateThread(NULL, 0, pic_search_worker, context, 0, &lpPicSearchThreadId);
	if (!thread_create_check(shape_hd))return -1;

	//pic data update
	fprintf(flog, "pic data update begin\n");
	fflush(flog);
	string data_updata_ip = env_value["data_update_ip"].isNull() ? strServerIP : env_value["data_update_ip"].asCString();
	sprintf(strDataUpdate, "%s%s%s%s%d", LISTEN_PROTO, "://", data_updata_ip, ":", nPicDataUpate);
	fprintf(flog, "pic 11\n");
	fflush(flog);

	memset(identity, 0, IDENTIFY_BUFFER_SIZE);
	sprintf(identity, "%04X-%04X", rand() % (0x10000), rand() % (0x10000));
	fprintf(flog, "pic 22\n");
	fflush(flog);
	zmq_setsockopt(pic_data_update_sk, ZMQ_IDENTITY, identity, strlen(identity));
	nconnect_status = zmq_connect(pic_data_update_sk, strDataUpdate);
	fprintf(flog, "search  nconnect_status === %d strDataUpdate == %s\n", nconnect_status, strDataUpdate);
	fprintf(flog, "pic data update end\n");
	fflush(flog);

//monitor_worker
	monitor_hd = CreateThread(NULL, 0, monitor_worker, context, 0, &lpMonitorThreadId);

//////////////////////
//send change camera info2 facedt media
	Sleep(2000);
	if (lpRtspThreadId != 0) {//current just support one camera 
		java_send_change_camera_info(g_change_camera_value);
	//	pre_request_finish_status = false;
	}
	else {
		fprintf(flog, "[%s] [%d] send change camera json fail\n", __FUNCTION__, __LINE__);
		fflush(flog);
		return -1;
	}

	if (lpFaceDtThreadId != 0) {
		char *facedt_tmp = NULL;
		if (trans_msg2_another_thread(RTSP_CHANGE_FACEDETECTION_CAMERA, &g_change_camera_value, lpFaceDtThreadId, &facedt_tmp, NULL)) {//success

		}
		else {
			fprintf(flog, "[%s] [%d] send change camera json fail\n", __FUNCTION__, __LINE__);
			fflush(flog);
			return -1;
		}
	}

	//CloseHandle(frontend);
	WaitForSingleObject(java,INFINITE);
	WaitForSingleObject(client_hd, INFINITE);
	WaitForSingleObject(broadcast_hd, INFINITE);
	WaitForSingleObject(face_dt_hd, INFINITE);
	WaitForSingleObject(face_tl_hd, INFINITE);

	CloseHandle(java);
	CloseHandle(client_hd);
	CloseHandle(broadcast_hd);
	CloseHandle(face_dt_hd);
	CloseHandle(face_tl_hd);
	CloseHandle(m_facetell_mutex);
	CloseHandle(g_client_msg_map_mutex);
	CloseHandle(g_picsearch_muxtex);
	zmq_close(frontend);
	zmq_close(broadcast_sk);
	zmq_close(java_sk);
	zmq_close(face_dt_sk);
	zmq_close(face_tl_sk);
	zmq_close(search_sk);
	fclose(flog);
	return 0;
}

bool java_send_change_camera_info(Json::Value &value)
{
	if (trans_msg2_another_thread(JAVA_CHANGE_CAMERA, &value, lpRtspThreadId, &g_common_str_java, NULL)) {//success
		return true;
	}
	else
	{
		return false;
	}
}