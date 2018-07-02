#ifndef _MSG_INTERACT_PRO_DEFINE_2018_05_03_CLENT_CTEATED_
#define _MSG_INTERACT_PRO_DEFINE_2018_05_03_CLENT_CTEATED_

//EXPORT_WebOffLineMapWnd.h
/*********************************************************************************************
Copyright (C), ....-...., PINGAN Technology Co.,Ltd.
File name:	   EXPORT_WebOffLineMapWnd.h
Author:		   Mr JA.CUI R&D Department.
Version:	   V1.2.0.0
Date:		   2018-05-03
Description:   消息传递组装类
namespace:     
Others:		   PINGAN Technology Co.,Ltd. All rights reserved.
**********************************************************************************************/

//#include "windows.h"
//#include<iostream>  
#include<atltime.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <fstream>

//#include "..\include\zmq.h"
#include "..\jsonInclude\json.h"
//#include "..\zhelpers.hpp"

//状态定义
typedef enum _State_MsgPro
{
	MSG_PRO_STATE_OK = 0x000,//成功状态
	MSG_PRO_STATE_FAIL = 0X03E7,//失败状态
}State_MsgPro;

//消息是否需要回复定义
typedef enum _Type_MsgReply
{
	MSG_REPLY_STATE_NO = 0X000,//无需回复
	MSG_REPLY_STATE_YES = 0x001,//需要回复
	MSG_REPLY_STATE_RESPONSE = 0x002,//回复消息
}Type_MsgReply;

//消息使用者
typedef enum _USER_MsgComm
{
	MSG_COMM_USER_CLENT = 0x001,//客户端
	MSG_COMM_USER_SEVER = 0X002,//服务端
}USER_MsgComm;

//消息体类型定义
typedef enum _Type_MsgFit
{
	MSG_COMM_TYPE_JSON = 0x001,//JSON格式
	MSG_COMM_TYPE_HTTP = 0X002,//HTTP格式
}Type_MsgFit;

using namespace std;
using namespace Json;
class CMsgInteractPro
{
public:
	CMsgInteractPro();
	~CMsgInteractPro();

private:
    Value          m_sarchCdn;  //查询条件
	//string         m_strCdn;    //查询条件
	USER_MsgComm   m_user;      //消息使用端
	Type_MsgFit    m_type;      //消息体类型
public:
	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   设置使用者
	*-> @param1     pUser  使用者
	*-> #return     void 
	/*/
	void SetMsgUser(USER_MsgComm pUser); 

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   设置消息体类型
	*-> @param1     pType  类型
	*-> #return     void
	/*/
	void SetMsgType(Type_MsgFit pType);

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   获取组装结果（Json）
	*-> @param1    
	*-> #return     Value
	/*/
	Value GetJsonMsg();

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   获取组装结果（string）
	*-> @param1
	*-> #return     string
	/*/
	string GetStringMsg();

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   组装待发送消息的根消息体
	*-> @param1     msgCode  消息类型
	*-> @param2     serverIP 服务器地址
	*-> @param3     clientIP 客户端地址
	*-> #return     State_MsgPro 状态
	/*/

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   组装待发送消息的根消息体
	*-> @param1     msgCode  消息码
	*-> @param2     msgType  消息类型
	*-> @param3     serverIP 服务器地址
	*-> @param4     clientIP 客户端地址
	*-> #return     State_MsgPro 状态
	/*/
	State_MsgPro SetMsgRoot(int msgCode, Type_MsgReply msgType, string serverIP = "192.168.1.110", string clientIP = "192.168.1.100");

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   给消息体的“数据块”添加消息项 - 直接在data作用域
	*-> @param1     key 键值
	*-> @param2     sDataValue/nDataValue/fDataValue 值
	*-> #return     State_MsgPro 状态
	/*/
	State_MsgPro AddItemToMsgBody(const char* key, string sDataValue);
	State_MsgPro AddItemToMsgBody(const char* key, int nDataValue);
	State_MsgPro AddItemToMsgBody(const char* key, float fDataValue);

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   给消息体的“数据块”添加数组 - 
	*-> @param1     key 键值
	*-> #return     State_MsgPro 状态
	/*/
	State_MsgPro AddArrayToMsgBody(const char* key);

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   设置消息体的“状态块”
	*-> @param1     nCode 状态值
	*-> @param2     pMsg  状态描述
	*-> #return     State_MsgPro 状态
	/*/
	State_MsgPro SetMsgBodyState(int nCode, string pMsg);

public:
	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   strsing转char*码
	*-> @param1     gb2312 输入字符
	*-> #return     char*  输出字符
	/*/
	const char* StringToConstCharX(string str);

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   GB2312转utf_8码
	*-> @param1     gb2312 输入字符
	*-> #return     string  输出字符
	/*/
	string Gb2312ToUtf_8(const char* gb2312);

	/*////////////////////////////////接口说明////////////////////////////////*/
	/**
	*-> &function   GB2312转utf_8码
	*-> @param1     gb2312 输入字符
	*-> #return     string  输出字符
	/*/
	string Gb2312ToUtf_8_EX(string gb2312);
};

#endif // !_MSG_INTERACT_PRO_DEFINE_2018_05_03_CLENT_CTEATED_



