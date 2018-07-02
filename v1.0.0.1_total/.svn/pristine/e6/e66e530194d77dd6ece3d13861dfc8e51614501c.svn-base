#include "stdafx.h"
#include "pc_client.h"
#include "CameraManager.h"


//#include "zhelper.h"
char *g_client_strAliveCheck = NULL;
map<long,std::string>g_client_requestid_map;//requestid -> identi
//map<long, bool>g_client_requestid_finish_map;
map<string, long>g_client_ident_req_map;//ident -> requestid
map<long, long>g_client_requestid_time_map;//requestid -> time
PcClient::PcClient()
{
}
PcClient::~PcClient()
{
}

bool PcClient::CameraArrayAppend(Json::Value *dst, Json::Value *src)
{
	if (dst == NULL || src == NULL) {
		fprintf(flog_client,"[%s] [%s] [%d] run into ==== %s\n", __TIME__,__FUNCTION__, __LINE__, "exception");
		//fflush(flog_client);
		return false;
	}

	Json::Value val;
	val["camName"] = (*src)["camName"];
	val["camID"] = (*src)["camID"].asInt();
	val["mediaUserName"] = (*src)["mediaUserName"];
	val["mediaPassWord"] = (*src)["mediaPassWord"];
	val["mediaPort"] = (*src)["mediaPort"];
	val["mediaIP"] = (*src)["mediaIP"];
	val["camIP"] = (*src)["camIP"];
	val["camPort"] = (*src)["camPort"];
	val["camMapX"] = (*src)["camMapX"];
	val["camMapY"] = (*src)["camMapY"];
	val["camState"] = (*src)["camState"];
	val["streamType"] = (*src)["streamType"];
	val["inOrOut"] = (*src)["inOrOut"];
	val["camLng"] = (*src)["camLng"];
	val["camLat"] = (*src)["camLat"];
	if (dst != NULL) {
		(*dst).append(val);
	}
	return true;
}
bool PcClient::DistricArrayAppend(Json::Value *dst, Json::Value *src)
{
	if (dst == NULL || src == NULL) {
		fprintf(flog_client,"[%s] [%s] [%d] run into ==== %s\n", __TIME__,__FUNCTION__, __LINE__, "exception");
		//fflush(flog_client);
		return false;
	}

	Json::Value val;
	val["districtName"] = (*src)["districtName"];
	val["districtID"] = (*src)["districtID"].asInt();
	val["districtUrl"] = (*src)["districtUrl"];
	val["cameraArray"] = {};

	CameraArrayAppend(&(val["cameraArray"]),src);

	if (dst != NULL)
	{		
		(*dst).append(val);
	}
	return true;
}
bool PcClient::EaraArrayAppend(Json::Value *dst, Json::Value *src)
{
	if (dst == NULL || src == NULL) {
		fprintf(flog_client,"[%s] [%s] [%d] run into ==== %s\n", __TIME__,__FUNCTION__, __LINE__, "exception");
		//fflush(flog_client);
		return false;
	}

	Json::Value val;
	val["earaName"] = (*src)["earaName"];
	val["earaID"] = (*src)["earaID"].asInt();
	val["districArray"] = {};

	DistricArrayAppend(&(val["districArray"]), src);

	if (dst != NULL )
	{
		(*dst).append(val);
	}
	return true;
}

bool PcClient::CameraListToJson(Json::Value *dst, Json::Value *src,int len)//dst Ö¸ÏòdataSend,src ÎªÏà»úÁÐ±íÖ¸Õë
{
	if (len && dst != NULL && src != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			Json::Value val = (*src)[i];
			int earaID = val["earaID"].asInt();
			//string earaName = val["earaName"].asCString();
			//printf("earaName === %s\n", (char *)earaName.c_str());
			int earaArrayLen = 0;
			Json::Value *earaArrayList = &(*dst)["earaArray"];
			fprintf(flog_client,"earaArrayList Len0 ==  ===== %d\n", (*earaArrayList).size());
			//fflush(flog_client);
			if (!(*dst)["earaArray"].isNull())
			{
				earaArrayLen = (*dst)["earaArray"].size();
			}
			else
			{
				(*dst)["earaArray"] = {};
				earaArrayLen = 0;
			}
			int j = 0;
			for (j = 0; j < earaArrayLen; j++)
			{
				if ((*dst)["earaArray"][j].isNull())
					break;
#ifdef CLIENT_VALUE_PRINT
				fprintf(flog_client,"[%s] [%s] [%d]  i == %d earaID == %d\n", __TIME__,__FUNCTION__, __LINE__, j, earaID);
				//fflush(flog_client);
#endif
				if ((*dst)["earaArray"][j]["earaID"] == earaID)
				{
					break;
				}
			}

			if (j >= earaArrayLen)//²»ÔÚÆäÖÐ
			{			
				EaraArrayAppend(earaArrayList, &val);
				fprintf(flog_client,"earaArrayList  ==  ===== %s\n", (char *)(*earaArrayList).toStyledString().data());
				//fflush(flog_client);
			}
			else
			{
				int districArrayLen = 0;
				Json::Value * districArrayList = &(*dst)["earaArray"][j]["districArray"];
				if (!(*districArrayList).isNull())
				{
					districArrayLen = (*districArrayList).size();
				}
				else
				{
					(*dst)["earaArray"][j]["districArray"] = {};
					districArrayLen = 0;
				}
				int k = 0;
				int districID = val["districtID"].asInt();
				for (k = 0; k < districArrayLen; k++)
				{
#ifdef CLIENT_VALUE_PRINT
					fprintf(flog_client,"[%s] [%s] [%d] districArrayList === %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)(*districArrayList)[k]["districtID"].toStyledString().data());
					//fflush(flog_client);
#endif
					if (districID == (*districArrayList)[k]["districtID"].asInt())
						break;
				}
				if (k >= districArrayLen)//²»´æÔÚ
				{
					DistricArrayAppend(districArrayList, &val);
				}
				else
				{
					int cameraArrayLen = 0;
					Json::Value *cameraArrayList = &(*dst)["earaArray"][j]["districArray"][k]["cameraArray"];
					if (!(*cameraArrayList).isNull())
					{
						cameraArrayLen = (*cameraArrayList).size();
					}
					else
					{
						(*dst)["earaArray"][j]["districArray"][k]["cameraArray"] = {};
						cameraArrayLen = 0;
					}
					int m = 0;
					int camID = val["camID"].asInt();
					for (m = 0; m < cameraArrayLen; m++)
					{
						if (camID == (*cameraArrayList)[m]["camID"].asInt())
							break;
					}
					if (m >= cameraArrayLen)//²»´æÔÚ
					{						
						CameraArrayAppend(cameraArrayList, &val);
					}
					else
					{
						//do nothing
					}
				}
			}
		}
	}
	return true;
}


bool trans_query_msg2_java(Json::Value *val,Json::Value *request)
{
	if (val == NULL || request == NULL) {
		fprintf(flog_client, "[%s] [%s] [%d] %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)"val is NULL");
		//fflush(flog_client);
		return false;
	}

	int msgCode = (*val)["msgHead"]["msgCode"].asInt();//msgCode
	
	(*val)["msgHead"]["msgCode"] = JSONMSGCODE_SERVER_SEARCH_CAPTURE_LOOK_BACK;//20011 抓拍查询	

	(*request) = (*val);
	return true;
}
//bool pc_client_thread_init(Json::Value *  array[]) {
//	int len = 0,i;
//	GET_ARRAY_LEN(array, len);
//	for (i = 0; i < len; i++) {
//		(*array[i]).clear();
//	}
//}
bool client_combina_facesearch_msg(Json::Value &src, Json::Value &dst, void *param)
{
	Json::Value msgHead, msgBody, data, matchInfoArray,state;
	data = src["msgBody"]["data"];
	matchInfoArray = data["matchInfoArray"];	
	state = src["msgBody"]["state"];

	data["matchInfoArray"] = matchInfoArray;
	msgBody["data"] = data;
	msgBody["state"] = state;
	msgHead = src["msgHead"];
	msgHead["msgCode"] = JSONMSGCODE_CLIENT_GET_FACE_CHECKIN_N_BACK;
	dst["msgHead"] = msgHead;
	dst["msgBody"] = msgBody;
	for (int i = 0; i <dst["msgBody"]["data"]["matchInfoArray"].size(); i++)
	{
		if (!dst["msgBody"]["data"]["matchInfoArray"][i]["imgUrl"].isNull())
		{
			dst["msgBody"]["data"]["matchInfoArray"][i]["imgUrl"] =
				Gb2312ToUtf_8_EX(dst["msgBody"]["data"]["matchInfoArray"][i]["imgUrl"].asString());
		}
		if (!dst["msgBody"]["data"]["matchInfoArray"][i]["name"].isNull())
		{
			dst["msgBody"]["data"]["matchInfoArray"][i]["name"] =
				Gb2312ToUtf_8_EX(dst["msgBody"]["data"]["matchInfoArray"][i]["name"].asString());
		}
	}
#ifdef FACE_SEARCH_PRINT
	fprintf(flog_facesearch, "[%s] [%s] [%d] 2 client msg ===  %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)dst.toStyledString().data());
	fflush(flog_facesearch);
#endif 
	return true;
}
void CALLBACK client_timer_proc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)//server status query
{
	WaitForSingleObject(g_client_request_mutex, INFINITE);
	map<long, long>::iterator it;
	it = g_client_requestid_time_map.begin();
	while (it != g_client_requestid_time_map.end())
	{
		it->second += 1000;
	}
	ReleaseMutex(g_client_request_mutex);
}

bool client_update_request_time()
{
	UINT_PTR request_timer = -1;
	request_timer = SetTimer(NULL, 0, 1000, (TIMERPROC)client_timer_proc);
	if (request_timer == 0) {
		return false;
	}
	return true;
}
DWORD  WINAPI client_worker(void * context)
{

	MSG msg;	
	Json::Value array;
	Json::Value value,camera_list;
	Json::Reader reader;
	int nJsonMsgCode;
	Json::Value sendValue;
	Json::Value requestValue;
	Json::Value msgBody;
	Json::Value dataSend;
	char identity[IDENTITY_STR_LEN] = { 0 };
	zmq_msg_t msg_recv;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	
	FrontendMsg sendMsg(context, frontend);

	/*<-------------------------------cuijainhua--------------------------------------->*/
	CameraManager* pCamManager = CameraManager::GetCameraManager();
	/*<---------ok---------->*/

	PcClient Client;
	int ret = 0;
	int nMsgType = 0;
	char *strTmp = NULL;
	int len = 0;
	int malloc_len_pre = 0;
	long requestid = 0;
	bool send2_java = false;
	bool send2_track = false;
	bool send2_face_tell = false;
	std::ifstream in_w;
	char *str_face_tell = NULL;
	time_t now_secondes;

	printf("[%s] [%s] [%d] client worker start timepoint \n", __TIME__,__FUNCTION__, __LINE__);
	fprintf(flog_client, "[%s] [%s] [%d] client worker start timepoint \n",  __TIME__,__FUNCTION__, __LINE__);
	fflush(flog_client);
	zmq_pollitem_t items[] = { { frontend,0,ZMQ_POLLIN,0 } };
	g_client_requestid_map.clear();



	while (true) {
		while (true)
		{
			zmq_poll(items, 1, zmq_poll_timeout);			
			if (items[0].revents & ZMQ_POLLIN) {			

				sendMsg.RecvFrontendMsg(&msg_recv);
#ifdef CLIENT_VALUE_PRINT
				fprintf(flog_client,"[%s] [%s] [%d] client recv client msg ===  %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
				fflush(flog_client);
#endif

 
				
				if (reader.parse((char *)zmq_msg_data(&msg_recv), value)) {
					
					
					nJsonMsgCode = value["msgHead"]["msgCode"].asInt();					
#if 1

#else
					value["msgHead"]["requestID"] = rand() % 1000;
#endif
					requestid = value["msgHead"]["requestID"].asInt64();

/////////////////////////////////////request controll
#ifdef PC_REQUEST_CONTROLL
					WaitForSingleObject(g_client_request_mutex, INFINITE);
					string temp = sendMsg.get_identity();
					std::map<string, long>::iterator it;
					it = g_client_ident_req_map.find(temp);

					//if(g_client_ident_req_map.find(sendMsg.get_identity()))
					string identity = sendMsg.get_identity();
					time(&now_secondes);
					if (it == g_client_ident_req_map.end()) {//new identity						
						g_client_ident_req_map.insert(make_pair(identity, requestid));//ident - > requestid
						g_client_requestid_map.insert(make_pair(requestid, identity));//requestid -> ident
						g_client_requestid_time_map.insert(make_pair(requestid, now_secondes));//request -> time
					}
					else {
						int before = -1;
						int time = 0;
						before = g_client_ident_req_map[identity];//get pre request
						time = g_client_requestid_time_map[before];//get pre time
						if (now_secondes - time > CLIENT_REQUEST_TIMEOUT) {//请求滞留时间
							g_client_ident_req_map.erase(identity);
							g_client_requestid_map.erase(before);
							g_client_requestid_time_map.erase(before);

							g_client_ident_req_map[identity] = requestid;
							g_client_requestid_map[requestid] = identity;
							g_client_requestid_time_map[requestid] = 0;
						}
						else {//pre request not  finish，return reject
							Json::Value state,msgBody;
							value["msgHead"]["msgType"] = JSONMSGTYPE_RESPONSE;
							state["code"] = -1;
							state["msg"] = "before request unfinish";
							msgBody["state"] = state;
							value.removeMember("msgBody");
							value["msgBody"] = msgBody;
							
							sendMsg.SendOuterMsg((char *)value.toStyledString().data());
							continue;
						}
					}
					ReleaseMutex(g_client_request_mutex);
#endif
/////////////////////////////////////////////////end of request controll
#ifdef CLIENT_VALUE_PRINT
					//fprintf(flog_client,"[%s] [%s] [%d] nJsonMsgCode === %d\n", __TIME__,__FUNCTION__, __LINE__, nJsonMsgCode);
					////fflush(flog_client);
#endif
					requestValue.clear();
					msgBody.clear();
					requestid = value["msgHead"]["requestID"].asLargestUInt();
					WaitForSingleObject(g_client_msg_map_mutex, INFINITE);
					g_mapmsgclient.insert(make_pair(requestid,(char *)value.toStyledString().data()));//store client request value
					ReleaseMutex(g_client_msg_map_mutex);

					switch (nJsonMsgCode)
					{
					case JSONMSGCODE_CLIENT_CONNECTTEST:	
#ifdef CLIENT_MULTI_CLIENT_LOGIN	
						printf("recv msg ===== %s\n", (char *)value.toStyledString().data());
						sendMsg.SendOuterMsg((char *)value.toStyledString().data());
						break;
						
#endif
#ifdef CLIENT_LINK_TEST
						fprintf(flog_client,"[%s] [%s] [%d] nJsonMsgCode === %d\n", __TIME__,__FUNCTION__, __LINE__, nJsonMsgCode);
						fflush(flog_client);
#endif
						nMsgType = CLIENT_CONNECTTEST;							
						SetMsgHead(&requestValue, &value, JSONMSGTYPE_REQUEST, JSONMSGCODE_SERVER_GET_PC_CLIENT_VERSION);
						msgBody["dataRequest"] = {};
						msgBody["dataRequest"]["newClientVer"] = "";
						msgBody["dataRequest"]["newClientUrl"] = "";
						msgBody["dataPush"] = {};
#ifdef DEBUG
						msgBody["dataPush"]["msgString"] = "jsonmsgcode_server_get_pc_client_version";
#endif
						msgBody["dataPush"]["oldVersion"] = value["msgBody"]["dataPush"]["oldVersion"];
						requestValue["msgBody"] = msgBody;
						//Client.InitParam(&value, context, nJsonMsgCode);
						//Client.FillValue(&sendValue, &value);
						break;

					case JSONMSGCODE_CLIENT_GET_TREEINFO:
#ifdef CLIENT_VALUE_PRINT
						fprintf(flog_client_tree, "[%s] [%s] [%d] JSONMSGCODE_CLIENT_GET_TREEINFO === %d\n", __TIME__, __FUNCTION__, __LINE__, JSONMSGCODE_CLIENT_GET_TREEINFO);
						fflush(flog_client_tree);
#endif
						nMsgType = SERVER_GETCAMERA_INFO;
						SetMsgHead(&requestValue, &value, JSONMSGTYPE_REQUEST, JSONMSGCODE_SERVER_GETCAMERA_INFO);
						msgBody["dataRequest"] = "";
						msgBody["dataPush"] = {};
#ifdef DEBUG
						msgBody["dataPush"]["msgString"] = "server_get_camera_info";
#endif
						requestValue["msgBody"] = msgBody;
						break;
					case JSONMSGCODE_CLIENT_LOGIN:
						nMsgType = PC_CONFIRM_USERNAME_AND_PWD;
						SetMsgHead(&requestValue, &value, JSONMSGTYPE_REQUEST, JSONMSGCODE_SERVER_CONFIRM_USERNAME_AND_PWD);
						msgBody["dataRequest"] = {};
						msgBody["dataRequest"]["code"] = "";
						msgBody["dataPush"] = {};
						msgBody["dataPush"]["userName"] = value["msgBody"]["dataPush"]["userName"];
						msgBody["dataPush"]["passWord"] = value["msgBody"]["dataPush"]["passWord"];
						requestValue["msgBody"] = msgBody;
						break;							 
					case JSONMSGCODE_CLIENT_SEARCH_CAPTUER_LOOK_BACK:
						nMsgType = CLIENT_SEARCH_CAPTURE_LOOK_BACK;
					//	trans_query_msg2_java(&value,&requestValue);//value -> requestValue
						value["msgHead"]["msgCode"] = JSONMSGCODE_SERVER_SEARCH_CAPTURE_LOOK_BACK;//20011 抓拍查询	
						requestValue = value;
						break;
					case JSONMSGCODE_CLIENT_SEARCH_ALARAM_LOOK_BACK://报警列表查询
						nMsgType = CLIENT_SEARCH_ALARAM_LOOK_BACK;					
						value["msgHead"]["msgCode"] = JSONMSGCODE_SERVER_SEARCH_ALARAM_LOOK_BACK;//20016 
						requestValue = value;
						break;
					case JSONMSGCODE_CLIENT_SEARCH_ALARAM_DETAIL://单个人物报警的回放视频和追踪路径查询
						nMsgType = CLIENT_SEARCH_ALARAM_DETAIL;
						value["msgHead"]["msgCode"] = JSONMSGCODE_SERVER_SEARCH_ALARAM_DETAIL;//20019 
						requestValue = value;
						break;
					case JSONMSGCODE_CLIENT_SEARCH_RECORD_LOOK_BACK://日志查询
						nMsgType = CLIENT_SEARCH_RECORD_LOOK_BACK;
						value["msgHead"]["msgCode"] = JSONMSGCODE_SERVER_SEARCH_RECORD_LOOK_BACK;//20017 日志查询
						requestValue = value;
						break;
					case JSONMSGCODE_CLIENT_LOG_RECORD://日志存储
						nMsgType = CLIENT_LOG_RECORD;
						value["msgHead"]["msgCode"] = JSONMSGCODE_SERVER_LOG_RECORD;//20018
						requestValue = value;
						break;
					case JSONMSGCODE_CLIENT_TRACE_PERSON_CHANGE://track person detail req
						nMsgType = CLIENT_TRACK_PERSON_DETAIL;
						value["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_PAGACHANGE_GET_TRACK_DETAIL;//30603
						requestValue = value;
						break;
					case JSONMSGCODE_CLIENT_ALARM_DEAL://client deal with alarm msg
						nMsgType = CLIENT_ALARM_DEAL;
						value["msgHead"]["msgCode"] = JSONMSGCODE_TRACKDO_CLIENT_ALARM_DEAL;//30604
						requestValue = value;
						break;
					case JSONMSGCODE_CLIENT_GET_FACE_CHECKIN://1vs1
#ifdef CLIENT_ONE_VS_ONE
						fprintf(flog_one_vs_one, "[%s] [%s] [%d] JSONMSGCODE_CLIENT_GET_FACE_CHECKIN one vs one=== %d\n", get_system_misecond_time(), __FUNCTION__, __LINE__, JSONMSGCODE_CLIENT_GET_FACE_CHECKIN);
						fflush(flog_one_vs_one);
#endif
						nMsgType = CLIENT_GET_FACE_CHECKIN;
						trans_msg2_another_thread(nMsgType, &value, lpFaceDtThreadId,&g_common_str_client,NULL);
						break;
					case JSONMSGCODE_CLIENT_GET_USING_IMG_CHECKIN_IMG://search pic with pic
#ifdef PIC_WITH_PIC_PRINT
						fprintf(flog_search,"g_face_search_index ======= %d [%s] [%s] [%d] nJsonMsgCode === %d\n", (g_face_search_index++), get_system_misecond_time(),__FUNCTION__, __LINE__, JSONMSGCODE_CLIENT_GET_USING_IMG_CHECKIN_IMG);
						fflush(flog_search);
#endif 
						nMsgType = CLIENT_USING_IMG_CHECKIN_IMG;
						trans_msg2_another_thread(nMsgType, &value, lpFaceDtThreadId,&g_common_str_client,NULL);
						break;
					case JSONMSGCODE_CLIENT_GET_FACE_CHECKIN_N:
#ifdef FACE_SEARCH_PRINT
						fprintf(flog_facesearch, "[%s] [%s] [%d] nJsonMsgCode === %d\n", get_system_misecond_time(), __FUNCTION__, __LINE__, JSONMSGCODE_CLIENT_GET_FACE_CHECKIN_N);
						fflush(flog_facesearch);
#endif
						nMsgType = CLIENT_FACE_SEARCH;
						trans_msg2_another_thread(nMsgType, &value, lpFaceDtThreadId, &g_common_str_client, NULL);
						break;
					default:
						fprintf(flog_client,"UNKown type\n");
						//fflush(flog_client);
						break;
					}//end of switch
					
					switch (nMsgType)
					{
					case CLIENT_TRACK_PERSON_DETAIL://track person detail req

						send2_track = true;
						break;
					case CLIENT_LOG_RECORD:
					case CLIENT_SEARCH_RECORD_LOOK_BACK:
					case CLIENT_SEARCH_ALARAM_DETAIL:
					case CLIENT_SEARCH_ALARAM_LOOK_BACK:
					case CLIENT_SEARCH_CAPTURE_LOOK_BACK:
					case PC_CONFIRM_USERNAME_AND_PWD:
					case SERVER_GETCAMERA_INFO:
					case CLIENT_CONNECTTEST:
						send2_java = true;
						break;	
					case CLIENT_ALARM_DEAL:
						send2_face_tell = true;
						send2_track = true;
						send2_java = true;
						break;
					default:
						break;
					}
					if (lpJavaThreadId != 0 && send2_java) {
						send2_java = false;
						len = strlen((char *)requestValue.toStyledString().data());	
						strTmp = (char *)malloc(len + 100);
						memset(strTmp, 0, len + 100);
						
						strncpy(strTmp, (char *)requestValue.toStyledString().data(),len);
#ifdef STEP_PRINT
						fprintf(flog_client,"[%s] [%s] [%d]  client worker send msg to java thread == %s\n", __TIME__,__FUNCTION__, __LINE__, strTmp);
						//fflush(flog_client);
#endif
					//	ret = PostThreadMessage(lpJavaThreadId, nMsgType, (WPARAM)strTmp, NULL);
//#ifndef EMPTY_MSG_DEBUG
						if (lpJavaThreadId != 0) {
							ret = PostThreadMessage(lpJavaThreadId, nMsgType, (WPARAM)strTmp, NULL);
						}
						if (ret == 0) {
							wparam_free(&strTmp);
							fprintf(flog_client,"[%s] [%s] [%d] send msg failed\n", __TIME__,__FUNCTION__, __LINE__);
							//fflush(flog_client);
							getchar();
						}
//#endif
					}
					if (lpTrackThreadId != 0 && send2_track) {
						send2_track = false;
						postthreadmessage_mem_malloc(&strTmp, &requestValue);
						fprintf(flog_client, "[%s] [%s] [%d] client send msg to track ==== %s\n", __TIME__,__FUNCTION__, __LINE__, strTmp);
						//fflush(flog_client);
						strncpy(strTmp, (char *)requestValue.toStyledString().data(), len);
						ret = PostThreadMessage(lpTrackThreadId, nMsgType, (WPARAM)strTmp, NULL);
						if (ret == 0) {
							fprintf(flog_client, "[%s] [%s] [%d] send msg failed GetLastError == %d\n", __TIME__,__FUNCTION__, __LINE__, GetLastError());
							//fflush(flog_client);
							wparam_free(&strTmp);
						}
					}
					trans_msg2_another_thread(CLIENT_UPDATE_ALARM_SET, &requestValue, lpFaceTellThreadId, &str_face_tell, NULL);
				fflush(flog_client);

				}
				zmq_msg_close(&msg_recv);
			}

		
		
		if (PeekMessage(&msg, 0, 0, 0, NULL))
		{
			memset(&msg, 0, sizeof(msg));
			ret = GetMessage(&msg, NULL, 0, 0);
			if (ret == -1) {
				fprintf(flog_client, "[%s] [%s] [%d]  GetMessage failed error ==== %d \n", __TIME__,__FUNCTION__, __LINE__, GetLastError());				
				continue;
			}

			char * pInfo = (char *)msg.wParam;
			char *lParam = (char *)msg.lParam;
		
			value.clear();

			string identity;

			int alive_msg = CLIENT_ALIVE_CHECK;

			if (msg.message <= WM_USER) {
				continue;
			}

			if (!parse_queuemsg2_json(pInfo, reader, value, msg, &alive_msg))//parse pInfo2 Json fail
			{
			//	continue;
			}
			else
			{
#ifdef CLIENT_VALUE_PRINT	
			//	if (msg.message != WM_TIMER) {//WM_TIMER no pInfo
					fprintf(flog, "msg.message == %d client worker queue msg============== %s", msg.message, pInfo);
					fflush(flog);
			//	}
#endif
			}

			sendValue.clear();
			dataSend.clear();
			sendValue = {};
			sendValue["msgBody"] = {};


///////////////////////
			if (msg.message != CLIENT_ALIVE_CHECK && msg.message > WM_USER) {
				if (value["msgHead"]["requestID"].isString()) {
					requestid = atoi(value["msgHead"]["requestID"].asCString());
				}
				else {
					requestid = value["msgHead"]["requestID"].asInt64();
				}
#ifdef PC_REQUEST_CONTROLL
				if (!g_client_requestid_map[requestid].empty()) {//get identity
					string temp = (char *)g_client_requestid_map[requestid].data();
					sendMsg.set_identity((char *)temp.c_str());
					identity = g_client_requestid_map[requestid];//identity
					
					g_client_ident_req_map.erase(identity);//ident -> requestid
					g_client_requestid_time_map.erase(requestid);//requestid - > time
					g_client_requestid_map.erase(requestid);//删除key
					
				}
				else//not find the identity
				{
					continue;
				}
#endif
			}
//////////////////////


			string strCamlist = "";
			switch (msg.message)
			{
			case JAVA_SEND_CAMERA_INFO:
				/*<---------------------------------------cuijianhua---------------------------------------------------->*/
				strCamlist = "";
				strCamlist = pCamManager->GetCamList();
				sendMsg.SendOuterMsg((char *)strCamlist.data());
#ifdef CLIENT_VALUE_PRINT
				fprintf(flog_client_tree, "[%s] [%s] [%d] JAVA_SEND_CAMERA_INFO == %d send camera msg to client  ==  %s\n", __TIME__, __FUNCTION__, __LINE__, JAVA_SEND_CAMERA_INFO, (char *)strCamlist.c_str());
				fflush(flog_client_tree);
#endif
				/*<-------------------------------->*/
/*
				SetMsgHead(&sendValue, &value, JSONMSGTYPE_RESPONSE, JSONMSGCODE_CLIENT_SEND_TREEINFO);
				len = value["msgBody"]["dataSend"]["cameraList"].size();
				Client.CameraListToJson(&dataSend, &value["msgBody"]["dataSend"]["cameraList"], len);
				dataSend["code"] = JSONMSGCODE_CLIENT_SEND_TREEINFO;
				sendValue["msgBody"]["dataSend"] = dataSend;


				sendMsg.SendOuterMsg((char *)sendValue.toStyledString().data());*/
				break;
			
			case JAVA_SEND_USERNAME_NOT_EXIST:
				SetMsgHead(&sendValue, &value, JSONMSGTYPE_RESPONSE, JSONMSGCODE_CLIENT_LOGIN_ERR_USERNAME);
				sendValue["msgBody"]["dataSend"] = {};
				sendValue["msgBody"]["dataRecv"] = "";
				sendValue["msgBody"]["dataSend"]["code"] = JSONMSGCODE_CLIENT_LOGIN_ERR_USERNAME;
				sendMsg.SendOuterMsg((char *)sendValue.toStyledString().data());
				break;
			case JAVA_SEND_PASSWORD_ERROR:		
				SetMsgHead(&sendValue, &value, JSONMSGTYPE_RESPONSE, JSONMSGCODE_CLIENT_LOGIN_ERR_PASSWORD);
				sendValue["msgBody"]["dataSend"] = {};
				sendValue["msgBody"]["dataRecv"] = "";
				sendValue["msgBody"]["dataSend"]["code"] = JSONMSGCODE_CLIENT_LOGIN_ERR_PASSWORD;
				sendMsg.SendOuterMsg((char *)sendValue.toStyledString().data());				
				break;
			case SERVER_GET_PC_CLIENT_VERSION:
#ifdef CLIENT_LINK_TEST
				fprintf(flog_client, "[%s] [%s] [%d] client send msg to get camerainfo ==  %s\n", __TIME__, __FUNCTION__, __LINE__, sendValue.toStyledString().data());
				fflush(flog_client);
#endif 
				SetMsgHead(&sendValue, &value, JSONMSGTYPE_RESPONSE, JSONMSGCODE_CLIENT_CONNECTTEST);
				sendValue["msgBody"]["dataSend"] = {};
				sendValue["msgBody"]["dataRecv"] = "";
				sendValue["msgBody"]["dataSend"] = value["msgBody"]["dataSend"];
				sendValue["msgBody"]["dataSend"]["code"] = JSONMSGCODE_CLIENT_CONNECT_UPDATE;	
				
				sendMsg.SendOuterMsg((char *)sendValue.toStyledString().data());
				break;
			case JAVA_SEND_OK:
				SetMsgHead(&sendValue, &value, JSONMSGTYPE_RESPONSE, JSONMSGCODE_CLIENT_LOGIN);
				sendValue["msgBody"]["dataSend"] = {};
				sendValue["msgBody"]["dataRecv"] = JSONMSGCODE_CLIENT_LOGIN;
				sendValue["msgBody"]["dataSend"]["pubsubPort"] = nBroadCastPort;
				sendValue["msgBody"]["dataSend"]["code"] = value["msgBody"]["dataSend"]["code"];
				sendMsg.SendOuterMsg((char *)sendValue.toStyledString().data());
				break;
			case FACE_TELL_RESULT:
				SetMsgHead(&sendValue, &value, JSONMSGTYPE_NOTIFY, JSONMSGCODE_CLIENT_NEW_WARNINFO);
				sendValue["msgBody"]["dataSend"] = {};
				sendValue["msgBody"]["dataRecv"] = "";
				sendValue["msgBody"]["dataSend"]["code"] = JSONMSGCODE_CLIENT_NEW_WARNINFO;
				sendMsg.SendOuterMsg((char *)sendValue.toStyledString().data());
			
				break;
			case TRACKSERVER_PERSON_LOST:
				sendMsg.SendOuterMsg((char *)msg.wParam);
				break;
			case TRACESERVER_PERSON_INTRACKING:
#ifdef PERSON_TRACK_PRINT
				fprintf(flog_track, "[%s] [%s] [%d] send track sure msg to client ==  %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)msg.wParam);
				fflush(flog_track);
#endif 
				sendMsg.SendOuterMsg((char *)msg.wParam);
				break;
			case TRACESERVER_MAKESUER_TARGET:
				sendMsg.SendOuterMsg((char *)msg.wParam);
				break;
			case TRACESERVER_GOTOANOTHER_CAMERA:
#ifdef CLIENT_VALUE_PRINT
				fprintf(flog_client, "[%s] [%s] [%d] return change tap reslut to client ==== %s\n", __TIME__, __FUNCTION__, __LINE__, (char *)msg.wParam);
				fflush(flog_client);
#endif 
				sendMsg.SendOuterMsg((char *)msg.wParam);
				break;
			case JAVA_RETURN_CAPTURE_LOOK_RESULT://return cap query reslut to client
#ifdef CLIENT_VALUE_PRINT
				fprintf(flog_client, "[%s] [%s] [%d] return cap query reslut to client ==== %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)msg.wParam);
				//fflush(flog_client);
#endif // CLIENT_VALUE_PRINT
				sendMsg.SendOuterMsg((char *)msg.wParam);//need switch
				break;
			case JAVA_RETURN_ALARAM_LOOK_BACK:
#ifdef CLIENT_VALUE_PRINT
				fprintf(flog_client, "[%s] [%s] [%d] return alarm list query reslut to client ==== %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)msg.wParam);
				//fflush(flog_client);
#endif // CLIENT_VALUE_PRINT
				sendMsg.SendOuterMsg((char *)msg.wParam);//need switch
				break;
			case JAVA_RETURN_ALARAM_DETAIL:
#ifdef CLIENT_VALUE_PRINT
				fprintf(flog_client, "[%s] [%s] [%d] return alarm detail query reslut to client ==== %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)msg.wParam);
				//fflush(flog_client);
#endif // CLIENT_VALUE_PRINT
				sendMsg.SendOuterMsg((char *)msg.wParam);//need switch
				break;	
			case JAVA_RETURN_RECORD_LOOK_BACK:
#ifdef CLIENT_VALUE_PRINT
				fprintf(flog_client, "[%s] [%s] [%d] return record_look_back query reslut to client ==== %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)msg.wParam);
				//fflush(flog_client);
#endif // CLIENT_VALUE_PRINT
				sendMsg.SendOuterMsg((char *)msg.wParam);//need switch
				break;
			case JAVA_LOG_REDORD_RETURN:
#ifdef CLIENT_VALUE_PRINT
				fprintf(flog_client, "[%s] [%s] [%d] return log record reslut to client ==== %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)msg.wParam);
				//fflush(flog_client);
#endif // CLIENT_VALUE_PRINT
				sendMsg.SendOuterMsg((char *)msg.wParam);//need switch
				break;
			case FACETELL_GET_FACE_CHECKIN:
#ifdef CLIENT_ONE_VS_ONE
				fprintf(flog_one_vs_one, "[%s] [%s] [%d] return get_face_checkin reslut to client ==== %s\n", get_system_misecond_time(),__FUNCTION__, __LINE__, (char *)msg.wParam);
				fflush(flog_one_vs_one);
#endif 
				sendMsg.SendOuterMsg((char *)msg.wParam);
				break;
			case FACEDT_FACE_CHECKIN_FAILED:
#ifdef CLIENT_VALUE_PRINT
				fprintf(flog_client, "[%s] [%s] [%d] return get_face_checkin error reslut to client ==== %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)msg.wParam);
				//fflush(flog_client);
#endif 
				sendMsg.SendOuterMsg((char *)msg.wParam);
				break;
			case FACEDT_GET_USING_IMG_CHECKIN_IMG_FAILED:
#ifdef PIC_WITH_PIC_PRINT

				fprintf(flog_search, "[%s] [%s] [%d] return search pic  error reslut to client ==== %s\n", get_system_misecond_time(),__FUNCTION__, __LINE__, (char *)msg.wParam);
				fflush(flog_search);
#endif 
				sendMsg.SendOuterMsg((char *)msg.wParam);
				break;
			case FACETELL_SEARCH_PIC_FAILED:
#ifdef PIC_WITH_PIC_PRINT

				fprintf(flog_search, "g_face_search_index ==== %d [%s] [%s] [%d] return search pic  error reslut to client ==== %s\n", (g_face_search_index++), get_system_misecond_time(),__FUNCTION__, __LINE__, (char *)msg.wParam);
				fflush(flog_search);

#endif 
				sendMsg.SendOuterMsg((char *)msg.wParam);
				break;
			case JAVA_RETURN_PIC_SEARCH_RESULT:
#ifdef PIC_WITH_PIC_PRINT

				fprintf(flog_search, "g_face_search_index === %d [%s] [%s] [%d] return search pic  search reslut to client ==== %s\n",(g_face_search_index++), get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)msg.wParam);
				fflush(flog_search);
#endif 
				sendMsg.SendOuterMsg((char *)msg.wParam);
				break;
			case PIC_SEARCH_SEARCH_PIC_FAILED:
#ifdef CLIENT_VALUE_PRINT
				fprintf(flog_client, "[%s] [%s] [%d] return search pic  error reslut to client ==== %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)msg.wParam);
				//fflush(flog_client);
#endif 
				sendMsg.SendOuterMsg((char *)msg.wParam);
				break;
			case CLIENT_ALIVE_CHECK:
				nMsgType = CLIENT_RETURN_IAM_ALIVE;
				g_client_strAliveCheck = (char *)malloc(strlen(FACETELL_STILL_ALIVE) + 10);
				memset(g_client_strAliveCheck, 0, strlen(FACETELL_STILL_ALIVE) + 10);
				strcpy(g_client_strAliveCheck, FACETELL_STILL_ALIVE);
				if (lpMonitorThreadId != 0) {
					ret = PostThreadMessage(lpMonitorThreadId, nMsgType, (WPARAM)g_client_strAliveCheck, NULL);
					if (!postthreadmessage_check(ret)) {
						wparam_free(&g_client_strAliveCheck);
					}
				}
				break;
			case FACEDT_FACE_SEARCH_FAILED:
#ifdef FACE_SEARCH_PRINT
				fprintf(flog_facesearch, "[%s] [%s] [%d] return face search  error reslut to client ==== %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)msg.wParam);
				fflush(flog_facesearch);
#endif
				sendMsg.SendOuterMsg((char *)msg.wParam);
				break;
			case FACETELL_RETURN_FACE_SEARCH_RESULT:
#ifdef FACE_SEARCH_PRINT
				fprintf(flog_facesearch, "[%s] [%s] [%d] return face search   reslut to client ==== %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)msg.wParam);
				fflush(flog_facesearch);
#endif
				client_combina_facesearch_msg(value, sendValue, NULL);
				sendMsg.SendOuterMsg((char *)sendValue.toStyledString().data());
				break;
			default:
				fprintf(flog_client, "[%s] [%s] [%d] run into ==== %s\n", __TIME__,__FUNCTION__, __LINE__, "exception");
				//fflush(flog_client);
				break;
			}
			
			fflush(flog_client);
			switch (msg.message)
			{
			case JAVA_SEND_CAMERA_INFO:
			case JAVA_SEND_USERNAME_NOT_EXIST:
			case JAVA_SEND_PASSWORD_ERROR:
			case SERVER_GET_PC_CLIENT_VERSION:
			case JAVA_SEND_OK:
			case FACE_TELL_RESULT:
			case TRACKSERVER_PERSON_LOST:
			case TRACESERVER_PERSON_INTRACKING:
			case TRACESERVER_MAKESUER_TARGET:
			case TRACESERVER_GOTOANOTHER_CAMERA:
			case JAVA_RETURN_CAPTURE_LOOK_RESULT:
			case JAVA_RETURN_ALARAM_LOOK_BACK:
			case JAVA_RETURN_ALARAM_DETAIL:
			case JAVA_RETURN_RECORD_LOOK_BACK:
			case JAVA_LOG_REDORD_RETURN:
			case FACETELL_GET_FACE_CHECKIN:
			case FACEDT_FACE_CHECKIN_FAILED:
			case FACEDT_GET_USING_IMG_CHECKIN_IMG_FAILED:
			case FACETELL_SEARCH_PIC_FAILED:
			case JAVA_RETURN_PIC_SEARCH_RESULT:
			case PIC_SEARCH_SEARCH_PIC_FAILED:
			case FACETELL_RETURN_FACE_SEARCH_RESULT:
				wparam_free(&pInfo);
				break;
			case CLIENT_ALIVE_CHECK:
				wparam_free(&pInfo);
				break;
			default:
				break;
			}
		}		
	}	
	
		//	MessageBox(NULL, (LPCTSTR)"client_worker exit ", (LPCTSTR)"title", MB_OK);
	fprintf(flog_client,"[%s] [%s] [%d] client worker end timepoint \n",  __TIME__,__FUNCTION__, __LINE__);
	fflush(flog_client);
	}
	return 0;
}
