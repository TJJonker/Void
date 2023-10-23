#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <functional>

#ifdef VOID_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include "Void/Debug/Log.h"
#include "Void/Core/Core.h"
#include "Void/Debug/Assertion.h"

#include <glm/glm.hpp>