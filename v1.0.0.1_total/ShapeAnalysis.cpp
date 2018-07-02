#include "stdafx.h"
#include "ShapeAnalysis.h"
#include "common.h"
#include <fstream>
bool shape_rep2req(Json::Value *val)
{
	point_empty_check(val);
	if ((*val)["msgBody"].isNull())
		return false;
	if ((*val)["msgBody"]["dataSend"].isNull())
		return false;
	/*if ((*val)["msgBody"]["dataRecv"].isNull())
		return false;*/

	Json::Value Time;
	int code = 0;
	(*val)["msgBody"]["dataRequest"] = (*val)["msgBody"]["dataRecv"];
	(*val)["msgBody"]["dataPush"] = (*val)["msgBody"]["dataSend"];
	(*val)["msgBody"].removeMember("dataRecv");
	(*val)["msgBody"].removeMember("dataSend");
	Time["sec"] = 0;//后期修改
	Time["usec"] = 0;//后期修改
	//(*val)["msgBody"]["dataPush"]["personID"] = (*val)["msgBody"][]
	(*val)["msgBody"]["dataPush"]["Time"] = Time;
	code = (*val)["msgBody"]["dataPush"]["code"].asInt();

	if (code != 0) 
	{
		(*val)["msgBody"]["dataPush"]["HumenROI"] = {};
		//(*val)["msgBody"]["dataPush"]["HumenROI"] = (*val)["msgBody"]["dataPush"]["FaceRect"];
		(*val)["msgBody"]["dataPush"]["HumenROI"]["X"] = (*val)["msgBody"]["dataPush"]["FaceRect"]["x"];
		(*val)["msgBody"]["dataPush"]["HumenROI"]["Y"] = (*val)["msgBody"]["dataPush"]["FaceRect"]["y"];
		(*val)["msgBody"]["dataPush"]["HumenROI"]["Width"] = (*val)["msgBody"]["dataPush"]["FaceRect"]["width"];
		(*val)["msgBody"]["dataPush"]["HumenROI"]["Height"] = (*val)["msgBody"]["dataPush"]["FaceRect"]["height"];
	}
	else
	{
			(*val)["msgBody"]["dataPush"]["HumenROI"] = {};
			//(*val)["msgBody"]["dataPush"]["HumenROI"] = (*val)["msgBody"]["dataPush"]["FaceRect"];
			(*val)["msgBody"]["dataPush"]["HumenROI"]["X"] = (*val)["msgBody"]["dataPush"]["HumanShapeRectInfo"]["x"];
			(*val)["msgBody"]["dataPush"]["HumenROI"]["Y"] = (*val)["msgBody"]["dataPush"]["HumanShapeRectInfo"]["y"];
			(*val)["msgBody"]["dataPush"]["HumenROI"]["Width"] = (*val)["msgBody"]["dataPush"]["HumanShapeRectInfo"]["width"];
			(*val)["msgBody"]["dataPush"]["HumenROI"]["Height"] = (*val)["msgBody"]["dataPush"]["HumanShapeRectInfo"]["height"];
		
     }
#if 0
	(*val)["msgBody"]["dataPush"]["camId"] = (*val)["msgBody"]["dataPush"]["camID"];
	(*val)["msgBody"]["dataPush"]["CameraFrameAddr"] = (*val)["msgBody"]["dataPush"]["SrcPicturePathDir"];
	(*val)["msgBody"]["dataPush"].removeMember("camID");
#else
	(*val)["msgBody"]["dataPush"]["camId"] = (*val)["msgBody"]["dataPush"]["camId"];// 205;
	(*val)["msgBody"]["dataPush"]["CameraFrameAddr"] = (*val)["msgBody"]["dataPush"]["CameraFrameAddr"];
#endif


	(*val)["msgBody"]["dataPush"]["SrcPhotoUrl"] = (*val)["msgBody"]["dataPush"]["SrcPicturePathDir"];
	(*val)["msgBody"]["dataPush"]["capPhotoUrl"] = (*val)["msgBody"]["dataPush"]["RoiPicturePathDir"];
	(*val)["msgBody"]["dataPush"].removeMember("SrcPicturePathDir");
	(*val)["msgBody"]["dataPush"].removeMember("RoiPicturePathDir");
//	(*val)["msgBody"]["dataPush"].removeMember("FaceRect");
	(*val)["msgBody"]["dataPush"].removeMember("HumanShapeRectInfo");
	return true;
}
DWORD  WINAPI shape_worker(void * context)
{
	point_empty_check(context);

	MSG msg;
	Json::Value value;
	Json::Value sendValue, msgHead;
	Json::Reader reader;
	int nJsonMsgCode;
	zmq_msg_t msg_recv;
	char *strThreadMsg = NULL;
	std::ifstream in;
	char *strTmp = NULL;
	

	int ret = 0;
	int len = 0;
	int nMsgType = 0;
	int malloc_len_pre = 0;
	int code = 0;
	DealerModeSendRecv dealer(context, shape_sk);

	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

	//第一次给Shape发送数据建立连接
	in.open("server_send_shape_connect_req.json", std::ios::binary);
	json_open_check(&in);

	json_parse2_value(&in, &value);

	int len_value = strlen((char *)value.toStyledString().data());
	
	
//	len = zmq_send(shape_sk, "", 0, ZMQ_SNDMORE);
	char empty[] = { "" };
	s_sendmore(shape_sk, empty);
	
//	len = zmq_send(shape_sk, (char *)value.toStyledString().data(), len_value, 0);
	s_send(shape_sk, (char *)value.toStyledString().data());
#ifdef 	SHAPE_STEP_PRINT
	fprintf(flog, "[%s] [%d] shape send connect req ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
	//fflush(flog);
#endif


	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

	zmq_pollitem_t items[] = { { shape_sk,0,ZMQ_POLLIN,0 } };

	while (true) {
		while (true)
		{
			zmq_poll(items, 1, zmq_poll_timeout);
			if (items[0].revents & ZMQ_POLLIN) {
				value.clear();
				sendValue.clear();
				msgHead.clear();

			zmq_msg_init(&msg_recv);
			
			zmq_msg_recv(&msg_recv, shape_sk, 0);
			ret = zmq_msg_recv(&msg_recv, shape_sk, 0);
#ifdef SHAPE_STEP_PRINT				
			fprintf(flog,"[%s] [%d] receive msg content ==== %s\n", __FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
			fflush(flog);
#endif
			if (ret&&reader.parse((char *)zmq_msg_data(&msg_recv), value)) {
				nJsonMsgCode = value["msgHead"]["msgCode"].asInt();
				code = value["msgBody"]["dataSend"]["code"].asInt();
#ifdef SHAPE_STEP_PRINT
				fprintf(flog,"[%s] [%d] nJsonMsgCode ==== %d\n", __FUNCTION__, __LINE__, nJsonMsgCode);
				//fflush(flog);
			
#endif
				switch (nJsonMsgCode)
				{
				case JSONMSGCODE_HUMANSHAPE_INIT_OUT://shape 初始化结果返回
					if (code == JSONMSGCODE_RESPONSE_OK || code == JSONMSGCODE_HUMANSHAPE_INIT_OUT) {
#ifdef SHAPE_STEP_PRINT
						fprintf(flog,"[%s] [%d] recv msg ==== %s\n", __FUNCTION__, __LINE__, "shape connect already build");
						//fflush(flog);						
#endif
					}
					break;
//				case JSONMSGCODE_FACE_TELL_RESULT://
//#ifdef SHAPE_STEP_PRINT
//					printf("[%s] [%d] recv msg ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
//#endif
//					
//					break;
				case JSONMSGCODE_HUMANSHAPE_ALARM_OUT://人型算法返回人型消息
#ifdef PERSON_TRACK_PRINT
					fprintf(flog_track,"[%s] [%s] [%d] shape recv shape result ==== %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
#endif
					SetMsgHead(&sendValue, &value, JSONMSGTYPE_REQUEST, JSONMSGCODE_HUMANSHAPE_ONEHUMANSHAPE_IN);
					sendValue["msgBody"] = value["msgBody"];
					//sendValue["msgHead"] = msgHead;
					nMsgType = SHAPE_MSG2_TRACK;
					shape_rep2req(&sendValue);
					postthreadmessage_mem_malloc(&strTmp, &sendValue);
					if (lpTrackThreadId != 0) {
						ret = PostThreadMessage(lpTrackThreadId, nMsgType, (WPARAM)strTmp, NULL);
						if (!postthreadmessage_check(ret)) {
							fprintf(flog_track, "[%s] [%s] [%d] PostThreadMessage failed\n", get_system_misecond_time(), __FUNCTION__, __LINE__);
							//fflush(flog);
							wparam_free(&strTmp);
						}
					}
					else {
						fprintf(flog, "[%s] [%s] [%d] error lpTrackThreadId ==== %d\n", get_system_misecond_time(), __FUNCTION__, __LINE__, lpTrackThreadId);
						//fflush(flog);
					}

					break;
				case JSONMSGCODE_ALLHUMANSHAPE_ALLHUMANSHAPE_OUT:
				//	SetMsgHead(&sendValue, &value, JSONMSGTYPE_RESPONSE, JSONMSGCODE_HUMANSHAPE_ALLHUMANSHAPE_IN);
					value["msgHead"]["msgCode"] = JSONMSGCODE_HUMANSHAPE_ALLHUMANSHAPE_IN;
					nMsgType = SHAPE_PERSON_RETELL_REC2_TRACK;
					postthreadmessage_mem_malloc(&strTmp, &value);
					ret = PostThreadMessage(lpTrackThreadId, nMsgType, (WPARAM)strTmp, NULL);
					if (!postthreadmessage_check(ret)) {
						fprintf(flog, "[%s] [%s] [%d] %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, "postthreadmessage_check failed");
						//fflush(flog);
						wparam_free(&strTmp);
					}
					break;
				default:
					break;
				}
				fflush(flog_track);
				zmq_msg_close(&msg_recv);
			}
		}
		if (PeekMessage(&msg, 0, 0, 0, NULL))
		{
			memset(&msg, 0, sizeof(msg));
			ret = GetMessage(&msg, NULL, 0, 0);
			if (ret == -1) {
				fprintf(flog, "[%s][%s] [%d]  GetMessage failed error ==== %d \n", get_system_misecond_time(), __FUNCTION__, __LINE__, GetLastError());
				//fflush(flog);
				continue;
			}
			
			char * pInfo = (char *)msg.wParam;
			char *lParam = (char *)msg.lParam;
#ifdef SHAPE_VALUE_PRINT
			fprintf(flog,"[%s] [%d] shape worker receive queue msg === %s\n", __FUNCTION__, __LINE__, pInfo);
			fflush(flog);
#endif
			value.clear();

			if (msg.message <= WM_USER) {
				continue;
			}

			if (!parse_queuemsg2_json(pInfo, reader, value, msg, NULL))//parse pInfo2 Json fail
			{
			//	continue;
			}
			else
			{
#ifdef SHAPE_VALUE_PRINT			
			//	if (msg.message > WM_USER) {
					fprintf(flog_shape, "shape worker queue msg============== %s", pInfo);
					fflush(flog);
			//	}
#endif
			}

			switch (msg.message)
			{
			case FACE_TELL_RESULT://
#ifdef PERSON_TRACK_PRINT
				value["msgBody"]["dataSend"]["msgString"] = "i love";
				fprintf(flog_track, "[%s] [%s] [%d] send face tell msg to shape ==== %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)msg.wParam);
				
#endif			
				dealer.SendDealerMsg((char *)msg.wParam);
				break;
			case TRACESERVER_PERSON_RETELL:
				dealer.SendDealerMsg((char *)msg.wParam);
				break;
			default:
				fprintf(flog, "[%s] [%s] [%d] run into ==== %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, "unkown type");
				//fflush(flog);
				break;
			}			
			fflush(flog_track);

			switch (msg.message)
			{
			case FACE_TELL_RESULT://
			case TRACESERVER_PERSON_RETELL:
				wparam_free(&pInfo);
				break;
			default:
				break;
			}
			}
		}
		fprintf(flog, "[%s]  [%s] [%d] shape worker end timepoint \n", get_system_misecond_time(), __FUNCTION__, __LINE__);
		fflush(flog);
	}
	return 0;
}
