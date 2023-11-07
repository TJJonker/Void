#pragma once
#include "MetaData.h"

namespace Void {
	class Serializable
	{
	protected:
		std::string m_MetaTitle;
		std::vector<MetaData> m_MetaData;

	protected:
		void AddMetaTitle(std::string title);
		void AddMetaData(MetaData metaData);

	public:
		std::vector<MetaData> GetMetaData() const { return m_MetaData; }
		std::string GetMetaTitle() const { return m_MetaTitle; }
	};
}
