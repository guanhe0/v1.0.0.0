#include "stdafx.h"
#include "rtspServer.h"
#include "common.h"
#include <fstream>

//int value define
static int rtsp_len_pre = 0;
char *rtsp_str_tmp = NULL;
static Json::Value *rtsp_request_value;
static Json::Value media_java_change_camera;
bool rtsp_trans_msg2_out(int nMsgType,Json::Value *val,DWORD ThreadId);//rtsp_trans_msg2_out(nMsgType,&value, ThreadId);

bool rtsp_trans_msg2_out(int nMsgType, Json::Value *val, DWORD ThreadId)
{
	if (nMsgType <= WM_USER || val == NULL || ThreadId <= 0) {
		fprintf(flog, "[%s] [%d]   %s\n", __FUNCTION__, __LINE__, "run to exception");
		//fflush(flog);
	}

	int ret = 0;
	postthreadmessage_mem_malloc(&rtsp_str_tmp, val);

	ret = PostThreadMessage(ThreadId, nMsgType, (WPARAM)(rtsp_str_tmp), NULL);
	if (!postthreadmessage_check(ret)) {
		fprintf(flog, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
		//fflush(flog);
		wparam_free(&rtsp_str_tmp);
		return false;
	}
	else {
#ifdef 	RTSP_VALUE_PRINT
		fprintf(flog, "[%s] [%d]   rtsp send msg out ========= %s\n", __FUNCTION__, __LINE__, (char *)rtsp_str_tmp);
		//fflush(flog);
#endif
	}
	return true;
}
bool rtsp_change_java_change_camera_req(Json::Value &src,Json::Value &dst)
{
	Json::Value msgHead, msgBody, dataRequest, dataPush, cameraList, cameralist_child;
	Json::Value media_camera_list, cameraInfo, cluster, cluster_child, meadiaRtspAddr;
	int i,len,j,leng, clusterType = 0, TimeDelay1 = 0, TimeDelay2 = 0;
	msgHead = src["msgHead"];
	msgHead["msgCode"] = JSONMSGCODE_MEDIA_CHANGE_CAMERA;
	dst["msgHead"] = msgHead;
	dataRequest["code"] = 0;
	dataPush["cameraChangeType"] = src["msgBody"]["dataPush"]["cameraChangeType"];
	cameraList = src["msgBody"]["dataPush"]["cameraList"];
	len = cameraList.size();
	for (i = 0; i < len; i++) {//media_camera_list.append
		cameralist_child = cameraList[i];
		cameraInfo = cameralist_child["cameraInfo"];
		cluster = cameralist_child["cluster"];
		leng = cluster.size();
		TimeDelay1 = 0, TimeDelay2 = 0;
		for (j = 0; j < leng; j++) {
			cluster_child = cluster[j];
			clusterType = cluster_child["clusterType"].asInt();
			if (clusterType == RTSP_SERVER) {
				TimeDelay1 = cluster_child["strategy"]["TimeDelay1"].asInt();
				TimeDelay2 = cluster_child["strategy"]["TimeDelay2"].asInt();
				meadiaRtspAddr = cluster_child["strategy"]["meadiaRtspAddr"];
				break;
			}
		}
	//	if (j > leng) { return false; }
		//camName
		cameraInfo["camName"] = cameraInfo["cameraName"];
		cameraInfo.removeMember("cameraName");
		//camID
		cameraInfo["camID"] = cameraInfo["cameraID"];
		cameraInfo.removeMember("cameraID");
		//camPort
		cameraInfo["camPort"] = cameraInfo["cameraPort"];
		cameraInfo.removeMember("cameraPort");
		//camIP
		cameraInfo["camIP"] = cameraInfo["cameraIP"];
		cameraInfo.removeMember("cameraIP");
		//mediaPort
		//cameraInfo["mediaPort"] = cameraInfo["mediaPort"];
		//cameraInfo.removeMember("mediaPort");
		//camType
		cameraInfo["camType"] = cameraInfo["cameraType"];
		cameraInfo.removeMember("cameraType");
		//streamType
		cameraInfo["streamType"] = cameraInfo["streamType"];
		cameraInfo.removeMember("streamType");
		//subType
		cameraInfo["subType"] = cameraInfo["subType"];
		cameraInfo.removeMember("subType");
		//TimeDelay1
		cameraInfo["TimeDelay1"] = TimeDelay1;		
		//TimeDelay2
		cameraInfo["TimeDelay2"] = TimeDelay2;
		//rtspAddr
		cameraInfo["rtspAddr"] = meadiaRtspAddr.isNull() ? "" : meadiaRtspAddr;

		media_camera_list.append(cameraInfo);
	}
	dataPush["cameraList"] = media_camera_list;
	msgBody["dataPush"] = dataPush;
	msgBody["dataRequest"] = dataRequest;
	dst["msgBody"] = msgBody;

	printf("[%s] [%d] send change camera to media ==== %s\n", __FUNCTION__, __LINE__, (char *)dst.toStyledString().data());
	fprintf(flog, "[%s] [%d] send change camera to media ==== %s\n", __FUNCTION__, __LINE__, (char *)dst.toStyledString().data());
	//fflush(flog);

	return true;
}
bool rtsp_video_sava_chinese_combina(Json::Value &value)
{
	if (value["msgBody"].isMember("data")) {
		if (value["msgBody"]["data"].isMember("videoURL")) {
			string url = value["msgBody"]["data"]["videoURL"].asCString();
			value["msgBody"]["data"]["videoURL"] = Json::Value(url.c_str());
		}
	}
	return true;
}
DWORD  WINAPI rtsp_worker(void * context)
{
	int sendTime = 1;//COUNT SEND MSG NUMBER TO RTSP 


	if (context == NULL) {
#ifdef RTSP_STEP_PRINT
		fprintf(flog,"[%s] [%d]   %s\n", __FUNCTION__, __LINE__,"context ==== NULL");
		//fflush(flog);
#endif
		return -1;
	}
	MSG msg;
	Json::Value value, camera_list,connect_req,dataPush, dataRequest, msgBody, msgHead, serverErrList_0;
	Json::Value request;
	Json::Reader reader;
	Json::Value dataSend;
	char identity[IDENTITY_STR_LEN] = { 0 };
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

	int ret = 0,len = 0, nJsonMsgCode = 0,replyCode = 0,str_len = 0, msgType = 0;
	char *rtsp_str_tmp = NULL;
	int nMsgType = 0;
	int code = 0;
	std::ifstream in,in_cam;
	DealerModeSendRecv messenger(context, rtsp_sk);

	//judge camera_lsit wheter exist
	in_cam.open("g_camera_list.json", std::ios::in);
	if (in_cam.is_open()) {//exist local
		if (!reader.parse(in_cam, camera_list)) {
			printf("[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "parse g_camera_list.json failed");
			fprintf(flog, "[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "parse g_camera_list.json failed");
			//fflush(flog);
			return false;
		}
		else {
			SetMsgHead(&connect_req, NULL, JSONMSGTYPE_REQUEST, JSONMSGCODE_SERVER_RTSP_CONNECT_REQ);
			dataRequest["code"] = 0;
			dataPush["cameraList"] = camera_list;
			msgBody["dataPush"] = dataPush;
			msgBody["dataRequest"] = dataRequest;
		//	connect_req["msgHead"] = msgHead;
			connect_req["msgBody"] = msgBody;
		}
	}
	else {
		in_cam.close();
		in_cam.open("server_rtsp_connect_req.json", std::ios::binary);
		if (in_cam.is_open()) {//exist local
			if (!reader.parse(in_cam, connect_req)) {
				printf("[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "parse g_camera_list.json failed");
				fprintf(flog, "[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "parse g_camera_list.json failed");
				//fflush(flog);
				return false;
			}
		}
	}
//////////////////
	if (connect_req.size()) {

	//	zmq_send(rtsp_sk, "", 0, ZMQ_SNDMORE);
		char empty[] = { "" };
	//	s_sendmore(rtsp_sk, empty);
		
		len = strlen((char *)connect_req.toStyledString().data());
		rtsp_str_tmp = (char *)malloc(len + 1);
		memset(rtsp_str_tmp, 0, len + 1);
		memcpy(rtsp_str_tmp, (char*)connect_req.toStyledString().data(), len);
	//	zmq_send(rtsp_sk, rtsp_str_tmp, len, 0);
	//	s_send(rtsp_sk, rtsp_str_tmp);
		free(rtsp_str_tmp);
	}
//////////////////

#ifdef RTSP_VALUE_PRINT
	fprintf(flog, "[%s] [%d]  len == %d send rtsp req content ==== %s\n", __FUNCTION__, __LINE__,len, rtsp_str_tmp);
	//fflush(flog);
#endif
	Sleep(100);
//	free(rtsp_str_tmp);
	rtsp_str_tmp = NULL;

	while (true) {
		

		zmq_pollitem_t items[] = { { rtsp_sk,0,ZMQ_POLLIN,0 } };
			zmq_poll(items, 1, zmq_poll_timeout);
			if (items[0].revents & ZMQ_POLLIN) {
				zmq_msg_t msg_recv;
				zmq_msg_init(&msg_recv);
				value.clear();
				zmq_msg_recv(&msg_recv, rtsp_sk, 0);
				len = zmq_msg_recv(&msg_recv, rtsp_sk, 0);
#ifdef RTSP_VALUE_PRINT
				fprintf(flog, "[%s] [%d]  rtsp worker recv msg ========= %s\n", __FUNCTION__, __LINE__,(char *)zmq_msg_data(&msg_recv));
				fflush(flog);
#endif 
				str_len = strlen((char *)zmq_msg_data(&msg_recv));
				if (str_len <= 0) {
					continue;
				}
				if (len&&reader.parse((char *)zmq_msg_data(&msg_recv), value)) {
					nJsonMsgCode = value["msgHead"]["msgCode"].asInt();
					replyCode = value["msgBody"]["dataSend"]["code"].asInt();
					msgType = value["msgHead"]["msgType"].asInt();
					switch (nJsonMsgCode)
					{
					case JSONMSGCODE_RTSP_CONNECT_REQ_REPLY://60000

#ifdef RTSP_VALUE_PRINT
						fprintf(flog,"[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "rtsp connect already connect");
						//fflush(flog);
#endif
						//serverErrList_0["clusterID"] = RTSP_SERVER;
						//serverErrList_0["severList"] = "";
						trans_msg2_another_thread(RTSP_CONNECT_REPLY, &serverErrList_0, lpJavaThreadId,&g_common_str_rtsp,NULL);
					break;
					case JSONMSGCODE_RTSP_CAMERA_STATUS_REPLY:
#ifdef RTSP_VALUE_PRINT
						fprintf(flog, "[%s] [%d]  rtsp recv msg ===== %s\n", __FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
						//fflush(flog);
#endif
						value["msgHead"]["msgCode"] = rtsp2java[JSONMSGCODE_RTSP_CAMERA_STATUS_REPLY];
						nMsgType = RTSP_CAMERA_STATUS_REPLY;
						rtsp_trans_msg2_out(nMsgType,&value, lpJavaThreadId);

						break;
					case JSONMSGCODE_JAVA_CHANGE_CAMERA:
#ifdef RTSP_VALUE_PRINT
						fprintf(flog_change_camera,"[%s] [%d]  rtsp recv msg ===== %s\n", __FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
						fflush(flog_change_camera);
#endif
						if (msgType == JSONMSGTYPE_RESPONSE)
						{
							msgBody = value["msgBody"];
							dataSend = msgBody["dataSend"];
							code = dataSend["code"].asInt();
						//	printf("[%s] [%d]  code == %d\n", __FUNCTION__, __LINE__, code);
							if (code == JSONMSGCODE_JAVA_CHANGE_CAMERA_SUCCESS) {//send to lpFaceDtThreadId
							//	rtsp_trans_msg2_out(RTSP_CHANGE_FACEDETECTION_CAMERA, &media_java_change_camera, lpFaceDtThreadId);
							
								//send change camera msg to facedt and track thread
//								rtsp_trans_msg2_out(JAVA_CHANGE_CAMERA, &media_java_change_camera, lpTrackThreadId);
//								rtsp_trans_msg2_out(JAVA_CHANGE_CAMERA, &media_java_change_camera, lpFaceDtThreadId);
							}
							else
							{//change camre error
								rtsp_trans_msg2_out(RTSP_CHANGE_CAMERA, &value, lpJavaThreadId);
							}
						}
						break;
					case JSONMSGCODE_JAVA_CHANGE_STATEG:
						if (msgType == JSONMSGTYPE_RESPONSE)
						{
							rtsp_trans_msg2_out(RTSP_CHANGE_STATEG, &value, lpJavaThreadId);
						}
						break;
					case JSONMSGCODE_RTSP_ALARM_VIDEO_SAVE:
						if (msgType == JSONMSGTYPE_RESPONSE)
						{
							rtsp_video_sava_chinese_combina(value);
#if 1
							fprintf(flog_media, "[%s] [%s] [%d]  rtsp recv msg ===== %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
							fflush(flog_media);
#endif 
							trans_msg2_another_thread(RTSP_ALARM_VIDEO_SAVE, &value, lpJavaThreadId, &rtsp_str_tmp,NULL);
						}
						break;
					default:
						fprintf(flog, "[%s] [%s] [%d] run into ==== %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, "unkown type");
						//fflush(flog);
						break;
					}
					fflush(flog);

					
				}
				zmq_msg_close(&msg_recv);
			}
	//	}
#ifdef RTSP_STEP_PRINT
	//	printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, "rtsp  woker run\n");
		//fflush(flog);
	//	Sleep(2000);
#endif
		if (PeekMessage(&msg, 0, 0, 0, NULL))
		{
			memset(&msg, 0, sizeof(msg));
			ret = GetMessage(&msg, NULL, 0, 0);
			if (ret == -1) {
				fprintf(flog, "[%s] [%d]  GetMessage failed error ==== %d \n", __FUNCTION__, __LINE__, GetLastError());
				//fflush(flog);
				continue;
			}
			char * pInfo = (char *)msg.wParam;
			char *lParam = (char *)msg.lParam;

			value.clear();

			if (msg.message <= WM_USER) {
				continue;
			}

			if (!parse_queuemsg2_json(pInfo, reader, value, msg, NULL))//parse pInfo2 Json fail
			{
				//continue;
			}
			else
			{
#ifdef RTSP_VALUE_PRINT			
			//	if (msg.message > WM_USER) {
					fprintf(flog, "rtsp worker queue msg============== %s", pInfo);
					fflush(flog);
			//	}
#endif
			}

			switch (msg.message)
			{
			case CAMERA_INFO_UPDATE:
				break;
			case FACE_TELL_RESULT:
#ifdef RTSP_VALUE_PRINT
				fprintf(flog, "[%s] [%d]  send face tell msg to rtsp ==== %s\n", __FUNCTION__, __LINE__, pInfo);
				//fflush(flog);
#endif
				messenger.SendDealerMsg(pInfo);
				break;
			case TRACESERVER_PERSON_INTRACKING:
				messenger.SendDealerMsg(pInfo);
				#if 1
				SYSTEMTIME sts;
				::GetLocalTime(&sts);
				printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&----------track\n\n\n\n\n");
				//fprintf(flog, "system minu=%d,sec=%d,msec=%d ++++send message to rtsp media %d times++++\n",sts.wMinute,sts.wSecond,sts.wMilliseconds, sendTime++);
				//fflush(flog);
				printf("system minu=%d,sec=%d,msec=%d ++++send message to rtsp media %d times++++\n", sts.wMinute, sts.wSecond, sts.wMilliseconds, sendTime++);
				printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&----------track\n\n\n\n\n");
				#endif
				break;
			case TRACESERVER_MAKESUER_TARGET:
				messenger.SendDealerMsg(pInfo);
				break;
			case TRACESERVER_GOTOANOTHER_CAMERA:
				messenger.SendDealerMsg(pInfo);
				break;
			case CAMERA_STATUS_CHECK:
				messenger.SendDealerMsg(pInfo);
#ifdef GET_CAMERA_STATUS_FROM_JSON_FILE
				in.close();
				value.clear();
				in.open("camerastatus.json", std::ios::binary);
				if (!in.is_open())
					return -1;
				if (reader.parse(in, value)) {
					value["msgHead"]["msgCode"] = rtsp2java[JSONMSGCODE_RTSP_CAMERA_STATUS_REPLY];
					nMsgType = RTSP_CAMERA_STATUS_REPLY;
					rtsp_trans_msg2_out(nMsgType, &value, lpJavaThreadId);
				}
#endif 
				break;
			case JAVA_CHANGE_CAMERA:
				request.clear();
				if (!rtsp_change_java_change_camera_req(value, request)) {
					break;//no media message
				}

				messenger.SendDealerMsg((char *)request.toStyledString().data());
#ifdef RTSP_VALUE_PRINT
				printf("[%s] [%d] rtsp send java change camera msg ==== %s\n", __FUNCTION__, __LINE__, (char *)request.toStyledString().data());
				fprintf(flog_change_camera, "[%s] [%d] rtsp send java change camera msg ==== %s\n", __FUNCTION__, __LINE__, (char *)request.toStyledString().data());
				fflush(flog_change_camera);
#endif
				media_java_change_camera = value;
				break;
			case JAVA_CHANGE_STATEG:
#ifdef RTSP_VALUE_PRINT
				printf("[%s] [%d] rtsp send java change stateg msg ==== %s\n", __FUNCTION__, __LINE__, (char *)request.toStyledString().data());
				fprintf(flog, "[%s] [%d] rtsp send java change stateg msg ==== %s\n", __FUNCTION__, __LINE__, (char *)request.toStyledString().data());
				//fflush(flog);
#endif 
				messenger.SendDealerMsg((char *)value.toStyledString().data());
				break;
			default:
				fprintf(flog, "[%s] [%s] [%d] run into ==== %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, "unkown type");
				//fflush(flog);
				break;
			}

			switch (msg.message)
			{
			case CAMERA_INFO_UPDATE:
			case FACE_TELL_RESULT:
			case TRACESERVER_PERSON_INTRACKING:
			case TRACESERVER_MAKESUER_TARGET:
			case TRACESERVER_GOTOANOTHER_CAMERA:
			case CAMERA_STATUS_CHECK:
			case JAVA_CHANGE_CAMERA:
			case JAVA_CHANGE_STATEG:
				wparam_free(&pInfo);
				break;
			default:
				break;
			}
			
			fflush(flog);
			}
		}
		fprintf(flog, "[%s] [%s] [%d] rtsp worker end timepoint \n", get_system_misecond_time(), __FUNCTION__, __LINE__);
		fflush(flog);
	
	//if (rtsp_str_tmp != NULL) {
	//	free(rtsp_str_tmp);
	//}
}
