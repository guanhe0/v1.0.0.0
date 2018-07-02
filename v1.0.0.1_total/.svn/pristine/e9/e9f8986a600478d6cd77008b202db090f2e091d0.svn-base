#include "stdafx.h"
#include "server_config.h"

int nListJava = 5507;
int nListJavaInit = 5557;
int nReqJava = 5500;
int nFaceTell = 5558;
int nFaceTrackPort = 6002;
int nShapePort =  6004;
int nSearchPort = 6013;
int nPicDataUpate = 6015;
int nRtspServer = 6000;
int FaceTellPort = 5558;

string strFaceDetectUrl = "D:\\test\\FaceDetect";
string strFacePointInfoUrl = "D:\\test\\FaceDetectPointInfo";
string strFaceTellUrl = "192.168.1.137";
double nSimilarity = 0.8;
char strFaceDetect[LISTEN_ADDR_LEN] = { 0 };
char strTrackInit[LISTEN_ADDR_LEN] = { 0 };
char strFaceTell[LISTEN_ADDR_LEN] = { 0 };
char strRtspSever[LISTEN_ADDR_LEN] = { 0 };
char strTrack[LISTEN_ADDR_LEN] = { 0 };
char strShape[LISTEN_ADDR_LEN] = { 0 };
char strSearchPic[LISTEN_ADDR_LEN] = { 0 };
char strDataUpdate[LISTEN_ADDR_LEN] = { 0 };
//char strMsgHeadFile[255] = {"..\\..\\..\\..\\MsgHeadFile\\server_send_face_dt_init_req.json"};
//char strMsgHeadFile[255] = { "server_send_face_dt_init_req.json" };
string strMsgHeadFile = "server_send_face_dt_init_req.json";
map<int, int> rtsp2java;
map<int, int> func2java;
bool msg_code_map_init()
{
	rtsp2java[JSONMSGCODE_RTSP_CAMERA_STATUS_REPLY] = JSONMSGCODE_SERVER_MONITOR_CAMERA;
//	func2java[] = JSONMSGCODE_SERVER_MONITOR_SERVER;
	return true;
}
int change_camera_timeout = 20000;
std::string  g_envalue_file = "ip_config.json";