#pragma once

#ifndef _DEBUG
#pragma comment(lib, "../../lib/ARS.lib")
#pragma comment(lib, "../../lib/WML.lib")
#else
#pragma comment(lib, "../../lib/ARSd.lib")
#pragma comment(lib, "../../lib/WMLd.lib")
#endif

#define _CRT_SECURE_NO_WARNINGS

#include "../../include/ars.h"
#define CLASSNAME "ARSTEST"
#define APPNAME "ARSTEST"
