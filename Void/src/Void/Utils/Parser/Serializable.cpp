#include "pch.h"
#include "Serializable.h"

namespace Void {
	void Serializable::AddMetaData(MetaData metaData)
	{
		m_MetaData.push_back(metaData);
	}
}