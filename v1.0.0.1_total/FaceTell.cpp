#include "stdafx.h"
#include "FaceTell.h"
#include "common.h"
#include <fstream>
long long face_tell_num = 0;
long long face_dt_num=0;
int g_facedt_faceminisize = 64;
float g_facedt_faceminquality = 0.8;
char *g_facetell_strAliveCheck = NULL;


FaceTell::FaceTell(void *sok)
{
	if (sok == NULL) {
		printf("point is NULL");
		getchar();
	}
	dealer_sok = sok;
}

FaceTell::~FaceTell()
{
}
bool FaceTell::FaceMsgFill(Json::Value *src, Json::Value *ret)
{
	if (src == NULL || ret == NULL) {
		printf("[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
		fprintf(flog,"[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
		//fflush(flog);
	}

	Json::Value sendValue; 
	Json::Value msgBody;
	Json::Value dataRequest;
	Json::Value dataPush;
	Json::Value FaceDetection;

	SetMsgHead(&sendValue, src, JSONMSGTYPE_REQUEST, JSONMSGCODE_FACE_NEED_TELL);
	FaceDetection = (*src)["msgBody"]["dataRecv"]["dataPush"]["FaceDetection"];
	dataPush["similarity"] = nSimilarity;
	dataPush["FaceDetection"] = FaceDetection;
	dataRequest["code"] = JSONMSGCODE_SERVER_FACERECG;
	msgBody["dataRequest"] = dataRequest;
	msgBody["dataPush"] = dataPush;
	sendValue["msgBody"] = msgBody;
	(*ret) = sendValue;
	return true;
}
bool FaceTellMsg2ShapeFormat(Json::Value *src, Json::Value *val)//人脸识别消息组装成shape所需，src提供信息，val返回结果，针对shape算法
{
	point_empty_check(src);
	point_empty_check(val);

	Json::Value sendOut;
	Json::Value	msgBody;
	Json::Value VIPLFaceInfo;
	Json::Value *pVIPLFaceInfo;
	Json::Value *pMaxSimValueFaceMsg,*pMaxSimValueFaceMsgValue;
	Json::Value dataRequest;
	Json::Value dataPush;
	SetMsgHead(&sendOut, src, JSONMSGTYPE_REQUEST, JSONMSGCODE_HUMANSHAPE_ALARM_IN);
	if ((*src)["msgBody"]["dataSend"].isNull()) {
		printf("[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
		fprintf(flog,"[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
		//fflush(flog);
		run_into_exception();
		return false;
	}
	else {
		if ((*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"].isNull()) {
			printf("[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
			fprintf(flog,"[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
			//fflush(flog);
			run_into_exception();
			return false;
		}
		else {
			if ((*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0].isNull()) {
				printf("[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
				fprintf(flog,"[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
				//fflush(flog);
				run_into_exception();
				return false;
			}
			else {
				if ((*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["VIPLFaceInfo"].isNull()) {
					printf("[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
					fprintf(flog,"[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
					//fflush(flog);

					run_into_exception();
					return false;
				}
			}
		}
	}

	pVIPLFaceInfo = &((*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["VIPLFaceInfo"]);	
	pMaxSimValueFaceMsg = &((*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["MaxSimValueFaceMsg"]);
	pMaxSimValueFaceMsgValue = &((*pMaxSimValueFaceMsg)["MaxSimValueFaceMsgValue"]);
	dataRequest["code"] = 0;
	msgBody["dataRequest"] = dataRequest;
	dataPush["camId"] = (*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["camID"];
	dataPush["time"] = (*pMaxSimValueFaceMsgValue)["Time"];
	string RoiPicturePathDir = (*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["capPhotoUrl"].asCString();
	dataPush["RoiPicturePathDir"] = Json::Value(RoiPicturePathDir.c_str());
	string SrcPicturePathDir = (*src)["msgBody"]["dataSend"]["SrcPhotoUrl"].asCString();
	dataPush["SrcPicturePathDir"] = Json::Value(SrcPicturePathDir.c_str());
	dataPush["VIPLFaceInfo"] = (*pVIPLFaceInfo);
	//user for msg filter	
	dataPush["personID"] = (*pMaxSimValueFaceMsgValue)["personID"];
	dataPush["camID"] = (*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["camID"];
	//dataPush["optState"] = 0;

	msgBody["dataPush"] = dataPush;
	sendOut["msgBody"] = msgBody;
	(*val) = sendOut;
	return true;
}
bool FaceTellMsg2SearchFormat(Json::Value *src, Json::Value *val)
{
	if (src == NULL || val == NULL) {
		printf("[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
		fprintf(flog, "[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
		//fflush(flog);
		return false;
	}
	Json::Value value;
	Json::Value dataPush;
	Json::Value dataRequest;
	Json::Value msgBody;
	Json::Value *pMaxSimValueFaceMsgValue;
	Json::Value *pEachFaceComMsgRes0;

	pEachFaceComMsgRes0 = &((*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]);
	

	SetMsgHead(&value, src, JSONMSGTYPE_REQUEST, JSONMSGCODE_FACE_TELL_RESULT);
	dataRequest["code"] = 0;
	dataRequest["msg"] = "";
	//feaUrl
	dataPush["feaUrl"] = (*pEachFaceComMsgRes0).isMember("feaUrl") ? (*pEachFaceComMsgRes0)["feaUrl"]:"";
	//firstWarnTime
	dataPush["firstWarnTime"] = (*pEachFaceComMsgRes0).isMember("firstWarnTime") ? (*pEachFaceComMsgRes0)["firstWarnTime"] : "";
	//imgID
	dataPush["imgID"] = (*pEachFaceComMsgRes0).isMember("imgID") ? (*pEachFaceComMsgRes0)["imgID"] : 9999;
	msgBody["dataPush"] = dataPush;
	msgBody["dataRequest"] = dataRequest;
	value["msgBody"] = msgBody;
	//value["msgHead"]["requestID"] = 1234;// rand() % 2000;
	(*val) = value;
}
bool facetell_msg2_rtsp_format(Json::Value *src, Json::Value *dst)
{
	SetMsgHead(dst, src, JSONMSGTYPE_REQUEST, JSONMSGCODE_RTSP_ALARM_VIDEO_SAVE);
	Json::Value data;
	std::ifstream in_read;
	Json::Reader reader;
	Json::Value envalue;
	Json::Value *pMaxSimValueFaceMsgValue,*pEachFaceComMsgRes0;
	Json::Value msgBody;
	int nMsgId = rand() % (0x10000);
	nMsgId = (nMsgId << 4) + rand() % (0x10000);

	//videoURL
	in_read.open(g_envalue_file, std::ios::binary);
	if (!in_read.is_open()) {
		return false;
	}
	
	if (!reader.parse(in_read, envalue)) {
		return false;
	}
	string sava_ip = envalue.isMember("video_save_url") ? envalue["video_save_url"].asCString() : strServerIP;
	string date = "/" + g_system_date;
	string filetype = "/videotrack";
	//personid
	int personid = 0;
	int  topFaceNum = 0;
	string personname = "";
	string name = "";

	
	if (!(*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["MaxSimValueFaceMsg"].isNull())
	{
		topFaceNum = (*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["topFaceNum"].asInt();
	}
	if (topFaceNum > 0) {
		pMaxSimValueFaceMsgValue = &((*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["MaxSimValueFaceMsg"]["MaxSimValueFaceMsgValue"]);
		personid = (*pMaxSimValueFaceMsgValue)["personID"].asInt();
		personname = (*pMaxSimValueFaceMsgValue)["name"].asCString();		
	}
	else {
		personid = 0;
		personname = "xiaoming";
	}
	name = "/" + to_string(personid) + "_"+personname + "/";

	string videourl = "http://" + sava_ip + "/security/video" + date + name;


	//fprintf(flog_media, "[%s] [%d]  sava_ip == %s\n ", __FUNCTION__, __LINE__, sava_ip);
	//fprintf(flog_media, "[%s] [%d]  date == %s\n ", __FUNCTION__, __LINE__, date);
	//fprintf(flog_media, "[%s] [%d]  name == %s\n ", __FUNCTION__, __LINE__, name);
	fprintf(flog_media, "[%s] [%d]  videourl == %s\n ", __FUNCTION__, __LINE__, videourl.data());
	fflush(flog_media);
	data["videoURL"] = Json::Value(videourl.c_str());
	data["scaleTime"] = envalue.isMember("scaleTime") ? envalue["scaleTime"].asInt() : 5;

//	data["imgID"] = nMsgId;

	pEachFaceComMsgRes0 = &((*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]);

	if (!(*pEachFaceComMsgRes0)["camID"].isNull()) {
		data["camID"] = (*pEachFaceComMsgRes0)["camID"].asInt();
	}
	else {
		data["camID"] = 0;
	}
	if (!(*pEachFaceComMsgRes0)["imgID"].isNull()) {
		data["imgID"] = (*pEachFaceComMsgRes0)["imgID"].asString();
	}
	else {
		data["imgID"] = nMsgId;
	}
	msgBody["data"] = data;
	(*dst)["msgBody"] = msgBody;
	(*dst)["msgBody"]["data"]["videoURL"] = Json::Value(videourl.c_str());
	return true;
}
bool FaceTellMsg2NewAlarm(Json::Value *src, Json::Value * val)//人脸识别的消息过滤给客户端，src提供信息，val返回结果 针对给客户端value
{
	if (src == NULL || val == NULL) {
		printf("[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
		fprintf(flog,"[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
		//fflush(flog);
		return false;
	}

	Json::Value value;
	Json::Reader reader;
	Json::Value	msgHead;
	Json::Value	msgBody;
	Json::Value dataPush;
	Json::Value *pMaxSimValueFaceMsgValue;
	Json::Value *pMaxSimValueFaceMsg;
	Json::Value *pEachFaceComMsgRes0;

	int nMsgId = 0;
	int  topFaceNum = 0;
	if (!(*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["MaxSimValueFaceMsg"].isNull())
	{
		topFaceNum = (*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["topFaceNum"].asInt();
	}
	
	nMsgId = rand() % (0x10000);
	nMsgId = (nMsgId << 4) + rand() % (0x10000);
	
	//if (!value["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["MaxSimValueFaceMsg"].isNull()) 
	if(topFaceNum>0)
	{
		pMaxSimValueFaceMsgValue = &((*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["MaxSimValueFaceMsg"]["MaxSimValueFaceMsgValue"]);
		
#ifdef TELL_STEP_PRINT//TELL_STEP_PRINT
		
		fprintf(flog, "[%s] [%d] pMaxSimValueFaceMsgValue ===== %s\n", __FUNCTION__, __LINE__, (char *)(*pMaxSimValueFaceMsgValue).toStyledString().data());
		fprintf(flog, "[%s] [%d] src Adder === %s\n", __FUNCTION__, __LINE__, (*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["MaxSimValueFaceMsg"]["MaxSimValueFaceMsgValue"]["Adder"].toStyledString().data());
		fprintf(flog, "[%s] [%d] SimValue ==== %f\n", __FUNCTION__, __LINE__, (*pMaxSimValueFaceMsgValue)["SimValue"].asFloat());
		fprintf(flog, "[%s] [%d] Adder ========== %s\n", __FUNCTION__, __LINE__, (*pMaxSimValueFaceMsgValue)["Adder"].toStyledString().data());
		fprintf(flog, "[%s] [%d] personID ==== %d\n", __FUNCTION__, __LINE__, (*pMaxSimValueFaceMsgValue)["personID"]);
		//fflush(flog);
#endif // TELL_STEP_PRINT

		pMaxSimValueFaceMsg = &((*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["MaxSimValueFaceMsg"]);

		dataPush["personID"] = (*pMaxSimValueFaceMsgValue)["personID"];
		string strsrc = (*pMaxSimValueFaceMsgValue)["name"].asCString();
		dataPush["personName"] = Json::Value(strsrc.c_str());// (*pMaxSimValueFaceMsgValue)["name"];
		//string strsrc = (*pMaxSimValueFaceMsgValue)["name"].asCString();
		//string strdst = dataPush["personName"].asCString();
	//	fprintf(flog, "[%s] [%d] strsrc === %s\n", __FUNCTION__, __LINE__, dataPush["personName"].asCString());
		//fprintf(flog, "[%s] [%d] strdst === %s\n", __FUNCTION__, __LINE__, strdst.c_str());
		dataPush["warnDegree"] = (*pMaxSimValueFaceMsgValue)["warnDegree"];
		string strurl = (*pMaxSimValueFaceMsgValue)["libPhotoUrl"].asCString();
		dataPush["libPhotoUrl"] = Json::Value(strurl.c_str());
		dataPush["similarity"] = (*pMaxSimValueFaceMsg)["MaxSimValue"];
	}
	else {
		dataPush["personID"] = 0;
		dataPush["personName"] = "";
		dataPush["warnDegree"] = 0;
		dataPush["libPhotoUrl"] = "";
		dataPush["similarity"] = 0.0;
	}

		pEachFaceComMsgRes0 = &((*src)["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]);
	
		SetMsgHead(&value, src, JSONMSGTYPE_NOTIFY, JSONMSGCODE_FACE_TELL_RESULT);
	//	value["msgHead"] = msgHead;
		msgBody["dataRequest"] = {};
		msgBody["dataRequest"]["code"] = JSONMSGCODE_FACE_TELL_RESULT;
		dataPush["code"] = JSONMSGCODE_CLIENT_NEW_WARNINFO;
		dataPush["msgID"] = nMsgId;
		
	//	dataPush["Age"] = (*pEachFaceComMsgRes0)[0]["FaceAttribute"].isNull() ? 0 : (*pEachFaceComMsgRes0)[0]["FaceAttribute"]["Age"].asInt();
		dataPush["Age"] =(*pEachFaceComMsgRes0)["FaceAttribute"].isNull() ? 0 : (*pEachFaceComMsgRes0)["FaceAttribute"]["Age"].asInt();
		dataPush["Gender"] = (*pEachFaceComMsgRes0)["FaceAttribute"].isNull() ? 0 : (*pEachFaceComMsgRes0)["FaceAttribute"]["Gender"].asInt();
#ifdef TELL_STEP_PRINT
		

		
		fprintf(flog,"[%s] [%d] dataPush[personID] === %s\n", __FUNCTION__, __LINE__, dataPush["personID"]);
		//fflush(flog);
#endif // TELL_STEP_PRINT

		if (!(*pEachFaceComMsgRes0)["camID"].isNull()) {
			dataPush["camID"] = (*pEachFaceComMsgRes0)["camID"];
		}		
		else {
			dataPush["camID"] = 0;
		}
		dataPush["firstWarnTime"] = (*pEachFaceComMsgRes0)["firstWarnTime"];// (*src)["msgHead"]["timestamp"];// (*pMaxSimValueFaceMsgValue)["Time"];
		fprintf(flog,"alarm time get from face tell firstWarnTime ==== %s", dataPush["firstWarnTime"].toStyledString().data());
		
		dataPush["optState"] = UN_DEAL;
		dataPush["optStaff"] = "admin";
		dataPush["belief"] = 0;
		
		dataPush["capPhotoUrl"] = (*pEachFaceComMsgRes0)["capPhotoUrl"];
		dataPush["imgID"] = (*pEachFaceComMsgRes0)["imgID"];
		dataPush["feaUrl"] = (*pEachFaceComMsgRes0)["feaUrl"];
		dataPush["topFaceNum"] = (*pEachFaceComMsgRes0)["topFaceNum"];
		msgBody["dataPush"] = dataPush;
		value["msgBody"] = msgBody;

		(*val) = value;
#ifdef ALARM_INFO_PRINT
		fprintf(flog,"[%s] [%d] FaceTellMsg2NewAlarm value ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
		fflush(flog);
#endif 

		return true;
}
bool face_alarmmsg_status_change(unsigned int personid, stAlarmInfo &new_status)
{
	set<stAlarmInfo>::iterator it;
	unsigned int id = personid;

	for (it = AlarmInfoSet.begin(); it != AlarmInfoSet.end(); it++)
	{
		if (id == (*it).unpersonID) {
			break;
		}
	}
	AlarmInfoSet.erase((*it));
	AlarmInfoSet.insert(new_status);
	return true;
}
bool FaceAlarmMsgFilter(Json::Value *value)//true 需要广播 更新集合，false 不处理
{
	if (value == NULL) {
		fprintf(flog,"[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
		//fflush(flog);
		return false;
	}
	Json::Value dataPush;
	dataPush = (*value)["msgBody"]["dataPush"];
	int nPersonID = (*value)["msgBody"]["dataPush"]["personID"].asInt();
	int nCamID = (*value)["msgBody"]["dataPush"]["camID"].asInt();
	int nOptStatus = (*value)["msgBody"]["dataPush"]["optState"].asInt();
	set<stAlarmInfo>::iterator it;

	WaitForSingleObject(g_alarminfoset_mutex, INFINITE);
	for (it = AlarmInfoSet.begin(); it != AlarmInfoSet.end(); it++)
	{
		if (nPersonID == (*it).unpersonID) {
			break;
		}
	}
	

	if (AlarmInfoSet.begin() != AlarmInfoSet.end()) {
	ReleaseMutex(g_alarminfoset_mutex);
		if (it != AlarmInfoSet.end())//exist
		{
			stAlarmInfo alarm_info = (*it);
			if (nCamID == (*it).unCamID)//yes
			{
				nOptStatus = (*it).usoptState;//pre opt status
				if (nOptStatus != UN_DEAL)//已处理
				{
					if (nOptStatus != TRACING)//追踪中
					{
						if (nOptStatus != END_TRACE)//
						{
							if (nOptStatus == FALSE_ALARM)//误报
							{
								long long nPreAlarmTime = (*it).unWarnTime;
								long long  nCurrentAlarmTime = (*value)["msgBody"]["dataPush"]["firstWarnTime"].asInt64();
								if (nCurrentAlarmTime - nPreAlarmTime < nAlarmPad)//lower
								{
									return false;
								}
								else//greate
								{
									alarm_info.unWarnTime = nCurrentAlarmTime;
									face_alarmmsg_status_change(nPersonID, alarm_info);
									return true;
								}
							}
							else//no
							{
								return false;
							}
						}
						else//追踪结束,need to broadcast
						{
							alarm_info.usoptState = nOptStatus;
							face_alarmmsg_status_change(nPersonID, alarm_info);
							return true;
						}
					}
					else //in tracing,need to broadcast
					{
						alarm_info.usoptState = nOptStatus;
						face_alarmmsg_status_change(nPersonID, alarm_info);
						return true;
					}
				}
				else//pre == UN_DEAL ,need to broadcast
				{
					long long nPreAlarmTime = (*it).unWarnTime;
					long long  nCurrentAlarmTime = (*value)["msgBody"]["dataPush"]["firstWarnTime"].asInt64();
					if (nCurrentAlarmTime - nPreAlarmTime < nAlarmPad)//lower
					{
						return false;
					}
					else
					{
						alarm_info.unWarnTime = nCurrentAlarmTime;
						face_alarmmsg_status_change(nPersonID, alarm_info);
						return true;
					}
					//alarm_info.usoptState = nOptStatus;
					//face_alarmmsg_status_change(nPersonID, alarm_info);
					return true;
				}
			}
			else// camid change,need to broadcast
			{
				alarm_info.unCamID = nCamID;
				face_alarmmsg_status_change(nPersonID, alarm_info);
				return true;
			}
		}
		else //no exist ,need to broadcast
		{
			stAlarmInfo new_alarm;
			new_alarm.unCamID = dataPush["camID"].asInt();
			new_alarm.unFirstTime = dataPush["firstWarnTime"].asInt64();
			//new_alarm.unMsgID = dataPush["msgID"].asInt();
			new_alarm.unpersonID = dataPush["personID"].asInt();
			new_alarm.usoptState = dataPush["optState"].asInt();
			new_alarm.strOptStaff = dataPush["optStaff"].asCString();
			AlarmInfoSet.insert(new_alarm);
			return true;
		}
	}
	else {
		ReleaseMutex(g_alarminfoset_mutex);

		stAlarmInfo new_alarm;
		new_alarm.unCamID = dataPush["camID"].asInt();
		new_alarm.unFirstTime = dataPush["firstWarnTime"].asInt64();
		//new_alarm.unMsgID = dataPush["msgID"].asInt();
		new_alarm.unpersonID = dataPush["personID"].asInt();
		new_alarm.usoptState = dataPush["optState"].asInt();
		new_alarm.strOptStaff = dataPush["optStaff"].asCString();
		AlarmInfoSet.insert(new_alarm);
		return true;
	}
	return true;
}
bool facetell_connect_status_update()
{
#ifdef TELL_STEP_PRINT
	fprintf(flog, "[%s] [%d] recv msg ==== %s\n", __FUNCTION__, __LINE__, "face tell connect already build");
	//fflush(flog);	
#endif
	WaitForSingleObject(m_facetell_mutex, INFINITE);
	face_tell_connect_builded = true;
#ifdef TELL_STEP_PRINT
	fprintf(flog, "[%s] [%d] face tell finaly get the muxtex %s\n", __FUNCTION__, __LINE__);
	//fflush(flog);
#endif	

	ReleaseMutex(m_facetell_mutex);
	return true;
}
bool face_tell_set_alarminfoset(Json::Value &value,int opt_status)
{
	int personId = value["msgBody"]["dataPush"]["personID"].asInt();
	WaitForSingleObject(g_alarminfoset_mutex, INFINITE);	
	set<stAlarmInfo>::iterator it;
	for (it = AlarmInfoSet.begin(); it != AlarmInfoSet.end(); it++) {
		if (personId == (*it).unpersonID) {
			break;
		}
	}
	if (it != AlarmInfoSet.end()) {
		stAlarmInfo alarm_info = (*it);
		face_alarmmsg_status_change(personId, alarm_info);
	}
	ReleaseMutex(g_alarminfoset_mutex);
	return true;
}
bool facetell_combina_face_search_msg(Json::Value &src, Json::Value &dst, void *param)
{
	Json::Value msgHead,msgBody,faceLibArray,clientMsg,data;
	string  str = src.toStyledString().data();
	Json::Reader read;
	long requestid = (long)src["msgHead"]["requestID"].asInt64();
	msgHead = src["msgHead"];
	//faceLibArray
	WaitForSingleObject(g_client_msg_map_mutex, INFINITE);
	//clientMsg =  g_mapmsgclient[requestid];
	read.parse(g_mapmsgclient[requestid], clientMsg);
	if (clientMsg.isNull()) {
		ReleaseMutex(g_client_msg_map_mutex);
		return false;
	}	
	ReleaseMutex(g_client_msg_map_mutex);	
	if (!clientMsg["msgBody"]["data"]["faceLibArray"].isNull())
	{
       faceLibArray = clientMsg["msgBody"]["data"]["faceLibArray"];
	   data["faceLibArray"] = faceLibArray;
	}
	

	int height = 0, width = 0, mul_max = 0, index = 0;

	Json::Value *pFaceInfoArray = &(src["msgBody"]["data"]["FaceInfoArray"]);
	int len = (*pFaceInfoArray).size();
	for (int i = 0; i < len; i++)
	{
		height = (*pFaceInfoArray)[i]["VIPLFaceInfo"]["height"].asInt();
		width = (*pFaceInfoArray)[i]["VIPLFaceInfo"]["width"].asInt();
		if (height * width > mul_max) {
			mul_max = height * width;
			index = i;
		}
	}
	//RoiURL
	data["RoiURL"] = (*pFaceInfoArray)[index]["RoiURL"];

	// faceOutNumber
	if (!clientMsg["msgBody"]["faceOutNumber"].isNull())
	{
		data["faceOutNumber"] = clientMsg["msgBody"]["faceOutNumber"];
	}

	
	//minAlarmThreshold
	if (!clientMsg["msgBody"]["minAlarmThreshold"].isNull())
	{
		data["minAlarmThreshold"] = clientMsg["msgBody"]["minAlarmThreshold"];
	}

	
	msgBody["data"] = data;
	dst["msgBody"] = msgBody;
	/*CUIIJIANHUA + 1v1 + CHANGE + ADD*/
	int nSize = src["msgBody"]["data"]["FaceInfoArray"].size();
	string ssssss = dst.toStyledString();
	for (int i = 0; i < nSize; i++)
	{
		dst["msgBody"]["data"]["FaceInfoArray"][i]["RoiURL"] = Gb2312ToUtf_8_EX(src["msgBody"]["data"]["FaceInfoArray"][i]["RoiURL"].asString());
	}
	string dddd1 = src["msgBody"]["data"]["imgURL"].asString();
	dst["msgBody"]["data"]["imgURL"] = Gb2312ToUtf_8_EX(src["msgBody"]["data"]["imgURL"].asString());
	dst["msgBody"]["data"]["RoiURL"] = Gb2312ToUtf_8_EX(src["msgBody"]["data"]["FaceInfoArray"][0]["RoiURL"].asString());
	/*END*/
	dst["msgHead"] = msgHead;
	return true;
}
DWORD  WINAPI facetell_worker(void * context)
{

	if (context == NULL) {
		fprintf(flog,"[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
		//fflush(flog);
		return -1;
	}

	MSG msg;
	Json::Value value, dataRequest;
	Json::Value sendValue,shapeNeedValue, serverErrList_0, dataPush,client_req,picDataUpate,rtsp_value;
	Json::Reader reader;
	int nJsonMsgCode;
	float similarThread;
	zmq_msg_t msg_recv;
	std::ifstream in;
	int face_number = 0;
	char identity[IDENTITY_STR_LEN] = { 0 };
	
	
	char *strThreadMsg2java = NULL, *strTmp = NULL,*rtsp_str;
	char *strThreadMsg = NULL;
	char *strThreadMsg2broadcast = NULL;
	char *strThreadMsg2dataUpdat = NULL;

	DealerModeSendRecv dealer(context, face_tl_sk);
	int ret = 0;
	int len = 0;
	int topFaceNum = 0;
	int nMsgType = 0, msgType = 0, errorcode = 0;
	int malloc_len_pre = 0,nLenShape = 0,request_id = 0;
	int nMsgType1 = 0;
#ifdef FACETELL_RATE
	int worker_num = 4;
#endif
	FaceTell faceTell(face_tl_sk);
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	
//第一次给FaceDetect发送数据建立连接
	in.open("server_send_face_tell_connect_req.json", std::ios::binary);
	if (!in.is_open()) {
		printf("[%s] [%d]  open server_send_face_tell_connect_req.json failed\n", __FUNCTION__, __LINE__);
		getchar();
		return -1;
	}
		

	if (!reader.parse(in, value))
	{
		printf("[%s] [%d]  parse server_send_face_tell_connect_req.json failed\n", __FUNCTION__, __LINE__);
		getchar();
		return -1;
	}
	int len_req = strlen((char *)value.toStyledString().data());
//	len = zmq_send(face_tl_sk, "", 0, ZMQ_SNDMORE);
	char empty[] = { "" };
	s_sendmore(face_tl_sk, empty);
	
#ifdef TELL_STEP_PRINT
	fprintf(flog, "[%s] [%d]  face tell send req msg ==== %s\n", __FUNCTION__, __LINE__,(char *)value.toStyledString().data());
#endif
//	len = zmq_send(face_tl_sk, value.toStyledString().data(), len_req, 0);
	s_send(face_tl_sk, (char *)value.toStyledString().data());
//	zmq_send_check(len);

	while (true) {
			zmq_pollitem_t items[] = { { face_tl_sk,0,ZMQ_POLLIN,0 } };

			zmq_poll(items, 1, zmq_poll_timeout);
			if (items[0].revents & ZMQ_POLLIN) {	
			zmq_msg_init(&msg_recv);
			zmq_msg_recv(&msg_recv, face_tl_sk, 0);
	
			ret = zmq_msg_recv(&msg_recv, face_tl_sk, 0);
#ifdef TELL_STEP_PRINT		

			//fprintf(flog,"[%s] [%d] face tell receive msg content ==== %s\n", __FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
			//fflush(flog);

#endif
			value.clear();
			sendValue.clear();
			shapeNeedValue.clear();
			nJsonMsgCode = 0;
			string strMsg;
			string str = (char *)zmq_msg_data(&msg_recv);
		//	fprintf(flog, "[%s] [%d] face tell receive msg content ==== %s\n", __FUNCTION__, __LINE__, str.c_str());
			if (ret&&reader.parse((char *)zmq_msg_data(&msg_recv), value)) {
				nJsonMsgCode = value["msgHead"]["msgCode"].asInt();				
				fprintf(flog, "[%s] [%d] face tell msg after parse ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
				fflush(flog);
				switch (nJsonMsgCode)
				{
				case JSONMSGCODE_FACE_TELL_RESULT:
#ifdef FACETELL_RATE
					worker_num++;//add one worker
#endif 
					nMsgType = FACE_TELL_RESULT;
						topFaceNum = value["msgBody"]["dataSend"]["EachFaceComMsgRes"][0]["topFaceNum"].asInt();
						
						printf("[%s] [%d] face_number  ==== %d ************************** \n", __FUNCTION__, __LINE__, topFaceNum);
						
						FaceTellMsg2NewAlarm(&value, &sendValue);//FaceIDFMsg.json -> E:\svn\MsgHeadFile\客户端消息应答推送\服务器推送\new_warn.json
						FaceTellMsg2ShapeFormat(&value, &shapeNeedValue);//FaceIDFMsg.json ->形体分析仪.json
						//combina msg for searhc
						FaceTellMsg2SearchFormat(&value, &picDataUpate);

						if(!FaceAlarmMsgFilter(&sendValue)) {//不需要广播，直接返回 sendValue 针对给客户端
							break;
						}
						postthreadmessage_mem_malloc(&strThreadMsg2java, &sendValue);
						postthreadmessage_mem_malloc(&strThreadMsg2broadcast, &sendValue);
						//combian msg with data update
						postthreadmessage_mem_malloc(&strThreadMsg2dataUpdat, &picDataUpate);
						
#ifdef TELL_STEP_PRINT					
						fprintf(flog,"[%s] [%d] shapeNeedValue == %s\n", __FUNCTION__, __LINE__, (char *)shapeNeedValue.toStyledString().data());						
#endif
						postthreadmessage_mem_malloc(&strTmp, &shapeNeedValue);

#ifdef TELL_STEP_PRINT
						fprintf(flog,"[%s] [%d]   ==== %s\n", __FUNCTION__, __LINE__, "send msg to JavaThread");
						//fflush(flog);
#endif
						if (lpJavaThreadId != 0) {
							ret = PostThreadMessage(lpJavaThreadId, nMsgType, (WPARAM)strThreadMsg2java, NULL);
							if (ret == 0) {
								fprintf(flog,"[%s] [%d] send to lpJavaThreadId failed\n", __FUNCTION__, __LINE__);
								//fflush(flog);
								wparam_free(&strThreadMsg2java);
							}
						}
#ifdef TELL_STEP_PRINT
						fprintf(flog,"[%s] [%d]   ==== %s\n", __FUNCTION__, __LINE__, "send msg to lpBroadCastThreadId");
						//fflush(flog);
#endif
						//send to search
						if (lpPicSearchThreadId) {//strThreadMsg2dataUpdat
							nMsgType1 = FACETELL_RESULT2_DATA_UPATE;
							ret = PostThreadMessage(lpPicSearchThreadId, nMsgType1, (WPARAM)strThreadMsg2dataUpdat, NULL);
							if (ret == 0) {
								fprintf(flog, "[%s] [%d] send to lpPicSearchThreadId failed\n", __FUNCTION__, __LINE__);								
								wparam_free(&strThreadMsg2dataUpdat);
							}
						}

						if (topFaceNum <= 0) {//cap alarm not need broadcast
							break;
						}
						printf("[%s] [%d] ****************************************************************** \n", __FUNCTION__, __LINE__);
						fprintf(flog, "[%s] [%d] ****************************************************************** \n", __FUNCTION__, __LINE__);

						if (lpBroadCastThreadId != 0) {
							ret = PostThreadMessage(lpBroadCastThreadId, nMsgType, (WPARAM)strThreadMsg2broadcast, NULL);
							if (ret == 0) {
								fprintf(flog,"[%s] [%d] send to lpBroadCastThreadId failed\n", __FUNCTION__, __LINE__);
								//fflush(flog);
								wparam_free(&strThreadMsg2broadcast);
							}
							//fprintf(flog, "face_tell send a Alarm Msg to lpBroadCastThreadId success", __FUNCTION__, __LINE__);

						}
#ifdef PERSON_TRACK_PRINT
						fprintf(flog_track,"[%s] [%s] [%d]   face tell send strTmp to shape ==== %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)strTmp);
						fflush(flog_track);
#endif
						if (lpShapeThreadId != 0) {
							nMsgType = FACE_TELL_RESULT;
							ret = PostThreadMessage(lpShapeThreadId, nMsgType, (WPARAM)strTmp, NULL);
							if (ret == 0) {
								fprintf(flog,"[%s] [%d] send to lpShapeThreadId failed\n", __FUNCTION__, __LINE__);
								//fflush(flog);
								wparam_free(&strTmp);
							}
						}

#ifdef TELL_STEP_PRINT
						fprintf(flog, "[%s] [%d]   ==== %s\n", __FUNCTION__, __LINE__, "send msg to lpRtspThreadId");
						//fflush(flog);
#endif
						facetell_msg2_rtsp_format(&value,&rtsp_value);
						postthreadmessage_mem_malloc(&rtsp_str, &rtsp_value);
						fprintf(flog_media, "[%s] [%d]  rtsp_str ==== %s\n", __FUNCTION__, __LINE__, rtsp_str);
						fflush(flog_media);
						if (lpRtspThreadId != 0) {
							ret = PostThreadMessage(lpRtspThreadId, nMsgType, (WPARAM)rtsp_str, NULL);
							if (ret == 0) {
								fprintf(flog, "[%s] [%d] send to lpRtspThreadId failed\n", __FUNCTION__, __LINE__);
								//fflush(flog);
								wparam_free(&strTmp);
							}
						}
#ifdef TELL_STEP_PRINT
						//fprintf(flog, "[%s] [%d]   ==== %s\n", __FUNCTION__, __LINE__, "send msg to lpRtspThreadId");
						////fflush(flog);
						//if (lpTrackThreadId != 0) {
						//	ret = PostThreadMessage(lpTrackThreadId, nMsgType, (WPARAM)strTmp, NULL);
						//	if (ret == 0) {
						//		fprintf(flog, "[%s] [%d] send to lpRtspThreadId failed\n", __FUNCTION__, __LINE__);
						//		//fflush(flog);
						//		wparam_free(&strTmp);
						//	}
						//}
#endif 

				//	}
				break;
				case JSONMSGCODE_FACE_TELL_CONNECT_REPLY:	
					facetell_connect_status_update();
				break;
				//case JSONMSGCODE_FACEIDF_FACEFEATURES_OUT:
				//	nMsgType = FACEDETECTION_ONEPICTURE;//特征值返回给java
				//	postthreadmessage_mem_malloc(malloc_len_pre, &strThreadMsg, &value);
				//	ret = PostThreadMessage(lpJavaThreadId, nMsgType, (WPARAM)strThreadMsg, NULL);
				//	postthreadmessage_check(ret);
				//	break;
				//case JSONMSGCODE_FACEDETECTION_ONEPICTURE://计算单张图片人脸特征值
				//	nMsgType = FACEDETECTION_ONEPICTURE;//特征值返回给java
				//	postthreadmessage_mem_malloc(&malloc_len_pre, &strThreadMsg, &value);
				//	ret = PostThreadMessage(lpJavaThreadId, nMsgType, (WPARAM)strThreadMsg, NULL);
				//	postthreadmessage_check(ret);
				//	break;
				case JSONMSGCODE_FACEDETECTION_PICTUREDIR_OUT://文件夹特征值返回
					nMsgType = FACEDETECTION_PICTUREDIR_IN;//特征值返回给java

					//postthreadmessage_mem_malloc(&strThreadMsg, &value);
					strThreadMsg = (char *)malloc(str.length() + 100);
					memset(strThreadMsg, 0, str.length() + 100);

					//	strncpy((*p_str), (*p_value).toStyledString().data(), len);
					memcpy(strThreadMsg, str.data(), str.length());

					strMsg=value["msgBody"]["dataSend"]["FeaDir"].asCString();

					//strMsg = G2U(strThreadMsg);
					printf("[%s] [%d]   face tell send msg to pic search ==== %s\n", __FUNCTION__, __LINE__, strThreadMsg);
					//printf("  this face need search!!");

					if (lpJavaThreadId != 0) {
						ret = PostThreadMessage(lpJavaThreadId, nMsgType, (WPARAM)strThreadMsg, NULL);
						if (!postthreadmessage_check(ret)) {
							fprintf(flog_pic_in, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
							//fflush(flog);
							wparam_free(&strThreadMsg);
						}
					}
					else {
						fprintf(flog_pic_in, "erroe lpJavaThreadId ============== %d", lpJavaThreadId);
						//fflush(flog);
					}
					fflush(flog_pic_in);
					break;
				case JSONMSGCODE_JAVA_CHANGE_FACELIB://face tell reply to java th,need to chek msgType 
					postthreadmessage_mem_malloc(&strThreadMsg, &value);
					if (lpJavaThreadId != 0) {
						ret = PostThreadMessage(lpJavaThreadId, FACETH_REPLY2_JAVAREQ_CHANGE_FACELIB, (WPARAM)strThreadMsg, NULL);
						if (!postthreadmessage_check(ret)) {
							fprintf(flog, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
							//fflush(flog);
							wparam_free(&strThreadMsg);
						}
					}
					else {
						fprintf(flog, "erroe lpJavaThreadId ============== %d", lpJavaThreadId);
						//fflush(flog);
					}
					break;
				case JSONMSGCODE_JAVA_CHANGE_CAMERA:
					msgType = value["msgHead"]["msgType"].asInt();
					if (msgType == JSONMSGTYPE_RESPONSE) {
						trans_msg2_another_thread(FACEDT_CHANGE_FACEDETECTION_CAMERA, &value, lpJavaThreadId,&g_common_str_facetell,NULL);
					}
					break;
				case JSONMSGCODE_JAVA_CHANGE_STATEG:
					msgType = value["msgHead"]["msgType"].asInt();
					if (msgType == JSONMSGTYPE_RESPONSE) {
						trans_msg2_another_thread(FACETELL_CHANGE_CAMERA_STATEG, &value, lpJavaThreadId,&g_common_str_facetell,NULL);
					}
					break;		
				case JSONMSGCODE_CLIENT_GET_FACE_CHECKIN_BACK:
					msgType = value["msgHead"]["msgType"].asInt();
					if (msgType == JSONMSGTYPE_RESPONSE) {
#ifdef CLIENT_ONE_VS_ONE
						fprintf(flog_one_vs_one,"[%s] [%s] [%d] value ===== %s \n", get_system_misecond_time(), __FUNCTION__, __LINE__,(char *)value.toStyledString().data());
						fflush(flog_one_vs_one);
#endif 
						trans_msg2_another_thread(FACETELL_GET_FACE_CHECKIN, &value, lpClientThreadId,&g_common_str_facetell,NULL);
					}
					break;
				case JSONMSGCODE_CLIENT_GET_USING_IMG_CHECKIN_IMG_BACK:
#ifdef PIC_WITH_PIC_PRINT				
					fprintf(flog_search, "g_face_search_index == %d [%s] [%s] [%d] face tell receive search result msg == %s\n",(g_face_search_index++), get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)msg.wParam);
					fflush(flog_search);
#endif
					msgType = value["msgHead"]["msgType"].asInt();
					if (msgType == JSONMSGTYPE_RESPONSE) {
						errorcode = value["msgBody"]["dataSend"]["code"].asInt();
						if (errorcode == JSONMSGCODE_FACEDT_GET_FACE_CHECKIN_NO_READ_PIC || \
							errorcode == JSONMSGCODE_FACEDT_GET_FACE_CHECKIN_FACE_UNQUA || \
							errorcode == JSONMSGCODE_FACEDT_NO_FACE_DT) {//come out error to client
							value["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_GET_USING_IMG_CHECKIN_IMG_BACK;
							value["msgBody"]["dataSend"]["resReallyCount"] = 0;
							trans_msg2_another_thread(FACETELL_SEARCH_PIC_FAILED, &value, lpClientThreadId,&g_common_str_facetell,NULL);
							break;
						}
						dataRequest["code"] = 0;
						dataRequest["msg"] = "";
						//request_id = value["msgBody"]["requestID"].asInt64();
						//client_req = g_mapmsgpisearch[request_id];
						//if (!client_req.isNull()) {
						//	similarThread = client_req["msgBody"]["dataPush"]["similarThread"].asFloat();
						//}
						similarThread = value["msgBody"]["dataRecv"]["similarThread"].asFloat();
						value["msgBody"]["dataRequest"] = dataRequest;
						dataPush = value["msgBody"]["dataSend"];
						dataPush["similarThread"] = similarThread;
						value["msgBody"]["dataPush"] = dataPush;
						value["msgBody"].removeMember("dataSend");
						value["msgBody"].removeMember("dataRecv");
						value["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_GET_USING_IMG_CHECKIN_IMG;
#ifdef TELL_STEP_PRINT
						fprintf(flog, "[%s] [%d]   face tell send msg to pic search ==== %s\n", __FUNCTION__, __LINE__,(char *)value.toStyledString().data());
						fflush(flog);						
#endif
						trans_msg2_another_thread(FACETELL_RETURN_PIC_SEARCH_RESULT, &value, lpPicSearchThreadId,&g_common_str_facetell,NULL);
					}
					break;
				case JSONMSGCODE_CLIENT_GET_FACE_CHECKIN_N:
#ifdef FACE_SEARCH_PRINT				
					fprintf(flog_facesearch, "[%s] [%s] [%d] face tell receive face search result msg == %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
					fflush(flog_facesearch);
#endif
					msgType = value["msgHead"]["msgType"].asInt();
					if (msgType == JSONMSGTYPE_RESPONSE) {
						trans_msg2_another_thread(FACETELL_RETURN_FACE_SEARCH_RESULT, &value, lpClientThreadId, &g_common_str_facetell, NULL);
					}
					break;
				default:
				break;
				}
				fflush(flog);
			}
			else {
			json_parse_fail();
			}
			zmq_msg_close(&msg_recv);
	}
	

		if (PeekMessage(&msg, 0, 0, 0, NULL))
		{
			memset(&msg, 0, sizeof(msg));
			ret = GetMessage(&msg, NULL, 0, 0);
			if (ret == -1) {
				fprintf(flog, "[%s] [%d]  GetMessage failed error ==== %d \n", __FUNCTION__, __LINE__, GetLastError());				
				continue;
			}
			char * pInfo = (char *)msg.wParam;	
			char *lParam = (char *)msg.lParam;
		
			int alive_msg = FACETELL_ALIVE_CHECK;

			if (msg.message <= WM_USER) {
				continue;
			}

			if (!parse_queuemsg2_json(pInfo, reader, value, msg, &alive_msg))//parse pInfo2 Json fail
			{
			//	continue;
			}
			else
			{
#ifdef TELL_STEP_PRINT			
			//	if (msg.message != FACETELL_ALIVE_CHECK) {
					fprintf(flog, "face tell worker queue msg============== %s", pInfo);
					fflush(flog);
			//	}
#endif
			}
			string buff;
			switch (msg.message)
			{
			case FACEDETECT_NEED_FACETELL:
#ifdef FACETELL_RATE
				if (worker_num <= 0) {//worker all used
					break;
				}
				//else {
				//	worker_num--;//worker reduce
				//}
#endif 

				faceTell.FaceMsgFill(&value, &sendValue);
#ifdef TELL_STEP_PRINT
				fprintf(flog,"[%s] [%d] %s\n", __FUNCTION__, __LINE__, "send msg to face tell al");
				//fflush(flog);			
#endif
				if (dealer.SendDealerMsg((char *)msg.wParam))
				{
					//printf("[%s] [%d] face tell send a facerecognize msg ****id is [%d] \n", __FUNCTION__, __LINE__,face_dt_num++);
					printf("[%s] [%d] face tell send a facerecognize msg \n", __FUNCTION__, __LINE__);
#ifdef FACETELL_RATE
					worker_num--;

					printf(" face tell worker number is: %d\n", __FUNCTION__, __LINE__, worker_num);
#endif
				}
				
				break;
			case FACEIDF_FACEFEATURES_IN:
#ifdef PICS_IN_LIB_PRINT
			//	printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, "face tell send face dt pic_in_lib msg to face tell al");
				fprintf(flog_pic_in,"[%s] [%d] %s\n", __FUNCTION__, __LINE__, "face tell send face dt pic_in_lib msg to face tell al");
				fflush(flog_pic_in);
				
#endif
				
				//buff = (char *)msg.wParam;
				//printf( "[%s] [%d] %s\n", __FUNCTION__, __LINE__, (char *)msg.wParam);
				dealer.SendDealerMsg((char *)msg.wParam);
				
				break;
			case FACETELL_ALIVE_CHECK:
#ifdef TELL_STEP_PRINT				
				//fprintf(flog, "[%s] [%d] msg.wParam == %x\n", __FUNCTION__, __LINE__, msg.wParam);
				////fflush(flog);
#endif
				nMsgType = FACETELL_RETURN_IAM_ALIVE;	
				g_facetell_strAliveCheck = (char *)malloc(strlen(FACETELL_STILL_ALIVE) + 10);
				memset(g_facetell_strAliveCheck, 0, strlen(FACETELL_STILL_ALIVE) + 10);
				strcpy(g_facetell_strAliveCheck, FACETELL_STILL_ALIVE);
				if (lpMonitorThreadId != 0) {
					ret = PostThreadMessage(lpMonitorThreadId, nMsgType, (WPARAM)g_facetell_strAliveCheck, NULL);
					if (!postthreadmessage_check(ret)) {
						fprintf(flog, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
						wparam_free(&g_facetell_strAliveCheck);
					}
				}
				else {
					fprintf(flog, "erroe lpMonitorThreadId ============== %d", lpMonitorThreadId);
					//fflush(flog);
				}
				
				break;
			case SERVER_TRANS_JAVAREQ_CHANGE_FACELIB:
#ifdef TELL_STEP_PRINT				
				fprintf(flog, "[%s] [%d] face tell send change facelib msg == %x\n", __FUNCTION__, __LINE__, (char *)msg.wParam);
				//fflush(flog);
#endif
				dealer.SendDealerMsg((char *)msg.wParam);
				
				break;
			case JAVA_CHANGE_STATEG:
#ifdef TELL_STEP_PRINT				
				fprintf(flog, "[%s] [%d] face tell send change stateg msg == %x\n", __FUNCTION__, __LINE__, (char *)msg.wParam);
				//fflush(flog);
#endif
				dealer.SendDealerMsg((char *)msg.wParam);
				
				break;
			//case JAVA_CHANGE_CAMERA:
			//	dealer.SendDealerMsg((char *)msg.wParam);
			//	break;
			case FACEDT_GET_FACE_CHECKIN:
#ifdef CLIENT_ONE_VS_ONE				
			//	fprintf(flog_one_vs_one,"[%s] [%d] face tell send face_checkin msg == %s\n", __FUNCTION__, __LINE__, (char *)msg.wParam);				
				fprintf(flog_one_vs_one,"[%s] [%s] [%d] face tell send one vs one to face tell al \n", get_system_misecond_time(),__FUNCTION__, __LINE__);
				fflush(flog_one_vs_one);
#endif
				dealer.SendDealerMsg((char *)msg.wParam);
				
				break;
			case FACEDT_GET_USING_IMG_CHECKIN_IMG_SUCCESS:
#ifdef PIC_WITH_PIC_PRINT				

				fprintf(flog_search, "g_face_search_index === %d [%s] [%s] [%d] face tell send search msg to al == %s\n",(g_face_search_index++), get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)msg.wParam);
				fflush(flog_search);

#endif
				dealer.SendDealerMsg((char *)msg.wParam);
				break;		
			case FACEDT_FACE_SEARCH_SUCCESS:
			{


				facetell_combina_face_search_msg(value, sendValue, NULL);
				dealer.SendDealerMsg((char *)sendValue.toStyledString().data());
#ifdef FACE_SEARCH_PRINT				
				fprintf(flog_facesearch, "[%s] [%s] [%d] face tell send face search msg to al == %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)sendValue.toStyledString().data());
				fflush(flog_facesearch);
#endif
			}
				break;
			case CLIENT_UPDATE_ALARM_SET:
				//set AlarmInfoSet 
				face_tell_set_alarminfoset(value, TRACING);
				break;
			default:
				break;
			}
			fflush(flog);
			
			switch (msg.message)//free case 
			{
			case FACEDETECT_NEED_FACETELL:
				wparam_free(&pInfo);
				break;
			case FACEIDF_FACEFEATURES_IN:
			
			case SERVER_TRANS_JAVAREQ_CHANGE_FACELIB:
			case JAVA_CHANGE_STATEG:
			case FACEDT_GET_FACE_CHECKIN:
			case FACEDT_GET_USING_IMG_CHECKIN_IMG_SUCCESS:
				wparam_free(&pInfo);
				break;
			case FACETELL_ALIVE_CHECK:
				wparam_free(&pInfo);
				break;
			case FACEDT_FACE_SEARCH_SUCCESS:
				wparam_free(&pInfo);
				break;
			default:
				break;
			}
		}

	
	//fprintf(flog,"[%s] [%d]   ==== %s\n", __FUNCTION__, __LINE__, "face tell stop");
	//fflush(flog);

		strThreadMsg = NULL;
		strTmp = NULL;
	}
	getchar();
	return 0;

}
