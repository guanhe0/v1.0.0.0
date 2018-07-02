#include "stdafx.h"
#include "Conversation2Java.h"
#include <fstream>
#include <iostream> 
#include "CameraManager.h"

#pragma  comment(lib, "Winmm.lib")
#include "zhelpers.hpp"
struct change_camera_s {
	FrontendMsg *ms;
	int *count;
	bool *pre_request_finish_status;
};
char *g_java_strAliveCheck = NULL;
bool java_alarm_video_sava2_db(Json::Value &value);
bool java_alarm_video_sava_reply(Json::Value &value);
/*CUIJIANHUA+ADD+CODE*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL SetChangeCameraToDt(Json::Value *dst, Json::Value *src)
{
		Json::Value msgHead;
		Json::Value reValue;
		//getTimeStamp(&time);

		//(*src)["msgHead"]["timestamp"].toStyledString().data();
		if (src != NULL)
		{
			msgHead["msgHead"] = (*src)["msgHead"]["msgHead"];
			msgHead["clientIP"] = (*src)["msgHead"]["clientIP"];
			msgHead["msgCode"] = (*src)["msgHead"]["msgCode"];
			msgHead["msgType"] = (*src)["msgHead"]["msgType"];
			msgHead["timestamp"] = (*src)["msgHead"]["timestamp"];
			msgHead["requestID"] = (*src)["msgHead"]["requestID"];
			msgHead["boundID"] =   (*src)["msgHead"]["boundID"];
			msgHead["authorization"] = (*src)["msgHead"]["authorization"];
		}
		reValue["msgHead"] = msgHead;
		reValue["msgBody"] = (*src)["msgBody"];

		return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool java_start_services_result_collect(Json::Value &responValue, Json::Value &value, FrontendMsg &ms);
//bool onepicture_into_lib(Json::Value *pVal) 
//{
//	point_empty_check k(pVal);
//
//	Json::Value value;
//	SetMsgHead(&value, pVal, JSONMSGTYPE_REQUEST, JSONMSGCODE_FACEDETECTION_ONEPICTURE);
//
//}
void CALLBACK java_change_camera_timer_pro(UINT wTimerID, UINT nMsg, DWORD dwUser, DWORD dwl, DWORD dw2)
{
	Json::Value cameraErrList, dataSend;
	struct time_event_s *p_t = (struct time_event_s *)(nMsg);
	Json::Value reponseValue = *((Json::Value *)(p_t->val));
	FrontendMsg ems = *((FrontendMsg *)(p_t->m));

	cameraErrList = reponseValue["msgBody"]["dataSend"]["cameraErrList"];
	if (!cameraErrList.isNull()) {//exist error
		dataSend["code"] = JSONMSGCODE_SERVER_FACE_DETECT_CHANGE_CAMERA_ERR;		
	}
	else {
		dataSend["code"] = JSONMSGCODE_SERVER_FACE_DETECT_CHANGE_CAMERA_SUCCESS;
	}
	ems.SendOuterMsg((char *)reponseValue.toStyledString().data());
}

bool java_change_camera_result_collect(int req_pre, Json::Value &value,Json::Value &responseValue,void *para)
{
	int requestid_pre = req_pre, requestid = 0;
	Json::Value cameraErrList;
	struct change_camera_s cs;
	int count = 0;
	
	cs = *(struct change_camera_s *)para;
	count = *(cs.count);

	requestid = value["msgHead"]["requestID"].asInt();
	if (requestid == requestid_pre) {// the same requestid
		cameraErrList = value["msgBody"]["dataSend"]["cameraErrList"];
		if (!cameraErrList.isNull()) {//exit error
			responseValue["msgBody"]["dataSend"]["cameraErrList"].append(cameraErrList);
			responseValue["msgBody"]["dataSend"]["code"] = JSONMSGCODE_SERVER_FACE_DETECT_CHANGE_CAMERA_ERR;
		}
		count--;
		if (count == 0) {
			responseValue["msgBody"]["dataSend"]["code"] = JSONMSGCODE_SERVER_FACE_DETECT_CHANGE_CAMERA_SUCCESS;
			cs.ms->SendOuterMsg((char *)responseValue.toStyledString().data());
			*(cs.pre_request_finish_status) = true;
		}

	}
	return true;
}

bool java_start_services_result_collect(Json::Value &responValue, Json::Value &value, FrontendMsg &ms)
{
	Json::Value serverErrList;
	if (responValue.isMember("msgBody")) {
		if (responValue["msgBody"].isMember("dataSend")) {
			if (responValue["msgBody"]["dataSend"].isMember("serverErrList")) {
				serverErrList = responValue["msgBody"]["dataSend"]["serverErrList"];
			}
		}
	}
	else {
		responValue = g_cluster_start_items;
		if (g_cluster_start_items["msgBody"].isMember("dataSend")) {
			if (g_cluster_start_items["msgBody"]["dataSend"].isMember("serverErrList")) {
				responValue["msgBody"]["dataSend"]["serverErrList"].clear();
			}
		}
	}
	serverErrList.append(value);
	//send over responValue set null
	if (serverErrList.size() == 3) {//face tell face dt rtsp

		ms.SendOuterMsg((char *)responValue.toStyledString().data());
		responValue.clear();
	}
	return true;
}

bool add_key_code2_value(Json::Value *val)
{
	point_empty_check(val);
	Json::Value *picturelist = NULL;
	int len = 0;
	if ((*val)["msgBody"].isNull()) return false;
	if ((*val)["msgBody"]["dataPush"].isNull())return false;
	if ((*val)["msgBody"]["dataPush"]["PictureList"].isNull())return false;
	picturelist = &((*val)["msgBody"]["dataPush"]["PictureList"]);
	if ((*val)["msgBody"]["dataPush"]["PictureList"].size() > 0) {
		string path = (*val)["msgBody"]["dataPush"]["PictureList"][0]["PicturePathDir"].asCString();
	}
	else {
		printf("\n[%s] [%s] [%d] PictureList size is zero ************** press eny key to exit\n", get_system_misecond_time(), __FUNCTION__, __LINE__);
//		getchar();//
	}
	point_empty_check(picturelist);
	len = (*picturelist).size();
#ifdef JAVA_VALUE_PRINT
	//fprintf(flog, "[%s] [%d]  len ==== %d\n", __FUNCTION__, __LINE__, len);
	////fflush(flog);
#endif
	for (int i = 0; i < len; i++)
	{
		(*picturelist)[i]["code"] = JSONMSGCODE_SERVER_FEA_CREATE_SUCCESS;
	}
	return true;
}

bool jthread_request2_other(int msg_type,DWORD thread,Json::Value &value,char **str_tmp,void *param)
{
	if (msg_type <= 0 || thread == 0 || str_tmp == NULL) {
		return false;
	}
	int len_pre = 0,ret = 0;
	//DWORD *pThreadId = (DWORD*)thread;
	DWORD ThreadId = thread;
	postthreadmessage_mem_malloc(str_tmp, &value);

	if (ThreadId != 0) {
		ret = PostThreadMessage(ThreadId, msg_type, (WPARAM)(*str_tmp), NULL);
		if (!postthreadmessage_check(ret)) {
			wparam_free(str_tmp);
			return false;			
		}
		else {
			return true;
		}
	}
	else {
		wparam_free(str_tmp);
		return false;
	}
}

bool trans_query_reslut2_client(int *len_pre, char **strTmp, Json::Value *val, int ThreadId, int nMsgType)
{
	if (len_pre == NULL || strTmp == NULL || val == NULL || ThreadId == 0) {
		fprintf(flog_java, "[%s] [%d]  param error\n", __FUNCTION__, __LINE__);
		//fflush(flog);
	}
//	int nMsgType = JAVA_RETURN_CAPTURE_LOOK_RESULT;//
	int msg_code = (*val)["msgHead"]["msgCode"].asInt();
	int ret = 0;
	switch (msg_code)
	{
	case JSONMSGCODE_JAVA_LOG_RECORD:
		(*val)["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_LOG_RECORD_BACK;
		(*val)["msgBody"]["dataSend"]["code"] = JSONMSGCODE_CLIENT_LOG_RECORD_BACK;
		break;
	case JSONMSGCODE_JAVA_SEARCH_RECORD_LOOK_BACK:
		(*val)["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_SEARCH_RECORD_LOOK_BACK_BACK;
		(*val)["msgBody"]["dataSend"]["code"] = JSONMSGCODE_CLIENT_SEARCH_RECORD_LOOK_BACK_BACK;
		break;
	case JSONMSGCODE_JAVA_SEARCH_ALARAM_LOOK_BACK:
		(*val)["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_SEARCH_ALARAM_LOOK_BACK_BACK;
		(*val)["msgBody"]["dataSend"]["code"] = JSONMSGCODE_CLIENT_SEARCH_ALARAM_LOOK_BACK_BACK;
		break;
	case JSONMSGCODE_JAVA_SEND_CAP_QUERY_RESULT:
		(*val)["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_SEARCH_CAPTUER_LOOK_BACK_BACK;
		(*val)["msgBody"]["dataSend"]["code"] = JSONMSGCODE_CLIENT_SEARCH_CAPTUER_LOOK_BACK_BACK;
		break;
	case JSONMSGCODE_JAVA_SEARCH_ALARAM_DETAIL:
		(*val)["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_SEARCH_ALARAM_DETAIL_BACK;
		(*val)["msgBody"]["dataSend"]["code"] = JSONMSGCODE_CLIENT_SEARCH_ALARAM_DETAIL_BACK;
		break;
	default:
		fprintf(flog_java, "[%s] [%d] Unkown java_msg type \n", __FUNCTION__, __LINE__);
		//fflush(flog);
		break;
	}

	postthreadmessage_mem_malloc(strTmp, val);
	if (ThreadId != 0) {
		ret = PostThreadMessage(ThreadId, nMsgType, (WPARAM)(*strTmp), NULL);
		if (!postthreadmessage_check(ret)) {
			fprintf(flog_java, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
			//fflush(flog);
			wparam_free(strTmp);
		}
		else {
#ifdef JAVA_VALUE_PRINT
			fprintf(flog, "[%s] [%d] send mst to client ==== %s\n", __FUNCTION__, __LINE__, (*strTmp));
			//fflush(flog);
#endif
		}
	}
	return true;
}
bool java_recombind_pic_search_msg2_client(Json::Value &value)
{
	int requestid = 0;
	requestid = value["msgHead"]["requestID"].asInt();
	Json::Value src;

	WaitForSingleObject(g_picsearch_muxtex, INFINITE);
	if (!g_pic_search_data[requestid].isNull()) {
		src = g_pic_search_data[requestid];
	}
	else {
		fprintf(flog, "[%s] [%d] g_pic_search_data get data fail\n", __FUNCTION__, __LINE__);
		ReleaseMutex(g_picsearch_muxtex);
		return false;
	}
	ReleaseMutex(g_picsearch_muxtex);

	Json::Value *pcameraArray = NULL,*pnewcameraArray = NULL; 
	if (!src.isNull()) {
		//value cameraArray
		pcameraArray = src["msgBody"]["dataSend"].isMember("resImgIdArray") ? &(src["msgBody"]["dataSend"]["resImgIdArray"]) : NULL;
	}

	if (!value.isNull()) {
		pnewcameraArray = value["msgBody"]["dataSend"].isMember("cameraArray") ? &(value["msgBody"]["dataSend"]["cameraArray"]) : NULL;
	}

	int size = 0,i, imgID,j,srcimgID;
	Json::Value *atom = NULL,*src_atom = NULL;
	int src_size = 0;
	
	//src size
	if (pcameraArray != NULL) {
		src_size = pcameraArray->size();
	}

	string imgidstr;
	string srcimgid;
	if (pnewcameraArray != NULL) {
		size = pnewcameraArray->size();
		for (i = 0; i < size; i++) {			
			atom = &(*pnewcameraArray)[i];
			imgidstr = (*atom).isMember("imgID") ? (*atom)["imgID"].asCString() : "";
			(*atom)["imgPath"] = Gb2312ToUtf_8_EX((*atom)["imgPath"].asString());
			//get similar
			for (j = 0; j < src_size; j++) {
				src_atom = &(*pcameraArray)[j];
				srcimgid = (*src_atom).isMember("imgID")?(*src_atom)["imgID"].asCString():"";
				if (strcmp(imgidstr.c_str(), srcimgid.c_str()) == 0) {
					break;
				}
			}
			(*atom)["similarValue"] = (*src_atom).isMember("similarValue")?(*src_atom)["similarValue"]:0;
		}
	}
	else {
		fprintf(flog, "[%s] [%d] g_pic_search_data get data fail\n", __FUNCTION__, __LINE__);
	}
	return true;
}

DWORD  WINAPI java_worker(void * para)
{
	if (para == NULL) {
		printf("[%s] [%d]   ==== %s\n", __FUNCTION__, __LINE__, "para is NULL");
		fprintf(flog_java, "[%s] [%d]   ==== %s\n", __FUNCTION__, __LINE__, "para is NULL");
		return -1;
	}
	void * context = ((java_identity_s *)para)->context;

	MSG java_msg;
	int nJsonMsgCode;
	int len = 0, malloc_len_pre = 0,msg_type = 0, requestid = 0, requestid_pre = 0;
	bool pre_request_finish_status = true;

	char identity[100] = { 0 };
	zmq_msg_t msg_recv;
	Json::Value value, sendValue,tmp;
	Json::Reader reader;
	int nJaport = 0;
	string strJaIP = "";
	Json::Value responseValue, dataSend, PictureList, cameraErrList;
	Json::Value msgBody;
	Json::Value requestValue;
	Json::Value msgHead, dataPush, cameraList, cluster;
	MMRESULT change_camera_time;

	char *strTmp = NULL,*strTmp1 = NULL,*strTmp2 = NULL,*strTmp3 = NULL;
	FrontendMsg sendMsg(context, java_sk);
	int nMsgType = 0, clusterType = 0;

	int ret = 0,num = 0;
	int nBodyCode = 0;
	int nchange_camera_count = 0;
	char strJsonMsgCode[20] = { 0 };
	struct time_event_s time_event;

	PeekMessage(&java_msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	//len = strlen(sendMsg.get_identity());
	//if (len <= 0) {
	//	if (((java_identity_s *)para)->identity != NULL)
	//		sendMsg.set_identity(((java_identity_s *)para)->identity);
	//}

//发送策略请求
#if 0
	std::ifstream in;
	in.open("server_send_analyer_strategy_req.json", std::ios::binary);
	if (!in.is_open())
		return -1;
	if (!reader.parse(in, value)) {
		fprintf(flog, "[%s] [%d]   ==== %s\n", __FUNCTION__, __LINE__, "file parse failed");
		//fflush(flog);
	}
	add_msg2_head(value);
#ifdef JAVA_VALUE_PRINT
	printf("[%s] [%d]  get strategy request id ==== %d\n", __FUNCTION__, __LINE__, value["msgHead"]["requestID"].asInt());
	fprintf(flog, "[%s] [%d]  get strategy request id ==== %d\n", __FUNCTION__, __LINE__, value["msgHead"]["requestID"].asInt());
	//fflush(flog);
#endif 
	sendMsg.SendOuterMsg((char *)value.toStyledString().data());
#endif
	struct change_camera_s cameras;
	cameras.count = &nchange_camera_count;
	cameras.ms = &sendMsg;
	cameras.pre_request_finish_status = &pre_request_finish_status;
	zmq_pollitem_t items[] = { { java_sk,0,ZMQ_POLLIN,0 } };

	/*<-------------------------------cuijainhua--------------------------------------->*/
	CameraManager* pCamManager = CameraManager::GetCameraManager();
	/*<---------ok---------->*/

	
		while (true)
		{

			zmq_poll(items, 1, zmq_poll_timeout);
			if (items[0].revents & ZMQ_POLLIN) {
				//zmq_msg_init(&msg_recv);
				if (!sendMsg.RecvFrontendMsg(&msg_recv))
				{
					continue;
				}
#ifdef JAVA_VALUE_PRINT
			//	printf("[%s] [%d]  java recv java_msg ==== %s\n", __FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
				fprintf(flog_java,"[%s] [%d]  java recv java_msg ==== %s\n", __FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
				fflush(flog_java);
#endif
				
				value.clear();
				string msgRecv= (char *)zmq_msg_data(&msg_recv);
				if (reader.parse((char *)zmq_msg_data(&msg_recv), value)) {
//					printf("[%s] [%d] flog_client_tree == %d java send java_msg to client ==== %s\n", __FUNCTION__, __LINE__, JSONMSGCODE_JAVA_SEND_CAMERA_INFO, (char *)value.toStyledString().data());
					if (value["msgBody"].isMember("dataSend") && value["msgBody"]["dataSend"].isMember("code")) {
						strcpy(strJsonMsgCode, value["msgBody"]["dataSend"]["code"].toStyledString().data());
						nBodyCode = atoi(strJsonMsgCode);//body code
					}

					if (!value["msgHead"]["msgCode"].isNull()) {
						memset(strJsonMsgCode, 0, sizeof(strJsonMsgCode));
						strcpy(strJsonMsgCode, value["msgHead"]["msgCode"].toStyledString().data());
						nJsonMsgCode = atoi(strJsonMsgCode);//head code
					}
					if (!value["msgHead"]["msgType"].isNull()) {
						msg_type = value["msgHead"]["msgType"].asInt();
					}

					
#ifdef JAVA_VALUE_PRINT					
					//fprintf(flog,"[%s] [%d]  java recv value ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());					
#endif
					responseValue.clear();
					msgBody.clear();
					string str;
					string str_dst;
					char *testbuff;
					Json::Value test_value;
					switch (nJsonMsgCode)
					{
					case JSONMSGCODE_JAVA_SEND_CAMERA_INFO:
						/*<---------------------------------------cuijianhua---------------------------------------------------->*/
						pCamManager->SetOrgCamInfoFromJava(value);
						/*<-------------------------------->*/
						nMsgType = JAVA_SEND_CAMERA_INFO;
						postthreadmessage_mem_malloc(&strTmp, &value);						
#ifdef JAVA_VALUE_PRINT
					//	printf("[%s] [%d] flog_client_tree == %d java send java_msg to client ==== %s\n", __FUNCTION__, __LINE__, JSONMSGCODE_JAVA_SEND_CAMERA_INFO, (char *)value.toStyledString().data());
					//	printf("[%s] [%d] flog_client_tree == %d java send java_msg to client ==== %s\n", __FUNCTION__, __LINE__, JSONMSGCODE_JAVA_SEND_CAMERA_INFO, (char *)strTmp);
						fprintf(flog_client_tree, "[%s] [%d] flog_client_tree == %d java send java_msg to client ==== %s\n", __FUNCTION__, __LINE__, JSONMSGCODE_JAVA_SEND_CAMERA_INFO,(char *)strTmp);
						fflush(flog_client_tree);
#endif
						if (lpClientThreadId != 0) {
							ret = PostThreadMessage(lpClientThreadId, nMsgType, (WPARAM)strTmp, NULL);
							if (!postthreadmessage_check(ret)) {
								fprintf(flog_java, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
								wparam_free(&strTmp);
							}
						}
						else {
							fprintf(flog_java, "erroe lpClientThreadId ============== %d", lpClientThreadId);
						}
						break;
					case JSONMSGCODE_JAVA_SEND_PC_CLIENT_VERSION:
						nMsgType = SERVER_GET_PC_CLIENT_VERSION;
						value["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_CONNECTTEST;
						value["msgBody"]["dataSend"]["code"] = JSONMSGCODE_CLIENT_OK;
						postthreadmessage_mem_malloc(&strTmp, &value);
#ifdef CLIENT_LINK_TEST
						fprintf(flog_client, "[%s] [%d]  java send java_msg to client ==== %s\n", __FUNCTION__, __LINE__, (char *)strTmp);
#endif
						if (lpClientThreadId != 0) {
							ret = PostThreadMessage(lpClientThreadId, nMsgType, (WPARAM)strTmp, NULL);
							if (!postthreadmessage_check(ret)) {
								fprintf(flog_client, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
								wparam_free(&strTmp);
							}
						}
						else {
							fprintf(flog_client, "erroe lpClientThreadId ============== %d", lpClientThreadId);
						}
						break;
					case JSONMSGCODE_SERVER_CONFIRM_USERNAME_AND_PWD:
						if (nBodyCode == JSONMSGCODE_JAVA_SEND_USERNAME_NOT_EXIST) {
							value["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_LOGIN_ERR_USERNAME;
							value["msgBody"]["dataSend"]["code"] = JSONMSGCODE_CLIENT_LOGIN_ERR_USERNAME;
							nMsgType = JAVA_SEND_USERNAME_NOT_EXIST;
						}
						else if (nBodyCode == JSONMSGCODE_JAVA_SEND_PASSWORD_WRONG) {
							value["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_LOGIN_ERR_PASSWORD;
							value["msgBody"]["dataSend"]["code"] = JSONMSGCODE_CLIENT_LOGIN_ERR_PASSWORD;
							nMsgType = JAVA_SEND_PASSWORD_ERROR;

						}
						else if (nBodyCode == JSONMSGCODE_JAVA_SEND_LOGIN_CONFIRM_OK) {
							value["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_OK;
							value["msgBody"]["dataSend"]["code"] = JSONMSGCODE_CLIENT_OK;
							nMsgType = JAVA_SEND_OK;
						}

						postthreadmessage_mem_malloc(&strTmp, &value);					
#ifdef JAVA_VALUE_PRINT
						fprintf(flog_java, "[%s] [%d]  java send msg to client ==== %s\n", __FUNCTION__, __LINE__, (char *)strTmp);
#endif
						if (lpClientThreadId != 0) {
							ret = PostThreadMessage(lpClientThreadId, nMsgType, (WPARAM)strTmp, NULL);
							if (!postthreadmessage_check(ret)) {
								fprintf(flog_java, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
								wparam_free(&strTmp);
							}
						}
						else {
							fprintf(flog_java, "erroe lpClientThreadId ============== %d", lpClientThreadId);
						}
						break;
					case JSONMSGCODE_FACEDETECTION_PICTUREDIR_IN://java_face_lib_and_others.json
#ifdef PICS_IN_LIB_PRINT
						fprintf(flog_pic_in, "[%s] [%d] %s\n", __FUNCTION__, __LINE__, "JSONMSGCODE_FACEDETECTION_PICTUREDIR_IN");
						fflush(flog_pic_in);
#endif 
						if (!add_key_code2_value(&value)) {
							fprintf(flog_pic_in, "[%s] [%d] %s\n", __FUNCTION__, __LINE__, "add_key_code2_value failed");
						}
						num = get_json_number((char *)value["msgBody"]["dataPush"]["Number"].toStyledString().data());
						sendMsg.set_pic_num(num);
						nMsgType = FACEDETECTION_PICTUREDIR_IN;
						postthreadmessage_mem_malloc(&strTmp, &value);
#ifdef PICS_IN_LIB_PRINT
					//	printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, value.toStyledString().data());
						fprintf(flog_pic_in,"[%s] [%d] %s\n", __FUNCTION__, __LINE__, value.toStyledString().data());
#endif
						if (lpFaceDtThreadId != 0) {
							testbuff = new char[msgRecv.length() + 100];
							memset((testbuff), 0, msgRecv.length() + 100);
							strncpy((testbuff), msgRecv.data(), msgRecv.length());
							ret = PostThreadMessage(lpFaceDtThreadId, nMsgType, (WPARAM)testbuff, NULL);
						//	ret = PostThreadMessage(lpFaceDtThreadId, nMsgType, (WPARAM)testbuff, NULL);
							if (!postthreadmessage_check(ret)) {
								fprintf(flog_pic_in, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
								wparam_free(&strTmp);
							}
						}
						else {
							fprintf(flog_pic_in, "erroe lpFaceDtThreadId ============== %d", lpFaceDtThreadId);
						}
						fflush(flog_pic_in);
						break;
					case JSONMSGCODE_JAVA_SEND_IP_INFO:
#ifdef JAVA_STEP_PRINT
						printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, "case java_send_ip_info");
						fprintf(flog,"[%s] [%d] %s\n", __FUNCTION__, __LINE__, "case java_send_ip_info");						
#endif						
						SetMsgHead(&responseValue, &value, JSONMSGTYPE_RESPONSE, JSONMSGCODE_JAVA_SEND_IP_INFO);
						msgBody["dataSend"] = {};
						msgBody["dataRecv"] = "";
						msgBody["dataSend"]["code"] = JSONMSGCODE_SERVER_RESPONSE_OK;
#ifdef DEBUG 
						msgBody["dataSend"]["msgString"] = "server_response_ok";
#endif
						responseValue["msgBody"] = msgBody;
#ifdef JAVA_STEP_PRINT
						printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, "java socket replay to java");
						fprintf(flog,"[%s] [%d] %s\n", __FUNCTION__, __LINE__, "java socket replay to java");
						//fflush(flog);
#endif
						sendMsg.SendOuterMsg((char *)responseValue.toStyledString().data());//reply to java for the ip info
						Sleep(100);
#ifdef JAVA_STEP_PRINT
						printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, "java socket reply ip info over");
						fprintf(flog,"[%s] [%d] %s\n", __FUNCTION__, __LINE__, "java socket reply ip info over");
						//fflush(flog);
#endif
						break;
					case JSONMSGCODE_JAVASERVER_INIT_IN:
						fprintf(flog_track_init, "[%s] [%d] %s\n", __FUNCTION__, __LINE__, "send track init msg to track thread");
						nMsgType = JAVATHREAD_PUSH_TRACK_INITMSG;
						postthreadmessage_mem_malloc(&strTmp, &value);
						fprintf(flog_track_init, "[%s] [%d] %s\n", __FUNCTION__, __LINE__, strTmp);
						if (lpTrackThreadId != 0) {
							ret = PostThreadMessage(lpTrackThreadId, nMsgType, (WPARAM)strTmp, NULL);
							if (!postthreadmessage_check(ret)) {
								fprintf(flog_track_init, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
								wparam_free(&strTmp);
							}
						}
						else {
							fprintf(flog_track_init, "erroe lpTrackThreadId ============== %d", lpTrackThreadId);
						}
						fflush(flog_track_init);
						break;
					case JSONMSGCODE_JAVA_SEND_CAP_QUERY_RESULT:
						trans_query_reslut2_client(&malloc_len_pre, &strTmp, &value, lpClientThreadId, JAVA_RETURN_CAPTURE_LOOK_RESULT);
						break;
					case JSONMSGCODE_JAVA_SEARCH_ALARAM_LOOK_BACK:
						trans_query_reslut2_client(&malloc_len_pre, &strTmp, &value, lpClientThreadId, JAVA_RETURN_ALARAM_LOOK_BACK);
						break;
					case JSONMSGCODE_JAVA_SEARCH_ALARAM_DETAIL:
						trans_query_reslut2_client(&malloc_len_pre, &strTmp, &value, lpClientThreadId, JAVA_RETURN_ALARAM_DETAIL);
						break;
					case JSONMSGCODE_JAVA_SEARCH_RECORD_LOOK_BACK://日志查询返回
						trans_query_reslut2_client(&malloc_len_pre, &strTmp, &value, lpClientThreadId, JAVA_RETURN_RECORD_LOOK_BACK);
						break;
					case JSONMSGCODE_JAVA_LOG_RECORD://日志存储返回
						trans_query_reslut2_client(&malloc_len_pre, &strTmp, &value, lpClientThreadId, JAVA_LOG_REDORD_RETURN);
						break;
					case JSONMSGCODE_JAVA_MONITOR_CAMERA://camera status reply
						fprintf(flog_java, "[%s] [%d] camera send to java's reply \n", __FUNCTION__, __LINE__);
						break;
					case JSONMSGCODE_JAVA_REPONSE_OK:
						break;
					case JSONMSGCODE_JAVA_RETURN_STRATEGY:
#ifdef JAVA_VALUE_PRINT
						fprintf(flog_java, "[%s] [%d] java worker recv strategy msg ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
#endif 
						analyser_strategy_value = value;
						break;
					case JSONMSGCODE_JAVA_MONITOR_SERVER:
						if (nBodyCode == JSONMSGCODE_JAVA_REPONSE_OK) {
							fprintf(flog_java, "[%s] [%d] java send to server status reply \n", __FUNCTION__, __LINE__);
						}
						break;
					case JSONMSGCODE_JAVA_CHANGE_FACELIB:
						if (msg_type = JSONMSGTYPE_REQUEST) {							
							if (!jthread_request2_other(SERVER_TRANS_JAVAREQ_CHANGE_FACELIB, lpFaceTellThreadId, value, &strTmp, NULL)) {
#ifdef JAVA_VALUE_PRINT
								fprintf(flog_java, "[%s] [%d] send msg to face tell failed ==== %s\n", __FUNCTION__, __LINE__, (strTmp));
#endif								
							}
						}
						else if (msg_type == JSONMSGTYPE_RESPONSE) {

						}
						break;
					case JSONMSGCODE_JAVA_CHANGE_CAMERA:
						nchange_camera_count = 0;
						requestid = value["msgHead"]["requestID"].asInt();
						if (pre_request_finish_status == false) {//pre request unfinish ,reply error to java
							SetMsgHead(&sendValue, &value, JSONMSGTYPE_RESPONSE, JSONMSGCODE_SERVER_FACE_DETECT_CHANGE_CAMERA_ERR);
							sendValue["msgBody"] = value["msgBody"];
							sendValue["msgBody"]["dataRequest"]["code"] = JSONMSGCODE_SERVER_FACE_DETECT_CHANGE_CAMERA_ERR;
							sendMsg.SendOuterMsg((char *)sendValue.toStyledString().data());
							break;
						}
					//	if (jthread_request2_other(JAVA_CHANGE_CAMERA, lpRtspThreadId, value, &strTmp, NULL))
						if(trans_msg2_another_thread(JAVA_CHANGE_CAMERA,&value, lpRtspThreadId,&g_common_str_java,NULL))
						{//rtsp
							pre_request_finish_status = false;
							nchange_camera_count++;
#ifdef JAVA_VALUE_PRINT
							fprintf(flog_change_camera, "[%s] [%d] trans msg2 media ==== %s\n", __FUNCTION__, __LINE__, (char *)g_common_str_java);
							fflush(flog_change_camera);
#endif
						}
#if 1
						if (jthread_request2_other(RTSP_CHANGE_FACEDETECTION_CAMERA, lpFaceDtThreadId, value, &strTmp1, NULL)) {//lpFaceDtThreadId
#ifdef JAVA_VALUE_PRINT
							//fprintf(flog_change_camera, "[%s] [%d] trans msg2 face dt ==== %s\n", __FUNCTION__, __LINE__, (*strTmp1));
							//fflush(flog_change_camera);
#endif
							nchange_camera_count++;
						}
						if (0)//(jthread_request2_other(JAVA_CHANGE_CAMERA, lpTrackThreadId, value, &strTmp2, NULL))
						{//lpFaceTellThreadId
#ifdef JAVA_VALUE_PRINT
							/*fprintf(flog, "[%s] [%d] send java_msg to lpFaceTellThreadId failed ==== %s\n", __FUNCTION__, __LINE__, (*strTmp));
							//fflush(flog);*/
#endif
							nchange_camera_count++;

						}

#endif 
						requestid_pre = requestid;
						//time_event.val = &responseValue;
						//time_event.m = &sendMsg;
						//change_camera_time = timeSetEvent(change_camera_timeout, 0, (LPTIMECALLBACK)java_change_camera_timer_pro, (DWORD_PTR)&time_event, TIME_ONESHOT);
						SetMsgHead(&responseValue, &value, JSONMSGTYPE_RESPONSE, JSONMSGCODE_JAVA_CHANGE_CAMERA);
						dataSend["code"] = "";
						dataSend["cameraErrList"] = {};
						responseValue["msgBody"]["dataSend"] = dataSend;
						break;
					case JSONMSGCODE_JAVA_CHANGE_STATEG://no response right now,add it alter
#ifdef JAVA_VALUE_PRINT
						fprintf(flog_java, "[%s] [%d]  ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
						//fflush(flog);
#endif
						if (0){//(value["msgBody"].isMember("dataPush")) {//相机添加 附加参数,例如相似度,java 分三次发送
							g_cameraadd_attach_para = value["msgBody"]["dataPush"];
							dataPush = value["msgBody"]["dataPush"];
							cameraList = dataPush["cameraList"];
							cluster = dataPush["cluster"];
							clusterType = cluster["clusterType"].asInt();
							switch (clusterType)
							{
								case FACE_TELL:								
								if (jthread_request2_other(JAVA_CHANGE_STATEG, lpFaceTellThreadId, value, &strTmp1, NULL)) {
#ifdef JAVA_VALUE_PRINT
									fprintf(flog_java, "[%s] [%d] java send change stateg msg to face tell ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
									//fflush(flog);
#endif								
								}
									break;
								case FACE_DETECTION:
									if (jthread_request2_other(JAVA_CHANGE_STATEG, lpFaceDtThreadId, value, &strTmp2, NULL)) {
#ifdef JAVA_VALUE_PRINT
										fprintf(flog_java, "[%s] [%d] java send change stateg msg to face dt ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
										//fflush(flog);
#endif									
									}
								case HUMAN_TRACK:
									if (jthread_request2_other(JAVA_CHANGE_STATEG, lpTrackThreadId, value, &strTmp, NULL)) {
#ifdef JAVA_VALUE_PRINT
										fprintf(flog_java, "[%s] [%d] java send change stateg msg to track ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
										//fflush(flog);
#endif																		
									}
								case RTSP_SERVER:
									if (jthread_request2_other(JAVA_CHANGE_STATEG, lpRtspThreadId, value, &strTmp3, NULL)) {
#ifdef JAVA_VALUE_PRINT
										fprintf(flog_java, "[%s] [%d] java send change stateg msg to rtsp ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
										//fflush(flog);
#endif										
									}
									break;
							}
						}						
						break;
					case JSONMSGCODE_CLIENT_GET_USING_IMG_CHECKIN_IMG_BACK:
						if (msg_type = JSONMSGTYPE_RESPONSE) {
#ifdef PIC_WITH_PIC_PRINT									
							fprintf(flog_search, "g_face_search_index ====== %d [%s] [%s] [%d] java reply searhc result msg to client thread ==  \n", (g_face_search_index++), get_system_misecond_time(), __FUNCTION__, __LINE__);
#if 1							
							fprintf(flog_search, "[%s] [%s] [%d] msg is == %s \n", __TIME__, __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
#endif							
							fflush(flog_search);
#endif
							java_recombind_pic_search_msg2_client(value);
							trans_msg2_another_thread(JAVA_RETURN_PIC_SEARCH_RESULT, &value, lpClientThreadId,&g_common_str_java,NULL);
						}
						break;
					case JSONMSGCODE_JAVA_START_SERVER_ITEMS://change server ip in run time,not process temp
						break;
					case JSONMSGCODE_SERVER_ALARM_VIDEO_SAVA:
						if (!java_alarm_video_sava_reply(value)) {
							fprintf(flog, "[%s] [%d] %s  \n", __FUNCTION__, __LINE__, "alarm video save fail");
						}
						break;
					default:
						printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, "run to unknown");
						fprintf(flog_java,"[%s] [%d] %s nJsonMsgCode == %d \n", __FUNCTION__, __LINE__, "run to unknown", nJsonMsgCode);
						//fflush(flog);
						break;
					}//end of switch
					fflush(flog);
				}
				zmq_msg_close(&msg_recv);
			}
	

		if (PeekMessage(&java_msg, 0, 0, 0, NULL))
		{
			memset(&java_msg, 0, sizeof(java_msg));
			ret = GetMessage(&java_msg, NULL, 0, 0);
			if (ret == -1) {
				fprintf(flog_java, "[%s] [%d]  GetMessage failed error ==== %d \n", __FUNCTION__, __LINE__, GetLastError());
				continue;
			}
			char * pInfo = (char *)java_msg.wParam;
			char * lParam = (char *)java_msg.lParam;

			value.clear();
			sendValue.clear();
			dataSend.clear();
			
			int alive_msg = (int)JAVA_ALIVE_CHECK;

			if ((int)java_msg.message <= WM_USER) {
				continue;
			}

			if (!parse_queuemsg2_json(pInfo, reader, value, java_msg, &alive_msg))//parse pInfo2 Json fail,just parse userful string
			{
			//	continue;
			}
			else
			{
#ifdef JAVA_VALUE_PRINT			
			//	if (java_msg.message != WM_TIMER) {
					fprintf(flog_java, "java worker queue java_msg============== %s", pInfo);
					fflush(flog_java);
			//	}
#endif
			}

			string str_tell;

			switch (java_msg.message)
			{
			case CLIENT_CONNECTTEST:
			case PC_CONFIRM_USERNAME_AND_PWD:				
#ifdef CLIENT_LINK_TEST
			//	printf("[%s] [%d] %s ===== %s\n", __FUNCTION__, __LINE__, "java socket send data to java", (char *)java_msg.wParam);
				fprintf(flog_client,"[%s] [%d] %s ===== %s\n", __FUNCTION__, __LINE__, "java socket send data to java", (char *)java_msg.wParam);
				fflush(flog_client);
#endif
				sendMsg.SendOuterMsg((char *)java_msg.wParam);				
				break;
			case SERVER_GETCAMERA_INFO:
#ifdef JAVA_VALUE_PRINT		
				fprintf(flog_client_tree, "[%s] [%d] SERVER_GETCAMERA_INFO ===== %d \n", __FUNCTION__, __LINE__, SERVER_GETCAMERA_INFO);
				fflush(flog_client_tree);
#endif
				sendMsg.SendOuterMsg((char *)java_msg.wParam);				
				break;
			case FACE_TELL_RESULT:
				sendMsg.SendOuterMsg((char *)java_msg.wParam);				
				break;
			case FACEDETECTION_ONEPICTURE://特征值返回给java
				SetMsgHead(&sendValue, &value, JSONMSGTYPE_RESPONSE, JSONMSGCODE_FACEIDF_FACEFEATURES_OUT);
				sendValue["msgBody"] = value["msgBody"];
				sendMsg.SendOuterMsg((char *)sendValue.toStyledString().data());				
				break;
			case FACEDETECTION_PICTUREDIR_IN://list 接收数据，直到number个数量//入库、人脸检测、人脸识别初始化接口.json
#ifdef PICS_IN_LIB_PRINT
			//	printf("[%s] [%d] %s ===== %s\n", __FUNCTION__, __LINE__, "java socket send data to java**********************", (char *)java_msg.wParam);
				fprintf(flog_pic_in,"[%s] [%d] %s ===== %s\n", __FUNCTION__, __LINE__, "java socket send data to java", (char *)java_msg.wParam);
				fflush(flog_pic_in);
#endif
				if (sendMsg.add_back_pic_num() == sendMsg.get_pic_num()) {//java_face_lib_and_others.json 99
					sendMsg.backpiclist_append(&value["msgBody"]["dataSend"]);
					str_tell = value["msgBody"]["dataSend"]["FeaDir"].asCString();
					sendValue.clear();
					SetMsgHead(&sendValue, &value, JSONMSGTYPE_RESPONSE, JSONMSGCODE_FACEDETECTION_PICTUREDIR_IN);
					dataSend["Number"] = sendMsg.get_pic_num();
					sendMsg.get_backpiclist(&PictureList);					
					dataSend["PictureList"] = PictureList;			
					msgBody["dataSend"] = dataSend;
					sendValue["msgBody"] = msgBody;
					
					for (int i=0;i<sendValue["msgBody"]["dataSend"]["PictureList"].size();i++)
					{
						str_tell = sendValue["msgBody"]["dataSend"]["PictureList"][i]["FeaDir"].asCString();
						sendValue["msgBody"]["dataSend"]["PictureList"][i]["FeaDir"] = Json::Value(str_tell.c_str());
						str_tell = sendValue["msgBody"]["dataSend"]["PictureList"][i]["PicturePathDir"].asCString();
						sendValue["msgBody"]["dataSend"]["PictureList"][i]["PicturePathDir"] = Json::Value(str_tell.c_str());
					}
#ifdef PICS_IN_LIB_PRINT
					fprintf(flog_pic_in, "[%s] [%d] %s ===== %s\n", __FUNCTION__, __LINE__, "sendValue === ", (char *)sendValue.toStyledString().data());
				//	printf( "[%s] [%d] %s ===== %s\n", __FUNCTION__, __LINE__, "sendValue === ", (char *)sendValue.toStyledString().data());
#endif
					str_tell = sendValue.toStyledString().data();
					sendMsg.SendOuterMsg((char*)(sendValue.toStyledString().data()));
					sendMsg.delete_backpiclist();
				}
				else {
#ifdef PICS_IN_LIB_PRINT
					fprintf(flog_pic_in, "[%s] [%d] sendMsg.get_pic_num() == %d nPicCount %d ===== %s\n", __FUNCTION__, __LINE__, sendMsg.get_pic_num());
#endif
					sendMsg.backpiclist_append(&value["msgBody"]["dataSend"]);
					sendMsg.get_backpiclist(&tmp);
#ifdef PICS_IN_LIB_PRINT					
				//	printf("[%s] [%d] tmp == %s \n", __FUNCTION__, __LINE__, (char *)tmp.toStyledString().data());
					fprintf(flog_pic_in, "[%s] [%d] tmp == %s \n", __FUNCTION__, __LINE__, (char *)tmp.toStyledString().data());
#endif
				}				
				break;
			case TRACKSERVER_PERSON_LOST:
				sendMsg.SendOuterMsg((char *)java_msg.wParam);				
				break;
			case TRACESERVER_PERSON_INTRACKING:
				sendMsg.SendOuterMsg((char *)java_msg.wParam);				
				break;
			case TRACESERVER_REQUEST_TRACKSERVER_IP:
#ifdef JAVA_VALUE_PRINT
				fprintf(flog_track_init, "[%s] [%d] java thread recv msg TRACESERVER_REQUEST_TRACKSERVER_IP ======= %d\n", __FUNCTION__, __LINE__, TRACESERVER_REQUEST_TRACKSERVER_IP);
				fflush(flog_track_init);
#endif 
				sendMsg.SendOuterMsg((char *)java_msg.wParam);				
				break;
			case CLIENT_SEARCH_CAPTURE_LOOK_BACK://client query cap 20011
				sendMsg.SendOuterMsg((char *)java_msg.wParam);				
				break;
			case CLIENT_SEARCH_ALARAM_LOOK_BACK://client query alarm list 20016
				sendMsg.SendOuterMsg((char *)java_msg.wParam);
				break;
			case CLIENT_SEARCH_ALARAM_DETAIL://client query alarm detail 
				sendMsg.SendOuterMsg((char *)java_msg.wParam);
				break;
			case CLIENT_SEARCH_RECORD_LOOK_BACK://client query record detail 
				sendMsg.SendOuterMsg((char *)java_msg.wParam);
				break;
			case CLIENT_LOG_RECORD://JSONMSGCODE_CLIENT_LOG_RECORD://client log do record
				sendMsg.SendOuterMsg((char *)java_msg.wParam);
				break;
			case RTSP_CAMERA_STATUS_REPLY:
				sendMsg.SendOuterMsg((char *)java_msg.wParam);
				break;
			case SERVER_STATUS_PUSH:
				sendMsg.SendOuterMsg((char *)java_msg.wParam);
				break;
			case FACETH_REPLY2_JAVAREQ_CHANGE_FACELIB:
				sendMsg.SendOuterMsg((char *)java_msg.wParam);
				break;
			case RTSP_CHANGE_FACEDETECTION_CAMERA:
				java_change_camera_result_collect(requestid_pre,value,responseValue,&cameras);
				break;
			case FACEDT_CHANGE_FACEDETECTION_CAMERA:
#ifdef PIC_WITH_PIC_PRINT									
				fprintf(flog_search, "[%s] [%s] [%d] responseValue == %s \n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)java_msg.wParam);
				fflush(flog_search);
#endif
				java_change_camera_result_collect(requestid_pre, value, responseValue,&cameras);
				break;
			case TRACK_CHANGE_FACEDETECTION_CAMERA:
				java_change_camera_result_collect(requestid_pre, value, responseValue,&cameras);
				break;
			case FACEDT_CONNECT_REPLY:
				if (g_cluster_start_items["msgHead"]["requestID"] == value["msgHead"]["requestID"]) {
					java_start_services_result_collect(responseValue, value, sendMsg);
				}
				break;
			case FACE_TELL_CONNECT_REPLY:
				if (g_cluster_start_items["msgHead"]["requestID"] == value["msgHead"]["requestID"]) {
					java_start_services_result_collect(responseValue, value, sendMsg);
				}
			case RTSP_CONNECT_REPLY:
				if (g_cluster_start_items["msgHead"]["requestID"] == value["msgHead"]["requestID"]) {
					java_start_services_result_collect(responseValue, value, sendMsg);
				}
				break;
			case FACETELL_CHANGE_CAMERA_STATEG:
				sendMsg.SendOuterMsg((char *)java_msg.wParam);
				break;
			case RTSP_CHANGE_STATEG:
				sendMsg.SendOuterMsg((char *)java_msg.wParam);
				break;
			case FACEDT_CHANGE_STATEG:
				sendMsg.SendOuterMsg((char *)java_msg.wParam);
				break;
			case TRACK_CHANGE_CAMERA_STATEG:
				sendMsg.SendOuterMsg((char *)java_msg.wParam);
				break;
			case PIC_SEARCH_RESULT2_JAVA:

#ifdef PIC_WITH_PIC_PRINT									
				fprintf(flog_search, "g_face_search_index ==== %d [%s] [%s] [%d] java recv searhc al java_msg == %s \n", (g_face_search_index++), get_system_misecond_time(),__FUNCTION__, __LINE__, (char *)(char *)java_msg.wParam);
				fflush(flog_search);
#endif

				sendMsg.SendOuterMsg((char *)java_msg.wParam);
				break;
			case RTSP_CHANGE_CAMERA:
				sendMsg.SendOuterMsg((char *)java_msg.wParam);
				break;
			case JAVA_ALIVE_CHECK:
				nMsgType = JAVA_RETURN_IAM_ALIVE;
				g_java_strAliveCheck = (char *)malloc(strlen(FACETELL_STILL_ALIVE) + 10);
				memset(g_java_strAliveCheck, 0, strlen(FACETELL_STILL_ALIVE) + 10);
				strcpy(g_java_strAliveCheck, FACETELL_STILL_ALIVE);
				if (lpMonitorThreadId != 0) {
					ret = PostThreadMessage(lpMonitorThreadId, nMsgType, (WPARAM)g_java_strAliveCheck, NULL);
					if (!postthreadmessage_check(ret)) {
						wparam_free(&g_java_strAliveCheck);
					}
				}
				break;
			case RTSP_ALARM_VIDEO_SAVE:
				java_alarm_video_sava2_db(value);
#if 1
				fprintf(flog_media, "[%s] [%d]  send video msg 2 java	 ===== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
				fflush(flog_media);
#endif 
				sendMsg.SendOuterMsg((char *)value.toStyledString().data());
				break;
			default:
				fprintf(flog_java, "[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
				break;
			}
			
			switch (java_msg.message)//free pInfo case
			{
			case CLIENT_CONNECTTEST:
			case PC_CONFIRM_USERNAME_AND_PWD:
			case SERVER_GETCAMERA_INFO:
			case FACE_TELL_RESULT:
			case FACEDETECTION_ONEPICTURE://特征值返回给java
			case FACEDETECTION_PICTUREDIR_IN://list 接收数据，直到number个数量//入库、人脸检测、人脸识别初始化接口.json
			case TRACKSERVER_PERSON_LOST:
			case TRACESERVER_PERSON_INTRACKING:
			case TRACESERVER_REQUEST_TRACKSERVER_IP:
			case CLIENT_SEARCH_CAPTURE_LOOK_BACK://client query cap 20011
			case CLIENT_SEARCH_ALARAM_LOOK_BACK://client query alarm list 20016
			case CLIENT_SEARCH_ALARAM_DETAIL://client query alarm detail 
			case CLIENT_SEARCH_RECORD_LOOK_BACK://client query record detail 
			case CLIENT_LOG_RECORD://JSONMSGCODE_CLIENT_LOG_RECORD://client log do record
			case RTSP_CAMERA_STATUS_REPLY:
			
			case FACETH_REPLY2_JAVAREQ_CHANGE_FACELIB:
			case RTSP_CHANGE_FACEDETECTION_CAMERA:
			case FACEDT_CHANGE_FACEDETECTION_CAMERA:
			case TRACK_CHANGE_FACEDETECTION_CAMERA:
			case FACEDT_CONNECT_REPLY:
			case FACE_TELL_CONNECT_REPLY:
			case RTSP_CONNECT_REPLY:
			case FACETELL_CHANGE_CAMERA_STATEG:
			case RTSP_CHANGE_STATEG:
			case FACEDT_CHANGE_STATEG:
			case TRACK_CHANGE_CAMERA_STATEG:
			case PIC_SEARCH_RESULT2_JAVA:
			case RTSP_CHANGE_CAMERA:
			case RTSP_ALARM_VIDEO_SAVE:
				wparam_free(&pInfo);
				break;
			case SERVER_STATUS_PUSH:
				wparam_free(&pInfo);
				break;
			case JAVA_ALIVE_CHECK:
				wparam_free(&pInfo);
			default:
				break;
			}
			fflush(flog);
			
		}



		}
		fprintf(flog_java, "[%s] [%s] [%s] [%d] java worker end timepoint \n", __DATE__, __TIME__, __FUNCTION__, __LINE__);
		fflush(flog_java);
	
	return 0;
}
bool java_alarm_video_sava2_db(Json::Value &value)
{
	//string str = value.toStyledString();
	if (value["msgHead"].isMember("msgCode")) {
		value["msgHead"]["msgCode"] = JSONMSGCODE_SERVER_ALARM_VIDEO_SAVA;
	}
	if (value["msgHead"].isMember("msgType")) {
		value["msgHead"]["msgType"] = JSONMSGTYPE_REQUEST;
	}
	if (value["msgBody"].isMember("state")) {
		value["msgBody"].removeMember("state");
	}	
	value["msgBody"]["data"]["videoURL"] = TransUnicodeStringtoUTF8(value["msgBody"]["data"]["videoURL"]);
	//string str1 = value.toStyledString();
	return true;
}
bool java_alarm_video_sava_reply(Json::Value &value)
{
	int code = 0;
	char str[10] = { 0 };
	if (value["msgBody"].isMember("state")) {
		if (value["msgBody"]["state"].isMember("code")) {
			strcpy(str, value["msgBody"]["state"].toStyledString().data());
			code = atoi(str);
			if (code != 0) {
				return false;
			}
		}
	}
	return true;
}