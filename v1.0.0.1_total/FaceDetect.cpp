#include "stdafx.h"
#include "FaceDetect.h"
#include "common.h"
#include <fstream>
int nFaceDetectStrategy = 1;
Json::Value facedt_java_change_camera;
char *g_facedt_strAliveCheck = NULL;
FaceDetect::FaceDetect()
{
}
bool FaceDetect::InitParm(void *context, const int nMsgCode, Json::Value *value,void *soc)
{
	if (context == NULL || value == NULL | soc == NULL) {
		return false;
	}
	ctx = context;
	code = nMsgCode;
	val = value;
	socket = soc;
}

bool FaceDetect::FaceDetectSetResponse(Json::Value *value)
{
	if (value == NULL) {
		printf("value point is NULL");
		getchar();
		return false;
	}
	SetMsgHead(value, val, JSONMSGTYPE_RESPONSE, JSONMSGCODE_FACEDETECTED_MSG);
	Json::Value msgBody;
	Json::Value dataSend;
	Json::Value dataRecv;

	dataSend["code"] = JSONMSGCODE_SERVER_RESPONSE_OK;
#ifdef DEBUG
	dataSend["msgString"] = "server_response_ok_for_face_dt_msg";
#endif

	msgBody["dataSend"] = dataSend;
	msgBody["dataRecv"] = dataRecv;

	msgBody["dataSend"] = dataSend;
	msgBody["dataRecv"] = dataRecv;

	(*value)["msgBody"] = msgBody;
	return true;
}
bool FaceDetect::FaceDetectHandle()
{
	char number[10] = { 0 };
	Json::Value value = *val;
	Json::Value FaceDetection;
	Json::Value dataPush;

	if (value.isMember("msgBody")) {
		if (value["msgBody"].isMember("dataPush")) {
			dataPush = value["msgBody"]["dataPush"];
			if (value["msgBody"]["dataPush"].isMember("FaceDetection")) {
				FaceDetection = value["msgBody"]["dataPush"]["FaceDetection"];
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
#if 1
	//È¡Number
	strcpy(number, dataPush["Number"].toStyledString().data());

	int num = atoi(number);
#if 0
//	int nFramStrLen = strlen((char *)FaceDetection["src_mat"].toStyledString().data());

//	char *pSrcStr = (char *)malloc(nFramStrLen + 1);
//	memset(pSrcStr, 0, nFramStrLen + 1);
	//È¡Ô´Í¼Êý¾Ý
//	strcpy(pSrcStr, (char *)FaceDetection["src_mat"].toStyledString().data());

//	printf("FramStr ============== %s\n", pSrcStr);


#if 0 //²âÊÔÍ¼Æ¬Êý¾ÝÊÇ·ñÕý³£
	std::vector<uchar> showdata(FramStr.begin(), FramStr.end());
	cv::Mat srcImg = cv::imdecode(showdata, CV_LOAD_IMAGE_COLOR);
	cv::imshow("test", srcImg);
cv:cvWaitKey(1000);
#endif
	
//	FaceDetection["src_mat"] = "";
	int nSrcNameLen = strlen((char *)dataPush["srcPictureStr"].toStyledString().data());
	
	char *srcName = (char *)malloc(nSrcNameLen + 1);
	memset(srcName, 0, nSrcNameLen + 1);
	//Ô´Í¼Ãû×Ö
	strncpy(srcName, (char *)dataPush["srcPictureStr"].toStyledString().data(), nSrcNameLen - 2);
//	printf("name ============== %s\n", srcName);

	
	int nSrcStrNameLen = strFaceDetectUrl.size() + 2 + nSrcNameLen + 1;
	char *srcStrName = (char *)malloc(nSrcStrNameLen);
	memset(srcStrName, 0, nSrcStrNameLen);
	//Ô´Í¼Â·¾¶
//	sprintf(srcStrName, "%s%s%s", strFaceDetectUrl.c_str(), "\\", &srcName[1]);

//	printf("srcStrName ============= %s\n", srcStrName);
	FILE *srcFile = fopen(srcStrName, "w");
	if (srcFile != NULL) {
		fwrite(&srcStrName, nSrcStrNameLen, 1, srcFile);
		fclose(srcFile);
	}
	//°Ñ½ØÍ¼Êý¾Ý±£´æµ½ÎÄ¼þ
	FILE *capFile;

	char capFilePath[100] = { 0 };
	int nCapNameLen = 0, nCapDataLen = 0;

	char *pCapNameCont = NULL, *pCapDataCont = NULL;
	for (int i = 0; i < num; i++) {
		nCapNameLen = strlen((char *)FaceDetection[i]["Value"]["FacePicture"].toStyledString().data());
	//	nCapDataLen = strlen((char *)FaceDetection[i]["Value"]["mat"].toStyledString().data());
		pCapNameCont = (char *)malloc(nCapNameLen + 1);
	//	pCapDataCont = (char *)malloc(nCapDataLen + 1);
		memset(pCapNameCont, 0, nCapNameLen + 1);
	//	memset(pCapDataCont, 0, nCapDataLen + 1);
		strncpy(pCapNameCont, FaceDetection[i]["Value"]["FacePicture"].toStyledString().data(), nCapNameLen - 2);
	//	strncpy(pCapDataCont, FaceDetection["Value"][i]["mat"].toStyledString().data(), nCapDataLen - 2);
	//	printf("capName =============== %s\n", pCapNameCont);
	//	printf("pCapDataCont =============== %s\n", pCapNameCont);
		//int ncapPathLen = strFaceDetectUrl.size() + 2 + nCapNameLen + 1;
		//sprintf(capFilePath, "%s%s%s", strFaceDetectUrl.c_str(), "\\", &pCapNameCont[1]);
		//capFile = fopen(capFilePath, "w");
		//if (capFile != NULL) {
		//	fwrite(&pCapDataCont, nCapDataLen, 1, capFile);
		//	fclose(capFile);
		//}
	//	FaceDetection["Value"][i]["mat"] = "";

		free(pCapNameCont);
//		free(pCapDataCont);
	}

	FILE *pointFile;
	char pointPath[100] = { 0 };
	sprintf(pointPath, "%s%s%s", strFacePointInfoUrl.c_str(), "\\", "pointInfo.txt");
	pointFile = fopen(pointPath, "w+");
	int nPointLen = strlen(value.toStyledString().data());
	if (pointFile != NULL) {

		fwrite(value.toStyledString().data(), nPointLen, 1, pointFile);
		fclose(pointFile);
	}
	fclose(srcFile);
	free(srcName);
//	free(pSrcStr);
#endif
#endif
	return true;
}
FaceDetect::~FaceDetect()
{}
bool facedetection_result(Json::Value *val)
{
	point_empty_check(val);
	int ncode = 0;
	if ((*val)["msgBody"].isNull())return false;
	if ((*val)["msgBody"]["dataSend"].isNull())return false;
	if ((*val)["msgBody"]["dataSend"]["code"].isNull())return false;
	
	ncode = (*val)["msgBody"]["dataSend"]["code"].asInt();
	if (ncode == 0) {
		return true;
	}
	else {
		return false;
	}
}
bool facedt_recombind_java_change_camera_req(Json::Value &src,Json::Value &dst)
{
	Json::Value msgHead, dataRequest, dataPush, cameraList, cameralist_child, msgBody;
	Json::Value cameraInfo, cluster, cluster_child, meadiaRtspAddr, strategy,facedt_camera_list;
	int len,i, j,leng, faceMinSize = 0,  clusterType = 0;
	float faceMinQuality =  0.0;
	//fill with msgHead
	msgHead = src["msgHead"];
	msgHead["msgCode"] = JSONMSGCODE_MEDIA_CHANGE_CAMERA;
	dst["msgHead"] = msgHead;

	//fill with msgBody
	dataRequest["code"] = 0;
	if (src["msgBody"]["dataPush"].isMember("cameraChangeType")) {
		dataPush["cameraChangeType"] = src["msgBody"]["dataPush"]["cameraChangeType"];
	}
	else {
		printf("[%s] [%d] need cameraChangeType", __FUNCTION__, __LINE__);
		getchar();
		return false;
	}

	if (src["msgBody"]["dataPush"].isMember("cameraList")) {
	cameraList = src["msgBody"]["dataPush"]["cameraList"];
	}
	else {
		printf("[%s] [%d] need cameraList", __FUNCTION__, __LINE__);
		getchar();
		return false;
	}
	len = cameraList.size();
	for (i = 0; i < len; i++) {//media_camera_list.append
		cameralist_child = cameraList[i];
		cameraInfo = cameralist_child["cameraInfo"];
		cluster = cameralist_child["cluster"];
		leng = cluster.size();
		faceMinSize = 64, faceMinQuality = 0.8;
		for (j = 0; j < leng; j++) {
			cluster_child = cluster[j];
			clusterType = cluster_child["clusterType"].asInt();
			if (clusterType == FACE_DETECTION) {
/*				faceMinSize = cluster_child["strategy"]["faceMinSize"].asInt();//20180522_hsq can't  prase string to int 
				faceMinQuality = cluster_child["strategy"]["faceMinQuality"].asFloat();	*/
				
				string tem = cluster_child["strategy"].isMember("faceMinSize") ? cluster_child["strategy"]["faceMinSize"].asCString() : to_string(faceMinSize);				
				faceMinSize = atoi(tem.c_str());

				tem= cluster_child["strategy"].isMember("faceMinQuality") ? cluster_child["strategy"]["faceMinQuality"].asCString() : to_string(faceMinQuality);
				faceMinQuality = atof(tem.c_str());

				break;
			}
		}

	//	if (j > leng) { return false; }

		//cameraID		
		//cameraName		
		//cameraType

		//rtspAddr

		//strategy
		  //faceMinSize
		strategy["faceMinSize"] = faceMinSize;
		strategy["faceMinQuality"] = faceMinQuality;
		cameraInfo["strategy"] = strategy;
		facedt_camera_list.append(cameraInfo);
		  //faceMinQuality
		  
	}
	dataPush["cameraList"] = facedt_camera_list;
	msgBody["dataPush"] = dataPush;
	msgBody["dataRequest"] = dataRequest;
	dst["msgBody"] = msgBody;
	return true;
}
bool facedt_recv2req(Json::Value *val)
{
	point_empty_check(val);	
	if ((*val)["msgHead"].isNull())
		return false;
	if ((*val)["msgBody"].isNull())
		return false;
	if ((*val)["msgHead"]["msgCode"].isNull())
		return false;
	if ((*val)["msgBody"]["dataRequest"].isNull())
		return false;
	if ((*val)["msgBody"]["dataPush"].isNull())
		return false;

	(*val)["msgHead"]["msgCode"] = JSONMSGCODE_FACE_NEED_TELL;
	int cameraid = (*val)["msgBody"]["dataPush"]["camID"].asInt();
	struct facetell_para para;
	para = g_cameraid_map2_facetell_para[cameraid];
	//facelibid
	vector<int>::iterator  it;
	Json::Value facelibs;
	for (it = para.facelibid.begin(); it != para.facelibid.end(); it++) {
		facelibs.append(Json::Value((*it)));
	}
	(*val)["msgBody"]["dataPush"]["facelibid"] = facelibs;// Json::Value(para.facelibid);
	(*val)["msgBody"]["dataPush"]["minalarmthreshold"] = para.minalarmthreshold;
	(*val)["msgBody"]["dataPush"]["facceoutnumber"] = para.facceoutnumber;
	return true;
}
bool facedt_result2_facetell_req(Json::Value *val, void *para)
{
	if (val == NULL) {
		return false;
	}
	Json::Value dataRequest, dataPush;
	int msgCode = (*val)["msgHead"]["msgCode"].asInt();
	dataRequest["code"] = 0;
	dataRequest["msg"] = "";
	(*val)["msgBody"]["dataRequest"] = dataRequest;

	dataPush = (*val)["msgBody"]["dataSend"];
	(*val)["msgBody"].removeMember("dataSend");

	dataPush["similarThread"] = (*val)["msgBody"]["dataRecv"]["similarThread"];
	(*val)["msgBody"].removeMember("dataRecv");
	(*val)["msgBody"]["dataPush"] = dataPush;
	
	
	if (msgCode == JSONMSGCODE_CLIENT_GET_USING_IMG_CHECKIN_IMG_BACK) {
		(*val)["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_GET_USING_IMG_CHECKIN_IMG;
		(*val)["msgBody"]["dataPush"]["imgURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["dataPush"]["imgURL"].asString());
		(*val)["msgBody"]["dataPush"]["RoiURL"] = Gb2312ToUtf_8_EX((*val)["msgBody"]["dataPush"]["RoiURL"].asString());
	}
	return true;
}
bool facedt_combina_face_search_msg(Json::Value &src, Json::Value &dst,void *para)
{
	fprintf(flog_facesearch,"[%s] [%d]  src === %s\n", __FUNCTION__, __LINE__, (char *)src.toStyledString().data());
	dst["msgHead"] = src["msgHead"];
	Json::Value data;
	Json::Value msgBody;
	Json::Value *pdata = &(src["msgBody"]["data"]);
	//imgURL
	data["imgURL"] = (*pdata)["imgURL"];
	//faceMinSize
	data["faceMinSize"] = g_facedt_faceminisize;
	//faceMinQuality
	data["faceMinQuality"] = g_facedt_faceminquality;
	//faceNum
	data["faceNum"] = (*pdata)["facceOutNumber"];

	msgBody["data"] = data;
	dst["msgBody"] = msgBody;
	fprintf(flog_facesearch,"[%s] [%d]  src === %s\n", __FUNCTION__, __LINE__, (char *)src.toStyledString().data());
	return true;
}
DWORD  WINAPI facedt_worker(void * context)
{
	if (context == NULL) {
		printf("[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "context is NULL");
		getchar();
		return -1;
	}

	MSG msg;
	Json::Value value, msgBody, dataRequest, dataPush, dataSend, serverErrList_0,request;
	Json::Reader reader;
	int nJsonMsgCode, msgType = 0,errorcode = 0;
	Json::Value sendValue, msgHead, strategy;
	char identity[IDENTITY_STR_LEN] = { 0 };
	zmq_msg_t msg_recv;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

	DealerModeSendRecv messenger(context, face_dt_sk);
	FaceDetect faceDetect;

	int ret = 0, msgCode = 0;
	int nMsgType = 0;

	std::ifstream in;
	int len = 0,len_req = 0,code = 0;
	char *strTmp = NULL;
	int malloc_len_pre = 0;
	
	in.open("server_send_face_detect_connect_req.json", std::ios::binary);
	if (!in.is_open()) {
		printf("[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "can not find  server_send_face_detect_connect_req.json");
		getchar();
		return -1;
	}
		
	
	if (reader.parse(in, value)) {
		len_req = strlen((char *)value.toStyledString().data());
		strTmp = (char *)malloc(len_req + 1);
		memset(strTmp, 0, len_req + 1);
		memcpy(strTmp, (char*)value.toStyledString().data(), len_req);
	}
	else {
#ifdef FD_STEP_PRINT
		fprintf(flog, "[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "parse file failed");
#endif
		getchar();
		return -1;
	}
	


//	len = zmq_send(face_dt_sk, "", 0, ZMQ_SNDMORE);
	char empty[] = { "" };
	s_sendmore(face_dt_sk, empty);
	
//	len = zmq_send(face_dt_sk, strTmp, len_req, 0);
//	zmq_send_check(len);
	s_send(face_dt_sk, strTmp);
#ifdef FD_STEP_PRINT
	printf("[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "face dt send connect req");
	fprintf(flog, "[%s] [%d]  face dt send connect req === %s\n", __FUNCTION__, __LINE__, strTmp);
#endif
	Sleep(100);

	char req_rep[100] = { "face dt recev connect reply" };
	
	zmq_pollitem_t items[] = { { face_dt_sk,0,ZMQ_POLLIN,0 } };
	string msgRecv;
	while(true){
		while (true) {
			len = 0;
			zmq_poll(items, 1, zmq_poll_timeout);
			if (items[0].revents & ZMQ_POLLIN) {				
				zmq_msg_init(&msg_recv);
				zmq_msg_recv(&msg_recv, face_dt_sk, 0);		
				len = zmq_msg_recv(&msg_recv, face_dt_sk, 0);
				if (len <= 0) {
#ifdef FD_VALUE_PRINT

			//	printf("[%s] [%d] face dt recv msg ==== %s\n", __FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
				fprintf(flog,"[%s] [%d] face dt recv msg ==== %s\n", __FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));

				fflush(flog);
#endif
					continue;
				}
				value.clear();
				sendValue.clear();
				msgHead.clear();
				dataSend.clear();
				msgBody.clear();

				 msgRecv = (char *)zmq_msg_data(&msg_recv);
				char *testbuff = NULL;
				if(len&&reader.parse((char *)zmq_msg_data(&msg_recv), value)) {						
				
					nJsonMsgCode = value["msgHead"]["msgCode"].asInt();				
					printf("[%s] [%d] nJsonMsgCode ==== %d\n", __FUNCTION__, __LINE__, nJsonMsgCode);
					switch (nJsonMsgCode)
					{
					case JSONMSGCODE_FACE_DETECT_CONNECT_REPLY://FACEDETECT_JUST_REPLY
#ifdef FD_STEP_PRINT
						printf("[%s] [%d] recv msg ==== %s\n", __FUNCTION__, __LINE__, "face detect connect already build");
						fprintf(flog,"[%s] [%d] recv msg ==== %s\n", __FUNCTION__, __LINE__, "face detect connect already build");
#endif

						//Sleep(10);//休息10ms后发送 face dt初始化信息
						//sendValue.clear();
						//SetMsgHead(&sendValue,&face_dt_init_value, JSONMSGTYPE_RESPONSE, JSONMSGCODE_FACEDETECTION_INIT_IN);
						//dataRequest["code"] = JSONMSGCODE_FACEDETECTION_INIT_IN;
						//dataPush = face_dt_init_value["msgBody"]["dataSend"];
						//sendValue["dataRequest"] = dataRequest;
						//sendValue["dataPush"] = dataPush;
						//messenger.SendDealerMsg((char *)sendValue.toStyledString().data());
						//Sleep(100);
						//return connect status to java
						
						break;
					case JSONMSGCODE_FACEDETECTED_MSG://FACEDETECT_NEED_TELL:
						if (nFaceDetectStrategy == FACEDETECT_NEED_TELL) {
							faceDetect.InitParm(context, nFaceDetectStrategy, &value, face_dt_sk);
							//if (!faceDetect.FaceDetectHandle()) {//face detect src pic name and data save,cap pic name and data save
							//	printf("[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
							//	fprintf(flog,"[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
							//	//fflush(flog);
							//}
							if (!faceDetect.FaceDetectSetResponse(&sendValue)) {//just face detect msg reply 
								printf("[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
								fprintf(flog,"[%s] [%d] run into ==== %s\n", __FUNCTION__, __LINE__, "exception");
							}
							//sendMsg.SendOuterMsg((char *)sendValue.toStyledString().data());
							//zmq_send(face_dt_sk, "", 0, ZMQ_SNDMORE);
							//zmq_send(face_dt_sk, sendValue.toStyledString().data(), strlen((char *)sendValue.toStyledString().data()) + 1, 0);
							facedt_recv2req(&value);
							nMsgType = FACEDETECT_NEED_FACETELL;
							WaitForSingleObject(m_facetell_mutex, INFINITE);//mutex read face_tell_connect_builded
							if (face_tell_connect_builded == false) {
								printf("[%s] [%d]  %s\n", __FUNCTION__, __LINE__, "face tell unconnected ,msg lost");
								fprintf(flog, "[%s] [%d] %s\n", __FUNCTION__, __LINE__, "face tell unconnected ,msg lost");
								//fflush(flog);
								ret = ReleaseMutex(m_facetell_mutex);
								break;//face tell unconnected,face detect msg lost
							}
							ret = ReleaseMutex(m_facetell_mutex);
							//fprintf(flog, "[%s] [%d] ReleaseMutex === %d\n", __FUNCTION__, __LINE__, ReleaseMutex);
							//fflush(flog);
							if (lpFaceTellThreadId != 0) {

								len = strlen((char *)value.toStyledString().data());
								strTmp = (char *)malloc(len + 100);
								memset(strTmp, 0, len + 100);

								strncpy(strTmp, (char *)value.toStyledString().data(), len);
								
#ifdef FD_STEP_PRINT								
								printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, "fd send que msg to face tell worker");
								fprintf(flog,"[%s] [%d]  to look facelibids === %s\n", __FUNCTION__, __LINE__, strTmp);
								//fflush(flog);
#endif
								if (lpFaceTellThreadId == 0) {
									fprintf(flog, "erroe lpFaceTellThreadId ============== %d", lpFaceTellThreadId);
									//fflush(flog);
								}								
								ret = PostThreadMessage(lpFaceTellThreadId, nMsgType, (WPARAM)strTmp, NULL);
#ifdef FD_VALUE_PRINT
								fprintf(flog,"[%s] [%d] PostThreadMessage ret == %d\n", __FUNCTION__, __LINE__, ret);
#endif
								if (ret == 0) {								
									printf("[%s] [%d]  error ==== %d\n", __FUNCTION__, __LINE__, GetLastError());								
									fprintf(flog,"[%s] [%d]  error ==== %d\n", __FUNCTION__, __LINE__, GetLastError());
									//fflush(flog);
									wparam_free(&strTmp);
								}

							}//end of lpFaceTellThreadId

						}
#ifdef FACE_DT2_RTSP
						nMsgType = RTSP_NEED_FACEDT;
						if (lpRtspThreadId != 0) {
							len = strlen((char *)value.toStyledString().data());
							strTmp = (char *)malloc(len + 100);
							memset(strTmp, 0, len + 100);
							strncpy(strTmp, (char *)value.toStyledString().data(), len);
#ifdef FD_STEP_PRINT								
							printf("[%s] [%d] %s\n", __FUNCTION__, __LINE__, "fd send que msg to rtsp worker");
							fprintf(flog, "[%s] [%d] %s\n", __FUNCTION__, __LINE__, "fd send que msg to rtsp worker");
							//fflush(flog);
#endif
							ret = PostThreadMessage(lpRtspThreadId, nMsgType, (WPARAM)strTmp, NULL);
							if (ret == 0) {
								printf("[%s] [%d]  error ==== %d\n", __FUNCTION__, __LINE__, GetLastError());
								fprintf(flog, "[%s] [%d]  error ==== %d\n", __FUNCTION__, __LINE__, GetLastError());
								//fflush(flog);
								wparam_free(&strTmp);
							}
						}
#endif 
						break;
					//case JSONMSGCODE_FACEIDF_FACEFEATURES_IN://发往人脸识别，计算特征值
					//	SetMsgHead(&sendValue, &value, JSONMSGTYPE_REQUEST, JSONMSGCODE_FACEIDF_FACEFEATURES_IN);
					//	sendValue["msgBody"] = value["msgBody"];
					//	nMsgType = FACEIDF_FACEFEATURES_IN;
					//	postthreadmessage_mem_malloc(malloc_len_pre, &strTmp, &value);
					//	ret = PostThreadMessage(lpFaceTellThreadId, nMsgType, (WPARAM)strTmp, NULL);
					//	postthreadmessage_check(ret);
					//	break;
					//case JSONMSGCODE_FACEDETECTION_ONEPICTURE://发往人脸识别，计算特征值
					//	SetMsgHead(&sendValue, &value, JSONMSGTYPE_REQUEST, JSONMSGCODE_FACEDETECTION_ONEPICTURE);
					//	sendValue["msgBody"] = value["msgBody"];
					//	nMsgType = FACEIDF_FACEFEATURES_IN;
					//	postthreadmessage_mem_malloc(&malloc_len_pre, &strTmp, &value);
					//	ret = PostThreadMessage(lpFaceTellThreadId, nMsgType, (WPARAM)strTmp, NULL);
					//	postthreadmessage_check(ret);
					//	break;
					case JSONMSGCODE_FACEDETECTION_PICTUREDIR_OUT:
/////////////////////////
						testbuff = new char[msgRecv.length() + 100];
						std::memset((testbuff), 0, msgRecv.length() + 100);
						std::strncpy((testbuff), msgRecv.data(), msgRecv.length());
/////////////////////////	

						
						if (facedetection_result(&value)) {//检测到人脸
#ifdef PICS_IN_LIB_PRINT
							fprintf(flog_pic_in, "[%s] [%d] checked face code == %d \n", __FUNCTION__, __LINE__, value["msgBody"]["dataSend"]["code"].asInt());
							//fflush(flog);
#endif
							SetMsgHead(&sendValue, &value, JSONMSGTYPE_REQUEST, JSONMSGCODE_FACEDETECTION_PICTUREDIR_OUT);
							sendValue["msgBody"] = value["msgBody"];  
						//	printf( "[%s] [%d] checked face code == %s \n", __FUNCTION__, __LINE__, sendValue.toStyledString().data());
						//	printf("[%s] [%d] checked face code == %s \n", __FUNCTION__, __LINE__, value.toStyledString().data());
							for (int i=0;i<value["msgBody"]["dataSend"]["FaceDetection"].size();i++)
							{
								sendValue["msgBody"]["dataSend"]["FaceDetection"][i]["Value"]["FacePicture"] 
									= Json::Value(value["msgBody"]["dataSend"]["FaceDetection"][i]["Value"]["FacePicture"].asCString());
							}
							sendValue["msgBody"]["dataSend"]["srcPictureStr"]
								= Json::Value(value["msgBody"]["dataSend"]["srcPictureStr"].asCString());
							facedt_recv2req(&sendValue);

							nMsgType = FACEIDF_FACEFEATURES_IN;
							postthreadmessage_mem_malloc(&strTmp, &sendValue);
							if (lpFaceTellThreadId == 0) {
								fprintf(flog_pic_in, "erroe lpFaceTellThreadId ============== %d", lpFaceTellThreadId);
								//fflush(flog);
							}
							else {


								ret = PostThreadMessage(lpFaceTellThreadId, nMsgType, (WPARAM)strTmp, NULL);
								if (!postthreadmessage_check(ret)) {
									fprintf(flog_pic_in, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
									//fflush(flog);
									wparam_free(&strTmp);
								}
							}
						}
						else {//没有检测到人脸，空特征值返回
#ifdef PICS_IN_LIB_PRINT
							fprintf(flog_pic_in, "[%s] [%d] unchecked face code == %d \n", __FUNCTION__, __LINE__, value["msgBody"]["dataSend"]["code"].asInt());
							//fflush(flog);
#endif
							sendValue.clear();
							msgHead.clear();
							nMsgType = FACEDETECTION_PICTUREDIR_IN;//特征值返回给java
							SetMsgHead(&msgHead, &value, JSONMSGTYPE_REQUEST, JSONMSGCODE_FACEDETECTION_PICTUREDIR_OUT);
							dataSend["FeaDir"] = "";
							dataSend["PictureID"] = value["msgBody"]["dataSend"]["FaceDetection"][0]["Value"]["PictureID"];
							string strPathDir = value["msgBody"]["dataSend"]["srcPictureStr"].asCString();
							dataSend["PicturePathDir"] = Json::Value(strPathDir.c_str());
							dataSend["code"] = value["msgBody"]["dataSend"]["code"];
							msgBody["dataSend"] = dataSend;
							msgBody["dataRecv"] = {};
							msgBody["dataRecv"]["code"] = JSONMSGCODE_FACEDETECTION_PICTUREDIR_OUT;
							sendValue["msgBody"] = msgBody;
							sendValue["msgHead"] = msgHead;
							postthreadmessage_mem_malloc(&strTmp, &sendValue);
//#ifdef EMPTY_MSG_DEBUG
							if (lpJavaThreadId != 0) {
								ret = PostThreadMessage(lpJavaThreadId, nMsgType, (WPARAM)strTmp, NULL);
								if (!postthreadmessage_check(ret)) {
									fprintf(flog_pic_in, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
									//fflush(flog);
									wparam_free(&strTmp);
								}
							}
							else {
								fprintf(flog, "erroe lpJavaThreadId ============== %d", lpJavaThreadId);
								//fflush(flog);
							}
//#endif
						}
#ifdef PICS_IN_LIB_PRINT
						fprintf(flog_pic_in, "[%s] [%d] order to order run \n", __FUNCTION__, __LINE__);
						fflush(flog_pic_in);
#endif
						break;
					case JSONMSGCODE_JAVA_CHANGE_CAMERA:
						msgType = value["msgHead"]["msgType"].asInt();
						if (msgType == JSONMSGTYPE_RESPONSE) {
							trans_msg2_another_thread(FACEDT_CHANGE_FACEDETECTION_CAMERA, &value, lpJavaThreadId,&g_common_str_facedt,NULL);
#ifdef FD_STEP_PRINT
							fprintf(flog_change_camera, "[%s] [%d] JSONMSGCODE_JAVA_CHANGE_CAMERA == %d \n", __FUNCTION__, __LINE__, JSONMSGCODE_JAVA_CHANGE_CAMERA);
							fflush(flog_change_camera);
#endif
						}
						break;
					case JSONMSGCODE_JAVA_CHANGE_STATEG:
						msgType = value["msgHead"]["msgType"].asInt();
						if (msgType == JSONMSGTYPE_RESPONSE) {
							trans_msg2_another_thread(FACEDT_CHANGE_STATEG, &value, lpJavaThreadId,&g_common_str_facedt,NULL);
						}
						break;
					case JSONMSGCODE_CLIENT_GET_FACE_CHECKIN://1vs1
						msgType = value["msgHead"]["msgType"].asInt();
						if (msgType == JSONMSGTYPE_RESPONSE) {
 
							errorcode = value["msgBody"]["dataSend"]["code"].asInt();
#ifdef CLIENT_ONE_VS_ONE
							fprintf(flog_one_vs_one,"[%s] [%s] [%d] errorcode one vs one=== %d\n", get_system_misecond_time(), __FUNCTION__, __LINE__, errorcode);
							fflush(flog_one_vs_one);
#endif
							if (errorcode == JSONMSGCODE_FACEDT_GET_FACE_CHECKIN_NO_READ_PIC || \
								errorcode == JSONMSGCODE_FACEDT_GET_FACE_CHECKIN_FACE_UNQUA || \
								errorcode == JSONMSGCODE_FACEDT_NO_FACE_DT) {//come out error
								trans_msg2_another_thread(FACEDT_FACE_CHECKIN_FAILED, &value, lpClientThreadId,&g_common_str_facedt,NULL);
								break;
							}
							trans_msg2_another_thread(FACEDT_GET_FACE_CHECKIN, &value, lpFaceTellThreadId,&g_common_str_facedt,NULL);
						}
						break;
					case JSONMSGCODE_CLIENT_GET_USING_IMG_CHECKIN_IMG_BACK://face dt search pic result
#ifdef PIC_WITH_PIC_PRINT
					fprintf(flog_search,"g_face_search_index === %d [%s] [%s] [%d] face dt receive search resutl  ==== %s \n",(g_face_search_index++), get_system_misecond_time(), __FUNCTION__, __LINE__,(char *)value.toStyledString().data());
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
								trans_msg2_another_thread(FACEDT_GET_USING_IMG_CHECKIN_IMG_FAILED, &value, lpClientThreadId,&g_common_str_facedt,NULL);
								break;
							}
							//face dt result to face tell req
							msgCode = JSONMSGCODE_CLIENT_GET_USING_IMG_CHECKIN_IMG;
							facedt_result2_facetell_req(&value,&msgCode);
							trans_msg2_another_thread(FACEDT_GET_USING_IMG_CHECKIN_IMG_SUCCESS, &value, lpFaceTellThreadId,&g_common_str_facedt,NULL);
						}
						break;
					case JSONMSGCODE_CLIENT_GET_FACE_CHECKIN_N:
#ifdef FACE_SEARCH_PRINT
						fprintf(flog_facesearch, "[%s] [%s] [%d] face dt receive ==== %s \n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
						fflush(flog_facesearch);
#endif
						msgType = value["msgHead"]["msgType"].asInt();
						if (msgType == JSONMSGTYPE_RESPONSE) {
							errorcode = value["msgBody"]["state"]["code"].asInt();
							if (errorcode == JSONMSGCODE_CLIENT_FACE_1VSN_NO_SOURCE_IMG || \
								errorcode == JSONMSGCODE_CLIENT_FACE_1VSN_SOURCE_IMG_UNQUALITY || \
								errorcode == JSONMSGCODE_CLIENT_FACE_1VSN_NO_FACE_IN_SOURCE_IMG) {
								value["msgBody"]["data"] = "";
								trans_msg2_another_thread(FACEDT_FACE_SEARCH_FAILED, &value, lpClientThreadId, &g_common_str_facedt, NULL);
								break;
							}
							else {//facedt success								
								trans_msg2_another_thread(FACEDT_FACE_SEARCH_SUCCESS, &value, lpFaceTellThreadId, &g_common_str_facedt, NULL);
							}
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


#ifdef FD_STEP_PRINT
//			printf("[%s] [%d] face dt worker running ==== \n", __FUNCTION__, __LINE__);
#endif
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

			value.clear();
			sendValue.clear();

			int alive_msg = FACEDT_ALIVE_CHECK;
			if (msg.message <= WM_USER) {
				continue;
			}
			string java_src = pInfo;
			if (!parse_queuemsg2_json(pInfo, reader, value, msg, &alive_msg))//parse pInfo2 Json fail
			{
			//	continue;
			}
			else
			{
#ifdef FD_VALUE_PRINT			
			//	if (msg.message != FACEDT_ALIVE_CHECK && msg.message > WM_TIMER) {
					fprintf(flog, "facedt worker queue msg============== %s", pInfo);
					fflush(flog);
			//	}
#endif
			}
			string  str;
			string  strSrc;
			char *szUtf8 = NULL;
			switch (msg.message)
			{
			case FACE_TELL_RESULT:
				break;
			//case FACEDETECTION_ONEPICTURE://发送单张人脸往人脸检测算法
			//	SetMsgHead(&sendValue, &value, JSONMSGTYPE_REQUEST, JSONMSGCODE_FACEDETECTION_ONEPICTURE);
			//	sendValue["msgBody"] = value["msgBody"];
			//	messenger.SendDealerMsg((char *)sendValue.toStyledString().data());
			//	break;
			case FACEDETECTION_PICTUREDIR_IN://发送文件夹图片往人脸检测算法
				SetMsgHead(&sendValue, &value, JSONMSGTYPE_REQUEST, JSONMSGCODE_FACEDETECTION_PICTUREDIR_IN);
				sendValue["msgBody"] = value["msgBody"];
			//	printf("[%s] [%d] value ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
				//strSrc = value["msgBody"]["dataPush"]["PictureList"][0]["PicturePathDir"].asCString();
								
#ifdef PICS_IN_LIB_PRINT
				printf("[%s] [%d] FACEDETECTION_PICTUREDIR_IN ==== %s\n", __FUNCTION__, __LINE__, (char *)sendValue.toStyledString().data());
				fprintf(flog_pic_in,"[%s] [%d] FACEDETECTION_PICTUREDIR_IN ==== %s\n", __FUNCTION__, __LINE__, (char *)sendValue.toStyledString().data());
				fflush(flog_pic_in);
#endif
				for (int i = 0; i < value["msgBody"]["dataPush"]["PictureList"].size(); i++)
				{
					str = sendValue["msgBody"]["dataPush"]["PictureList"][i]["PicturePathDir"].asCString();
					sendValue["msgBody"]["dataPush"]["PictureList"][i]["PicturePathDir"] = Json::Value(str.c_str());

				}
				str = sendValue.toStyledString();
				messenger.SendDealerMsg((char *)sendValue.toStyledString().data());//到此人脸检测收到完整人脸文件夹信息				
				break;
			case RTSP_CHANGE_FACEDETECTION_CAMERA:
				request.clear();
				if (!facedt_recombind_java_change_camera_req(value, request)) {
#ifdef FD_VALUE_PRINT					
					fprintf(flog_change_camera, "[%s] [%d] can not combind change camera msg2 facedt\n", __FUNCTION__, __LINE__);
#endif
					break;//no match message
				}
#ifdef FD_VALUE_PRINT
			//	printf("[%s] [%d] JAVA_CHANGE_CAMERA ==== %s\n", __FUNCTION__, __LINE__, (char *)request.toStyledString().data());
				fprintf(flog_change_camera, "[%s] [%d] JAVA_CHANGE_CAMERA ==== %s\n", __FUNCTION__, __LINE__, (char *)request.toStyledString().data());
				fflush(flog_change_camera);
#endif
				facedt_java_change_camera = request;
				messenger.SendDealerMsg((char *)request.toStyledString().data());
			//	wparam_free(&lParam);
				break;
			case JAVA_CHANGE_STATEG:
#ifdef FD_VALUE_PRINT
			//	printf("[%s] [%d] facedt send change stateg msg to face dt al ==== %s\n", __FUNCTION__, __LINE__, (char *)request.toStyledString().data());
				fprintf(flog, "[%s] [%d] facedt send change stateg msg to face dt al ==== %s\n", __FUNCTION__, __LINE__, (char *)request.toStyledString().data());
				//fflush(flog);
#endif
				messenger.SendDealerMsg((char *)request.toStyledString().data());
			case FACEDT_ALIVE_CHECK:
				nMsgType = FACEDT_RETURN_IAM_ALIVE;
				g_facedt_strAliveCheck = (char *)malloc(strlen(FACEDT_STILL_ALIVE) + 10);
				memset(g_facedt_strAliveCheck, 0, strlen(FACEDT_STILL_ALIVE) + 10);
				strcpy(g_facedt_strAliveCheck, FACEDT_STILL_ALIVE);
				if (lpMonitorThreadId != 0) {
					ret = PostThreadMessage(lpMonitorThreadId, nMsgType, (WPARAM)g_facedt_strAliveCheck, NULL);
					if (!postthreadmessage_check(ret)) {
						fprintf(flog, "[%s] [%d] PostThreadMessage failed\n", __FUNCTION__, __LINE__);
						//fflush(flog);
						wparam_free(&g_facedt_strAliveCheck);

					}
				}
				else {
					fprintf(flog, "erroe lpMonitorThreadId ============== %d", lpMonitorThreadId);
					//fflush(flog);
				}
				break;
			case CLIENT_GET_FACE_CHECKIN:
			{
				/*CUIIJIANHUA + 1v1 + CHANGE + ADD*/
				value["msgBody"]["dataPush"]["imgFirstURL"] = Gb2312ToUtf_8_EX(value["msgBody"]["dataPush"]["imgFirstURL"].asString());
				value["msgBody"]["dataPush"]["imgSecondURL"] = Gb2312ToUtf_8_EX(value["msgBody"]["dataPush"]["imgSecondURL"].asString());
				/*END*/
#ifdef CLIENT_ONE_VS_ONE
				fprintf(flog_one_vs_one,"[%s] [%s] [%d] facedt send client_get_face_checkin msg to face dt al ==== %s\n", get_system_misecond_time(), __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
				fflush(flog_one_vs_one);
			//	fprintf(flog, "[%s] [%d] facedt send client_get_face_checkin to face dt al ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
				//fflush(flog);
#endif
				messenger.SendDealerMsg((char *)value.toStyledString().data());
			}
				break;
			case CLIENT_USING_IMG_CHECKIN_IMG://search pic with pic

				strategy["faceMinSize"] = 0;
				strategy["faceMinQuality"] = 0.0;//value["msgBody"]["dataPush"]["similarThread"];
			//	value["msgBody"]["dataPush"].removeMember("similarThread");
				value["msgBody"]["dataPush"]["strategy"] = strategy;
				value["msgBody"]["dataPush"]["imgURL"] = Gb2312ToUtf_8_EX(value["msgBody"]["dataPush"]["imgURL"].asString());
#ifdef FD_VALUE_PRINT

				//printf("[%s] [%d] facedt search pic with pic to face dt al ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
				//fprintf(flog, "[%s] [%d] facedt send search pic with  to face dt al ==== %s\n", __FUNCTION__, __LINE__, (char *)value.toStyledString().data());
				fprintf(flog_search,"g_face_search_index === %d [%s] [%s] [%d] facedt search pic with pic to face dt al ==== %s\n", (g_face_search_index++),__TIME__,__FUNCTION__, __LINE__, (char *)value.toStyledString().data());

#endif
				messenger.SendDealerMsg((char *)value.toStyledString().data());
	
				break;
			case CLIENT_FACE_SEARCH:
			{
				facedt_combina_face_search_msg(value, sendValue, NULL);
				/*CUIIJIANHUA + 1v1 + CHANGE + ADD*/
				string bfValue = Gb2312ToUtf_8_EX(value["msgBody"]["data"]["imgURL"].asString());
				sendValue["msgBody"]["data"]["imgURL"] = bfValue;
				/*END*/
				  str =(char *)sendValue.toStyledString().data();
				messenger.SendDealerMsg((char *)sendValue.toStyledString().data());
			}
				break;
			default:
				break;
			}
			fflush(flog);
			switch (msg.message)//free case
			{
			case FACE_TELL_RESULT:
			case FACEDETECTION_PICTUREDIR_IN:
			case JAVA_CHANGE_CAMERA:
			case JAVA_CHANGE_STATEG:
			
			case CLIENT_GET_FACE_CHECKIN:
			case CLIENT_USING_IMG_CHECKIN_IMG:
				wparam_free(&pInfo);
				break;
			case FACEDT_ALIVE_CHECK:
				wparam_free(&pInfo);
				break;
			case CLIENT_FACE_SEARCH:
				wparam_free(&pInfo);
				break;
			default:
				break;
			}		
		}


			}
		fprintf(flog, "[%s] [%s] [%s] [%d] face dt worker end timepoint \n", __DATE__, __TIME__, __FUNCTION__, __LINE__);
		fflush(flog);
		}
	return 0;
}
Json::Value face_dt_init_value;


