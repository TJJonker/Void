#include "pch.h"
#include "JSONParser.h"
#include "nlohmann/json.hpp"

namespace Void {
    std::string JSONParser::Serialize(const Serializable& data)
    {
        nlohmann::json jsonData;
        for (const MetaData& metaData : data.GetMetaData()) {
            switch (metaData.Type) {
                case MetaData::DataType::INT: jsonData[metaData.Name] = *static_cast<int*>(metaData.Field); break;
                case MetaData::DataType::FLOAT: jsonData[metaData.Name] = *static_cast<float*>(metaData.Field); break;
                case MetaData::DataType::STRING: jsonData[metaData.Name] = *static_cast<std::string*>(metaData.Field); break;
                case MetaData::DataType::VEC3:
                    glm::vec3 data = *static_cast<glm::vec3*>(metaData.Field);
                    jsonData[metaData.Name]["X"] = data.x; 
                    jsonData[metaData.Name]["Y"] = data.y; 
                    jsonData[metaData.Name]["Z"] = data.z; 
                    break;
            }
        }
        return jsonData.dump();
    }

    std::string JSONParser::Serialize(const std::vector<Serializable>& dataList)
    {
        nlohmann::json result;

        for (const Serializable data : dataList) {
            nlohmann::json jsonData;
            for (const MetaData& metaData : data.GetMetaData()) {
                switch (metaData.Type) {
                case MetaData::DataType::INT: jsonData[metaData.Name] = *static_cast<int*>(metaData.Field); break;
                case MetaData::DataType::FLOAT: jsonData[metaData.Name] = *static_cast<float*>(metaData.Field); break;
                case MetaData::DataType::STRING: jsonData[metaData.Name] = *static_cast<std::string*>(metaData.Field); break;
                case MetaData::DataType::VEC3:
                    glm::vec3 data = *static_cast<glm::vec3*>(metaData.Field);
                    jsonData[metaData.Name]["X"] = data.x;
                    jsonData[metaData.Name]["Y"] = data.y;
                    jsonData[metaData.Name]["Z"] = data.z;
                    break;
                }
            }
            nlohmann::json jsonArray;
            jsonArray[data.GetMetaTitle()] = jsonData;
            result.push_back(jsonArray);
        }

        return result.dump();
    }

    bool JSONParser::Deserialize(const char* data)
    {
        return false;
    }
}