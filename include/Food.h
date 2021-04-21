#pragma once
#include "Block.h"

struct Food : public Block
{
    Food();
    // random vi tri cua food
    void spawn();
};