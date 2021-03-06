//
// Made by secondwtq <lovejay-lovemusic@outlook.com> with Love.
//
// Date: 2015-08-23
// Copyright (c) 2015 SCU ISDC All rights reserved.
//
// This file is part of the HOWARD11 Game Engine.
//
// WE ARE STANDING ON THE EDGE.
//

#ifndef HOWARD11_HAMMERTRANSFORM_HXX
#define HOWARD11_HAMMERTRANSFORM_HXX

#include "../Common.hxx"

namespace Howard {
namespace Hammer {

struct Transform {

    Transform() :
            position(.0, .0, .0), rotation() { }
    Transform(const HAnyCoord& p, const HQuaternion& r)
            : position(p), rotation(r) { }
    Transform(const HAnyCoord& p)
            : position(p), rotation() { }
    Transform(const HQuaternion& r)
            : position(), rotation(r) { }

    static inline Transform createDefault() {
        return { }; }
    static inline Transform create
            (const HAnyCoord& position, const HQuaternion& rotation) {
        return { position, rotation }; }
    static inline Transform createPositioned
            (const HAnyCoord& position) {
        return { position }; }
    static inline Transform createRotated
            (const HQuaternion& rotation) {
        return { rotation }; }

    HAnyCoord position;
    HQuaternion rotation;

    static inline HQuaternion createEuler(const HAnyCoord& src) {
        return HQuaternion(src); }
};

}
}

#endif // HOWARD11_HAMMERTRANSFORM_HXX
