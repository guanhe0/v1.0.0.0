#pragma once
#include <string>
#define  CONNETTAILAFTERSERVER  "tcp://localhost:55556"


#define	JSONMSGTYPE_NOTIFY   0//通知消息(被请求方不需要回复)
#define	JSONMSGTYPE_REQUEST  1//请求消息(被请求方需要回复)
#define	JSONMSGTYPE_RESPONSE 2//回复消息


#define JSONMSGCODE_CLIENT_ALARM_DEAL  4007
#define  JSONMSGCODE_CLIENT_OK  0
#define JSONMSGCODE_CLIENT_TRACE_PERSON_CHANGE  4008	//客户端切换到跟踪标签页指定跟踪某个报警ID
//
//#define JSONMSGCODE_SERVER_TAILAFTER_RES_FOLLOWING_IN 0 //跟踪
//#define JSONMSGCODE_SERVER_TAILAFTER_RES_LOST_IN 1 //丢失
//#define JSONMSGCODE_SERVER_TAILAFTER_ALLHUMANSHAPE_IN 2 //重识别
//#define JSONMSGCODE_SERVER_TAILAFTER_RES_SWAPCAMERA_IN 3 //出相机

#define JSONMSGCODE_SERVER_HUMANSHAPE_INIT_IN				30101				//初始化接口
#define JSONMSGCODE_SERVER_HUMANSHAPE_INIT_OUT				30102				//初始化结果接口
#define JSONMSGCODE_SERVER_HUMANSHAPE_ALARM_IN				30103				//传入告警信息接口
#define JSONMSGCODE_SERVER_HUMANSHAPE_ALARM_OUT				30104				//传出告警信息对应的人形框接口
#define JSONMSGCODE_SERVER_ALLHUMANSHAPE_ALLHUMANSHAPE_IN	30105				//传入重识别接口
#define JSONMSGCODE_SERVER_ALLHUMANSHAPE_ALLHUMANSHAPE_OUT  30106				//传出重识别信息接口

#define JSONMSGCODE_SERVER_TAILAFTER_ONEHUMANSHAPE_OUT		30201				//传入告警人形框架接口 
#define JSONMSGCODE_SERVER_TAILAFTER_ALLHUMANSHAPE_IN		30202				//传入需要重识别人形的接口
#define JSONMSGCODE_SERVER_TAILAFTER_ALLHUMANSHAPE_OUT		30203				//传入重识别人形接口
#define JSONMSGCODE_SERVER_TAILAFTER_RES_LOST_IN			30204				//传入跟踪状态（丢失）信息接口
#define JSONMSGCODE_SERVER_TAILAFTER_RES_FOLLOWING_IN		30205				//传入跟踪状态（跟踪）信息接口
#define JSONMSGCODE_SERVER_TAILAFTER_RES_SWAPCAMERA_IN		30206				//传入跟踪状态（人物走出相机）信息接口
#define JSONMSGCODE_SERVER_TAILAFTER_RES_SWAPCAMERA_OUT		30207				//传出跟踪状态（人物走出相机）信息接口



#define JSONMSGCODE_SERVER_JAVASERER_INIT_OUT				30301				//请求初始化数据 
#define JSONMSGCODE_SERVER_JAVASERER_INIT_IN				30302				//返回初始化数据
#define JSONMSGCODE_SERVER_TAILAFTER_TRACK_OUT				30303				//发送跟踪轨迹接口
#define JSONMSGCODE_SERVER_TAILAFTER_FOLLOW_OUT				30304				//发送跟踪接口
#define JSONMSGCODE_SERVER_TAILAFTER_LOST_OUT				30305				//发送丢失接口

#define JSONMSGCODE_SERVER_TAILAFTER_FRAM_OUT				30401				//跟踪
#define JSONMSGCODE_SERVER_TAILAFTER_CHANGECAMERA_OUT		30401				//切换相机

#define JSONMSGCODE_SERVER_TAILAFTER_ONEHUMANSHAPE_IN		30501				//传入人形框架接口
#define JSONMSGCODE_SERVER_TAILAFTER_ALLHUMANSHAPE_OUT		30502				//传出需要做重识别人形的接口 
#define JSONMSGCODE_SERVER_TAILAFTER_ALLHUMANSHAPE_IN		30503				//传入重识别人形接口


DWORD lpClientThreadId = 0;
DWORD lpJavaThreadId = 0;
DWORD lpFaceDetectThreadId = 0;
DWORD lpFaceTellThreadId = 0;
DWORD lpRtspThreadId = 0;
DWORD lpTrackThreadId = 0;
DWORD lpFaceDtThreadId = 0;
DWORD lpBroadCastThreadId = 0;

typedef struct TailTrackStruct
{
	int s_CamId;//相机ID
	struct timeval s_time;//时间戳
}TailTrackStruct;



typedef struct RecvFromAlarmStruct
{
	//需要跟踪目标
	int s_TailPersonId =0;
	//
	//
	//

}RecvFromAlarmStruct;
typedef struct RecvFromFramServerStruct
{

}RecvFromFramServerStruct;
typedef struct RecvFromClientServerStruct
{
	int s_personId;//人物id
	//确定跟踪人物id
	int s_TailPersonId = 0;
	int s_msgID;   
	int s_optState = -1;//操作状态
	std::string s_optStaff;//操作者
	//跟踪错误
	int s_TailWrong = 0;
	int s_ChangeTap = 0;//切换标签页
	int s_lastPersonID;//上一页的人物id   personID 当前的人物id
	int s_Misinformtion = 0;//误报
	//查询跟踪轨迹
	int s_getTailTrack = 0;
}RecvFromClientServerStruct;
typedef struct InitTailServerStruct {
	std::vector<std::string> sv_connectSocketAddr;
}InitTailServerStruct;

typedef struct ConnetTailAfterSocketStruct {
	intptr_t s_Id;
	zmq::socket_t *s_connetTailAfterSocket;
}ConnetTailAfterSocketStruct;

typedef struct HumanROI {
	int s_ix;
	int s_iy;
	int s_iwidth;
	int s_ihight;

}HumanROI;

typedef struct RecvFromJavaServerStruct {
	int InitTailAfterMsg = 0;
	int AddTailAfterMsg = 0;
	int RemoveTailAfterMsg = 0;
}RecvFromJavaServerStruct;
typedef struct RecvFromHumanShapeServerStruct {
	int						AlamMsg = 0;
	int						AllHumanShape = 0;
	timeval					s_timeval;
	
	int						s_personId;//人物id
	int						s_camID;//相机id
	std::string				s_camAddr;
	std::string				s_srcPictureDir;//源图路径
	std::string				s_roiPictureDir;//抠图路径
	std::vector<HumanROI>	sv_roi;//人形ROI

}RecvFromHumanShapeServerStruct;
typedef struct RecvFromTailAfterStruct {
	int			s_lost = 0;				//丢失
	int			s_Tailing = 0;			//跟踪
	int			s_regAgin = 0;			//重识别
	int			s_outFromCamera = 0;	//出相机

	int			s_iPersonID;
	int			s_iCamId;
	timeval	s_lTime;//时间戳

	int			s_iDirection;//方向
	HumanROI	s_RHumenROI;
	std::string s_sTrackerSrcpictureFramName;
	
}RecvFromTailAfterStruct;
typedef struct RecvFromServerStruct {
	int			s_FramServer = 0;//流媒体模块
	int			s_client = 0;	//客户端模块
	int			s_javaServer = 0;//JavaServer模块  1，Init 2,
	int			s_HumenShape = 0;//人形分析仪模块
	int			s_Alarm = 0;	//告警模块
	InitTailServerStruct			s_initTailServerStruct;
	RecvFromJavaServerStruct		s_recvFromJavaServerStruct;
	RecvFromAlarmStruct				s_recvFromAlarmStruct;
	RecvFromFramServerStruct		s_recvFromFramServerStruct;
	RecvFromClientServerStruct		s_recvFromClientServerStruct;
	RecvFromHumanShapeServerStruct	s_recvFromHumanShapeServerStruct;
}RecvFromServerStruct;


typedef struct RecvFromHumenShape{

}RecvFromHumenShape;
typedef struct RecvFromClient{

}RecvFromClient;
typedef struct RecvFromAlarm {

}RecvFromAlarm;
typedef struct RecvFromjavaServer {

}RecvFromjavaServer;
typedef struct PersonMsg {
	int								m_personId;//跟踪的人物id
	short							m_TailerPort;//跟踪器的端口
	short							m_TailStatus =0;//0：跟踪 1：丢失 2：出相机
	std::string						m_TailerIp;//跟踪器的ip
	std::string						m_oprationName;//跟踪处理操作者
	std::vector<TailTrackStruct>	mv_tailTrackStruct;//跟踪轨迹向量											  
	ConnetTailAfterSocketStruct		m_connetTailAfterSocketStruct;//跟踪器socket句柄
}PersonMsg;
static std::vector<PersonMsg> g_vPersonMsg;//跟踪队列

typedef struct clientTailPersonMsg {
	int								m_personId;//跟踪的人物id
	short							m_TailerPort;//跟踪器的端口
	short							m_TailStatus = 0;//0：跟踪 1：丢失 2：出相机
	std::string						m_TailerIp;//跟踪器的ip
	std::string						m_oprationName;//跟踪处理操作者
	int								m_optState  = -1;
	std::vector<TailTrackStruct>	mv_tailTrackStruct;//跟踪轨迹向量											  
	ConnetTailAfterSocketStruct		m_connetTailAfterSocketStruct;//跟踪器socket句柄
}clientTailPersonMsg;
static std::vector<clientTailPersonMsg> g_vclientTailPersonMsg;//client跟踪队列