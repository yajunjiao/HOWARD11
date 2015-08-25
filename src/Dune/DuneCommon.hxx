//
// Created by secondwtq <lovejay-lovemusic@outlook.com> 2015/08/25.
// Copyright (c) 2015 SCU ISDC All rights reserved.
//
// This file is part of ISDCNext.
//
// We have always treaded the borderland.
//

#ifndef HOWARD11_DUNECOMMON_HXX
#define HOWARD11_DUNECOMMON_HXX

#include <glm/glm.hpp>

namespace Howard {
namespace Dune {

struct VertFormatDuneTerrain {

    VertFormatDuneTerrain() :
            VertFormatDuneTerrain(glm::vec2()) { }
    VertFormatDuneTerrain(const glm::vec2& p)
            : position(p) { }

    glm::vec2 position;
};

struct VertFormatDuneCache {

};

}
}

#endif // HOWARD11_DUNECOMMON_HXX