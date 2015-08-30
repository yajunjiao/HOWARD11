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

#include "Stannum.hxx"
#include "StannumSprite.hxx"
#include "StannumSpriteShader.hxx"

#include "Verdandi/GLVertexBufferExt.hxx"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Debug.hxx"

#include "Misc/AtTheVeryBeginning.hxx"

namespace Howard {
namespace Stannum {

MappedVertexBuffer<VertFormatSprite> *CommandSprite::m_buf = nullptr;

template<typename T>
MappedVertexBuffer<T> *SharedVertexBuffer::map(size_t count) {
    size_t sz_rounded = this->mapped_end;
    for (size_t i = 0; i < sizeof(T); i++) {
        if (sz_rounded % sizeof(T) == 0) { break; }
        sz_rounded++;
    }
    if (count * sizeof(T) + sz_rounded <= this->m_size) {
        MappedVertexBuffer<T> *ret = new MappedVertexBuffer<T>(this, count, sz_rounded);
        this->mapped_end = sz_rounded + count * sizeof(T);
        this->m_mappings.push_back(ret);
        return ret;
    }
    return nullptr;
}

void StannumRenderer::init() {
    this->m_shader_cache.load_shaders();
    this->m_shared_vb.init(2048 * sizeof(glm::vec3) * 3);

    CommandSprite::m_buf = this->m_shared_vb.map<VertFormatSprite>(128);
}

void StannumRenderer::destroy() {
    this->m_shader_cache.destroy_shaders();
}

void CommandSprite::execute(StannumRenderer *renderer) {
    renderer->m_sprites.push_back(this->m_data);
}

void DispatchCommandSprite::execute(StannumRenderer *renderer) {
    using namespace AtTheVeryBeginning;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    auto *shader = renderer->shaders()->get_shader<SpriteShader>
            (ShaderType::CommonSprite);
    shader->use();
    CommandSprite::m_buf->bind();

    glm::mat4 projection = glm::ortho(0.f, (float) Setting<WindowSetting>::instance()->actual_width,
            (float) Setting<WindowSetting>::instance()->actual_height, 0.f, -16384.f, 16384.f);
    SET_UNIFORMAT4(*shader, mvp, projection);

    auto scope = Verdandi::VertexAttributeArrayScope<4>({ 0, 1, 2, 3 });
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertFormatSprite),
            (void *) CommandSprite::m_buf->m_start);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertFormatSprite),
            (void *) (CommandSprite::m_buf->m_start + sizeof(glm::vec3)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertFormatSprite),
            (void *) (CommandSprite::m_buf->m_start + 2 * sizeof(glm::vec3)));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(VertFormatSprite),
            (void *) (CommandSprite::m_buf->m_start + 2 * sizeof(glm::vec3) +
                      sizeof(glm::vec2)));

    size_t idx = 0;
    for (auto data : renderer->m_sprites) {
        for (size_t i = 0; i < 6; i++) {
            idx = CommandSprite::m_buf->push(&data->data[i]); }
    }

    CommandSprite::m_buf->upload();
    idx = 0;
    for (auto data : renderer->m_sprites) {
        BIND_TEXTUREP(shader, texture_major, data->texture->id(), 0);
        glDrawArrays(GL_TRIANGLES, idx, 6);
        idx += 6;
    }

    CommandSprite::m_buf->clear();
    renderer->m_sprites.clear();
}

}
}
