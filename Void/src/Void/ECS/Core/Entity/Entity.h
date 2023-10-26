#pragma once

typedef unsigned long long EntityID;
typedef unsigned int EntityIndex;
typedef unsigned int EntityVersion;

inline EntityID CreateEntityId(EntityIndex index, EntityVersion version) {
	EntityID id = static_cast<EntityID>(index) << 32;
	id |= static_cast<EntityID>(version);
	return id;
}

inline EntityVersion GetEntityVersion(EntityID id) {
	return static_cast<EntityVersion>(id);
}

inline EntityIndex GetEntityIndex(EntityID id) {
	return id >> 32;
}