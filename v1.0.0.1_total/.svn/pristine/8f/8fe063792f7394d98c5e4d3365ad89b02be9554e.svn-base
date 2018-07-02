#include "stdafx.h"
#include "pic_search.h"
bool recv_and_process_pic_data_update(zmq_msg_t &msg_recv, void **psocket, Json::Value &value, Json::Value &msgBody, Json::Value &dataRequest, Json::Reader &reader, void *param)
{
	if (psocket == NULL || (*psocket) == NULL) {
		return false;
	}
	int len = 0;
	zmq_msg_init(&msg_recv);
	zmq_msg_recv(&msg_recv, search_sk, 0);
	len = zmq_msg_recv(&msg_recv, search_sk, 0);
	value.clear();
	msgBody.clear();
	dataRequest.clear();

#ifdef SEARCH_VALUE_PRINT
	printf("[%s] [%s] [%d] data upate recv msg ==== %s\n", __TIME__, __FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
	fprintf(flog, "[%s] [%s] [%d] data upate recv msg ==== %s\n", __TIME__, __FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
	fflush(flog);
#endif
	if (len&&reader.parse((char *)zmq_msg_data(&msg_recv), value)) {

	}
	zmq_msg_close(&msg_recv);
}
bool send_msg2_data_update(char *val)
{
	if (val == NULL)
		return false;
	int len = 0;
	zmq_msg_t msg;
	zmq_msg_init_size(&msg, 0);
	memcpy(zmq_msg_data(&msg), "", 0);
	len = zmq_msg_send(&msg, pic_data_update_sk, ZMQ_SNDMORE);

	zmq_msg_init_size(&msg, strlen(val));
	memcpy(zmq_msg_data(&msg), val, strlen(val));
	len = zmq_msg_send(&msg, pic_data_update_sk, 0);
	zmq_msg_close(&msg);
	if (len) {
		return true;
	}
	else {
		return false;
	}
}
bool pic_search_sava_pic_search_result(Json::Value &value)
{
	int requestid = 0;
	requestid = value["msgHead"]["requestID"].asInt();
	WaitForSingleObject(g_picsearch_muxtex, INFINITE);
	g_pic_search_data.insert(make_pair(requestid, value));
	ReleaseMutex(g_picsearch_muxtex);
	return true;
}
DWORD WINAPI pic_search_worker(void * context)
{
	zmq::context_t * ct = (zmq::context_t *)context;

	zmq_pollitem_t items[] = { { search_sk,0,ZMQ_POLLIN,0 },{ pic_data_update_sk ,0,ZMQ_POLLIN,0} };
	zmq_msg_t msg_recv;
	int len = 0, nJsonMsgCode = 0, ret = 0, resReallyCount = 0;
	Json::Reader reader;
	Json::Value value, character, dataRequest, msgBody, dataPush;
	MSG msg;
	DealerModeSendRecv dealer(context, search_sk);
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

#if 0
	Json::Reader reader_test;
	std::ifstream in_w;
	Json::Value value_read;
	in_w.open("pic_search_req.json", std::ios::binary);
	
	if (!in_w.is_open()) {
		return -1;
	}
	if (reader_test.parse(in_w, value_read)) {
		in_w.close();
		in_w.open("charater.json", std::ios::binary);
		if (!in_w.is_open()) {
			return -1;
		}
		if (reader.parse(in_w, character)) {
			printf("[%s] [%s] [%d] character ==== %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)character.toStyledString().data());
			value_read["msgBody"]["dataPush"]["character"] = character["charater"];
		}
		
	}
	//printf("[%s] [%s] [%d] send msg to search ==== %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)(char *)value_read.asString().c_str());
	//fprintf(flog_search, "[%s] [%s] [%d] send msg to search ==== %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)(char *)value_read.asString().c_str());
	//fflush(flog);
	dealer.SendDealerMsg((char *)value_read.toStyledString().data());
//	dealer.SendDealerMsg((char *)value_read.asString().c_str());
#endif 
	while (true) {
		while (true)
		{
			zmq_poll(items, 1, zmq_poll_timeout);
			if (items[0].revents & ZMQ_POLLIN) {
				zmq_msg_init(&msg_recv);
				zmq_msg_recv(&msg_recv, search_sk, 0);
				len = zmq_msg_recv(&msg_recv, search_sk, 0);
#ifdef PIC_WITH_PIC_PRINT
			printf("[%s] [%s] [%d] search recv msg ==== %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
			fprintf(flog_search, "g_face_search_index ==== %d [%s] [%s] [%s] [%d] search recv msg ==== %s\n",(g_face_search_index++), get_system_misecond_time(), get_system_misecond_time(),__FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
			fflush(flog);
#endif
			value.clear();
			msgBody.clear();
			dataRequest.clear();


			if (len&&reader.parse((char *)zmq_msg_data(&msg_recv), value)) {
				nJsonMsgCode = value["msgHead"]["msgCode"].asInt();
				switch (nJsonMsgCode)
				{
				case JSONMSGCODE_CLIENT_GET_USING_IMG_CHECKIN_IMG_BACK://search return pic with pic result
					pic_search_sava_pic_search_result(value);
#ifdef PIC_WITH_PIC_PRINT					
					fprintf(flog_search, "g_face_search_index === %d [%s] [%d] receiv search al search result msg ==== %s\n", (g_face_search_index++),__FUNCTION__, __LINE__, (char *)value.toStyledString().data());
					fflush(flog_search);
#endif 
				value["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_GET_USING_IMG_CHECKIN_IMG;
				dataRequest["code"] = 0;
				dataRequest["msg"] = "";
				value["msgBody"]["dataRequest"] = dataRequest;

				dataPush = value["msgBody"]["dataSend"];
				value["msgBody"]["dataPush"] = dataPush;
				resReallyCount = value["msgBody"]["dataSend"]["resReallyCount"].asInt();

				value["msgBody"].removeMember("dataSend");
				
				if (resReallyCount > 0) {
					trans_msg2_another_thread(PIC_SEARCH_RESULT2_JAVA, &value, lpJavaThreadId,&g_common_str_search,NULL);
				}
				else {
					value["msgHead"]["msgCode"] = JSONMSGCODE_CLIENT_GET_USING_IMG_CHECKIN_IMG_BACK;					
					trans_msg2_another_thread(PIC_SEARCH_SEARCH_PIC_FAILED, &value, lpClientThreadId,&g_common_str_search,NULL);
				}
					break;
				default:
					printf("[%s] [%s] [%d] unkown type msg ==== %s\n", __TIME__,__FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
					fprintf(flog_search, "g_face_search_index === %d [%s] [%s] [%d] unkown type msg ==== %s\n", (g_face_search_index++),__TIME__,__FUNCTION__, __LINE__, (char *)zmq_msg_data(&msg_recv));
					//fflush(flog);
					break;
				}
				fflush(flog);
			}
			zmq_msg_close(&msg_recv);
		}
		if (items[1].revents & ZMQ_POLLIN) {//pic_data_update_sk

			recv_and_process_pic_data_update(msg_recv,&pic_data_update_sk,value,msgBody,dataRequest,reader,NULL);
		}

		if (PeekMessage(&msg, 0, 0, 0, NULL))
		{
			memset(&msg, 0, sizeof(msg));
			ret = GetMessage(&msg, NULL, 0, 0);
			if (ret == -1) {
				fprintf(flog_search, "g_face_search_index === %d [%s] [%s] [%d]  GetMessage failed error ==== %d \n",(g_face_search_index++), __TIME__,__FUNCTION__, __LINE__, GetLastError());
				//fflush(flog);
				continue;
			}
			char * pInfo = (char *)msg.wParam;
			char *lParam = (char *)msg.lParam;
#ifdef PIC_WITH_PIC_PRINT					
			fprintf(flog_search, "g_face_search_index === %d [%s] [%s] [%d] search worker  msg queue recv msg ==== %s\n", (g_face_search_index++), get_system_misecond_time(),__FUNCTION__, __LINE__, pInfo);
			fflush(flog);
#endif
			value.clear();

			if (msg.message <= WM_USER) {
				continue;
			}

			if (!parse_queuemsg2_json(pInfo, reader, value, msg, NULL))//parse pInfo2 Json fail
			{
			//	continue;
			}
			else
			{
#ifdef SEARCH_VALUE_PRINT			
			//	if (msg.message > WM_USER) {
					fprintf(flog_search, "g_face_search_index === %d broadcast worker queue msg============== %s", (g_face_search_index++),pInfo);
					fflush(flog);
			//	}
#endif
			}
			switch (msg.message)
			{	
			case FACETELL_RETURN_PIC_SEARCH_RESULT://search pic with pic
#ifdef PIC_WITH_PIC_PRINT					
				fprintf(flog_search, "g_face_search_index === %d [%s] [%s] [%d] send face tell result msg to search al ==== %s\n",(g_face_search_index++), get_system_misecond_time(), __FUNCTION__, __LINE__, pInfo);
				fflush(flog_search);
#endif
				dealer.SendDealerMsg((char *)msg.wParam);
				break;
			case FACETELL_RESULT2_DATA_UPATE:
#ifdef SEARCH_VALUE_PRINT					
				fprintf(flog, "[%s] [%s] [%d] send face tell result msg to data update al ==== %s\n", __TIME__, __FUNCTION__, __LINE__, pInfo);
				fflush(flog);
#endif
				if (!send_msg2_data_update((char *)msg.wParam))
				{
#ifdef SEARCH_VALUE_PRINT					
					fprintf(flog, "[%s] [%s] [%d] send_msg2_data_update fail ==== \n", __TIME__, __FUNCTION__, __LINE__);
					fflush(flog);
#endif
				}
				break;
			default:
#ifdef PIC_WITH_PIC_PRINT					
				fprintf(flog_search, "g_face_search_index === %d [%s] [%s] [%d] receiv unknown msg type ==== %s\n", (g_face_search_index++), get_system_misecond_time(),__FUNCTION__, __LINE__, pInfo);
				//fflush(flog);
#endif
				break;
			}
			fflush(flog);

			switch (msg.message)//free case
			{
			case FACETELL_RETURN_PIC_SEARCH_RESULT:
			case FACETELL_RESULT2_DATA_UPATE:
				wparam_free(&pInfo);

				break;
			default:
				break;
			}
		}
		}//1th while
		fprintf(flog_search, "[%s] [%s] [%d] search worker end timepoint \n", __TIME__,__FUNCTION__, __LINE__);
		fflush(flog);
	}
		return 0;
}
