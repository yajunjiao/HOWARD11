//
//  GLShader.cpp
//  MarXsCube
//
//  Created by SeconDatke on 1/28/15.
//  Copyright (c) 2015 MarXsCube Staff. All rights reserved.
//

#include "GLCommon.hxx"
#include "GLShader.hxx"
#include "GLShaderExt.hxx"

#include "thirdpt/howardgl.hxx"

#include <stdlib.h>
#include <string>

namespace Howard {
namespace Verdandi {

const std::size_t LENGTH_SHADER_READBUFFER = 8192;

namespace {
char _shader_readbuffer[LENGTH_SHADER_READBUFFER] { 0 };
}

// from http://blog.csdn.net/racehorse/article/details/6616256
std::string gl_shader::log(SHADERTYPE type) {
	VGLIDX obj = (type == SHADERTYPE::FRAG) ? this->frag_id : this->vert_id;
	int length = 0, chwritten = 0;
	char *log_buffer;
	std::string ret = "";

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &length);

	if (length > 0) {
		log_buffer = (char *) malloc(length);
		glGetShaderInfoLog(obj, length, &chwritten, log_buffer);
		ret = log_buffer;
		free(log_buffer);
	}

	return ret;
}

void gl_shader::load_file(SHADERTYPE type, const std::string& path) {
	FILE *fp = fopen(path.c_str(), "r");
	std::size_t len = fread(_shader_readbuffer, 1, LENGTH_SHADER_READBUFFER - 1, fp);
	_shader_readbuffer[len] = '\0';
	this->load_str(type, _shader_readbuffer);
	fclose(fp);
}

void gl_shader::load_str(SHADERTYPE type, const char *src) {
	VGLIDX *target = (type == SHADERTYPE::FRAG) ? &this->frag_id : &this->vert_id;
	auto shader_tp = (type == SHADERTYPE::FRAG) ? GL_FRAGMENT_SHADER : GL_VERTEX_SHADER;

	*target = glCreateShader(shader_tp);
	const char *t[1] { src };
	glShaderSource(*target, 1, t, nullptr);
	glCompileShader(*target);
}

void gl_shader::load_str(SHADERTYPE type, const std::string& src) {
	this->load_str(type, src.c_str());
}

void gl_shader::create() {
	this->obj_id = glCreateProgram();

	glAttachShader(this->obj_id, this->vert_id);
	glAttachShader(this->obj_id, this->frag_id);
	glLinkProgram(this->obj_id);

	glDeleteShader(this->vert_id);
	glDeleteShader(this->frag_id);
}

void gl_shader::use() {
	glUseProgram(this->obj_id); }

void gl_shader::destroy() {
	glUseProgram(0);
	glDeleteProgram(this->obj_id);
	this->obj_id = this->vert_id = this->frag_id = -1;
}

int gl_shader::attribute(const char *name) {
	return glGetAttribLocation(this->obj_id, name); }

int gl_shader::uniform(const char *name) {
	return glGetUniformLocation(this->obj_id, name); }

void gl_shader_ext::postInitialize() {
    glUseProgram(id());
//    glDrawArrays(GL_TRIANGLES, 0, 6);
//    glGetError();
    glUseProgram(0);
}

}
}
