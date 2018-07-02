#ifndef _SEVER_LOGIC_COMMUNICAT_CAMERA_MANAGER_2018_05_04_
#define _SEVER_LOGIC_COMMUNICAT_CAMERA_MANAGER_2018_05_04_
//CameraManager.h
/*********************************************************************************************
Copyright (C), ....-...., PINGAN Technology Co.,Ltd.
File name:	   EXPORT_WebOffLineMapWnd.h
Author:		   Mr JA.CUI R&D Department.
Version:	   V1.2.0.0
Date:		   2018-05-04
Description:   ��Ϣ������װ��
namespace:
Others:		   PINGAN Technology Co.,Ltd. All rights reserved.
**********************************************************************************************/
#include ".\MsgInteractPro.h"
#include <map>
#define  F_FLLUSH_INDEX 1

using namespace std;
using namespace Json;
//_WINSOCK_DEPRECATED_NO_WARNINGS
typedef struct _EaraMapStruct
{
	int     eId;      //������ID
	int     eSize;    //������֮��С��������
	string  eName;    //����������
	_EaraMapStruct()
	{
		eId = 0;
		eSize = 0;
		eName = "";
	}
}EaraMapStruct;
inline EaraMapStruct Build_EaraMapStruct(int id, int size, string name)
{
	EaraMapStruct res;
	res.eId = id;
	res.eSize = size;
	res.eName = name;
}

typedef struct _DistMapStruct
{
	int     dId;     //С����ID
	int     dSize;   //С�������������
	string  dName;   //С��������
	string  dAddress;//��ͼ��ַ
	_DistMapStruct()
	{
		dId = 0;
		dSize = 0;
		dName = "";
		dAddress = "";
	}
}DistMapStruct;
inline DistMapStruct Build_DistMapStruct(int id, int size, string name, string address)
{
	DistMapStruct res;
	res.dId = id;
	res.dSize = size;
	res.dName = name;
	res.dAddress = address;
	return res;
}

typedef struct _CameraStruct
{
	int    camID;//���id
	string camIP;//���ip
	double camLat;//Gis����γ��
	double camLng;//Gis��������
	double camMapX;//��ͼx����
	double camMapY;//��ͼy����
	string camName;//�����
	int	   camPort;//����˿�
	int	   camState;//���״̬
	int	   inOrOut;//���ڻ�����
	string mediaIP;//��ý���ַ
	string mediaPassWord;//��ý������
	int	   mediaPort;//��ý��˿�
	string mediaUserName;//ý��������û���
	int	   streamType;//������

	int     earaID;//������ID
	string	earaName;//����������
	int     districtID;//С����ID
	string  districtName;//С��������
	string  districtUrl;//��ͼ��ַ
	_CameraStruct()
	{
		camID = 0;
		camIP = "";
		camLat = 0.0;
		camLng = 0.0;
		camMapX = 0.0;
		camMapY = 0.0;
		camName = "";
		camPort = 0;
		camState = 0;
		inOrOut = 0;
		mediaIP = "";
		mediaPassWord = "";
		mediaPort = 0;
		mediaUserName = "";
		streamType = 0;

		earaID = 0;
		earaName = "";
		districtID = 0;
		districtName = "";
		districtUrl = ""; 
	}
}CameraStruct;

typedef enum _STATE_CAMERA_PRO_
{
	STATE_CAMERA_PRO_OK = 0x0001,  //����״̬
	STATE_CAMERA_PRO_DATA_PRASE_REE = -0x0101,  //���ݽ�������
	STATE_CAMERA_PRO_CODE_NOT_EXIST = -0x0102,  //�ֶβ�����
	STATE_CAMERA_PRO_CAM_IS_NULL = -0x0102,     //�����ĿΪ0
	STATE_CAMERA_PRO_TREE_CREATE_ERR = -0x0104,  //�������װʧ��
	STATE_CAMERA_TREE_ADD_ACAN_ERR = -0x0105,  //��������ʧ��
	STATE_CAMERA_TREE_DEL_ACAM_ERR = -0x0106,  //ɾ�������ʧ��
}STATE_CAMERA_PRO;

class CameraManager
{
private:
	CameraManager();
	~CameraManager();
private:
	string m_pOrgCamInfo;                //����Java��ԭʼ����
	Value  m_pGetWithJavaCamInfo;        //����Java���������Ϣ

	BOOL   m_bIsCameraMapExist;          //���map�Ƿ����
	BOOL   m_bIsCameraTreeCreated;       //������Ƿ��Ѿ�����
	map<int, CameraStruct> m_mapCamera;  //����洢map
	Value  m_pSendToClientValue;         //���͸��ͻ��˵��������Value��
	string m_pStringCamTree;             //���͸��ͻ��˵��������string��

	FILE  *m_camDebugFile;               //��־����ĵ�
	int    m_nWriteTimes;                 //��־д�����
public:
	static CameraManager* m_camManager;		   //����
	static CameraManager* GetCameraManager();  //��ȡ�������



private:
	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ��װ�����ͻ��˵��������������������У��
	*-> @param1
	*-> #return     void
	/*/
	void CheckAreaData(Json::Value & arrayEara/*in out*/, int & areaIndex/*out*/, CameraStruct & cameraStruct);

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ��װ�����ͻ��˵����������С��������У��
	*-> @param1
	*-> #return     void
	/*/
	void CheckPlatData(Json::Value & arrayPlat/*in out*/, int & platIndex/*out*/, CameraStruct & cameraStruct);

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ��װ�����ͻ��˵����������������ݲ���
	*-> @param1
	*-> #return     void
	/*/
	void GetCameraJson(Json::Value & JCamera/*out*/, CameraStruct & cameraStruct);

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ��������java����Ϣ�����map
	*-> @param1
	*-> #return     void
	/*/
	void    PraseCamInfoFromJavaMsg();
	void    PraseCamInfoFromJavaMsg(Json::Value info);


	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ��ӡ��־
	*-> @param1
	*-> #return     void
	/*/
	void    PrintDebugMsg(string msg, STATE_CAMERA_PRO state = STATE_CAMERA_PRO_OK);

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   �ֶ��Ƿ���ڼ�飨msgbody��
	*-> @param1     field ������ֶ�
	*-> @param2     reries ����
	*-> #return     void
	/*/
	bool    CheckMemberExist(const char* field, int reries);
	bool    CheckMemberExist(Json::Value root, const char* field, int reries);
public:
	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ����ԭʼ���յ�����Ϣ����
	*-> @param1     info  ����java��ԭʼ����
	*-> #return     void
	/*/
	void    SetOrgCamInfoFromJava(string info);
	void    SetOrgCamInfoFromJava(Json::Value info);

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ��װ�����ͻ��˵������
	*-> @param1
	*-> #return     void
	/*/
	void CreatCameraTree();

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ��ȡ�����
	*-> @param1
	*-> #return     string/Value �����
	/*/
	string  GetCamList();
	Value   GetCamListEX();

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ���һ�����
	*-> @param1
	*-> #return     
	/*/
	void    AddCamera(Json::Value info);

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ɾ��һ�����
	*-> @param1
	*-> #return
	/*/
	void    DeleteCamera(Json::Value info);

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   �޸�һ�����
	*-> @param1
	*-> #return
	/*/
	void    AmendCamera(Json::Value info);
};
#endif // _SEVER_LOGIC_COMMUNICAT_CAMERA_MANAGER_2018_05_04_
