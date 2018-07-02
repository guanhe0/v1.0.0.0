#include "stdafx.h"
#include "MsgInteractPro.h"


CMsgInteractPro::CMsgInteractPro()
{
	m_sarchCdn.clear();
	//m_strCdn = "";
	m_user = MSG_COMM_USER_SEVER;
	m_type = MSG_COMM_TYPE_JSON;
}

CMsgInteractPro::~CMsgInteractPro()
{
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-03
修改日期：
修改内容：
修改人员：Mr JA.CUI
*/
void CMsgInteractPro::SetMsgUser(USER_MsgComm pUser)
{
	m_user = pUser;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-03
修改日期：
修改内容：
修改人员：Mr JA.CUI
*/
void CMsgInteractPro::SetMsgType(Type_MsgFit pType)
{
	m_type = pType;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-03
修改日期：
修改内容：
修改人员：Mr JA.CUI
*/
Value CMsgInteractPro::GetJsonMsg()
{
	return m_sarchCdn;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-03
修改日期：
修改内容：
修改人员：Mr JA.CUI
*/
string CMsgInteractPro::GetStringMsg()
{
	string pStr = m_sarchCdn.toStyledString();
	return pStr;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-03
修改日期：
修改内容：
修改人员：Mr JA.CUI
*/
State_MsgPro CMsgInteractPro::SetMsgRoot(int msgCode, Type_MsgReply msgType, string serverIP, string clientIP)
{
	State_MsgPro state = MSG_PRO_STATE_OK;
	//获取系统时间戳
	SYSTEMTIME tmSys;
	GetLocalTime(&tmSys);
	CTime tm3(tmSys);
	__int64 tmDst = __int64(tm3.GetTime()) * 1000 + tmSys.wMilliseconds;
	//Json消息体
	if (MSG_COMM_TYPE_JSON == m_type)
	{
		m_sarchCdn["msgHead"] = {};
		if (MSG_COMM_USER_CLENT == m_user)
		{
			m_sarchCdn["msgHead"]["serverIP"] = serverIP; //服务器的地址
		}
		m_sarchCdn["msgHead"]["clientIP"] = clientIP;     //客户端的地址（本地）
		m_sarchCdn["msgHead"]["msgCode"] = msgCode;       //消息码
		m_sarchCdn["msgHead"]["msgType"] = (int)msgType;  //消息类型 0-无需 1-必须回复
		m_sarchCdn["msgHead"]["timestamp"] = tmDst;       //时间戳
		m_sarchCdn["msgHead"]["requestID"] = 1000;	      //请求ID
		m_sarchCdn["msgHead"]["boundID"] = 0;		      //业务认证得到的ID
		m_sarchCdn["msgHead"]["authorization"] = "";      //签名

		m_sarchCdn["msgBody"] = {};
		if (MSG_COMM_USER_CLENT == m_user)
		{
			m_sarchCdn["msgBody"]["request"] = {};        //请求消息体回馈描述
			m_sarchCdn["msgBody"]["request"]["code"] = {};//请求回馈状态
			m_sarchCdn["msgBody"]["request"]["msg"] = {}; //回馈状态描述
		}
		else
		{
			m_sarchCdn["msgBody"]["state"] = {};           //回复描述
			m_sarchCdn["msgBody"]["state"]["code"] = {};   //回馈状态
			m_sarchCdn["msgBody"]["state"]["msg"] = {};    //回馈状态描述
		}
		m_sarchCdn["msgBody"]["data"] = {};                //数据
	}
	else
	{
		//http消息体
	}
	return state;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-03
修改日期：
修改内容：
修改人员：
*/
State_MsgPro CMsgInteractPro::AddItemToMsgBody(const char* key, string sDataValue)
{
	//转码操作
	const char* utf_81 = StringToConstCharX(sDataValue);
	string strValue = Gb2312ToUtf_8(utf_81);
	if (utf_81) delete[] utf_81;

	if (MSG_COMM_TYPE_JSON == m_type)
	{
		m_sarchCdn["msgBody"]["data"][key] = strValue;
	}

	//...
	return MSG_PRO_STATE_OK;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-03
修改日期：
修改内容：
修改人员：Mr JA.CUI
*/
State_MsgPro CMsgInteractPro::AddItemToMsgBody(const char* key, int nDataValue)
{
	if (MSG_COMM_TYPE_JSON == m_type)
	{
		m_sarchCdn["msgBody"]["data"][key] = nDataValue;
	}
	//...
	return MSG_PRO_STATE_OK;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-03
修改日期：
修改内容：
修改人员：Mr JA.CUI
*/
State_MsgPro CMsgInteractPro::AddItemToMsgBody(const char* key, float fDataValue)
{
	if (MSG_COMM_TYPE_JSON == m_type)
	{
		m_sarchCdn["msgBody"]["data"][key] = fDataValue;
	}
	//...
	return MSG_PRO_STATE_OK;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-05
修改日期：
修改内容：
修改人员：Mr JA.CUI
*/
State_MsgPro CMsgInteractPro::AddArrayToMsgBody(const char* key)
{
	if (MSG_COMM_TYPE_JSON == m_type)
	{
		if (m_sarchCdn["msgBody"]["data"][key].isNull())
		{
			m_sarchCdn["msgBody"]["data"][key] = {};                //数据
		}
	}
	//...
	return MSG_PRO_STATE_OK;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-03
修改日期：
修改内容：
修改人员：Mr JA.CUI
*/
State_MsgPro CMsgInteractPro::SetMsgBodyState(int nCode, string pMsg)
{
	const char* utf_81 = StringToConstCharX(pMsg);
	string strValue = Gb2312ToUtf_8(utf_81);
	if (utf_81) delete[] utf_81;

	if (MSG_COMM_TYPE_JSON == m_type && MSG_COMM_USER_CLENT == m_user)
	{
		m_sarchCdn["msgBody"]["request"]["code"] = nCode;//请求回馈状态
		m_sarchCdn["msgBody"]["request"]["msg"] = strValue; //回馈状态描述
	}
	if (MSG_COMM_TYPE_JSON == m_type && MSG_COMM_USER_SEVER == m_user)
	{
		m_sarchCdn["msgBody"]["state"]["code"] = nCode;//回馈状态
		m_sarchCdn["msgBody"]["state"]["msg"] = strValue; //回馈状态描述
	}
	//...
	return MSG_PRO_STATE_OK;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-03
修改日期：
修改内容：
修改人员：Mr JA.CUI
*/
const char* CMsgInteractPro::StringToConstCharX(string str)
{
	char* c;
	const int len = (const int)(str.length());
	c = new char[len + 1];
	strcpy(c, str.c_str());
	return c;

}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-03
修改日期：
修改内容：
修改人员：Mr JA.CUI
*/
string CMsgInteractPro::Gb2312ToUtf_8(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr)
	{
		delete[] wstr;
		wstr = NULL;
	}
	string resStr = "";
	resStr = str;
	if (str)
	{
		delete[] str;
		str = NULL;
	}
	return resStr;
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
实现日期：2018-05-04
修改日期：
修改内容：
修改人员：Mr JA.CUI
*/
string CMsgInteractPro::Gb2312ToUtf_8_EX(string gb2312)
{
	const char* utf_81 = StringToConstCharX(gb2312);
	string strValue = Gb2312ToUtf_8(utf_81);
	if (utf_81) delete[] utf_81;
	return strValue;
}