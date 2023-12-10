#pragma once
#include "Quantum/Common.h"
#include "Quantum/DataStructs/AABB.h"
#include <Quantum/Objects/ICollider.h>

namespace Quantum {
    struct OctreeNode {
        AABB BoundingBox;
        std::vector<ICollider*> Objects;
        OctreeNode SubNodes[8] = {0};

        OctreeNode(const AABB& box) : BoundingBox(box) {
            for (int i = 0; i < 8; ++i) {
                SubNodes[i] = nullptr;
            }
        }
    };
}