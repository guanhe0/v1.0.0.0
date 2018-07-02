#pragma once
#include <winsock2.h>
#include <windows.h>
#include "json\json.h"
#include <json\config.h>

bool shape_rep2req(Json::Value *val);
DWORD  WINAPI shape_worker(void * context);
