#pragma once
#include "json\json.h"
#include <json\config.h>
//#include "zmq.h"
//#include "zmq_utils.h"
#include "zmq.hpp"
//#include "zhelper.h"
#include "server_config.h"
#include <windows.h>
DWORD  WINAPI rtsp_worker(void * context);
