#pragma once
#include "Quantum/Common.h"
#include "Quantum/DataStructs/AABB.h"
#include <Quantum/Objects/ICollider.h>

namespace Quantum {
    constexpr uint8_t MaxSubnodes = 8;
    constexpr uint8_t TempMaxObjectsPerNode = 255;

    struct OctreeNode {
        AABB BoundingBox;
        uint8_t AmountOfObjects;
        ICollider* Objects[TempMaxObjectsPerNode];
        uint8_t SubNodes[MaxSubnodes] = {0};

        OctreeNode() {
            for (int i = 0; i < MaxSubnodes; ++i) {
                SubNodes[i] = 0;
            }
        }
    };
}