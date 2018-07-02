#ifndef _SEVER_LOGIC_COMMUNICAT_CAMERA_MANAGER_2018_05_04_
#define _SEVER_LOGIC_COMMUNICAT_CAMERA_MANAGER_2018_05_04_
//CameraManager.h
/*********************************************************************************************
Copyright (C), ....-...., PINGAN Technology Co.,Ltd.
File name:	   EXPORT_WebOffLineMapWnd.h
Author:		   Mr JA.CUI R&D Department.
Version:	   V1.2.0.0
Date:		   2018-05-04
Description:   消息传递组装类
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
	int     eId;      //大区域ID
	int     eSize;    //大区域之下小区域数量
	string  eName;    //大区域名称
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
	int     dId;     //小区域ID
	int     dSize;   //小区域下相机数量
	string  dName;   //小区域名称
	string  dAddress;//地图地址
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
	int    camID;//相机id
	string camIP;//相机ip
	double camLat;//Gis布防纬度
	double camLng;//Gis布防经度
	double camMapX;//地图x坐标
	double camMapY;//地图y坐标
	string camName;//相机名
	int	   camPort;//相机端口
	int	   camState;//相机状态
	int	   inOrOut;//室内或室外
	string mediaIP;//流媒体地址
	string mediaPassWord;//流媒体密码
	int	   mediaPort;//流媒体端口
	string mediaUserName;//媒体服务器用户名
	int	   streamType;//流类型

	int     earaID;//大区域ID
	string	earaName;//大区域名字
	int     districtID;//小区域ID
	string  districtName;//小区域名称
	string  districtUrl;//地图地址
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
	STATE_CAMERA_PRO_OK = 0x0001,  //正常状态
	STATE_CAMERA_PRO_DATA_PRASE_REE = -0x0101,  //数据解析错误
	STATE_CAMERA_PRO_CODE_NOT_EXIST = -0x0102,  //字段不存在
	STATE_CAMERA_PRO_CAM_IS_NULL = -0x0102,     //相机数目为0
	STATE_CAMERA_PRO_TREE_CREATE_ERR = -0x0104,  //相机树组装失败
	STATE_CAMERA_TREE_ADD_ACAN_ERR = -0x0105,  //添加相机树失败
	STATE_CAMERA_TREE_DEL_ACAM_ERR = -0x0106,  //删除相机树失败
}STATE_CAMERA_PRO;

class CameraManager
{
private:
	CameraManager();
	~CameraManager();
private:
	string m_pOrgCamInfo;                //来自Java的原始数据
	Value  m_pGetWithJavaCamInfo;        //来自Java的相机树信息

	BOOL   m_bIsCameraMapExist;          //相机map是否存在
	BOOL   m_bIsCameraTreeCreated;       //相机树是否已经创建
	map<int, CameraStruct> m_mapCamera;  //相机存储map
	Value  m_pSendToClientValue;         //发送给客户端的相机树（Value）
	string m_pStringCamTree;             //发送给客户端的相机树（string）

	FILE  *m_camDebugFile;               //日志输出文档
	int    m_nWriteTimes;                 //日志写入次数
public:
	static CameraManager* m_camManager;		   //单例
	static CameraManager* GetCameraManager();  //获取操作句柄



private:
	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   组装交给客户端的相机树——大区域数据校验
	*-> @param1
	*-> #return     void
	/*/
	void CheckAreaData(Json::Value & arrayEara/*in out*/, int & areaIndex/*out*/, CameraStruct & cameraStruct);

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   组装交给客户端的相机树——小区域数据校验
	*-> @param1
	*-> #return     void
	/*/
	void CheckPlatData(Json::Value & arrayPlat/*in out*/, int & platIndex/*out*/, CameraStruct & cameraStruct);

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   组装交给客户端的相机树——相机数据插入
	*-> @param1
	*-> #return     void
	/*/
	void GetCameraJson(Json::Value & JCamera/*out*/, CameraStruct & cameraStruct);

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   解析来自java的消息到相机map
	*-> @param1
	*-> #return     void
	/*/
	void    PraseCamInfoFromJavaMsg();
	void    PraseCamInfoFromJavaMsg(Json::Value info);


	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   打印日志
	*-> @param1
	*-> #return     void
	/*/
	void    PrintDebugMsg(string msg, STATE_CAMERA_PRO state = STATE_CAMERA_PRO_OK);

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   字段是否存在检查（msgbody）
	*-> @param1     field 待检测字段
	*-> @param2     reries 级数
	*-> #return     void
	/*/
	bool    CheckMemberExist(const char* field, int reries);
	bool    CheckMemberExist(Json::Value root, const char* field, int reries);
public:
	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   设置原始接收到的消息数据
	*-> @param1     info  来自java的原始数据
	*-> #return     void
	/*/
	void    SetOrgCamInfoFromJava(string info);
	void    SetOrgCamInfoFromJava(Json::Value info);

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   组装交给客户端的相机树
	*-> @param1
	*-> #return     void
	/*/
	void CreatCameraTree();

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   获取相机树
	*-> @param1
	*-> #return     string/Value 相机树
	/*/
	string  GetCamList();
	Value   GetCamListEX();

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   添加一个相机
	*-> @param1
	*-> #return     
	/*/
	void    AddCamera(Json::Value info);

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   删除一个相机
	*-> @param1
	*-> #return
	/*/
	void    DeleteCamera(Json::Value info);

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   修改一个相机
	*-> @param1
	*-> #return
	/*/
	void    AmendCamera(Json::Value info);
};
#endif // _SEVER_LOGIC_COMMUNICAT_CAMERA_MANAGER_2018_05_04_
