#include "stdafx.h"
#include "TrackServer.h"
using namespace std;
char *g_trackserver_stralivecheck = NULL;

TrackServer::TrackServer()
{
}


TrackServer::~TrackServer()
{
	if (mv_connetTrackSocketStruct.size() > 0)
	{
		for (auto it = mv_connetTrackSocketStruct.begin(); it != mv_connetTrackSocketStruct.end();)
		{
			if ((*it).s_connetTrackSocket) {
				delete (*it).s_connetTrackSocket;
			}
			it = mv_connetTrackSocketStruct.erase(it);
		}
	}
}

int TrackServer::mTrackServerRunForTrack(std::string & recvStr, std::string & sendStr)
{
	RecvFromTrackStruct recvFromTrackStruct;
	//对接收数据反序列化
	parseTrackStrToJson(recvStr, recvFromTrackStruct);
	//对接收消息做处理

	switch (recvFromTrackStruct.s_msgCode)
	{
	case JSONMSGCODE_TAILAFTER_RES_LOST_IN://丢失
		TrackServerDealLost(recvFromTrackStruct, sendStr);
		break;
	case JSONMSGCODE_TAILAFTER_RES_FOLLOWING_IN://跟踪
		TrackServerDealTailing(recvFromTrackStruct, sendStr);
		break;
	case JSONMSGCODE_TAILAFTER_RES_SWAPCAMERA_IN://出相机
		TrackServerDealOutFromCamera(recvFromTrackStruct, sendStr);
		break;
	case JSONMSGCODE_TAILAFTER_ALLHUMANSHAPE_IN://重识别
		TrackServerDealRegAgin(recvFromTrackStruct, sendStr);
		break;
	default:
		std::cout << "MsgCode Unknown!!!" << std::endl;
		break;
	}

	return 0;
}

int TrackServer::parseTrackStrToJson(std::string & recvStr, RecvFromTrackStruct & recvFromTrackStruct)
{

	Json::Reader		reader;
	Json::Value			valuerRoot;
	Json::Value			msgHead;
	Json::Value			msgBody;

	reader.parse(recvStr, valuerRoot);
	if (true == valuerRoot.isNull())
	{
		return -2;
	}
	msgHead = valuerRoot["msgHead"];//解析json头


	int msgCode = msgHead["msgCode"].asInt();
	msgBody = valuerRoot["msgBody"];//解析消息体
	recvFromTrackStruct.s_msgCode = msgCode;
	if (msgCode == JSONMSGCODE_TAILAFTER_RES_FOLLOWING_IN) //跟踪
	{
		recvFromTrackStruct.s_Tailing = 1;
		Json::Value dataPush = msgBody["dataPush"];

		recvFromTrackStruct.s_iPersonID = dataPush["personID"].asInt();
		//recvFromTrackStruct.s_iCamId = dataPush["camId"].asInt();//20180325 修改处理后CameraID为0问题
		recvFromTrackStruct.s_iCamId = dataPush["camId"].asInt();//camId is fact data
		Json::Value Time;
		Time = dataPush["Time"];
		recvFromTrackStruct.s_lTime.tv_sec = Time["sec"].asInt64();
		recvFromTrackStruct.s_lTime.tv_usec = Time["usec"].asInt64();
		Json::Value  HumenROI = dataPush["HumenROI"];
		recvFromTrackStruct.s_RHumenROI.s_ix = HumenROI["X"].asInt();
		recvFromTrackStruct.s_RHumenROI.s_iy = HumenROI["Y"].asInt();
		recvFromTrackStruct.s_RHumenROI.s_iwidth = HumenROI["Width"].asInt();
		recvFromTrackStruct.s_RHumenROI.s_ihight = HumenROI["Height"].asInt();
		//解析跟踪数据完成
	}
	if (msgCode == JSONMSGCODE_TAILAFTER_RES_LOST_IN) //丢失
	{
		recvFromTrackStruct.s_lost = 1;
		Json::Value dataPush = msgBody["dataPush"];

		recvFromTrackStruct.s_iPersonID = dataPush["personID"].asInt();
		recvFromTrackStruct.s_iCamId = dataPush["camId"].asInt();
		Json::Value Time;
		Time = dataPush["Time"];
		recvFromTrackStruct.s_lTime.tv_sec = Time["sec"].asInt64();
		recvFromTrackStruct.s_lTime.tv_usec = Time["usec"].asInt64();
		 //解析丢失数据完成
	}
	if (msgCode == JSONMSGCODE_TAILAFTER_ALLHUMANSHAPE_IN)//重识别
	{
		recvFromTrackStruct.s_regAgin = 1;
		Json::Value dataPush = msgBody["dataPush"];

		recvFromTrackStruct.s_iPersonID = dataPush["personID"].asInt();
		recvFromTrackStruct.s_iCamId = dataPush["camId"].asInt();
		Json::Value Time;
		Time = dataPush["Time"];
		recvFromTrackStruct.s_lTime.tv_sec = Time["sec"].asInt64();
		recvFromTrackStruct.s_lTime.tv_usec = Time["usec"].asInt64();
		recvFromTrackStruct.s_sTrackerSrcpictureFramName = dataPush["TrackerSrcpictureFramName"].asString();
		//解析重识别数据完成
	}
	if (msgCode == JSONMSGCODE_TAILAFTER_RES_SWAPCAMERA_IN)//出相机
	{
		recvFromTrackStruct.s_outFromCamera = 1;
		Json::Value dataPush = msgBody["dataPush"];

		recvFromTrackStruct.s_iPersonID = dataPush["personID"].asInt();
		recvFromTrackStruct.s_iCamId = dataPush["camId"].asInt();
		Json::Value Time;
		Time = dataPush["Time"];
		recvFromTrackStruct.s_lTime.tv_sec = Time["sec"].asInt64();
		recvFromTrackStruct.s_lTime.tv_usec = Time["usec"].asInt64();
		recvFromTrackStruct.s_iDirection = dataPush["direction"].asInt();
		//解析出相机数据完成
	}
	return 0;
}
int TrackServer::parseOthrerThreadStrToJson(std::string & recvStr, RecvFromServerStruct & recvFromServerStruct)
{
	
	Json::Reader		reader;
	Json::Value			valuerRoot;
	Json::Value			msgHead;
	Json::Value			msgBody;
	if (recvStr.size() < 0)
	{
		return -1;
	}
	reader.parse(recvStr, valuerRoot);
	if (true == valuerRoot.isNull())
	{
		return -2;
	}

	msgHead = valuerRoot["msgHead"];//解析json头
	int msgCode = msgHead["msgCode"].asInt();
	msgBody = valuerRoot["msgBody"];//解析消息体
	recvFromServerStruct.s_requestid = msgHead["requestID"].asInt64();

	if (msgCode == JSONMSGCODE_JAVASERVER_INIT_IN) //java线程数据
	{
		Json::Value dataPush = msgBody["dataPush"];
		Json::Value TailAddrArr;
		TailAddrArr = dataPush["TailAddrArr"];
	//	string strr = TailAddrArr.toStyledString();

		recvFromServerStruct.s_javaServer = 1;
		recvFromServerStruct.s_recvFromJavaServerStruct.InitTrackMsg = 1;
		int number = TailAddrArr.size();
		if (number > 0)
		{
			//camStruct tempCamStruct;
			for (int i = 0; i < number; i++) {
				InitTailServerStruct tempInitTailServerStruct;
				Json::Value TailAddr;
				TailAddr = TailAddrArr[i]["TailAddr"];
				tempInitTailServerStruct.TailName = TailAddr["TailName"].asString();///
				if (strcmp(tempInitTailServerStruct.TailName.c_str(), "track") != 0) {
					continue;
				}
				tempInitTailServerStruct.TailId = TailAddr["TailId"].asInt();///

				std::string connectSocketIp = TailAddr["TailIP"].asString();
				int connectSocketPort = TailAddr["TailPort"].asInt();
				std::string connectSocketAddr;
				char temBuf[50];

				sprintf(temBuf, "tcp://%s:%d", connectSocketIp.c_str(), connectSocketPort);
				string connectAddr(temBuf);
				tempInitTailServerStruct.s_connectSocketAddr = connectAddr;///
				g_InitTailServerStruct.push_back(tempInitTailServerStruct);
			}
		}
		else {
			return -1;
		}
		Json::Value CameraArr;
		CameraArr = dataPush["CameraArr"];
		if (int number = CameraArr.size() > 0)
		{
			for (int i = 0; i < number; i++)
			{
				camStruct tempCamStruct;
				tempCamStruct.s_camID = CameraArr[i]["CameraId"].asInt();
				tempCamStruct.s_zoneID = CameraArr[i]["zoneID"].asInt();
				Json::Value direction;
				direction = CameraArr[i];// ["direction"];
				tempCamStruct.s_UcamID = direction["ucamId"].asInt();
				tempCamStruct.s_DcamID = direction["dcamId"].asInt();
				tempCamStruct.s_LcamID = direction["lcamId"].asInt();
				tempCamStruct.s_RcamID = direction["rcamId"].asInt();
				tempCamStruct.s_FcamID = direction["fcamId"].asInt();
				tempCamStruct.s_BcamID = direction["bcamId"].asInt();
				g_vCamStruct.push_back(tempCamStruct);
			}
		}

	}
	else if (msgCode == JSONMSGCODE_HUMANSHAPE_ONEHUMANSHAPE_IN) //形体分析仪传入告警信息
	{
		Json::Value dataPush = msgBody["dataPush"];
		
		Json::Value Time;
		Time = dataPush["Time"];
		recvFromServerStruct.s_HumenShape = 1;
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.AlamMsg = 1;
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_timeval.tv_sec = Time["sec"].asInt64();
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_timeval.tv_usec = Time["usec"].asInt64();
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_personId = dataPush["personId"].asInt();
		Json::Value JsonHumenROI;
		JsonHumenROI = dataPush["HumenROI"];
		HumanROI tempHumanROI;
		tempHumanROI.s_ix = JsonHumenROI["X"].asInt();
		tempHumanROI.s_iy = JsonHumenROI["Y"].asInt();
		tempHumanROI.s_iwidth = JsonHumenROI["Width"].asInt();
		tempHumanROI.s_ihight = JsonHumenROI["Height"].asInt();
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_roi.push_back(tempHumanROI);
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_camID = dataPush["camId"].asInt();
		//recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_camID = 1;//由于消息里没有带暂时强赋值
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_camAddr = dataPush["CameraFrameAddr"].asString();
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_srcPictureDir = dataPush["SrcPhotoUrl"].asString();
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_roiPictureDir = dataPush["capPhotoUrl"].asString();

		Json::Value FaceRoi;
		FaceRoi = dataPush["FaceRect"];
		FaceROI faceROI;
		faceROI.height = FaceRoi["height"].asInt();
		faceROI.width = FaceRoi["width"].asInt();
		faceROI.x = FaceRoi["x"].asInt();
		faceROI.y = FaceRoi["y"].asInt();
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_face_roi.push_back(faceROI);
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_camID = dataPush["camId"].asInt();
	}
	else if (msgCode == JSONMSGCODE_HUMANSHAPE_ALLHUMANSHAPE_IN) //形体分析仪传入重识别信息
	{
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.AllHumanShape = 1;
		//Json::Value dataPush = msgBody["dataPush"];
		Json::Value dataPush = msgBody["dataSend"];
		Json::Value Time;
		Time = dataPush["Time"];
		recvFromServerStruct.s_HumenShape = 1;
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_timeval.tv_sec = Time["sec"].asInt64();
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_timeval.tv_usec = Time["usec"].asInt64();
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_personId = dataPush["personID"].asInt();
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_camID = dataPush["camId"].asInt();
		recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_TrackerSrcpictureFramName = dataPush["TrackerSrcpictureFramName"].asString();
		Json::Value HumenROIArr;
		//HumenROIArr = dataPush["HumenROIArr"];
		 HumenROIArr = dataPush["HumanShapeInfoArr"]; 
		if (int number = HumenROIArr.size() > 0)
		{
			for (int i = 0; i < number; i++)
			{
				HumanROI tempHumenROI;
				Json::Value HumenROI;
				//HumenROI = HumenROIArr[i]["HumenROI"];

				tempHumenROI.s_ix = HumenROIArr[i]["x"].asInt();
				tempHumenROI.s_iy = HumenROIArr[i]["y"].asInt();

				tempHumenROI.s_iwidth = HumenROIArr[i]["width"].asInt();
				tempHumenROI.s_ihight = HumenROIArr[i]["height"].asInt();
				recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_roi.push_back(tempHumenROI);
			}
		}

	}
	else if (msgCode == JSONMSGCODE_TRACKDO_CLIENT_ALARM_DEAL)//跟踪或误报
	{
		recvFromServerStruct.s_client = 1;
		recvFromServerStruct.s_recvFromClientServerStruct.s_TailPersonId = 1;
	
		Json::Value dataPush = msgBody["dataPush"];
		
		recvFromServerStruct.s_recvFromClientServerStruct.s_personId = dataPush["personID"].asInt();
		recvFromServerStruct.s_recvFromClientServerStruct.s_msgID = dataPush["msgID"].asInt();
		recvFromServerStruct.s_recvFromClientServerStruct.s_optStaff = dataPush["optStaff"].asString();
		recvFromServerStruct.s_recvFromClientServerStruct.s_optState = dataPush["optState"].asInt();
		switch (recvFromServerStruct.s_recvFromClientServerStruct.s_optState)
		{
		case UN_DEAL:
			break;
		case TRACING:
			recvFromServerStruct.s_recvFromClientServerStruct.s_TailPersonId = 1;
			break;
		case  END_TRACE:
			break;
		case  FALSE_ALARM:
			recvFromServerStruct.s_recvFromClientServerStruct.s_Misinformtion = 1;
			break;
		case LOST_TARGET :
			break;
		default:
			break;
		}
	}
	else if ( msgCode == JSONMSGCODE_CLIENT_PAGACHANGE_GET_TRACK_DETAIL) //换标签页
	{
		recvFromServerStruct.s_client = 1;
		recvFromServerStruct.s_recvFromClientServerStruct.s_ChangeTap = 1;
	//	recvFromServerStruct.s_recvFromClientServerStruct.s_Misinformtion = 1;
		Json::Value dataPush = msgBody["dataPush"];
	
		recvFromServerStruct.s_recvFromClientServerStruct.s_lastPersonID = dataPush["lastPersonID"].asInt();
		recvFromServerStruct.s_recvFromClientServerStruct.s_personId = dataPush["personID"].asInt();
		recvFromServerStruct.s_recvFromClientServerStruct.s_optStaff = dataPush["optStaff"].asString();
		recvFromServerStruct.s_recvFromClientServerStruct.s_optState = dataPush["optState"].asInt();
		

	}
	else if (msgCode == JSONMSGCODE_CLIENT_TRACE_PERSON_TERMINER)//结束跟踪
	{
		Json::Value dataPush = msgBody["dataPush"];
		recvFromServerStruct.s_recvFromClientServerStruct.s_personId = dataPush["personID"].asInt();
	}
	else if (msgCode == JSONMSGCODE_CLIENT_PAGACHANGE_GET_TRACK_DETAIL)//client query person track detail
	{
		recvFromServerStruct.s_client = 1;
		Json::Value dataPush = msgBody["dataPush"];
		recvFromServerStruct.s_recvFromClientServerStruct.s_lastPersonID = dataPush["lastPersonID"].asInt();
		recvFromServerStruct.s_recvFromClientServerStruct.s_personId = dataPush["personID"].asInt();
		recvFromServerStruct.s_recvFromClientServerStruct.s_ChangeTap = 1;
	}
	else if (msgCode == JSONMSGCODE_TRACKDO_CLIENT_ALARM_DEAL)//client click track button
	{
		recvFromServerStruct.s_client = 1;
		Json::Value dataPush = msgBody["dataPush"];
		
		recvFromServerStruct.s_recvFromClientServerStruct.s_personId = dataPush["personID"].asInt();
		recvFromServerStruct.s_recvFromClientServerStruct.s_optState = dataPush["optState"].asInt();
		recvFromServerStruct.s_recvFromClientServerStruct.s_optStaff = dataPush["s_optStaff"].asCString();
		recvFromServerStruct.s_recvFromClientServerStruct.s_msgID = dataPush["msgID"].asInt();
	}
	return 0;
}
//丢失
int TrackServer::TrackServerDealLost(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr)
{
	if (g_vclientTailPersonMsg.size()>0)
	{
		for (auto it = g_vclientTailPersonMsg.begin();it != g_vclientTailPersonMsg.end();it++)
		{
			if ((*it).m_personId== recvFromTrackStruct.s_iPersonID)
			{
				if (sendLostMsgToJavaThread(recvFromTrackStruct, sendStr))
				{

					char* sendJavaBuf = (char*)malloc(sendStr.size());
					memcpy(sendJavaBuf, sendStr.c_str(), sendStr.size());
					if (lpJavaThreadId != 0) {
						int ret = PostThreadMessage(lpJavaThreadId, TRACKSERVER_PERSON_LOST, (WPARAM)sendJavaBuf, NULL);
						if (!ret)
						{
							free(sendJavaBuf);
						}
					}
					else {
						fprintf(flog, "[%s] [%s] [%d] error lpJavaThreadId ==== %d\n", get_system_misecond_time(), __FUNCTION__, __LINE__, lpJavaThreadId);
						//std:://fflush(flog);
					}
				}
				if (sendLostMsgToClientThread(recvFromTrackStruct, sendStr))
				{
					char* sendClientBuf = (char*)malloc(sendStr.size());
					memcpy(sendClientBuf, sendStr.c_str(), sendStr.size());
					if (lpClientThreadId != 0) {
						int ret = PostThreadMessage(lpClientThreadId, TRACKSERVER_PERSON_LOST, (WPARAM)sendClientBuf, NULL);
						if (!ret)
						{
							free(sendClientBuf);
						}
					}
					else {
						fprintf(flog, "[%s] [%s] [%d] error lpClientThreadId ==== %d\n", get_system_misecond_time(), __FUNCTION__, __LINE__, lpClientThreadId);
						//std:://fflush(flog);
					}
				}
			}

			}
		}

		

	//发送数据给client java 后端
	//更新g_vPersonMsg状态
	if (g_vPersonMsg.size() < 0)
	{
		return -1;
	}
	else {
		std::unique_lock<std::mutex> locker(g_mutex);
		for (auto it = g_vPersonMsg.begin(); it != g_vPersonMsg.end();) {
			if ((*it).m_personId == recvFromTrackStruct.s_iPersonID)
			{
				it = g_vPersonMsg.erase(it);//从g_vPersonMsg把丢失的任务id剔除
				break;
			}

		}
	}

	return 0;
}
//重识别
int TrackServer::TrackServerDealRegAgin(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr)
{


	if (sendRegAginMsgToHumanShapeThread(recvFromTrackStruct, sendStr))
	{
		char* sendHumanShapetBuf = (char*)malloc(sendStr.size());
		memcpy(sendHumanShapetBuf, sendStr.c_str(), sendStr.size());
		if (lpShapeThreadId != 0 ) {
			int ret = PostThreadMessage(lpShapeThreadId, TRACESERVER_PERSON_RETELL, (WPARAM)sendHumanShapetBuf, NULL);
			if (!ret)
			{
				free(sendHumanShapetBuf);
			}
		}
		else {
			fprintf(flog, "[%s] [%s] [%d] error lpShapeThreadId ==== %d\n", get_system_misecond_time(), __FUNCTION__, __LINE__, lpShapeThreadId);
			//std:://fflush(flog);
		}
	}
	//发送消息给人脸识别重新识别

	//发送消息给人形分析仪
	return 0;
}
//跟踪
int TrackServer::TrackServerDealTailing(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr)
{
	static	int sendTime = 1;//COUNT SEND MSG NUMBER TO RTSP 
	if (g_vclientTailPersonMsg.size() > 0)
	{
		for (auto it = g_vclientTailPersonMsg.begin(); it != g_vclientTailPersonMsg.end(); it++)
		{
			if ((*it).m_personId == recvFromTrackStruct.s_iPersonID)
			{
				//bool isFound = false;
				if (g_vPersonMsg.size() < 0)
				{
					return -1;
				}
				else {
					std::unique_lock<std::mutex> locker(g_mutex);
					for (auto it = g_vPersonMsg.begin(); it != g_vPersonMsg.end();it++) {
						if ((*it).m_personId == recvFromTrackStruct.s_iPersonID)
						{
							if ((*it).mv_tailTrackStruct.size() > 0)
							{
								for (auto tailTrackStructIt = (*it).mv_tailTrackStruct.begin(); tailTrackStructIt != (*it).mv_tailTrackStruct.end(); tailTrackStructIt++)
								{
									if ((*tailTrackStructIt).s_CamId == recvFromTrackStruct.s_iCamId)
									{
										struct timeval subTrackTime;
										subTrackTime.tv_sec = recvFromTrackStruct.s_lTime.tv_sec;
										subTrackTime.tv_usec = recvFromTrackStruct.s_lTime.tv_usec;
										(*tailTrackStructIt).s_VTrackTimeValue.push_back(subTrackTime);
									}
								}
							}
							else {
								struct timeval subTrackTime;
								TailTrackStruct tempTailTrackStruct;
								tempTailTrackStruct.s_CamId = recvFromTrackStruct.s_iCamId;
								subTrackTime.tv_sec = recvFromTrackStruct.s_lTime.tv_sec;
								subTrackTime.tv_usec = recvFromTrackStruct.s_lTime.tv_usec;
								tempTailTrackStruct.s_VTrackTimeValue.push_back(subTrackTime);
								(*it).mv_tailTrackStruct.push_back(tempTailTrackStruct);//把最新的跟踪相机和时间压入到跟踪轨迹队列
							}
							
							//isFound = true;
							//break;
						}
					}
				}
				if (sendTrackingMsgToClientThread(recvFromTrackStruct, sendStr))
				{
					char* sendClientBuf = (char*)malloc(sendStr.size());
					memcpy(sendClientBuf, sendStr.c_str(), sendStr.size());
					if (lpClientThreadId != 0) {
#ifdef PERSON_TRACK_PRINT
						fprintf(flog_track, "[%s] [%s] [%d]  track send sure msg to client ==  %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)sendClientBuf);
						fflush(flog_track);
#endif 
						int ret = PostThreadMessage(lpClientThreadId, TRACESERVER_PERSON_INTRACKING, (WPARAM)sendClientBuf, NULL);
						if (!ret)
						{
							free(sendClientBuf);
						}
					}
					else {
						fprintf(flog, "[%s] [%d] error lpClientThreadId ==== %d\n", __FUNCTION__, __LINE__, lpClientThreadId);
					//	std:://fflush(flog);
					}
				}

				if (sendTrackingMsgToMediaThread(recvFromTrackStruct, sendStr))
				{
					char* sendNediaBuf = (char*)malloc(sendStr.size());
					memcpy(sendNediaBuf, sendStr.c_str(), sendStr.size());
#ifdef PERSON_TRACK_PRINT
					SYSTEMTIME sts;
					::GetLocalTime(&sts);
					fprintf(flog_track, "system minu=%d,sec=%d,msec=%d ++++send message to rtsp media %d times++++\n", sts.wMinute, sts.wSecond, sts.wMilliseconds, sendTime++);
					fprintf(flog_track, "[%s] [%s] [%d]  track send sure msg to media ==  %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)sendNediaBuf);
					fflush(flog_track);
#endif
					if (lpRtspThreadId != 0) {
						int ret = PostThreadMessage(lpRtspThreadId, TRACESERVER_PERSON_INTRACKING, (WPARAM)sendNediaBuf, NULL);
						if (!ret)
						{
							free(sendNediaBuf);
						}
					}
					else {
						fprintf(flog, "[%s] [%s] [%d] error lpRtspThreadId ==== %d\n", get_system_misecond_time(), __FUNCTION__, __LINE__, lpRtspThreadId);
						//std:://fflush(flog);
					}
				}
			}
		}
	}
	else{
		if (g_vPersonMsg.size() < 0)
		{
			return -1;
		}
		else {
			for (auto it = g_vPersonMsg.begin(); it != g_vPersonMsg.end();it++) {
				if ((*it).m_personId == recvFromTrackStruct.s_iPersonID)
				{
					TailTrackStruct tempTailTrackStruct;
					struct timeval subTrackTime;
					tempTailTrackStruct.s_CamId = recvFromTrackStruct.s_iCamId;
					subTrackTime.tv_sec = recvFromTrackStruct.s_lTime.tv_sec;
					subTrackTime.tv_usec = recvFromTrackStruct.s_lTime.tv_usec;
					tempTailTrackStruct.s_VTrackTimeValue.push_back(subTrackTime);

					(*it).mv_tailTrackStruct.push_back(tempTailTrackStruct);//把最新的跟踪相机和时间压入到跟踪轨迹队列
																			//isFound = true;
					break;
				}
			}
		}
		
	}
	
	if (sendTrackingMsgToJavaThread(recvFromTrackStruct, sendStr))
	{
		char* sendJavaBuf = (char*)malloc(sendStr.size());
		memcpy(sendJavaBuf, sendStr.c_str(), sendStr.size());
		if (lpJavaThreadId != 0) {
			int ret = PostThreadMessage(lpJavaThreadId, TRACESERVER_PERSON_INTRACKING, (WPARAM)sendJavaBuf, NULL);
			if (!ret)
			{
				free(sendJavaBuf);
			}
		}
		else {
			fprintf(flog, "[%s] [%s] [%d] error lpJavaThreadId ==== %d\n", get_system_misecond_time(), __FUNCTION__, __LINE__, lpJavaThreadId);
		//	std:://fflush(flog);
		}
	}
	return 0;
}
//出相机
int TrackServer::TrackServerDealOutFromCamera(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr)
{
	if (g_vCamStruct.size() < 0) {
		//相机矩阵为空
		return -1;
	}
	else {
		for (auto it = g_vCamStruct.begin(); it != g_vCamStruct.end(); it++)
		{
			if ((*it).s_camID == recvFromTrackStruct.s_iCamId)
			{
				switch (recvFromTrackStruct.s_iDirection)
				{
				case LCAMID:
					recvFromTrackStruct.s_camStruct.s_LcamID = 1;
					break;
				case RCAMID:
					recvFromTrackStruct.s_camStruct.s_LcamID = 2;
					break;
				case FCAMID:
					recvFromTrackStruct.s_camStruct.s_LcamID = 3;
					break;
				case BCAMID:
					recvFromTrackStruct.s_camStruct.s_LcamID = 4;
					break;
				case UCAMID:
					recvFromTrackStruct.s_camStruct.s_LcamID = 5;
					break;
				case DCAMID:
					recvFromTrackStruct.s_camStruct.s_LcamID = 6;
					break;
				default:
					recvFromTrackStruct.s_camStruct.s_LcamID = 0;
					break;

				}
			}
		}
	}
	//发送相机数据给跟踪服务器
	if (sendTOutCameraMsgToTrackServer(recvFromTrackStruct, sendStr))
	{
		if (g_vPersonMsg.size() > 0)
		{
			std::unique_lock<std::mutex> locker(g_mutex);
			for (auto it = g_vPersonMsg.begin(); it != g_vPersonMsg.end(); it++)
			{
				if (recvFromTrackStruct.s_iPersonID == (*it).m_personId)
				{
					s_sendmore(*(*it).m_connetTrackSocketStruct.s_connetTrackSocket, "");
					s_send(*(*it).m_connetTrackSocketStruct.s_connetTrackSocket, sendStr);
					break;
				}
			}
		}

	}

	return 0;
}

int TrackServer::TrackServerInit(std::string & InitMsgStr)
{
	return 0;
}

int TrackServer::mTrackServerRunForServer(std::string & recvStr, std::string & sendStr)
{
	RecvFromServerStruct recvFromServerStruct;
	parseOthrerThreadStrToJson(recvStr, recvFromServerStruct);//根据msgCode置标志位
	//parseServerStrToJson(recvStr, recvFromServerStruct);

	//if (recvFromServerStruct.s_Alarm)//告警线程
	//{
	//	TrackServerDealOutFromAlarm(recvFromServerStruct, sendStr);
	//}
	if (recvFromServerStruct.s_client)//客户端线程
	{
		TrackServerDealOutFromClient(recvFromServerStruct, sendStr);
	}
	//if (recvFromServerStruct.s_FramServer)//流媒体线程
	//{
	//	TrackServerDealOutFromFramServer(recvFromServerStruct, sendStr);
	//}
	if (recvFromServerStruct.s_HumenShape)//人形分析仪线程 完成
	{
		TrackServerDealOutFromHumenShape(recvFromServerStruct, sendStr);
	}
	if (recvFromServerStruct.s_javaServer)//javaServer线程
	{
		TrackServerDealOutFromJavaServer(recvFromServerStruct, sendStr);

	}
	//解析数据失败或者是不兼容的数据
	return 0;
}
//int TrackServer::parseServerStrToJsonForMediaThread(std::string & sendStr, RecvFromServerStruct & recvFromServerStruct)
//{
//	Json::Value  root;//根节点
//	Json::Value  msgHead;//消息头
//	Json::Value  msgHeadSub;//消息头子节点
//	Json::Value  msgBody;//消息体
//						 //组msgHead
//	{
//		msgHeadSub["host"] = Json::Value("192.168.1.153");
//		msgHeadSub["faceDetectIP"] = Json::Value("localhost");
//
//
//
//		msgHeadSub["msgType"] = Json::Value(JSONMSGTYPE_REQUEST);
//		msgHeadSub["versionNo"] = Json::Value("v1.0.0");
//		long long Time = GetTickCount();
//		msgHeadSub["timestamp"] = Json::Value(Time);
//		msgHeadSub["requestID"] = Json::Value(0);
//		msgHeadSub["boundID"] = Json::Value(0);
//		msgHeadSub["authorization"] = Json::Value(0);
//		//msgHead["msgHead"] = Json::Value(msgHeadSub);
//
//		msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_SERVER_TRACK_FRAM_OUT);
//			
//		
//	}
//	if (true == msgHeadSub.isNull())
//	{
//		return -1;
//	}
//	root["msgHead"] = Json::Value(msgHeadSub);
//	//组msgBady
//	{
//		Json::Value dataRequest;
//		dataRequest["code"] = Json::Value(JSONMSGCODE_SERVER_TRACK_FRAM_OUT);
//		msgBody["dataRequest"] = Json::Value(dataRequest);
//		Json::Value dataPush;
//		if (g_vPersonMsg.size() > 0)
//		{
//			for (auto it = g_vPersonMsg.begin(); it !=g_vPersonMsg.end();it++)
//			{
//				if (recvFromServerStruct.s_recvFromClientServerStruct.s_personId == (*it).m_personId)
//				{
//					dataPush["camId"] = Json::Value((*it).m_camId);
//					dataPush["personId"] = Json::Value((*it).m_personId);
//
//				}
//			}
//		}
//		
//		
//
//
//
//	}
//	root["msgBody"] = Json::Value(msgBody);
//	if (true == root.isNull())
//	{
//		return -1;
//	}
//	sendStr = root.toStyledString();
//	return 1;
//}
int TrackServer::parseServerStrToJson(std::string & sendStr, RecvFromServerStruct & recvFromServerStruct)
{
	Json::Value  root;//根节点
	Json::Value  msgHead;//消息头
	Json::Value  msgHeadSub;//消息头子节点
	Json::Value  msgBody;//消息体
	Json::Value dataRecv;
	Json::Value dataSend;
	//组msgHead
	{
		msgHeadSub["host"] = Json::Value("192.168.1.153");
		msgHeadSub["faceDetectIP"] = Json::Value("localhost");
		msgHeadSub["msgType"] = Json::Value(JSONMSGTYPE_REQUEST);
		msgHeadSub["versionNo"] = Json::Value("v1.0.0");
		long long Time = GetTickCount();
		msgHeadSub["timestamp"] = Json::Value(Time);
		msgHeadSub["requestID"] = Json::Value(recvFromServerStruct.s_requestid);
		msgHeadSub["boundID"] = Json::Value(0);
		msgHeadSub["authorization"] = Json::Value(0);
		//msgHead["msgHead"] = Json::Value(msgHeadSub);

		if (recvFromServerStruct.s_Alarm)
		{
			//告警信息 组发送到跟踪器的数据

			//全部人形 组发送到跟踪器的数据

		}
		if (recvFromServerStruct.s_client)
		{
			//请求切换标签页接口
			if (recvFromServerStruct.s_recvFromClientServerStruct.s_ChangeTap)
			{
				msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_CLIENT_TRACE_PERSON_CHANGE_BACK);
			}
			//跟踪人物id处理接口
			if (recvFromServerStruct.s_recvFromClientServerStruct.s_TailPersonId)
			{
				msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_CLIENT_ALARM_DEAL);
			}
			//查询跟踪轨迹
			if (recvFromServerStruct.s_recvFromClientServerStruct.s_getTailTrack)
			{
				msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_TAILAFTER_ONEHUMANSHAPE_OUT);
			}
		}
		if (recvFromServerStruct.s_HumenShape)
		{
			if (recvFromServerStruct.s_recvFromHumanShapeServerStruct.AlamMsg)
			{
				msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_TAILAFTER_ONEHUMANSHAPE_OUT);
			}
			if (recvFromServerStruct.s_recvFromHumanShapeServerStruct.AllHumanShape)
			{
				msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_TAILAFTER_ALLHUMANSHAPE_OUT);
			}
		}
		if (recvFromServerStruct.s_javaServer)
		{

		}
	}
	if (true == msgHeadSub.isNull())
	{
		return -1;
	}
	root["msgHead"] = Json::Value(msgHeadSub);
	//组msgBady
	{
		if (recvFromServerStruct.s_Alarm)
		{

		}
		if (recvFromServerStruct.s_client)
		{
			//请求切换标签页接口

			if (recvFromServerStruct.s_recvFromClientServerStruct.s_ChangeTap)
			{
				dataSend["code"] = Json::Value(JSONMSGCODE_CLIENT_TRACE_PERSON_ROUTE);
				msgBody["dataRecv"] = JSONMSGCODE_CLIENT_TRACE_PERSON_CHANGE;
				

				if (g_vPersonMsg.size()>0)
				{
					for (auto it = g_vPersonMsg.begin();it != g_vPersonMsg.end();it ++)
					{
						if ((*it).m_personId == recvFromServerStruct.s_recvFromClientServerStruct.s_personId)
						{
							dataSend["personID"] = recvFromServerStruct.s_recvFromClientServerStruct.s_personId;
							dataSend["camID"] = (*it).m_camId;
							if (g_vCamStruct.size()>0)
							{
								for (auto CamStructIt = g_vCamStruct.begin(); CamStructIt != g_vCamStruct.end(); CamStructIt++)
								{
									if ((*CamStructIt).s_camID == (*it).m_camId)
									{
			
										dataSend["LcamID"] = (*CamStructIt).s_LcamID;
										dataSend["RcamId"] = (*CamStructIt).s_RcamID;
										dataSend["FcamID"] = (*CamStructIt).s_FcamID;
										dataSend["BcamID"] = (*CamStructIt).s_BcamID;
										break;
									}
								}

							}
							else
							{

							}
							//dataSend["LcamID"] = g_vPersonMsg[0].;//need wait
							//dataSend["RcamId"] = g_vPersonMsg[0];//need wait
							//dataSend["FcamID"] = g_vPersonMsg[0];//need wait
							//dataSend["BcamID"] = g_vPersonMsg[0];//need wait
							dataSend["platID"] = 123;
							Json::Value traceRoute;
							if ((*it).mv_tailTrackStruct.size() > 0)
							{
								int i = 0;
								for (auto tailTrackStructIt = (*it).mv_tailTrackStruct.begin(); tailTrackStructIt != (*it).mv_tailTrackStruct.end(); tailTrackStructIt++)
								{
									Json::Value traceRouteSub;
	
								//	traceRouteSub["CamNum"] = Json::Value(i++);
									traceRouteSub["CamId"] = Json::Value((*tailTrackStructIt).s_CamId);
									traceRoute.append(traceRouteSub);
								}
							}
							else {

							}
							dataSend["traceRoute"] = Json::Value(traceRoute);
						

							
							break;

						}

					}

				}
				else {
					dataSend["personID"] = recvFromServerStruct.s_recvFromClientServerStruct.s_personId;
					dataSend["camID"] = recvFromServerStruct.s_recvFromClientServerStruct.s_camId;// 205;
					//dataSend["LcamID"] = g_vPersonMsg[0].;//need wait
					//dataSend["RcamId"] = g_vPersonMsg[0];//need wait
					//dataSend["FcamID"] = g_vPersonMsg[0];//need wait
					//dataSend["BcamID"] = g_vPersonMsg[0];//need wait
					dataSend["platID"] = 0;
					Json::Value traceRoute;

					dataSend["traceRoute"] = "";

					dataSend["code"] = Json::Value(JSONMSGCODE_CLIENT_TRACE_PERSON_ROUTE);
					msgBody["dataRecv"] = JSONMSGCODE_CLIENT_TRACE_PERSON_CHANGE;
					msgBody["dataSend"] = Json::Value(dataSend);
				}
					
				msgBody["dataSend"] = Json::Value(dataSend);
			}



			//跟踪人物id处理接口
			if (recvFromServerStruct.s_recvFromClientServerStruct.s_TailPersonId)
			{
			//	dataSend["code"] = Json::Value(JSONMSGCODE_CLIENT_ALARM_DEAL_RESULT_FAILED);
				dataSend["code"] = Json::Value(0);
				msgBody["dataRecv"] = "";

				dataSend["personID"] = Json::Value(recvFromServerStruct.s_recvFromClientServerStruct.s_personId);
				dataSend["optState"] = Json::Value(recvFromServerStruct.s_recvFromClientServerStruct.s_optState);
				dataSend["optStaff"] = Json::Value(recvFromServerStruct.s_recvFromClientServerStruct.s_optStaff);

				msgBody["dataSend"] = Json::Value(dataSend);

			}
			////查询跟踪轨迹
			//if (recvFromServerStruct.s_recvFromClientServerStruct.s_getTailTrack)
			//{
			//	
			//}
			
		}
		if (recvFromServerStruct.s_HumenShape)
		{
			if (recvFromServerStruct.s_recvFromHumanShapeServerStruct.AlamMsg)
			{
				Json::Value dataRequest;
				dataRequest["code"] = Json::Value(JSONMSGCODE_TAILAFTER_ONEHUMANSHAPE_OUT);

				msgBody["dataRequest"] = Json::Value(dataRequest);
				Json::Value dataPush;
				dataPush["personID"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_personId);
				dataPush["cameraId"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_camID);
				Json::Value Time;
				Time["sec"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_timeval.tv_sec);
				Time["usec"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_timeval.tv_usec);
				dataPush["Time"] = Json::Value(Time);
				dataPush["TrackerSrcpictureDir"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_srcPictureDir);
				dataPush["CameraFrameAddr"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_camAddr);
				Json::Value HumenROI;
				HumenROI["X"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_roi[0].s_ix);
				HumenROI["Y"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_roi[0].s_iy);
				HumenROI["Width"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_roi[0].s_iwidth);
				HumenROI["Height"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_roi[0].s_ihight);
				Json::Value FaceROI;
				FaceROI["height"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_face_roi[0].height);
				FaceROI["width"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_face_roi[0].width);
				FaceROI["x"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_face_roi[0].x);
				FaceROI["y"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_face_roi[0].y);

				dataPush["FaceROI"] = Json::Value(FaceROI);
				dataPush["HumenROI"] = Json::Value(HumenROI);
				msgBody["dataRequest"] = Json::Value(dataRequest);
				msgBody["dataPush"] = Json::Value(dataPush);
				
				

			}
			if (recvFromServerStruct.s_recvFromHumanShapeServerStruct.AllHumanShape)
			{
				Json::Value dataRecv;
				dataRecv["code"] = Json::Value(JSONMSGCODE_TAILAFTER_ALLHUMANSHAPE_OUT);

				msgBody["dataSend"] = Json::Value(dataRecv);
				Json::Value dataSend;
				dataSend["personID"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_personId);
				dataSend["cameraId"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_camID);
				Json::Value Time;
				Time["sec"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_timeval.tv_sec);
				Time["usec"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_timeval.tv_usec);
				dataSend["Time"] = Json::Value(Time);
				dataSend["TrackerSrcpictureFramName"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_TrackerSrcpictureFramName);
				dataSend["CameraFrameAddr"] = Json::Value(recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_camAddr);
				Json::Value HumenROIArr;
				if (recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_roi.size() > 0)
				{
					for (auto it = recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_roi.begin();
						it != recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_roi.end();
						) {
						Json::Value HumenROI;
						HumenROI["initX"] = Json::Value((*it).s_ix);
						HumenROI["initY"] = Json::Value((*it).s_iy);
						HumenROI["initWidth"] = Json::Value((*it).s_iwidth);
						HumenROI["initHeight"] = Json::Value((*it).s_ihight);
						HumenROIArr["HumenROI"].append(HumenROI);
						it = recvFromServerStruct.s_recvFromHumanShapeServerStruct.sv_roi.erase(it);
					}

				}
				else {

				}
				dataSend["HumenROIArr"] = Json::Value(HumenROIArr);
				msgBody["dataSend"] = Json::Value(dataSend);
			}

		}
		if (recvFromServerStruct.s_javaServer)
		{

		}
	}
	if (true == msgBody.isNull())
	{
		return -1;
	}
	root["msgBody"] = Json::Value(msgBody);
	if (true == root.isNull())
	{
		return -1;
	}
	sendStr = root.toStyledString();
	//cout << "sendStr:*********************************************************"<< endl;
	//cout << "sendStr:"<< sendStr << endl;
	//cout << "sendStr:***********************************************************"  << endl;
	return 1;
}

int TrackServer::TrackServerDealOutFromAlarm(RecvFromServerStruct & recvFromServerStruct, std::string & sendStr)
{
	return 0;
}

int TrackServer::TrackServerDealOutFromClient(RecvFromServerStruct & recvFromServerStruct, std::string & sendStr)
{
	int ret = 0;
	int find_flag = 0;
	//if (recvFromServerStruct.s_recvFromClientServerStruct.s_getTailTrack)//查询跟踪轨迹
	//{
	//}
	if (recvFromServerStruct.s_recvFromClientServerStruct.s_TailPersonId)//确认跟踪目标
	{
		if (g_vclientTailPersonMsg.size() > 0)//全局量
		{
			for (auto it = g_vclientTailPersonMsg.begin(); it != g_vclientTailPersonMsg.end(); it++)//
			{
				if ((*it).m_personId == recvFromServerStruct.s_recvFromClientServerStruct.s_personId)//search track person status
				{
					recvFromServerStruct.s_recvFromClientServerStruct.s_optStaff = (*it).m_oprationName;
					recvFromServerStruct.s_recvFromClientServerStruct.s_optState = (*it).m_optState;
					//find_flag = 1;
					break;
				}
			}
		if (-1 == recvFromServerStruct.s_recvFromClientServerStruct.s_optState)//un
			//if (find_flag == 0)//un find 
			{
				clientTailPersonMsg subclientTailPersonMsg;
				subclientTailPersonMsg.m_personId = recvFromServerStruct.s_recvFromClientServerStruct.s_personId;
				subclientTailPersonMsg.m_optState = recvFromServerStruct.s_recvFromClientServerStruct.s_optState;
				subclientTailPersonMsg.m_oprationName = recvFromServerStruct.s_recvFromClientServerStruct.s_optStaff;
				g_vclientTailPersonMsg.push_back(subclientTailPersonMsg);
				return 1;
			}


		}
		else {
			clientTailPersonMsg subclientTailPersonMsg;
			subclientTailPersonMsg.m_personId = recvFromServerStruct.s_recvFromClientServerStruct.s_personId;
			subclientTailPersonMsg.m_optState = recvFromServerStruct.s_recvFromClientServerStruct.s_optState;
			subclientTailPersonMsg.m_oprationName = recvFromServerStruct.s_recvFromClientServerStruct.s_optStaff;
			g_vclientTailPersonMsg.push_back(subclientTailPersonMsg);
			//return 1;
		}
		//组数据发送给client
		std::string sendStr;
		if (parseServerStrToJson(sendStr, recvFromServerStruct))
		{
			char* sendBuf = (char*)malloc(sendStr.size());
			memcpy(sendBuf, sendStr.c_str(), sendStr.size());
			if (lpClientThreadId != 0) {
				int ret = PostThreadMessage(lpClientThreadId, TRACESERVER_MAKESUER_TARGET, (WPARAM)sendBuf, NULL);
				if (!ret)
				{
					free(sendBuf);
					return -1;
				}
			}
			else {
				fprintf(flog, "[%s] [%s] [%d] error lpClientThreadId ==== %d\n", get_system_misecond_time(), __FUNCTION__, __LINE__, lpClientThreadId);
				//fflush(flog);
			}
		}

		sendStr.clear();
		//组数据发送给流媒体线程
		if (parseServerStrToJson(sendStr, recvFromServerStruct))
		{
			char* sendNediaBuf = (char*)malloc(sendStr.size());
			memcpy(sendNediaBuf, sendStr.c_str(), sendStr.size());
			if (lpRtspThreadId != 0) {
				int ret = PostThreadMessage(lpRtspThreadId, TRACESERVER_MAKESUER_TARGET, (WPARAM)sendNediaBuf, NULL);
				if (!ret)
				{
					free(sendNediaBuf);
				}
			}
			else {
				fprintf(flog, "[%s] [%s] [%d] error lpRtspThreadId ==== %d\n", get_system_misecond_time(), __FUNCTION__, __LINE__, lpRtspThreadId);
				//fflush(flog);
			}
		}

	}
	//if (recvFromServerStruct.s_recvFromClientServerStruct.s_TailWrong)//跟踪错误
	//{

	//}

	if (recvFromServerStruct.s_recvFromClientServerStruct.s_Misinformtion)//误报 发送给java和 跟踪器结束跟踪
	{
		if (g_vPersonMsg.size())
		{
			std::unique_lock<std::mutex> locker(g_mutex);
			for (auto it = g_vPersonMsg.begin(); it != g_vPersonMsg.end();)
			{
				if (recvFromServerStruct.s_recvFromClientServerStruct.s_personId == (*it).m_personId)
				{
					//组误报的数据发送到对应的跟踪器
					std::string sendMisInformtionStr;
					if (parseServerStrToJson(sendMisInformtionStr, recvFromServerStruct))
					{
						s_sendmore(*((*it).m_connetTrackSocketStruct.s_connetTrackSocket), "");
						s_send(*((*it).m_connetTrackSocketStruct.s_connetTrackSocket), sendMisInformtionStr);
						//发送成功
						it = g_vPersonMsg.erase(it);
						break;
					}
					else {
						it++;
						//组数据失败
						return -1;
					}
				}
				it++;
			}
		}
	}
	if (recvFromServerStruct.s_recvFromClientServerStruct.s_ChangeTap)//切换标签页 --- 切换相机
	{
		//if (recvFromServerStruct.s_recvFromClientServerStruct.s_lastPersonID != -1)//切到跟踪标签页
		//{

		//}
		//else {
		//	//回到是主界面
		//}
		if (recvFromServerStruct.s_recvFromClientServerStruct.s_personId != -1)
		{
			if (g_vPersonMsg.size() > 0)
			{
				std::unique_lock<std::mutex> locker(g_mutex);
				for (auto it = g_vPersonMsg.begin(); it != g_vPersonMsg.end(); it++)
				{
					if (recvFromServerStruct.s_recvFromClientServerStruct.s_personId == (*it).m_personId)
					{
						//找到跟踪的id

						//组client数据
						std::string clientSendStr;
						parseServerStrToJson(clientSendStr, recvFromServerStruct);
						char* sendClientBuf = (char*)malloc(clientSendStr.size());
						memcpy(sendClientBuf, clientSendStr.c_str(), clientSendStr.size());
						if (lpClientThreadId != 0) {
							ret = PostThreadMessage(lpClientThreadId, TRACESERVER_GOTOANOTHER_CAMERA, (WPARAM)sendClientBuf, NULL);
//							std::cout << "clientSendStr is :" << clientSendStr.c_str() << std::endl;
							if (ret == 0)
							{
								if (lpClientThreadId != 0) {
#ifdef TRACK_VALUE_PRINT
									fprintf(flog, "track send msg to client ============== %d", sendClientBuf);
									//fflush(flog);
#endif
									ret = PostThreadMessage(lpClientThreadId, TRACESERVER_GOTOANOTHER_CAMERA, (WPARAM)sendClientBuf, NULL);
									//	std::cout << "clientSendStr is :" << clientSendStr.c_str() << std::endl;
									if (ret == 0)
									{


										free(sendClientBuf);

										//发送失败
									}
								}
							}
							else {
								fprintf(flog, "erroe lpClientThreadId ============== %d", lpClientThreadId);
								//fflush(flog);
							}
							//组数据发送到流媒体  lpRtspThreadId
							std::string framMediaSendStr;
							parseServerStrToJson(framMediaSendStr, recvFromServerStruct);
							char* sendMediaBuf = (char*)malloc(framMediaSendStr.size());
							memcpy(sendMediaBuf, framMediaSendStr.c_str(), framMediaSendStr.size());
							if (lpRtspThreadId != 0) {
								ret = PostThreadMessage(lpRtspThreadId, TRACESERVER_GOTOANOTHER_CAMERA, (WPARAM)sendMediaBuf, NULL);
							//	std::cout << "framMediaSendStr is :" << framMediaSendStr.c_str() << std::endl;
								if (ret == 0)
								{
									std::string clientSendStr;
									parseServerStrToJson(clientSendStr, recvFromServerStruct);
									char* sendClientBuf = (char*)malloc(clientSendStr.size());
									memcpy(sendClientBuf, clientSendStr.c_str(), clientSendStr.size());
									//发送失败
									free(sendClientBuf);

								}
							}
							else {
								fprintf(flog, "erroe lpRtspThreadId ============== %d", lpRtspThreadId);
								//fflush(flog);
							}
						}
					}
				}
			}

		}
		else {
			//是主界面
		}

	}
	if (recvFromServerStruct.s_recvFromClientServerStruct.s_OverTracking)//结束跟踪
	{

	}
	return 0;
}

int TrackServer::TrackServerDealOutFromFramServer(RecvFromServerStruct & recvFromServerStruct, std::string & sendStr)
{

	return 0;
}

int TrackServer::TrackServerDealOutFromHumenShape(RecvFromServerStruct & recvFromServerStruct, std::string & sendStr)
{
	if (recvFromServerStruct.s_recvFromHumanShapeServerStruct.AlamMsg)//告警信息
	{
		bool TrackPersonId = false;
		//任务id已经在跟踪,发送给跟踪器重新初始化 状态（重识别，出相机，跟踪）改变时需要发相机位置给java保存数据
		if (g_vPersonMsg.size() > 0)
		{
			std::unique_lock<std::mutex> locker(g_mutex);
			for (auto it = g_vPersonMsg.begin(); it != g_vPersonMsg.end(); it++)
			{
				if (recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_personId == (*it).m_personId) {
					//if ((*it).m_TailStatus == 1)//跟踪
					//{
					//}else if((*it).m_TailStatus == 2)//丢失
					//{
					//}else if ((*it).m_TailStatus == 3)//出相机
					//{
					//}
					TrackPersonId = true;
					std::string sendToTailServerMsg;
					if (parseServerStrToJson(sendToTailServerMsg, recvFromServerStruct)) {
						s_sendmore(*(it->m_connetTrackSocketStruct.s_connetTrackSocket), "");
						s_send(*(it->m_connetTrackSocketStruct.s_connetTrackSocket), sendToTailServerMsg);
					//	cout << "sendToTailServerMsg :" << sendToTailServerMsg << endl;
						fprintf(flog_track, "[%s] [%s] [%d] send shape msg 2 track al ==== %s\n", get_system_misecond_time(),__FUNCTION__, __LINE__, (char *)sendToTailServerMsg.c_str());
					}
					else {
						//组数据失败
					}
					break;

				}

			}
			if (!TrackPersonId) {//没找到person ID
				PersonMsg subPersonMsg;
				subPersonMsg.m_personId = recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_personId;
				subPersonMsg.m_TailStatus = 1;
				subPersonMsg.m_camId = recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_camID;
				//选择一个跟踪器做跟踪
				subPersonMsg.m_connetTrackSocketStruct.s_connetTrackSocket = mv_connetTrackSocketStruct[0].s_connetTrackSocket;
				//组发向跟踪器告警消息的str  相机决定跟踪目标，数据java server提供
				std::string sendToTailServerMsg;
				if (parseServerStrToJson(sendToTailServerMsg, recvFromServerStruct)) {
					s_sendmore(*(subPersonMsg.m_connetTrackSocketStruct.s_connetTrackSocket), "");
					s_send(*(subPersonMsg.m_connetTrackSocketStruct.s_connetTrackSocket), sendToTailServerMsg);
				//	cout << "sendToTailServerMsg :" << sendToTailServerMsg << endl;
					g_vPersonMsg.push_back(subPersonMsg);
				}
				else {
					//组数据失败
				}
			}
			
			

		}
		else {
			PersonMsg subPersonMsg;
			subPersonMsg.m_personId = recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_personId;
			subPersonMsg.m_TailStatus = 1;
			subPersonMsg.m_camId = recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_camID;
			//选择一个跟踪器做跟踪
			if (mv_connetTrackSocketStruct.size() == 0)
			{
				cout << "mv_connetTrackSocketStruct is NULL;" << endl;
				return -1;
			}
			else {
				subPersonMsg.m_connetTrackSocketStruct.s_connetTrackSocket = mv_connetTrackSocketStruct[0].s_connetTrackSocket;
			}

			//组发向跟踪器告警消息的str
			std::string sendToTailServerMsg;
			if (parseServerStrToJson(sendToTailServerMsg, recvFromServerStruct)) {
				s_sendmore(*(subPersonMsg.m_connetTrackSocketStruct.s_connetTrackSocket), "");
				s_send(*(subPersonMsg.m_connetTrackSocketStruct.s_connetTrackSocket), sendToTailServerMsg);
			//	cout << "sendToTailServerMsg :"<<sendToTailServerMsg <<endl;
				g_vPersonMsg.push_back(subPersonMsg);
			}
			else {
				//组数据失败
			}
		}
	}
	if (recvFromServerStruct.s_recvFromHumanShapeServerStruct.AllHumanShape)//全部人形
	{
		if (g_vPersonMsg.size() > 0)
		{
			std::unique_lock<std::mutex> locker(g_mutex);
			for (auto it = g_vPersonMsg.begin(); it != g_vPersonMsg.end(); it++)
			{
				if (recvFromServerStruct.s_recvFromHumanShapeServerStruct.s_personId == (*it).m_personId) {

					//组数据
					std::string sendToTailServerMsg;
					if (parseServerStrToJson(sendToTailServerMsg, recvFromServerStruct)) {
						s_sendmore(*(it->m_connetTrackSocketStruct.s_connetTrackSocket), "");
						s_send(*(it->m_connetTrackSocketStruct.s_connetTrackSocket), sendToTailServerMsg);
					}
					else {
						//组数据失败
					}
					//break;
				}

			}//没找到person ID
		}
		else 
		{

			//没有人物id在跟踪
		}
	}
	return 0;
}

int TrackServer::TrackServerDealOutFromJavaServer(RecvFromServerStruct & recvFromServerStruct, std::string & sendStr)
{
	if (recvFromServerStruct.s_recvFromJavaServerStruct.InitTrackMsg)
	{
		InitTrackMsg(recvFromServerStruct);
	}
	if (recvFromServerStruct.s_recvFromJavaServerStruct.AddTrackMsg)
	{
		AddTrackMsg(recvFromServerStruct);
	}
	if (recvFromServerStruct.s_recvFromJavaServerStruct.RemoveTrackMsg)
	{
		RemoveTrackMsg(recvFromServerStruct);
	}
	return 0;
}

std::vector<ConnetTrackSocketStruct>* TrackServer::getconnetTrackSocketStruct()
{
	if (mv_connetTrackSocketStruct.size() > 0)
	{
		return &mv_connetTrackSocketStruct;
	}
	else {
		return NULL;
	}
	// TODO: 在此处插入 return 语句
}

int TrackServer::ParseJsonInitMsg(std::string & sendInit)
{
	Json::Value  root;//根节点
	Json::Value  msgHead;//消息头
	Json::Value  msgHeadSub;//消息头子节点
	Json::Value  msgBody;//消息体
	//组消息头
	{
		msgHeadSub["host"] = Json::Value("192.168.1.153");
		msgHeadSub["faceDetectIP"] = Json::Value("localhost");

		msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_JAVASERVER_INIT_OUT);

		msgHeadSub["msgType"] = Json::Value(JSONMSGTYPE_REQUEST);
		msgHeadSub["versionNo"] = Json::Value("v1.0.0");
		long long Time = GetTickCount();
		msgHeadSub["timestamp"] = Json::Value(Time);
		msgHeadSub["requestID"] = Json::Value(0);
		msgHeadSub["boundID"] = Json::Value(0);
		msgHeadSub["authorization"] = Json::Value(0);
		//msgHead["msgHead"] = Json::Value(msgHeadSub);
	}
	//组消息体
	root["msgHead"] = Json::Value(msgHeadSub);
	{
		Json::Value dataRequest;
		dataRequest["code"] = Json::Value(JSONMSGCODE_JAVASERVER_INIT_OUT);
		msgBody["dataRequest"] = Json::Value(dataRequest);
		Json::Value dataPush;
		msgBody["dataPush"] = Json::Value(dataPush);
	}
	root["msgBody"] = Json::Value(msgBody);
	if (true == root.isNull())
	{
		return -1;
	}
	sendInit = root.toStyledString();
	return 1;
}

int TrackServer::InitTrackMsg(RecvFromServerStruct & recvFromServerStruct)
{
	if (g_InitTailServerStruct.size() == 0)
	{
		return -1;
	}

	//初始化对跟踪器的连接
	for (int i = 0; i < g_InitTailServerStruct.size(); i++)
	{
		ConnetTrackSocketStruct tempConnetTrackSocketStruct;

		tempConnetTrackSocketStruct.s_connetTrackSocket = new zmq::socket_t(contextT, ZMQ_DEALER);
		s_set_id(*(tempConnetTrackSocketStruct.s_connetTrackSocket), (intptr_t)(i+1));
		//printf("id===== %d \n", (intptr_t)(i + 1));
		(*(tempConnetTrackSocketStruct.s_connetTrackSocket)).connect(g_InitTailServerStruct[i].s_connectSocketAddr.c_str());
		fprintf(flog_track_init,"connect add ==== %s \n", g_InitTailServerStruct[i].s_connectSocketAddr.c_str());
		fflush(flog_track_init);
		//tempConnetTrackSocketStruct.s_connetTrackSocket = TrackSocket;
		tempConnetTrackSocketStruct.s_Id = (intptr_t)i;
		mv_connetTrackSocketStruct.push_back(tempConnetTrackSocketStruct);
	}
	////测试用的跟踪器信息 20180210  
	///***********************begin*************************/
	{
		/*ConnetTrackSocketStruct tempConnetTrackSocketStruct;
		tempConnetTrackSocketStruct.s_connetTrackSocket = new zmq::socket_t(contextT, ZMQ_DEALER);
		s_set_id(*(tempConnetTrackSocketStruct.s_connetTrackSocket), (intptr_t)12);
		(*(tempConnetTrackSocketStruct.s_connetTrackSocket)).connect(TRACKSERVE_RADDR);

		tempConnetTrackSocketStruct.s_Id = (intptr_t)12;
		mv_connetTrackSocketStruct.push_back(tempConnetTrackSocketStruct);*/

	}
	///***********************end*************************/
	//发送初始化数据给跟踪器
	for (int i = 0; i < mv_connetTrackSocketStruct.size(); i++)
	{
		if (sendInitTrackMsg(mv_connetTrackSocketStruct[i].s_connetTrackSocket))
		{
			//成功发送数据
			break;
		}
	}
	return 0;
}

int TrackServer::AddTrackMsg(RecvFromServerStruct & recvFromServerStruct)
{
	return 0;
}

int TrackServer::RemoveTrackMsg(RecvFromServerStruct & recvFromServerStruct)
{
	return 0;
}

int TrackServer::sendInitTrackMsg(zmq::socket_t *socket)
{

	//发送初始化数据给跟踪器
	std::string InitTrackMsg;
	TrackServerInit(InitTrackMsg);

	/*s_sendmore(*socket, "");
	s_send(*socket, InitTrackMsg);*/
	/*s_sendmore(*socket, "");
	s_send(*socket, "Hello!!!");*/
	return 1;
}

int TrackServer::bindTrackMsg()
{
	return 0;
}

int TrackServer::sendLostMsgToJavaThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr)
{
	Json::Value  root;//根节点
	Json::Value  msgHead;//消息头
	Json::Value  msgHeadSub;//消息头子节点
	Json::Value  msgBody;//消息体
	//组msgHead
	{
		msgHeadSub["host"] = Json::Value("192.168.1.153");
		msgHeadSub["faceDetectIP"] = Json::Value("localhost");
		msgHeadSub["msgType"] = Json::Value(JSONMSGTYPE_REQUEST);
		msgHeadSub["versionNo"] = Json::Value("v1.0.0");
		long long Time = GetTickCount();
		msgHeadSub["timestamp"] = Json::Value(Time);
		msgHeadSub["requestID"] = Json::Value(0);
		msgHeadSub["boundID"] = Json::Value(0);
		msgHeadSub["authorization"] = Json::Value(0);
		//msgHead["msgHead"] = Json::Value(msgHeadSub);


		msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_JAVASERVER_LOST_OUT);

	}
	if (true == msgHeadSub.isNull())
	{
		return -1;
	}
	root["msgHead"] = Json::Value(msgHeadSub);
	//组msgBady
	{
		Json::Value dataRequest;
		dataRequest["code"] = Json::Value(JSONMSGCODE_JAVASERVER_LOST_OUT);
		msgBody["dataRequest"] = Json::Value(dataRequest);
		Json::Value dataPush;
		dataPush["personID"] = Json::Value(recvFromTrackStruct.s_iPersonID);
		dataPush["cameraId"] = Json::Value(recvFromTrackStruct.s_iCamId);
		dataPush["zoneID"] = Json::Value(recvFromTrackStruct.s_iCamId);
		Json::Value Time;
		Time["sec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_sec);
		Time["usec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_usec);
		dataPush["Time"] = Json::Value(Time);
	}
	if (true == msgBody.isNull())
	{
		return -1;
	}
	root["msgBody"] = Json::Value(msgBody);
	if (true == root.isNull())
	{
		return -1;
	}
	sendStr = root.toStyledString();
	return 1;


}

int TrackServer::sendLostMsgToClientThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr)
{
	Json::Value  root;//根节点
	Json::Value  msgHead;//消息头
	Json::Value  msgHeadSub;//消息头子节点
	Json::Value  msgBody;//消息体
	//组msgHead
	{
		msgHeadSub["host"] = Json::Value("192.168.1.153");
		msgHeadSub["faceDetectIP"] = Json::Value("localhost");
		msgHeadSub["msgType"] = Json::Value(JSONMSGTYPE_REQUEST);
		msgHeadSub["versionNo"] = Json::Value("v1.0.0");
		long long Time = GetTickCount();
		msgHeadSub["timestamp"] = Json::Value(Time);
		msgHeadSub["requestID"] = Json::Value(0);
		msgHeadSub["boundID"] = Json::Value(0);
		msgHeadSub["authorization"] = Json::Value(0);
		//msgHead["msgHead"] = Json::Value(msgHeadSub);
		msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_JAVASERVER_LOST_OUT);

	}
	if (true == msgHeadSub.isNull())
	{
		return -1;
	}
	root["msgHead"] = Json::Value(msgHeadSub);
	//组msgBady
	{
		Json::Value dataRequest;
		dataRequest["code"] = Json::Value(JSONMSGCODE_JAVASERVER_LOST_OUT);
		msgBody["dataRequest"] = Json::Value(dataRequest);
		Json::Value dataPush;
		dataPush["personID"] = Json::Value(recvFromTrackStruct.s_iPersonID);
		dataPush["cameraId"] = Json::Value(recvFromTrackStruct.s_iCamId);
		dataPush["zoneID"] = Json::Value(recvFromTrackStruct.s_iCamId);
		Json::Value Time;
		Time["sec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_sec);
		Time["usec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_usec);
		dataPush["Time"] = Json::Value(Time);
		msgBody["dataPush"] = Json::Value(dataPush);
	}
	if (true == msgBody.isNull())
	{
		return -1;
	}
	root["msgBody"] = Json::Value(msgBody);
	if (true == root.isNull())
	{
		return -1;
	}
	sendStr = root.toStyledString();
	return 1;

}

int TrackServer::sendRegAginMsgToHumanShapeThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr)
{
	Json::Value  root;			//根节点
	Json::Value  msgHead;		//消息头
	Json::Value  msgHeadSub;	//消息头子节点
	Json::Value  msgBody;		//消息体
	//组msgHead
	{
		msgHeadSub["host"] = Json::Value("192.168.1.153");
		msgHeadSub["faceDetectIP"] = Json::Value("localhost");
		msgHeadSub["msgType"] = Json::Value(JSONMSGTYPE_REQUEST);
		msgHeadSub["versionNo"] = Json::Value("v1.0.0");
		long long Time = GetTickCount();
		msgHeadSub["timestamp"] = Json::Value(Time);
		msgHeadSub["requestID"] = Json::Value(0);
		msgHeadSub["boundID"] = Json::Value(0);
		msgHeadSub["authorization"] = Json::Value(0);
		//msgHead["msgHead"] = Json::Value(msgHeadSub);
		msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_HUMANSHAPE_ALLHUMANSHAPE_OUT);

	}
	if (true == msgHeadSub.isNull())
	{
		return -1;
	}
	root["msgHead"] = Json::Value(msgHeadSub);
	//组msgBady
	{
		Json::Value dataRequest;
		dataRequest["code"] = Json::Value(JSONMSGCODE_HUMANSHAPE_ALLHUMANSHAPE_OUT);
		msgBody["dataRequest"] = Json::Value(dataRequest);
		Json::Value dataPush;
		dataPush["personID"] = Json::Value(recvFromTrackStruct.s_iPersonID);
		dataPush["camId"] = Json::Value(recvFromTrackStruct.s_iCamId);
		dataPush["TrackerSrcpictureFramName"] = Json::Value(recvFromTrackStruct.s_sTrackerSrcpictureFramName);
		Json::Value Time;
		Time["sec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_sec);
		Time["usec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_usec);
		dataPush["Time"] = Json::Value(Time);
		msgBody["dataPush"] = Json::Value(dataPush);
	}

	if (true == msgBody.isNull())
	{
		return -1;
	}
	root["msgBody"] = Json::Value(msgBody);
	if (true == root.isNull())
	{
		return -1;
	}
	sendStr = root.toStyledString();
	return 1;
}

int TrackServer::sendTrackingMsgToJavaThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr)
{
	Json::Value  root;//根节点
	Json::Value  msgHead;//消息头
	Json::Value  msgHeadSub;//消息头子节点
	Json::Value  msgBody;//消息体
	//组msgHead
	{
		msgHeadSub["host"] = Json::Value("192.168.1.153");
		msgHeadSub["faceDetectIP"] = Json::Value("localhost");
		msgHeadSub["msgType"] = Json::Value(JSONMSGTYPE_REQUEST);
		msgHeadSub["versionNo"] = Json::Value("v1.0.0");
		long long Time = GetTickCount();
		msgHeadSub["timestamp"] = Json::Value(Time);
		msgHeadSub["requestID"] = Json::Value(0);
		msgHeadSub["boundID"] = Json::Value(0);
		msgHeadSub["authorization"] = Json::Value(0);
		//msgHead["msgHead"] = Json::Value(msgHeadSub);


		msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_JAVASERVER_FOLLOW_OUT);

	}
	if (true == msgHeadSub.isNull())
	{
		return -1;
	}
	root["msgHead"] = Json::Value(msgHeadSub);
	//组msgBady
	{
		Json::Value dataRequest;
		dataRequest["code"] = Json::Value(JSONMSGCODE_JAVASERVER_FOLLOW_OUT);
		msgBody["dataRequest"] = Json::Value(dataRequest);
		Json::Value dataPush;
		dataPush["personID"] = Json::Value(recvFromTrackStruct.s_iPersonID);
		dataPush["CamdId"] = Json::Value(recvFromTrackStruct.s_iCamId);
		dataPush["zoneID"] = Json::Value(recvFromTrackStruct.s_zoneID);
		Json::Value Time;
		Time["sec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_sec);
		Time["usec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_usec);
		dataPush["Time"] = Json::Value(Time);
		msgBody["dataPush"] = Json::Value(dataPush);
	}
	if (true == msgBody.isNull())
	{
		return -1;
	}
	root["msgBody"] = Json::Value(msgBody);
	if (true == root.isNull())
	{
		return -1;
	}
	sendStr = root.toStyledString();
	return 1;
}

/********************************************************************
//change message for client
*********************************************************************/
bool ClientThreadChangeTrackMsgForClient(string srcval, string &dstval)
{
	Json::Reader reader;
	Json::Value rootsrc;
	Json::Value rootdst;
	Json::Value  msgHeadSub;//消息头子节点
	Json::Value  srcBody;//消息体
	Json::Value  dstBody;//消息体

	reader.parse(srcval, rootsrc);
	int code;
	code = rootsrc["msgHead"]["msgCode"].asInt();
	if (code == JSONMSGCODE_CLIENT_TRACK)
	{
		msgHeadSub["host"] = Json::Value("192.168.1.153");
		msgHeadSub["faceDetectIP"] = Json::Value("localhost");
		msgHeadSub["msgType"] = Json::Value(JSONMSGTYPE_REQUEST);
		msgHeadSub["versionNo"] = Json::Value("v1.0.0");
		long long Time = GetTickCount();
		msgHeadSub["timestamp"] = Json::Value(Time);
		msgHeadSub["requestID"] = Json::Value(0);
		msgHeadSub["boundID"] = Json::Value(0);
		msgHeadSub["authorization"] = Json::Value(0);

		msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_CLIENT_TRACE_PERSON_CHANGE_BACK);//20180510_hsq modify msgcode because JSONMSGCODE_CLIENT_TRACK no prase for client in interface and JAVA not define the camera information for logic server
		if (true == msgHeadSub.isNull())
		{
			return -1;
		}
		rootdst["msgHead"] = Json::Value(msgHeadSub);

		srcBody = rootsrc["msgBody"];

		//dstBody["dateRecv"][] = srcBody["dataRequest"]["code"];
		Json::Value dataSend;

		///srcBody["dataPush"]["personID"];
		dataSend["personID"] = srcBody["dataPush"]["personID"];
		dataSend["camID"] = srcBody["dataPush"]["camID"];
		dataSend["platID"] = srcBody["dataPush"]["zoneID"];
		dataSend["LcamID"] = -1;
		dataSend["RcamID"] = -1;
		dataSend["FcamID"] = -1;
		dataSend["BcamID"] = -1;
		//dataSend["traceRoute"][0] = 204;//trace reback camera information
		dataSend["traceRoute"] = srcBody["dataPush"]["traceRoute"];//20180523_hsq  trace reback camera information

		dataSend["code"] = Json::Value(JSONMSGCODE_CLIENT_TRACE_PERSON_ROUTE);
		//Json::Value Time;
		dataSend["Time"]["sec"] = srcBody["dataPush"]["Time"]["sec"];
		dataSend["Time"]["usec"] = srcBody["dataPush"]["Time"]["usec"];
		dstBody["dataSend"] = Json::Value(dataSend);
		rootdst["msgBody"] = Json::Value(dstBody);
		dstval = rootdst.toStyledString();

		return true;
	}
	return false;
};


void ParseTestLibMsgToStr(std::string & sendStr, const char* testJsonAddr);
int TrackServer::sendTrackingMsgToClientThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr)
{
	Json::Value  root;//根节点
	Json::Value  msgHead;//消息头
	Json::Value  msgHeadSub;//消息头子节点
	Json::Value  msgBody;//消息体
						 //组msgHead
	{
		msgHeadSub["host"] = Json::Value("192.168.1.153");
		msgHeadSub["faceDetectIP"] = Json::Value("localhost");
		msgHeadSub["msgType"] = Json::Value(JSONMSGTYPE_REQUEST);
		msgHeadSub["versionNo"] = Json::Value("v1.0.0");
		long long Time = GetTickCount();
		msgHeadSub["timestamp"] = Json::Value(Time);
		msgHeadSub["requestID"] = Json::Value(0);
		msgHeadSub["boundID"] = Json::Value(0);
		msgHeadSub["authorization"] = Json::Value(0);
		//msgHead["msgHead"] = Json::Value(msgHeadSub);


	//	msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_CLIENT_TRACK);
		msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_CLIENT_TRACE_PERSON_CHANGE_BACK);

	}
	if (true == msgHeadSub.isNull())
	{
		return -1;
	}
	root["msgHead"] = Json::Value(msgHeadSub);
	//组msgBady
	{
		Json::Value dataRequest;
		dataRequest["code"] = Json::Value(JSONMSGCODE_CLIENT_TRACK);
		msgBody["dataRequest"] = Json::Value(dataRequest);
		Json::Value dataPush;
		dataPush["personID"] = Json::Value(recvFromTrackStruct.s_iPersonID);
		dataPush["camID"] = Json::Value(recvFromTrackStruct.s_iCamId);
		dataPush["zoneID"] = Json::Value(recvFromTrackStruct.s_zoneID);
		Json::Value Time;
		Time["sec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_sec);
		Time["usec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_usec);
		dataPush["Time"] = Json::Value(Time);
		msgBody["dataPush"] = Json::Value(dataPush);
	}
	if (true == msgBody.isNull())
	{
		return -1;
	}
	root["msgBody"] = Json::Value(msgBody);
	if (true == root.isNull())
	{
		return -1;
	}
	//sendStr = root.toStyledString();
	string temstr = root.toStyledString();
	ClientThreadChangeTrackMsgForClient(temstr, sendStr);
	return 1;
	
}

int TrackServer::sendTrackingMsgToMediaThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr)
{
	Json::Value  root;//根节点
	Json::Value  msgHead;//消息头
	Json::Value  msgHeadSub;//消息头子节点
	Json::Value  msgBody;//消息体
	//组msgHead
	{
		msgHeadSub["host"] = Json::Value("192.168.1.153");
		msgHeadSub["faceDetectIP"] = Json::Value("localhost");
		msgHeadSub["msgType"] = Json::Value(JSONMSGTYPE_REQUEST);
		msgHeadSub["versionNo"] = Json::Value("v1.0.0");
		long long Time = GetTickCount();
		msgHeadSub["timestamp"] = Json::Value(Time);
		msgHeadSub["requestID"] = Json::Value(0);
		msgHeadSub["boundID"] = Json::Value(0);
		msgHeadSub["authorization"] = Json::Value(0);
		//msgHead["msgHead"] = Json::Value(msgHeadSub);


		msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_TAILAFTER_FRAM_OUT);

	}
	if (true == msgHeadSub.isNull())
	{
		return -1;
	}
	root["msgHead"] = Json::Value(msgHeadSub);
	//组msgBady
	{
		Json::Value dataRequest;
		dataRequest["code"] = Json::Value(JSONMSGCODE_TAILAFTER_FRAM_OUT);
		msgBody["dataRequest"] = Json::Value(dataRequest);
		Json::Value dataPush;

		dataPush["camId"] = Json::Value(recvFromTrackStruct.s_iCamId);
		dataPush["zoneID"] = Json::Value(recvFromTrackStruct.s_iCamId);
		Json::Value Time;
		Time["sec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_sec);
		Time["usec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_usec);
		dataPush["Time"] = Json::Value(Time);
		Json::Value ROI;
		ROI["Form"] = Json::Value("RECTANGLE");
		ROI["X"] = Json::Value(recvFromTrackStruct.s_RHumenROI.s_ix);
		ROI["Y"] = Json::Value(recvFromTrackStruct.s_RHumenROI.s_iy);
		ROI["Width"] = Json::Value(recvFromTrackStruct.s_RHumenROI.s_iwidth);
		ROI["Height"] = Json::Value(recvFromTrackStruct.s_RHumenROI.s_ihight);
	//	msgBody["ROI"] = Json::Value(ROI);
		dataPush["ROI"] = Json::Value(ROI);
		msgBody["dataPush"] = Json::Value(dataPush);
	}
	if (true == msgBody.isNull())
	{
		return -1;
	}
	root["msgBody"] = Json::Value(msgBody);
	if (true == root.isNull())
	{
		return -1;
	}
	sendStr = root.toStyledString();
	return 1;
}

int TrackServer::sendTOutCameraMsgToTrackServer(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr)
{
	Json::Value  root;//根节点
	Json::Value  msgHead;//消息头
	Json::Value  msgHeadSub;//消息头子节点
	Json::Value  msgBody;//消息体
	//组msgHead
	{
		msgHeadSub["host"] = Json::Value("192.168.1.153");
		msgHeadSub["faceDetectIP"] = Json::Value("localhost");
		msgHeadSub["msgType"] = Json::Value(JSONMSGTYPE_REQUEST);
		msgHeadSub["versionNo"] = Json::Value("v1.0.0");
		long long Time = GetTickCount();
		msgHeadSub["timestamp"] = Json::Value(Time);
		msgHeadSub["requestID"] = Json::Value(0);
		msgHeadSub["boundID"] = Json::Value(0);
		msgHeadSub["authorization"] = Json::Value(0);
		//msgHead["msgHead"] = Json::Value(msgHeadSub);


		msgHeadSub["msgCode"] = Json::Value(JSONMSGCODE_TAILAFTER_RES_SWAPCAMERA_OUT);

	}
	if (true == msgHeadSub.isNull())
	{
		return -1;
	}
	root["msgHead"] = Json::Value(msgHeadSub);
	//组msgBady
	{
		Json::Value dataRecv;
		dataRecv["code"] = Json::Value(JSONMSGCODE_TAILAFTER_RES_SWAPCAMERA_OUT);
		msgBody["dataRecv"] = Json::Value(dataRecv);
		Json::Value dataSend;

		if (recvFromTrackStruct.s_camStruct.s_LcamID)
		{
			dataSend["cameraId"] = Json::Value(recvFromTrackStruct.s_camStruct.s_LcamID);
		}
		else if (recvFromTrackStruct.s_camStruct.s_RcamID)
		{
			dataSend["cameraId"] = Json::Value(recvFromTrackStruct.s_camStruct.s_RcamID);
		}
		else if (recvFromTrackStruct.s_camStruct.s_FcamID)
		{
			dataSend["cameraId"] = Json::Value(recvFromTrackStruct.s_camStruct.s_FcamID);
		}
		else if (recvFromTrackStruct.s_camStruct.s_BcamID)
		{
			dataSend["cameraId"] = Json::Value(recvFromTrackStruct.s_camStruct.s_BcamID);
		}
		else if (recvFromTrackStruct.s_camStruct.s_UcamID)
		{
			dataSend["cameraId"] = Json::Value(recvFromTrackStruct.s_camStruct.s_UcamID);
		}
		else if (recvFromTrackStruct.s_camStruct.s_DcamID)
		{
			dataSend["cameraId"] = Json::Value(recvFromTrackStruct.s_camStruct.s_DcamID);
		}

		Json::Value Time;
		Time["sec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_sec);
		Time["usec"] = Json::Value(recvFromTrackStruct.s_lTime.tv_usec);
		dataSend["Time"] = Json::Value(Time);
		msgBody["dataSend"] = Json::Value(dataSend);
	}
	if (true == msgBody.isNull())
	{
		return -1;
	}
	root["msgBody"] = Json::Value(msgBody);
	if (true == root.isNull())
	{
		return -1;
	}
	sendStr = root.toStyledString();
	return 1;
}
//DWORD  TrackWorker1();
//void main()
//{
//	TrackWorker1();
//}
//跟踪线程入口函数
DWORD TrackWorker(void * context)
////DWORD TrackWorker()
{
	MSG msg;
	TrackServer mTrackServer;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	std::vector<ConnetTrackSocketStruct> *v_connetTrackSocketStruct;
	std::string sendInitStr;
	int nMsgType, ret;
	Sleep(2000);
	//组init消息  请求跟踪服务器地址   然后发送消息java 线程
	{

		if (mTrackServer.ParseJsonInitMsg(sendInitStr))
		{
			char* sendInitSBuf = (char*)malloc(sendInitStr.size());
			memcpy(sendInitSBuf, sendInitStr.c_str(), sendInitStr.size());
			if (lpJavaThreadId != 0) {
				fprintf(flog_track_init, "[%s] [%d] track send init info to java thread ==== %s\n", __FUNCTION__, __LINE__, sendInitSBuf);
				fflush(flog_track_init);
				int ret = PostThreadMessage(lpJavaThreadId, TRACESERVER_REQUEST_TRACKSERVER_IP, (WPARAM)sendInitSBuf, NULL);
				if (!ret)
				{
					free(sendInitSBuf);
				}
			}
			else {
				fprintf(flog, "erroe lpJavaThreadId ============== %d", lpJavaThreadId);
				//fflush(flog);
			}
		}
	}
	bool testJavaInitMsg = false;
#if INIT_TRACK_FROM_JAVA
	bool get_addr_success = true;
	std::string recvPeekStr;
	while (get_addr_success)
	{
		std::string dealMsgForPeek;
		if (PeekMessage(&msg, 0, 0, 0, NULL))
		{
			ret = GetMessage(&msg, NULL, 0, 0);
			if (ret == -1) {
				fprintf(flog, "[%s] [%d]  GetMessage failed error ==== %d \n", __FUNCTION__, __LINE__, GetLastError());
				//fflush(flog);
				continue;
			}
			char * pInfo = (char *)msg.wParam;
			char *lParam = (char *)msg.lParam;
			fprintf(flog, "track worker queue msg============== %s", pInfo);
			//fflush(flog);
			if (msg.message > WM_USER && msg.message != TRACK_ALIVE_CHECK) {
				recvPeekStr.clear();				
				recvPeekStr = pInfo;				
			}

			switch (msg.message)
			{
			case JAVATHREAD_PUSH_TRACK_INITMSG:
#ifdef TRACK_VALUE_PRINT				
				fprintf(flog_track_init, "[%s] [%d] track recv the java thrad msg ==== %s\n", __FUNCTION__, __LINE__, recvPeekStr.c_str());
				fflush(flog_track_init);
#endif 
			//	ParseTestLibMsgToStr(recvPeekStr, "track_addrbak.json");
			//	printf("[%s] [%d] track recv the java thrad msg ==== %s\n", __FUNCTION__, __LINE__, recvPeekStr.c_str());
				mTrackServer.mTrackServerRunForServer(recvPeekStr, dealMsgForPeek);
				get_addr_success = false;
				break;
			case TRACK_ALIVE_CHECK:
				break;
			default:
				fprintf(flog, "[%s] [%d]  unkown msg type ==== %d \n", __FUNCTION__, __LINE__);
				//fflush(flog);
				break;
			}

		}
	}
#else
	
				std::string recvPeekStr;
				std::string dealMsgForPeek;
				ParseTestLibMsgToStr(recvPeekStr, "track_addrbak.json");
				mTrackServer.mTrackServerRunForServer(recvPeekStr, dealMsgForPeek);
#endif
	int work_num = 0;
	//}/*********************测试向java端发送init消息 end   20180210*************************/
	while (true) {
		while (1)
		{

			std::string dealMsgForPeek;
			std::string dealMsgForTrackServer;
			zmq_pollitem_t items[] = { 0 };
			if (v_connetTrackSocketStruct = mTrackServer.getconnetTrackSocketStruct())
			{

				int size = (*v_connetTrackSocketStruct).size();
				for (int i = 0; i < size; i++)
				{
					items[i].socket = *((*v_connetTrackSocketStruct)[i].s_connetTrackSocket);
					items[i].fd = 0;
					items[i].events = ZMQ_POLLIN;
					items[i].revents = 0;
				}
				//int nRet = zmq_poll(items, size, -1);
				int nRet = zmq_poll(items, size, zmq_poll_timeout);
				if (nRet == 0)
				{
					//没有触发的信息
				}
				else {
					for (int i = 0; i < size; i++)
					{
						if (items[i].revents & ZMQ_POLLIN) {
							//接收到跟踪器发来的消息							
							std::string empty = s_recv(*((*v_connetTrackSocketStruct)[i].s_connetTrackSocket));
							std::string recvFromTrackServer = s_recv(*((*v_connetTrackSocketStruct)[i].s_connetTrackSocket));
#ifdef PERSON_TRACK_PRINT
							fprintf(flog_track, "[%s] [%s] [%d] track recv track result ==== %s\n", get_system_misecond_time(),__FUNCTION__, __LINE__, (char *)recvFromTrackServer.c_str());
							fflush(flog_track);
#endif 
							//处理跟踪的数据
							mTrackServer.mTrackServerRunForTrack(recvFromTrackServer, dealMsgForTrackServer);
						}
					}
				}

			}
			
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

				
				if (msg.message <= WM_USER) {
					continue;
				}

				fprintf(flog,"track worker queue msg============== %s", pInfo);
				//fflush(flog);
				std::string recvPeekStr(pInfo);
				switch (msg.message)
				{
				case TRACK_ALIVE_CHECK:
					nMsgType = TRACK_RETURN_IAM_ALIVE;
					g_trackserver_stralivecheck = (char *)malloc(strlen(TRACK_STILL_ALIVE) + 10);
					memset(g_trackserver_stralivecheck, 0, strlen(TRACK_STILL_ALIVE) + 10);
					strcpy(g_trackserver_stralivecheck, TRACK_STILL_ALIVE);
					if (lpMonitorThreadId != 0) {
						ret = PostThreadMessage(lpMonitorThreadId, nMsgType, (WPARAM)g_trackserver_stralivecheck, NULL);
						if (!postthreadmessage_check(ret)) {
							fprintf(flog, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
							wparam_free(&g_trackserver_stralivecheck);
						}
					}
					else {
						fprintf(flog, "erroe lpMonitorThreadId ============== %d", lpMonitorThreadId);
						//fflush(flog);
					}
					break;
				case CLIENT_TRACK_PERSON_DETAIL:
					fprintf(flog, "track worker recv face client msg ============== %s", pInfo);
					//fflush(flog);
					mTrackServer.mTrackServerRunForServer(recvPeekStr, dealMsgForPeek);
					break;
				case CLIENT_ALARM_DEAL://client deal with alarm msg
					fprintf(flog, "track worker recv face client msg ============== %s", pInfo);
					//fflush(flog);
					mTrackServer.mTrackServerRunForServer(recvPeekStr, dealMsgForPeek);
					break;
				case JAVATHREAD_PUSH_TRACK_INITMSG:
					fprintf(flog, "track worker recv face tell msg ============== %s", pInfo);
					//fflush(flog);
					//cout << "recvPeekStr is:" << recvPeekStr << endl; 
					
					//if(!testJavaInitMsg){
					//	std::string recvPeekStr;
					//	ParseTestLibMsgToStr(recvPeekStr, "track_addrbak.json");
					//	mTrackServer.mTrackServerRunForServer(recvPeekStr, dealMsgForPeek);
					//	testJavaInitMsg = true;
					//}
					break;

				case SHAPE_PERSON_RETELL_REC2_TRACK:
					fprintf(flog, "track worker recv face shape_person_retell ============== %s", pInfo);
					//fflush(flog);
					mTrackServer.mTrackServerRunForServer(recvPeekStr, dealMsgForPeek);
					break;
				case FACE_TELL_RESULT:
#ifdef TRACK_VALUE_PRINT
					fprintf(flog, "track worker recv face tell ============== %s", pInfo);
					//fflush(flog);
#endif 
					mTrackServer.mTrackServerRunForServer(recvPeekStr, dealMsgForPeek);
					break;
				case SHAPE_MSG2_TRACK:
					fprintf(flog_track, "track worker recv face tell msg ============== %s", pInfo);
					fflush(flog_track);
					//cout << "recvPeekStr is:" << recvPeekStr << endl;
					mTrackServer.mTrackServerRunForServer(recvPeekStr, dealMsgForPeek);
					break;
				default:
					fprintf(flog, "type ==== %d track worker recv face tell msg ============== %s", msg.message,pInfo);
					//fflush(flog);
					//cout << "recvPeekStr is:" << recvPeekStr << endl;
					mTrackServer.mTrackServerRunForServer(recvPeekStr, dealMsgForPeek);
					break;
				}
				
				switch (msg.message)
				{
				case TRACK_ALIVE_CHECK:
					wparam_free(&pInfo);
					break;
				case CLIENT_TRACK_PERSON_DETAIL:
				case CLIENT_ALARM_DEAL:
				case JAVATHREAD_PUSH_TRACK_INITMSG:
				case SHAPE_PERSON_RETELL_REC2_TRACK:
				case FACE_TELL_RESULT:
				case SHAPE_MSG2_TRACK:
					wparam_free(&pInfo);
					break;
				default:
					break;
				}
			//	free(()msg.wParam);
			}
			//if (!testJavaInitMsg)
			//{
			//	std::string recvPeekStr;
			//	ParseTestLibMsgToStr(recvPeekStr, "track_addrbak.json");
			//	mTrackServer.mTrackServerRunForServer(recvPeekStr, dealMsgForPeek);
			//	testJavaInitMsg = true;
			//}
		}
		fprintf(flog, "[%s] [%s] [%s] [%d] track worker end timepoint \n", get_system_misecond_time(), __TIME__, __FUNCTION__, __LINE__);
		fflush(flog);
	}
		return 0;
	}

void ParseTestLibMsgToStr(std::string & sendStr, const char* testJsonAddr)
	{
		//std::string configFile = "testLib.json";
		std::string configFile = testJsonAddr;

		//if ((_access(configFile.c_str(), 0)) == -1)
		//{
		//	//cout << "The file config.json dir is NULL" << endl;
		//	return;
		//}
		Json::Reader configReader;
		Json::Value root;
		Json::Value getCameraFrameAddrArr;
		ifstream configFileIn(configFile.c_str(), ios::binary);
		if (configReader.parse(configFileIn, root))
		{
			//Json::Value InitMsg = root["InitMsg"];
			sendStr = root.toStyledString();
			//cout << "configFileIn is :" << sendStr << endl;
		}


	}
