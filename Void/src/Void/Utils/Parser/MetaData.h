#pragma once
#include <string>

namespace Void {
	struct MetaData {
		std::string Name;
		enum class DataType { STRING, INT, FLOAT, VEC3 } Type;
		void* Field;
	};
}