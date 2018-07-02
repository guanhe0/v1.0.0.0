#include "stdafx.h"
#include "CameraManager.h"

CameraManager* CameraManager::m_camManager = new CameraManager();

CameraManager* CameraManager::GetCameraManager()
{
	return m_camManager;
}

CameraManager::CameraManager()
{
	m_pGetWithJavaCamInfo.clear();
	m_pSendToClientValue.clear();
	m_pStringCamTree = "";
	m_pOrgCamInfo = "";

	//打开文件读写
	m_camDebugFile = fopen("log\\CamaraManager_debug_info.txt", "w");
	m_nWriteTimes = 0;

	m_bIsCameraMapExist = FALSE;
	m_bIsCameraTreeCreated = FALSE;
}

CameraManager::~CameraManager()
{
	if (m_camManager)
	{
		delete m_camManager;
		m_camManager = NULL;
	}
	if (m_camDebugFile != NULL)
	{
		//关闭文件读写
		fclose(m_camDebugFile);
		m_camDebugFile = NULL;
	}
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-06
修改日期：
修改内容：
修改人员：Mr Jhua.Cui
*/
void CameraManager::PrintDebugMsg(string msg, STATE_CAMERA_PRO state)
{
	if (m_camDebugFile)
	{
		m_nWriteTimes++;
		fprintf(m_camDebugFile, "[%s] [%s] [%d] *[%d]  GetMessage failed error ==== %s \n", __TIME__, __FUNCTION__, __LINE__, state, msg.data());
		if (F_FLLUSH_INDEX == m_nWriteTimes)
		{
			//更新txt
			fflush(m_camDebugFile);
			m_nWriteTimes = 0;
		}
	}
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-06
修改日期：
修改内容：
修改人员：Mr LYao.Chen
*/
void CameraManager::CheckPlatData(Json::Value & arrayPlat, int & platIndex, CameraStruct & cameraStruct)
{
	int existPlatSize = arrayPlat.size();
	int existPlatIndex = 0;
	int platID = cameraStruct.districtID;
	for (; existPlatIndex < existPlatSize; existPlatIndex++)
	{
		if (platID == arrayPlat[existPlatIndex]["districtID"].asInt())
		{
			break;//匹配，已经存在这个小区域
		}
	}
	if (existPlatIndex == existPlatSize)	//不匹配，需要插入新的小区域
	{
		Json::Value arrayCamera;//相机列表
		arrayCamera["cameraArray"] = {};
		arrayCamera["districtID"] = platID;
		arrayCamera["districtName"] = cameraStruct.districtName;
		arrayCamera["districtUrl"] = cameraStruct.districtUrl;
		arrayPlat.append(arrayCamera);
	}
	platIndex = existPlatIndex;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-06
修改日期：
修改内容：
修改人员：Mr LYao.Chen
*/
void CameraManager::GetCameraJson(Json::Value & JCamera, CameraStruct & cameraStruct)
{
	JCamera["camID"] = cameraStruct.camID;
	JCamera["camIP"] = cameraStruct.camIP;
	JCamera["camLat"] = cameraStruct.camLat;
	JCamera["camLng"] = cameraStruct.camLng;
	JCamera["camMapX"] = cameraStruct.camMapX;
	JCamera["camMapY"] = cameraStruct.camMapY;
	JCamera["camName"] = cameraStruct.camName;
	JCamera["camPort"] = cameraStruct.camPort;
	JCamera["camState"] = cameraStruct.camState;
	JCamera["inOrOut"] = cameraStruct.inOrOut;
	JCamera["mediaIP"] = cameraStruct.mediaIP;
	JCamera["mediaPassWord"] = cameraStruct.mediaPassWord;
	JCamera["mediaPort"] = cameraStruct.mediaPort;
	JCamera["mediaUserName"] = cameraStruct.mediaUserName;
	JCamera["streamType"] = cameraStruct.streamType;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-04
修改日期：2018-05-10
修改内容：实现多态
修改人员：Mr JA.CUI
*/
void CameraManager::SetOrgCamInfoFromJava(string info)
{
	if (("" != info) && (!m_bIsCameraMapExist))
	{
		PrintDebugMsg(info);
		m_pOrgCamInfo = info;
		Reader reader;
		if (!reader.parse(m_pOrgCamInfo, m_pGetWithJavaCamInfo))
		{
			PrintDebugMsg("消息解析错误！", STATE_CAMERA_PRO_DATA_PRASE_REE);
			return;
		}
		//解析消息到相机map
		PraseCamInfoFromJavaMsg();
	}	
}

void CameraManager::SetOrgCamInfoFromJava(Json::Value info)
{
	if(!m_bIsCameraMapExist)
	{ 
		//解析消息到相机map
		string orgStr = info.toStyledString();
		PrintDebugMsg(orgStr);
		PraseCamInfoFromJavaMsg(info);
	}	
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-10
修改日期：2018-05-10
修改内容：
修改人员：Mr Jhua.Cui
*/
bool CameraManager::CheckMemberExist(const char* field, int reries)
{
	bool isExist = true;
	switch (reries)
	{
	case 1:
		isExist = m_pGetWithJavaCamInfo.isMember(field);
		break;
	case 2:
		isExist = m_pGetWithJavaCamInfo["msgBody"].isMember(field);
		break;
	case 3:
		isExist = m_pGetWithJavaCamInfo["msgBody"]["dataSend"].isMember(field);
		break;
	case 4:
		isExist = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][0].isMember(field);
		break;
	case 5:
		//isExist = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][0].isMember(field);
		break;
	default:
		isExist = true;
		break;
	}
	if (!isExist)
	{
		string strField(field);
		string msg = "字段<" + strField + ">不存在";
		PrintDebugMsg(msg, STATE_CAMERA_PRO_CODE_NOT_EXIST);
	}
	return isExist;
}

bool CameraManager::CheckMemberExist(Json::Value root, const char* field, int reries)
{
	bool isExist = true;
	switch (reries)
	{
	case 1:
		isExist = root.isMember(field);
		break;
	case 2:
		isExist = root["msgBody"].isMember(field);
		break;
	case 3:
		isExist = root["msgBody"]["dataSend"].isMember(field);
		break;
	case 4:
		isExist = root["msgBody"]["dataSend"]["cameraList"][0].isMember(field);
		break;
	case 5:
		//isExist = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][0].isMember(field);
		break;
	default:
		isExist = true;
		break;
	}
	if (!isExist)
	{
		string strField(field);
		string msg = "字段<" + strField + ">不存在";
		PrintDebugMsg(msg, STATE_CAMERA_PRO_CODE_NOT_EXIST);
	}
	return isExist;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-04
修改日期：2018-05-10
修改内容：实现多态及字段检测
修改人员：Mr Jhua.Cui
*/
void CameraManager::PraseCamInfoFromJavaMsg()
{
	//检查消息中字段存在与否
	bool cdn = CheckMemberExist("msgBody", 1) && CheckMemberExist("dataSend", 2) && CheckMemberExist("cameraList", 3);
	if (!cdn)
	{
		return;
	}
	
	int camListSize = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"].size();
	if (0 == camListSize)
	{
		PrintDebugMsg("收到来自java后台的相机数目为0！", STATE_CAMERA_PRO_CAM_IS_NULL);
		return;
	}
	CMsgInteractPro pPro; //数据转换方法
	CameraStruct pCam;//相机对象
	string utf_8 = "";
	
	//检测相机列表下的所有字段是否都存在 
	bool bAllExist = CheckMemberExist("camID", 4) && CheckMemberExist("districtUrl", 4) && CheckMemberExist("camIP", 4) && CheckMemberExist("camLat", 4)
		  && CheckMemberExist("camLng", 4) && CheckMemberExist("camMapX", 4) && CheckMemberExist("camMapY", 4) && CheckMemberExist("camName", 4)
		  && CheckMemberExist("camPort", 4) && CheckMemberExist("camState", 4) && CheckMemberExist("inOrOut", 4) && CheckMemberExist("mediaIP", 4)
		  && CheckMemberExist("mediaPassWord", 4) && CheckMemberExist("mediaPort", 4) && CheckMemberExist("mediaUserName", 4) && CheckMemberExist("streamType", 4)
		  && CheckMemberExist("earaID", 4) && CheckMemberExist("earaName", 4) && CheckMemberExist("districtID", 4) && CheckMemberExist("districtName", 4);
	if (!bAllExist)
	{
		return;
	}

	//解析原始数据流到相机树
	for (int pCmaIndex = 0; pCmaIndex < camListSize; pCmaIndex++)
	{
		pCam.camID = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camID"].asInt();
		pCam.camIP = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camIP"].asString();
		pCam.camLat = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camLat"].asDouble();
		pCam.camLng = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camLng"].asDouble();
		pCam.camMapX = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camMapX"].asDouble();
		pCam.camMapY = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camMapY"].asDouble();
		
		utf_8.clear();
		utf_8 = pPro.Gb2312ToUtf_8_EX(m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camName"].asString());
		pCam.camName = utf_8;

		pCam.camPort = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camPort"].asInt();
		pCam.camState = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camState"].asInt();
		pCam.inOrOut = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["inOrOut"].asInt();
		pCam.mediaIP = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["mediaIP"].asString();
		pCam.mediaPassWord = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["mediaPassWord"].asString();
		pCam.mediaPort = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["mediaPort"].asInt();
		pCam.mediaUserName = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["mediaUserName"].asString();
		pCam.streamType = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["streamType"].asInt();
		pCam.earaID = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["earaID"].asInt();

		utf_8.clear();
		utf_8 = pPro.Gb2312ToUtf_8_EX(m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["earaName"].asString());
		pCam.earaName = utf_8;
		
		pCam.districtID = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["districtID"].asInt();

		utf_8.clear();
		utf_8 = pPro.Gb2312ToUtf_8_EX(m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["districtName"].asString());
		pCam.districtName = utf_8;

		utf_8.clear();
		utf_8 = pPro.Gb2312ToUtf_8_EX(m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["districtUrl"].asString());
		pCam.districtUrl = utf_8;
		m_mapCamera.insert(std::pair<int, CameraStruct>(pCam.camID, pCam));
	}
	m_bIsCameraMapExist = TRUE;
}

void CameraManager::PraseCamInfoFromJavaMsg(Json::Value info)
{
	//检查消息中字段存在与否
	bool cdn = CheckMemberExist(info, "msgBody", 1) && CheckMemberExist(info, "dataSend", 2) && CheckMemberExist(info, "cameraList", 3);
	if (!cdn)
	{
		return;
	}

	int camListSize = info["msgBody"]["dataSend"]["cameraList"].size();
	if (0 == camListSize)
	{
		PrintDebugMsg("收到来自java后台的相机数目为0！", STATE_CAMERA_PRO_CAM_IS_NULL);
		return;
	}

	//检测相机列表下的所有字段是否都存在
	bool bAllExist = CheckMemberExist(info, "camID", 4) && CheckMemberExist(info, "districtUrl", 4) && CheckMemberExist(info, "camIP", 4) && CheckMemberExist(info, "camLat", 4)
		&& CheckMemberExist(info, "camLng", 4) && CheckMemberExist(info, "camMapX", 4) && CheckMemberExist(info, "camMapY", 4) && CheckMemberExist(info, "camName", 4)
		&& CheckMemberExist(info, "camPort", 4) && CheckMemberExist(info, "camState", 4) && CheckMemberExist(info, "inOrOut", 4) && CheckMemberExist(info, "mediaIP", 4)
		&& CheckMemberExist(info, "mediaPassWord", 4) && CheckMemberExist(info, "mediaPort", 4) && CheckMemberExist(info, "mediaUserName", 4) && CheckMemberExist(info, "streamType", 4)
		&& CheckMemberExist(info, "earaID", 4) && CheckMemberExist(info, "earaName", 4) && CheckMemberExist(info, "districtID", 4) && CheckMemberExist(info, "districtName", 4);
	if (!bAllExist)
	{
		return;
	}
	CMsgInteractPro pPro; //数据转换方法
	CameraStruct pCam;//相机对象
	string utf_8;
	//解析原始数据流到相机树
	for (int pCmaIndex = 0; pCmaIndex < camListSize; pCmaIndex++)
	{
		pCam.camID = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camID"].asInt();
		pCam.camIP = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camIP"].asString();
		pCam.camLat = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camLat"].asDouble();
		pCam.camLng = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camLng"].asDouble();
		pCam.camMapX = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camMapX"].asDouble();
		pCam.camMapY = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camMapY"].asDouble();

		utf_8.clear();
		utf_8 = pPro.Gb2312ToUtf_8_EX(info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camName"].asString());
		pCam.camName = utf_8;

		pCam.camPort = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camPort"].asInt();
		pCam.camState = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["camState"].asInt();
		pCam.inOrOut = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["inOrOut"].asInt();
		pCam.mediaIP = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["mediaIP"].asString();
		pCam.mediaPassWord = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["mediaPassWord"].asString();
		pCam.mediaPort = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["mediaPort"].asInt();
		pCam.mediaUserName = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["mediaUserName"].asString();
		pCam.streamType = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["streamType"].asInt();
		pCam.earaID = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["earaID"].asInt();

		utf_8.clear();
		utf_8 = pPro.Gb2312ToUtf_8_EX(info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["earaName"].asString());
		pCam.earaName = utf_8;

		pCam.districtID = info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["districtID"].asInt();

		utf_8.clear();
		utf_8 = pPro.Gb2312ToUtf_8_EX(info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["districtName"].asString());
		pCam.districtName = utf_8;

		utf_8.clear();
		utf_8 = pPro.Gb2312ToUtf_8_EX(info["msgBody"]["dataSend"]["cameraList"][pCmaIndex]["districtUrl"].asString());
		pCam.districtUrl = utf_8;
		m_mapCamera.insert(std::pair<int, CameraStruct>(pCam.camID, pCam));
	}
	m_bIsCameraMapExist = TRUE;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-06
修改日期：
修改内容：
修改人员：Mr LYao.Chen
*/
void CameraManager::CreatCameraTree()
{
	if (!m_bIsCameraTreeCreated)
	{
		//构建相机树消息头
		CMsgInteractPro pInteractPro;
		pInteractPro.SetMsgUser(MSG_COMM_USER_SEVER);
		pInteractPro.SetMsgType(MSG_COMM_TYPE_JSON);
		pInteractPro.SetMsgRoot(4400, MSG_REPLY_STATE_RESPONSE);
		pInteractPro.SetMsgBodyState(0, "");

		Json::Value arrayEara;//大区域
		map<int, CameraStruct>::iterator mapCameraIt = m_mapCamera.begin();
		map<int, CameraStruct>::iterator mapCameraEnd = m_mapCamera.end();
		for (; mapCameraIt != mapCameraEnd; mapCameraIt++)
		{
			int areaIndex = 0;
			int platIndex = 0;

			// 校验大区域的数据
			CheckAreaData(arrayEara, areaIndex, mapCameraIt->second);

			// 校验小区域的数据
			CheckPlatData(arrayEara[areaIndex]["districArray"], platIndex, mapCameraIt->second);

			// 插入相机数据
			Json::Value JCamera;//相机
			GetCameraJson(JCamera, mapCameraIt->second);
			arrayEara[areaIndex]["districArray"][platIndex]["cameraArray"].append(JCamera);
		}
		m_pSendToClientValue.clear();
		m_pSendToClientValue = pInteractPro.GetJsonMsg();
		m_pSendToClientValue["msgBody"]["data"]["earaArray"] = arrayEara;
		m_pStringCamTree = m_pSendToClientValue.toStyledString();
		m_bIsCameraTreeCreated = TRUE;
	}	
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-08
修改日期：
修改内容：
修改人员：Mr LYao.Chen
*/
void CameraManager::CheckAreaData(Json::Value & arrayEara, int & areaIndex, CameraStruct & cameraStruct)
{
	int existAreaSize = arrayEara.size();
	int existAreaIndex = 0;
	int areaID = cameraStruct.earaID;
	for (; existAreaIndex < existAreaSize; existAreaIndex++)
	{
		if (areaID == arrayEara[existAreaIndex]["earaID"].asInt())
		{
			break;//匹配，已经存在这个大区域
		}
	}
	if (existAreaIndex == existAreaSize)	//不匹配，需要插入新的大区域
	{
		Json::Value arrayDistric;//小区域
		arrayDistric["earaID"] = areaID;
		arrayDistric["earaName"] = cameraStruct.earaName;
		arrayDistric["districArray"] = {};
		arrayEara.append(arrayDistric);
	}
	areaIndex = existAreaIndex;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-04
修改日期：
修改内容：
修改人员：Mr JA.CUI
*/
string CameraManager::GetCamList()
{
	//如果相机树已经创建，则返回相机树，否则生成相机树
	if(m_bIsCameraTreeCreated)
	{ 
		return m_pStringCamTree;
	}
	else
	{
		CreatCameraTree();
		return m_pStringCamTree;
	}
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-08
修改日期：
修改内容：
修改人员：Mr Jhua.Cui
*/
Value CameraManager::GetCamListEX()
{
	return m_pSendToClientValue;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-04
修改日期：
修改内容：
修改人员：Mr Jhua.Cui
*/
void CameraManager::AddCamera(Json::Value info)
{
	
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-04
修改日期：
修改内容：
修改人员：Mr Jhua.Cui
*/
void CameraManager::DeleteCamera(Json::Value info)
{

}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-10
修改日期：
修改内容：
修改人员：Mr Jhua.Cui
*/
void CameraManager::AmendCamera(Json::Value info)
{

}