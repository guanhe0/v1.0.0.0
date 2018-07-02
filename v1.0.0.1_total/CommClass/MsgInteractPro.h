#ifndef _MSG_INTERACT_PRO_DEFINE_2018_05_03_CLENT_CTEATED_
#define _MSG_INTERACT_PRO_DEFINE_2018_05_03_CLENT_CTEATED_

//EXPORT_WebOffLineMapWnd.h
/*********************************************************************************************
Copyright (C), ....-...., PINGAN Technology Co.,Ltd.
File name:	   EXPORT_WebOffLineMapWnd.h
Author:		   Mr JA.CUI R&D Department.
Version:	   V1.2.0.0
Date:		   2018-05-03
Description:   ��Ϣ������װ��
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

//״̬����
typedef enum _State_MsgPro
{
	MSG_PRO_STATE_OK = 0x000,//�ɹ�״̬
	MSG_PRO_STATE_FAIL = 0X03E7,//ʧ��״̬
}State_MsgPro;

//��Ϣ�Ƿ���Ҫ�ظ�����
typedef enum _Type_MsgReply
{
	MSG_REPLY_STATE_NO = 0X000,//����ظ�
	MSG_REPLY_STATE_YES = 0x001,//��Ҫ�ظ�
	MSG_REPLY_STATE_RESPONSE = 0x002,//�ظ���Ϣ
}Type_MsgReply;

//��Ϣʹ����
typedef enum _USER_MsgComm
{
	MSG_COMM_USER_CLENT = 0x001,//�ͻ���
	MSG_COMM_USER_SEVER = 0X002,//�����
}USER_MsgComm;

//��Ϣ�����Ͷ���
typedef enum _Type_MsgFit
{
	MSG_COMM_TYPE_JSON = 0x001,//JSON��ʽ
	MSG_COMM_TYPE_HTTP = 0X002,//HTTP��ʽ
}Type_MsgFit;

using namespace std;
using namespace Json;
class CMsgInteractPro
{
public:
	CMsgInteractPro();
	~CMsgInteractPro();

private:
    Value          m_sarchCdn;  //��ѯ����
	//string         m_strCdn;    //��ѯ����
	USER_MsgComm   m_user;      //��Ϣʹ�ö�
	Type_MsgFit    m_type;      //��Ϣ������
public:
	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ����ʹ����
	*-> @param1     pUser  ʹ����
	*-> #return     void 
	/*/
	void SetMsgUser(USER_MsgComm pUser); 

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ������Ϣ������
	*-> @param1     pType  ����
	*-> #return     void
	/*/
	void SetMsgType(Type_MsgFit pType);

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ��ȡ��װ�����Json��
	*-> @param1    
	*-> #return     Value
	/*/
	Value GetJsonMsg();

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ��ȡ��װ�����string��
	*-> @param1
	*-> #return     string
	/*/
	string GetStringMsg();

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ��װ��������Ϣ�ĸ���Ϣ��
	*-> @param1     msgCode  ��Ϣ����
	*-> @param2     serverIP ��������ַ
	*-> @param3     clientIP �ͻ��˵�ַ
	*-> #return     State_MsgPro ״̬
	/*/

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ��װ��������Ϣ�ĸ���Ϣ��
	*-> @param1     msgCode  ��Ϣ��
	*-> @param2     msgType  ��Ϣ����
	*-> @param3     serverIP ��������ַ
	*-> @param4     clientIP �ͻ��˵�ַ
	*-> #return     State_MsgPro ״̬
	/*/
	State_MsgPro SetMsgRoot(int msgCode, Type_MsgReply msgType, string serverIP = "192.168.1.110", string clientIP = "192.168.1.100");

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ����Ϣ��ġ����ݿ顱�����Ϣ�� - ֱ����data������
	*-> @param1     key ��ֵ
	*-> @param2     sDataValue/nDataValue/fDataValue ֵ
	*-> #return     State_MsgPro ״̬
	/*/
	State_MsgPro AddItemToMsgBody(const char* key, string sDataValue);
	State_MsgPro AddItemToMsgBody(const char* key, int nDataValue);
	State_MsgPro AddItemToMsgBody(const char* key, float fDataValue);

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ����Ϣ��ġ����ݿ顱������� - 
	*-> @param1     key ��ֵ
	*-> #return     State_MsgPro ״̬
	/*/
	State_MsgPro AddArrayToMsgBody(const char* key);

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   ������Ϣ��ġ�״̬�顱
	*-> @param1     nCode ״ֵ̬
	*-> @param2     pMsg  ״̬����
	*-> #return     State_MsgPro ״̬
	/*/
	State_MsgPro SetMsgBodyState(int nCode, string pMsg);

public:
	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   strsingתchar*��
	*-> @param1     gb2312 �����ַ�
	*-> #return     char*  ����ַ�
	/*/
	const char* StringToConstCharX(string str);

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   GB2312תutf_8��
	*-> @param1     gb2312 �����ַ�
	*-> #return     string  ����ַ�
	/*/
	string Gb2312ToUtf_8(const char* gb2312);

	/*////////////////////////////////�ӿ�˵��////////////////////////////////*/
	/**
	*-> &function   GB2312תutf_8��
	*-> @param1     gb2312 �����ַ�
	*-> #return     string  ����ַ�
	/*/
	string Gb2312ToUtf_8_EX(string gb2312);
};

#endif // !_MSG_INTERACT_PRO_DEFINE_2018_05_03_CLENT_CTEATED_



