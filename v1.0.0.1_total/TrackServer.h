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
//��������
#define LCAMID 1
#define RCAMID 2	
#define FCAMID 3
#define BCAMID 4
#define UCAMID 5
#define DCAMID 6


#define TRACKSERVE_RADDR			"tcp://localhost:36542" //���Եĸ��ٷ�������ַ

 static zmq::context_t contextT(1);

//������
 static std::mutex g_mutex;

typedef struct camStruct {
	int								s_zoneID;//�������
	int								s_camID;//���id
	int								s_LcamID = 0;//������ ���id
	int 							s_RcamID = 0;//������ ���id
	int 							s_FcamID = 0;//����ǰ ���id
	int 							s_BcamID = 0;//���򣺺� ���id
	int 							s_UcamID = 0;//������ ���id
	int 							s_DcamID = 0;//������ ���id
}camStruct;
static std::vector<camStruct> g_vCamStruct;//����������ݽṹ
typedef struct timeval TrackTimeValue;
//���ٶ���
typedef struct TailTrackStruct
{
	int s_CamId;//���ID
	std::vector<TrackTimeValue> s_VTrackTimeValue;
	//ʱ���
}TailTrackStruct;


//����client�߳����ݽṹ
typedef struct RecvFromAlarmStruct
{
	//��Ҫ����Ŀ��
	int s_TailPersonId = 0;
}RecvFromAlarmStruct;
//������ý�����ݽṹ
typedef struct RecvFromFramServerStruct
{

}RecvFromFramServerStruct;
//����client�̵߳����ݽṹ
typedef struct RecvFromClientServerStruct
{
	int				s_personId;//����id
							   //ȷ����������id
	int				s_TailPersonId = 0;
	int				s_msgID;
	int				s_optState = -1;//����״̬
	std::string		s_optStaff;//������
						   //���ٴ���
	int				s_TailWrong = 0;
	int				s_ChangeTap = 0;//�л���ǩҳ
	int				s_OverTracking = 0;
	int				s_lastPersonID;//��һҳ������id   personID ��ǰ������id
	int				s_Misinformtion = 0;//��
	int				s_camId;//���id
	//int				s_GetTrackPersoID = 0;
	//��ȡ���ٹ켣
	int				s_getTailTrack = 0;
}RecvFromClientServerStruct;

typedef struct InitTailServerStruct {
	std::string connectSocketIp;//������IP
	short  port;//�����ǵĶ˿�
	std::string TailName;//�����ǵ�����
	int TailId;//�����ǵ�id
	std::string s_connectSocketAddr;//�����ӵ�zmq::socket tcp��ַ
}InitTailServerStruct;
static std::vector<InitTailServerStruct> g_InitTailServerStruct;
//���ٷ���socket����
typedef struct ConnetTrackSocketStruct {
	intptr_t s_Id;
	zmq::socket_t *s_connetTrackSocket;
}ConnetTrackSocketStruct;
//��Ⱦ��
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
//����Java��̨����
typedef struct RecvFromJavaServerStruct {
	int						InitTrackMsg = 0;
	int						AddTrackMsg = 0;
	int						RemoveTrackMsg = 0;
}RecvFromJavaServerStruct;
//�������η��������ݽṹ
typedef struct RecvFromHumanShapeServerStruct {
	int						AlamMsg = 0;
	int						AllHumanShape = 0;
	timeval					s_timeval;

	int						s_personId;//����id
	int						s_camID;//���id
	std::string				s_camAddr;
	std::string				s_srcPictureDir;//Դͼ·��
	std::string				s_roiPictureDir;//��ͼ·��
	std::string				s_TrackerSrcpictureFramName;//����ͼ
	std::vector<HumanROI>	sv_roi;//����ROI
	std::vector<FaceROI>    sv_face_roi;//����ROI

}RecvFromHumanShapeServerStruct;
//���ո��ٷ������ݽṹ
typedef struct RecvFromTrackStruct {
	int						s_msgCode;
	int						s_lost = 0;				//��ʧ
	int						s_Tailing = 0;			//����
	int						s_regAgin = 0;			//��ʶ��
	int						s_outFromCamera = 0;	//�����

	int						s_zoneID;//�������
	int						s_iPersonID;//����id
	int						s_iCamId;//���id
	int						s_iDirection;//����
	timeval					s_lTime;//ʱ���
	HumanROI				s_RHumenROI;
	camStruct				s_camStruct;//�������
	std::string				s_sTrackerSrcpictureFramName;

}RecvFromTrackStruct;
//���յ������̵߳����ݽṹ
typedef struct RecvFromServerStruct {
	int								s_FramServer = 0;//��ý��ģ��
	int								s_client = 0;	//�ͻ���ģ��
	int								s_javaServer = 0;//JavaServerģ��  1��Init 2,
	int								s_HumenShape = 0;//���η�����ģ��
	int								s_Alarm = 0;	//�澯ģ��
	long							s_requestid = 0;
	InitTailServerStruct			s_initTailServerStruct;//��ʼ�����ٷ��������
	RecvFromJavaServerStruct		s_recvFromJavaServerStruct;//���յ�java�̵߳�����
	//RecvFromAlarmStruct			s_recvFromAlarmStruct;//���յ��澯������
	//RecvFromFramServerStruct		s_recvFromFramServerStruct;//������ý������
	RecvFromClientServerStruct		s_recvFromClientServerStruct;//����client �߳�
	RecvFromHumanShapeServerStruct	s_recvFromHumanShapeServerStruct;//�������η������߳�����
}RecvFromServerStruct;

typedef struct PersonMsg {
	int								m_camId;
	int								m_personId;					//���ٵ�����id
	short							m_TailerPort;				//�������Ķ˿�
	short							m_TailStatus = 8;			//0������ 1����ʧ 2������� 8����δ����
	std::string						m_TailerIp;					//��������ip
	std::string						m_oprationName;				//���ٴ��������
	std::vector<TailTrackStruct>	mv_tailTrackStruct;			//���ٹ켣����											  
	ConnetTrackSocketStruct			m_connetTrackSocketStruct;	//������socket���
	timeval							m_TrackingTime;				//����ʱ��
	int								m_optState = -1;			//����״̬
}PersonMsg;
static std::vector<PersonMsg>		g_vPersonMsg;				//��̨һֱ���ٵı�������id����

typedef struct clientTailPersonMsg {
	int								m_personId;//���ٵ�����id
	//short							m_TailerPort;//�������Ķ˿�
	//short							m_TailStatus = 0;//0������ 1����ʧ 2�������
	//std::string					m_TailerIp;//��������ip
	std::string						m_oprationName;//���ٴ��������
	int								m_optState = -1;
	std::vector<TailTrackStruct>	mv_tailTrackStruct;//���ٹ켣����											  
	//ConnetTrackSocketStruct		m_connetTrackSocketStruct;//������socket���
}clientTailPersonMsg;
static std::vector<clientTailPersonMsg> g_vclientTailPersonMsg;//����clientȷ�ϵ�Ŀ��ID����״̬����


class TrackServer
{
public:
	TrackServer();
	virtual ~TrackServer();
	//���Ը��ٷ���������
	int mTrackServerRunForTrack(std::string& recvStr, std::string& sendStr);
	//�������ٷ�����������
	int parseTrackStrToJson(std::string &recvStr, RecvFromTrackStruct &recvFromTrackStruct);
	//���������̷߳���������
	int parseOthrerThreadStrToJson(std::string &recvStr, RecvFromServerStruct &recvFromServerStruct);
	//��ʧ
	int TrackServerDealLost(RecvFromTrackStruct &recvFromTrackStruct, std::string &sendStr);
	//��ʶ��
	int TrackServerDealRegAgin(RecvFromTrackStruct &recvFromTrackStruct, std::string &sendStr);
	//����
	int TrackServerDealTailing(RecvFromTrackStruct &recvFromTrackStruct, std::string &sendStr);
	//�����
	int TrackServerDealOutFromCamera(RecvFromTrackStruct &recvFromTrackStruct, std::string &sendStr);

	//��ʼ�����ٷ���������
	int TrackServerInit(std::string &InitMsgStr);
	//����
	int mTrackServerRunForServer(std::string& recvStr, std::string& sendStr);
	//������
	int parseServerStrToJson(std::string &recvStr, RecvFromServerStruct &recvFromServerStruct);
	//�澯ģ������
	int  TrackServerDealOutFromAlarm(RecvFromServerStruct &recvFromServerStruct, std::string &sendStr);
	//client�߳�����
	int  TrackServerDealOutFromClient(RecvFromServerStruct &recvFromServerStruct, std::string &sendStr);
	//��ý���߳�����
	int  TrackServerDealOutFromFramServer(RecvFromServerStruct &recvFromServerStruct, std::string &sendStr);
	//���η������߳�����
	int  TrackServerDealOutFromHumenShape(RecvFromServerStruct &recvFromServerStruct, std::string &sendStr);
	//Java��̨�߳�����
	int  TrackServerDealOutFromJavaServer(RecvFromServerStruct &recvFromServerStruct, std::string &sendStr);
	//���ظ�������������
	std::vector<ConnetTrackSocketStruct> *getconnetTrackSocketStruct();
	//����java��̨�����ʼ������
	int ParseJsonInitMsg(std::string &sendInit);
	/***********************test begin**************************/
	//�洢���ٷ��������Ӷ���
	std::vector<ConnetTrackSocketStruct> mv_connetTrackSocketStruct;
	//���ͳ�ʼ�����ݸ����ٷ�����
	int sendInitTrackMsg(zmq::socket_t *socket);
	/***********************test end**************************/
private:
	//��ʼ�����ٷ���������
	int InitTrackMsg(RecvFromServerStruct &recvFromServerStruct);
	//���Ӹ��ٷ�����
	int AddTrackMsg(RecvFromServerStruct &recvFromServerStruct);
	//�Ƴ����ٷ�����
	int RemoveTrackMsg(RecvFromServerStruct &recvFromServerStruct);
	//���ͳ�ʼ�����ݸ����ٷ�����
	//int sendInitTrackMsg(zmq::socket_t *socket);
	//�������ٷ�����������
	int bindTrackMsg();
	//�洢���ٷ��������Ӷ���
	//std::vector<ConnetTrackSocketStruct> mv_connetTrackSocketStruct;

	//���Ͷ�ʧ��Ϣ��java �߳�
	int sendLostMsgToJavaThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
	//���Ͷ�ʧ��Ϣ��client�߳�
	int sendLostMsgToClientThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
	//������ʶ����Ϣ�����η����߳�
	int sendRegAginMsgToHumanShapeThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
	//���͸�����Ϣ��java�߳�
	int sendTrackingMsgToJavaThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
	//���͸�����Ϣ��java�߳�
	int sendTrackingMsgToClientThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
	//���͸�����Ϣ����ý��
	int sendTrackingMsgToMediaThread(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
	//���ͳ������������Ϣ�����ٷ�����
	int sendTOutCameraMsgToTrackServer(RecvFromTrackStruct & recvFromTrackStruct, std::string & sendStr);
};


#endif
typedef struct timeval TrackTimeValue;



//extern TailTrackStruct test;


DWORD  WINAPI TrackWorker(void * context);
extern char *g_trackserver_stralivecheck;
