//
// Created by nicomane on 03/06/22.
//

#include "Constants.h"

namespace Engine{
    uint32_t Constants::IMAGE_COUNT = 2;
    uint32_t Constants::swapWidth   = 480;
    uint32_t Constants::swapHeight  = 560;

    void Constants::setImageCount(uint32_t count) {
        IMAGE_COUNT = count;
    }
   // Constants::initialBackgroundColor  = {0.0f, 0.0f, 0.0f, 1.0f};
}