//
// Made by secondwtq <lovejay-lovemusic@outlook.com> with Love.
//
// Date: 2015-05-24
// Copyright (c) 2015 SCU ISDC All rights reserved.
//
// This file is part of the HOWARD11 Game Engine.
//
// WE ARE STANDING ON THE EDGE.
//

#include "GLFoundation.hxx"

#include "GLCommon.hxx"
#include "thirdpt/howardgl.hxx"

#include "Misc/AtTheVeryBeginning.hxx"

namespace Howard {
namespace Verdandi {

void resetRenderTarget() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 1600, 1200);
//    glViewport(0, 0,
//            AtTheVeryBeginning::Setting<AtTheVeryBeginning::WindowSetting>::instance()->actual_width,
//            AtTheVeryBeginning::Setting<AtTheVeryBeginning::WindowSetting>::instance()
//                       ->actual_height);
}

void init_target() {
    return resetRenderTarget(); }

void gl_init() {
    glClearDepth(1.f);
    init_target();
}

void clear_depth() {
    glClear(GL_DEPTH_BUFFER_BIT);
    return glClearDepth(1.0f);
}

}
}
