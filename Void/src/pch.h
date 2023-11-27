#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>

#include <functional>

#ifdef VOID_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include "Void/Utils/TimeSteps/Time.h"

#include "Void/Debug/Log.h"
#include "Void/Core/Core.h"
#include "Void/Debug/Assertion.h"

#include "Void/Utils/ExternalFiles/File/File.h"

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>
