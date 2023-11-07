#include "pch.h"
#include "Serializable.h"

namespace Void {
	void Serializable::AddMetaTitle(std::string title)
	{
		m_MetaTitle = title;
	}

	void Serializable::AddMetaData(MetaData metaData)
	{
		m_MetaData.push_back(metaData);
	}
}