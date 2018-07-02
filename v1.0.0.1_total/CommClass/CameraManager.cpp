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

	//���ļ���д
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
		//�ر��ļ���д
		fclose(m_camDebugFile);
		m_camDebugFile = NULL;
	}
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
ʵ�����ڣ�2018-05-06
�޸����ڣ�
�޸����ݣ�
�޸���Ա��Mr Jhua.Cui
*/
void CameraManager::PrintDebugMsg(string msg, STATE_CAMERA_PRO state)
{
	if (m_camDebugFile)
	{
		m_nWriteTimes++;
		fprintf(m_camDebugFile, "[%s] [%s] [%d] *[%d]  GetMessage failed error ==== %s \n", __TIME__, __FUNCTION__, __LINE__, state, msg.data());
		if (F_FLLUSH_INDEX == m_nWriteTimes)
		{
			//����txt
			fflush(m_camDebugFile);
			m_nWriteTimes = 0;
		}
	}
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
ʵ�����ڣ�2018-05-06
�޸����ڣ�
�޸����ݣ�
�޸���Ա��Mr LYao.Chen
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
			break;//ƥ�䣬�Ѿ��������С����
		}
	}
	if (existPlatIndex == existPlatSize)	//��ƥ�䣬��Ҫ�����µ�С����
	{
		Json::Value arrayCamera;//����б�
		arrayCamera["cameraArray"] = {};
		arrayCamera["districtID"] = platID;
		arrayCamera["districtName"] = cameraStruct.districtName;
		arrayCamera["districtUrl"] = cameraStruct.districtUrl;
		arrayPlat.append(arrayCamera);
	}
	platIndex = existPlatIndex;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
ʵ�����ڣ�2018-05-06
�޸����ڣ�
�޸����ݣ�
�޸���Ա��Mr LYao.Chen
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
ʵ�����ڣ�2018-05-04
�޸����ڣ�2018-05-10
�޸����ݣ�ʵ�ֶ�̬
�޸���Ա��Mr JA.CUI
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
			PrintDebugMsg("��Ϣ��������", STATE_CAMERA_PRO_DATA_PRASE_REE);
			return;
		}
		//������Ϣ�����map
		PraseCamInfoFromJavaMsg();
	}	
}

void CameraManager::SetOrgCamInfoFromJava(Json::Value info)
{
	if(!m_bIsCameraMapExist)
	{ 
		//������Ϣ�����map
		string orgStr = info.toStyledString();
		PrintDebugMsg(orgStr);
		PraseCamInfoFromJavaMsg(info);
	}	
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
ʵ�����ڣ�2018-05-10
�޸����ڣ�2018-05-10
�޸����ݣ�
�޸���Ա��Mr Jhua.Cui
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
		string msg = "�ֶ�<" + strField + ">������";
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
		string msg = "�ֶ�<" + strField + ">������";
		PrintDebugMsg(msg, STATE_CAMERA_PRO_CODE_NOT_EXIST);
	}
	return isExist;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
ʵ�����ڣ�2018-05-04
�޸����ڣ�2018-05-10
�޸����ݣ�ʵ�ֶ�̬���ֶμ��
�޸���Ա��Mr Jhua.Cui
*/
void CameraManager::PraseCamInfoFromJavaMsg()
{
	//�����Ϣ���ֶδ������
	bool cdn = CheckMemberExist("msgBody", 1) && CheckMemberExist("dataSend", 2) && CheckMemberExist("cameraList", 3);
	if (!cdn)
	{
		return;
	}
	
	int camListSize = m_pGetWithJavaCamInfo["msgBody"]["dataSend"]["cameraList"].size();
	if (0 == camListSize)
	{
		PrintDebugMsg("�յ�����java��̨�������ĿΪ0��", STATE_CAMERA_PRO_CAM_IS_NULL);
		return;
	}
	CMsgInteractPro pPro; //����ת������
	CameraStruct pCam;//�������
	string utf_8 = "";
	
	//�������б��µ������ֶ��Ƿ񶼴��� 
	bool bAllExist = CheckMemberExist("camID", 4) && CheckMemberExist("districtUrl", 4) && CheckMemberExist("camIP", 4) && CheckMemberExist("camLat", 4)
		  && CheckMemberExist("camLng", 4) && CheckMemberExist("camMapX", 4) && CheckMemberExist("camMapY", 4) && CheckMemberExist("camName", 4)
		  && CheckMemberExist("camPort", 4) && CheckMemberExist("camState", 4) && CheckMemberExist("inOrOut", 4) && CheckMemberExist("mediaIP", 4)
		  && CheckMemberExist("mediaPassWord", 4) && CheckMemberExist("mediaPort", 4) && CheckMemberExist("mediaUserName", 4) && CheckMemberExist("streamType", 4)
		  && CheckMemberExist("earaID", 4) && CheckMemberExist("earaName", 4) && CheckMemberExist("districtID", 4) && CheckMemberExist("districtName", 4);
	if (!bAllExist)
	{
		return;
	}

	//����ԭʼ�������������
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
	//�����Ϣ���ֶδ������
	bool cdn = CheckMemberExist(info, "msgBody", 1) && CheckMemberExist(info, "dataSend", 2) && CheckMemberExist(info, "cameraList", 3);
	if (!cdn)
	{
		return;
	}

	int camListSize = info["msgBody"]["dataSend"]["cameraList"].size();
	if (0 == camListSize)
	{
		PrintDebugMsg("�յ�����java��̨�������ĿΪ0��", STATE_CAMERA_PRO_CAM_IS_NULL);
		return;
	}

	//�������б��µ������ֶ��Ƿ񶼴���
	bool bAllExist = CheckMemberExist(info, "camID", 4) && CheckMemberExist(info, "districtUrl", 4) && CheckMemberExist(info, "camIP", 4) && CheckMemberExist(info, "camLat", 4)
		&& CheckMemberExist(info, "camLng", 4) && CheckMemberExist(info, "camMapX", 4) && CheckMemberExist(info, "camMapY", 4) && CheckMemberExist(info, "camName", 4)
		&& CheckMemberExist(info, "camPort", 4) && CheckMemberExist(info, "camState", 4) && CheckMemberExist(info, "inOrOut", 4) && CheckMemberExist(info, "mediaIP", 4)
		&& CheckMemberExist(info, "mediaPassWord", 4) && CheckMemberExist(info, "mediaPort", 4) && CheckMemberExist(info, "mediaUserName", 4) && CheckMemberExist(info, "streamType", 4)
		&& CheckMemberExist(info, "earaID", 4) && CheckMemberExist(info, "earaName", 4) && CheckMemberExist(info, "districtID", 4) && CheckMemberExist(info, "districtName", 4);
	if (!bAllExist)
	{
		return;
	}
	CMsgInteractPro pPro; //����ת������
	CameraStruct pCam;//�������
	string utf_8;
	//����ԭʼ�������������
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
ʵ�����ڣ�2018-05-06
�޸����ڣ�
�޸����ݣ�
�޸���Ա��Mr LYao.Chen
*/
void CameraManager::CreatCameraTree()
{
	if (!m_bIsCameraTreeCreated)
	{
		//�����������Ϣͷ
		CMsgInteractPro pInteractPro;
		pInteractPro.SetMsgUser(MSG_COMM_USER_SEVER);
		pInteractPro.SetMsgType(MSG_COMM_TYPE_JSON);
		pInteractPro.SetMsgRoot(4400, MSG_REPLY_STATE_RESPONSE);
		pInteractPro.SetMsgBodyState(0, "");

		Json::Value arrayEara;//������
		map<int, CameraStruct>::iterator mapCameraIt = m_mapCamera.begin();
		map<int, CameraStruct>::iterator mapCameraEnd = m_mapCamera.end();
		for (; mapCameraIt != mapCameraEnd; mapCameraIt++)
		{
			int areaIndex = 0;
			int platIndex = 0;

			// У������������
			CheckAreaData(arrayEara, areaIndex, mapCameraIt->second);

			// У��С���������
			CheckPlatData(arrayEara[areaIndex]["districArray"], platIndex, mapCameraIt->second);

			// �����������
			Json::Value JCamera;//���
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
ʵ�����ڣ�2018-05-08
�޸����ڣ�
�޸����ݣ�
�޸���Ա��Mr LYao.Chen
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
			break;//ƥ�䣬�Ѿ��������������
		}
	}
	if (existAreaIndex == existAreaSize)	//��ƥ�䣬��Ҫ�����µĴ�����
	{
		Json::Value arrayDistric;//С����
		arrayDistric["earaID"] = areaID;
		arrayDistric["earaName"] = cameraStruct.earaName;
		arrayDistric["districArray"] = {};
		arrayEara.append(arrayDistric);
	}
	areaIndex = existAreaIndex;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
ʵ�����ڣ�2018-05-04
�޸����ڣ�
�޸����ݣ�
�޸���Ա��Mr JA.CUI
*/
string CameraManager::GetCamList()
{
	//���������Ѿ��������򷵻���������������������
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
ʵ�����ڣ�2018-05-08
�޸����ڣ�
�޸����ݣ�
�޸���Ա��Mr Jhua.Cui
*/
Value CameraManager::GetCamListEX()
{
	return m_pSendToClientValue;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
ʵ�����ڣ�2018-05-04
�޸����ڣ�
�޸����ݣ�
�޸���Ա��Mr Jhua.Cui
*/
void CameraManager::AddCamera(Json::Value info)
{
	
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
ʵ�����ڣ�2018-05-04
�޸����ڣ�
�޸����ݣ�
�޸���Ա��Mr Jhua.Cui
*/
void CameraManager::DeleteCamera(Json::Value info)
{

}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
ʵ�����ڣ�2018-05-10
�޸����ڣ�
�޸����ݣ�
�޸���Ա��Mr Jhua.Cui
*/
void CameraManager::AmendCamera(Json::Value info)
{

}