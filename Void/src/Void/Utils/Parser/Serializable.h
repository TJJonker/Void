#pragma once
#include "MetaData.h"

namespace Void {
	class Serializable
	{
	protected:
		std::vector<MetaData> m_MetaData;

	protected:
		virtual void AddMetaData(MetaData metaData);

	public:
		std::vector<MetaData> GetMetaData() const { return m_MetaData; }
	};
}
