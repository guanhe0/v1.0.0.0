//#pragma once
#ifndef TRACKSERVER_H
#define TRACKSERVER_H
#include "json\json.h"
#include "zmq.hpp"
//#include "zmq_utils.h"
//#include "zhelper.h"
#include "zhelpers.hpp"
#include <iostream>
#include "msgDefine.h"
#include "common.h"
#include <mutex>
#include <fstream>
#include<Windows.h> 
using namespace std;
//相机矩阵宏
#define LCAMID 1
#define RCAMID 2	
#define FCAMID 3
#define BCAMID 4
#define UCAMID 5
#define DCAMID 6


#define TRACKSERVE_RADDR			"tcp://localhost:36542" //测试的跟踪服务器地址

 static zmq::context_t contextT(1);

//锁变量
 static std::mutex g_mutex;

typedef struct camStruct {
	int								s_zoneID;//相机区域
	int								s_camID;//相机id
	int								s_LcamID = 0;//方向：左 相机id
	int 							s_RcamID = 0;//方向：右 相机id
	int 							s_FcamID = 0;//方向：前 相机id
	int 							s_BcamID = 0;//方向：后 相机id
	int 							s_UcamID = 0;//方向：上 相机id
	int 							s_DcamID = 0;//方向：下 相机id
}camStruct;
static std::vector<camStruct> g_vCamStruct;//相机矩阵数据结构
typedef struct timeval TrackTimeValue;
//跟踪队列
typedef struct TailTrackStruct
{
	int s_CamId;//相机ID
	std::vector<TrackTimeValue> s_VTrackTimeValue;
	//时间戳
}TailTrackStruct;


//接收client线程数据结构
typedef struct RecvFromAlarmStruct
{
	//需要跟踪目标
	int s_TailPersonId = 0;
}RecvFromAlarmStruct;
//接收流媒体数据结构
typedef struct RecvFromFramServerStruct
{

}RecvFromFramServerStruct;
//接收client线程的数据结构
typedef struct RecvFromClientServerStruct
{
	int				s_personId;//人物id
							   //确定跟踪人物id
	int				s_TailPersonId = 0;
	int				s_msgID;
	int				s_optState = -1;//操作状态
	std::string		s_optStaff;//操作者
						   //跟踪错误
	int				s_TailWrong = 0;
	int				s_ChangeTap = 0;//切换标签页
	int				s_OverTracking = 0;
	int				s_lastPersonID;//上一页的人物id   personID 当前的人物id
	int				s_Misinformtion = 0;//误报
	int				s_camId;//相机id
	//int				s_GetTrackPersoID = 0;
	//获取跟踪轨迹
	int				s_getTailTrack = 0;
}RecvFromClientServerStruct;

typedef struct InitTailServerStruct {
	std::string connectSocketIp;//分析仪IP
	short  port;//分析仪的端口
	std::string TailName;//分析仪的名字
	int TailId;//分析仪的id
	std::string s_connectSocketAddr;//可连接的zmq::socket tcp地址
}InitTailServerStruct;
static std::vector<InitTailServerStruct> g_InitTailServerStruct;
//跟踪服务socket队列
typedef struct ConnetTrackSocketStruct {
	intptr_t s_Id;
	zmq::socket_t *s_connetTrackSocket;
}ConnetTrackSocketStruct;
//渲染框
typedef struct HumanROI {
	int s_ix;
	int s_iy;
	int s_iwidth;
	int s_ihight;

}HumanROI;
typedef struct FaceROI {
	int height;
	int width;
	int x;
	int y;
}FaceROI;
//接收Java后台数据
typedef struct RecvFromJavaServerStruct {
	int						InitTrackMsg = 0;
	int						AddTrackMsg = 0;
	int						RemoveTrackMsg = 0;
}RecvFromJavaServerStruct;
//接收人形分析仪数据结构
typedef struct RecvFromHumanShapeServerStruct {
	int						AlamMsg = 0;
	int						AllHumanShape = 0;
	timeval					s_timeval;

	int						s_personId;//人物id
	int						s_camID;//相机id
	std::string				s_camAddr;
	std::string				s_srcPictureDir;//源图路径
	std::string				s_roiPictureDir;//抠图路径
	std::string				s_TrackerSrcpictureFramName;//场景图
	std::vector<HumanROI>	sv_roi;//人形ROI
	std::vector<FaceROI>    sv_face_roi;//人脸ROI

}RecvFromHumanShapeServerStruct;
//接收跟踪服务数据结构
typedef struct RecvFromTrackStruct {
	int						s_msgCode;
	int						s_lost = 0;				//丢失
	int						s_Tailing = 0;			//跟踪
	int						s_regAgin = 0;			//重识别
	int						s_outFromCamera = 0;	//出相机

	int						s_zoneID;//相机区域
	int						s_iPersonID;//人物id
	int						s_iCamId;//相机id
	int						s_iDirection;//方向
	timeval					s_lTime;//时间戳
	HumanROI				s_RHumenROI;
	camStruct				s_camStruct;//相机矩阵
	std::string				s_sTrackerSrcpictureFramName;

}RecvFromTrackStruct;
//接收到其他线程的数据结构
typedef struct RecvFromServerStruct {
	int								s_FramServer = 0;//流媒体模块
	int								s_client = 0;	//客户端模块
	int								s_javaServer = 0;//JavaServer模块  1，Init 2,
	int								s_HumenShape = 0;//人形分析仪模块
	int								s_Alarm = 0;	//告警模块
	long							s_requestid = 0;
	InitTailServerStruct			s_initTailServerStruct;//初始化跟踪服务的数据
	RecvFromJavaServerStruct		s_recvFromJavaServerStruct;//接收到java线程的数据
	//RecvFromAlarmStruct			s_recvFromAlarmStruct;//接收到告警的数据
	//RecvFromFramServerStruct		s_recvFromFramServerStruct;//接收流媒体数据
	RecvFromClientServerStruct		s_recvFromClientServerStruct;//接收client 线程
	RecvFromHumanShapeServerStruct	s_recvFromHumanShapeServerStruct;//接收人形分析仪线程数据
}RecvFromServerStruct;

typedef struct PersonMsg {
	int								m_camId;
	int								m_personId;					//跟踪的人物id
	short							m_TailerPort;				//跟踪器的端口
	short							m_TailStatus = 8;			//0：跟踪 1：丢失 2：出相机 8：还未跟踪
	std::string						m_TailerIp;					//跟踪器的ip
	std::string						m_oprationName;				//跟踪处理操作者
	std::vector<TailTrackStruct>	mv_tailTrackStruct;			//跟踪轨迹向量											  
	ConnetTrackSocketStruct			m_connetTrackSocketStruct;	//跟踪器socket句柄
	timeval							m_TrackingTime;				//跟踪时间
	int								m_optState = -1;			//操作状态
}PersonMsg;
static std::vector<PersonMsg>		g_vPersonMsg;				//后台一直跟踪的报警人物id队列

typedef struct clientTailPersonMsg {
	int								m_personId;//跟踪的人物id
	//short							m_TailerPort;//跟踪器的端口
	//short							m_TailStatus = 0;//0：跟踪 1：丢失 2：出相机
	//std::string					m_TailerIp;//跟踪器的ip
	std::string						m_oprationName;//跟踪处理操作者
	int								m_optState = -1;
	std::vector<TailTrackStruct>	mv_tailTrackStruct;//跟踪轨迹向量											  
	//ConnetTrackSocketStruct		m_connetTrackSocketStruct;//跟踪器socket句柄
}clientTailPersonMsg;
static std::vector<clientTailPersonMsg> g_vclientTailPersonMsg;//保存client确认的目标ID跟踪状态队列


class TrackServer
{
public:
	TrackServer();
	virtual ~TrackServer();
	//来自跟踪服务器数据
	int mTrackServerRunForTrack(std::string& recvStr, std::string& sendStr);
	//解析跟踪服务发来的数据
	int parseTrackStrToJson(std::string &recvStr, RecvFromTrackStruct &recvFromTrackStruct);
	//解析其他线程发来的数据
	int parseOthrerThreadStrToJson(std::string &recvStr, RecvFromServerStruct &recvFromServerStruct);
	//丢失
	int TrackServerDealLost(RecvFromTrackStruct &recvFromTrackStruct, std::string &sendStr);
	//重识别
	int TrackServerDealRegAgin(RecvFromTrackStruct &recvFromTrackStruct, std::string &sendStr);
	//跟踪
	int TrackServerDealTailing(RecvFromTrackStruct &recvFromTrackStruct, std::string &sendStr);
	//出相机
	int TrackServerDealOutFromCamera(RecvFromTrackStruct &recvFromTrackStruct, std::string &sendStr);

	//初始化跟踪服务器数据
	int TrackServerInit(std::string &InitMsgStr);
	//处理
	int mTrackServerRunForServer(std::string& recvStr, std::string& sendStr);
	//组数据
	int parseServerStrToJson(std::string &recvStr, RecvFromServerStruct &recvFromServerStruct);
	//告警模块数据
	int  TrackServerDealOutFromAlarm(RecvFromServerStruct &recvFromServerStruct, std::string &sendStr);
	//client线程数据
	int  TrackServerDealOutFromClient(RecvFromServerStruct &recvFromServerStruct, std::string &sendStr);
	//流媒体线程数据
	int  TrackServerDealOutFromFramServer(RecvFromServerStruct &recvFromServerStruct, std::string &sendStr);
	//人形分析仪线程数据
	int  TrackServerDealOutFromHumenShape(RecvFromServerStruct &recvFromServerStruct, std::string &sendStr);
	//Java后台线程数据
	int  TrackServerDealOutFromJavaServer(RecvFromServerStruct &recvFromServerStruct, std::string &sendStr);
	//返回跟踪器连接数据
	std::vector<ConnetTrackSocketStruct> *getconnetTrackSocketStruct();
	//组向java后台请求初始化数据
	int ParseJsonInitMsg(std::string &sendInit);
	/***********************test begin**************************/
	//存储跟踪服务器连接队列
	std::vector<ConnetTrackSocketStruct> mv_connetTrackSocketStruct;
	//发送初始化数据给跟踪服务器
	int sendInitTrackMsg(zmq::socket_t *socket);
	/***********************test end**************************/
private:
	//初始化跟踪服务器连接
	int InitTrackMsg(RecvFromServerStruct &recvFromServerStruct);
	//增加跟踪服务器
	int AddTrackMsg(RecvFromServerStruct &recvFromServerStruct);
	//移除跟踪服务器
	int RemoveTrackMsg(RecvFromServerStruct &recvFromServerStruct);
	//发送初始化数据给跟踪服务器
	//int sendInitTrackMsg(zmq::socket_t *socket);
	//监听跟踪服务器的连接
	int bindTrackMsg();
	//存储跟踪服务器连接队列
	//std::vector<ConnetTrackSocketStruct> mv_connetTrackSocketStruct;

	//发送丢失消息给java 线程
	int sendLostMsgToJavaThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
	//发送丢失消息给client线程
	int sendLostMsgToClientThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
	//发送重识别消息给人形分析线程
	int sendRegAginMsgToHumanShapeThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
	//发送跟踪消息给java线程
	int sendTrackingMsgToJavaThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
	//发送跟踪消息给java线程
	int sendTrackingMsgToClientThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
	//发送跟踪消息给流媒体
	int sendTrackingMsgToMediaThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
	//发送出相机后的相机信息给跟踪服务器
	int sendTOutCameraMsgToTrackServer(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
};


#endif
typedef struct timeval TrackTimeValue;



//extern TailTrackStruct test;


DWORD  WINAPI TrackWorker(void * context);
extern char *g_trackserver_stralivecheck;
