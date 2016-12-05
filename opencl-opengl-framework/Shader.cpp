//
//  Shader.cpp
//  OpenGLTest
//
//  Created by Samuel Hall on 23/07/2016.
//
//

#include "Shader.hpp"

#include <stdlib.h>
#include <stdexcept>
#include <assert.h>

#include <glm/gtc/type_ptr.hpp>

#include "Utility.hpp"

bool check_shader_error(GLuint shader)
{
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Shader compilation error:\n") + infoLog);
        
        return false;
    }
    
    return true;
}

bool check_program_error(GLuint program)
{
    GLint success;
    GLchar info_log[512];
    
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, info_log);
        throw std::runtime_error(std::string("Program link error:\n") + info_log);
        
        return false;
    }
    
    return true;
}

GLuint compile_shader(std::string shader_src, GLuint shader_type)
{
    GLuint shader = glCreateShader(shader_type);
    
    const char *shader_source = shader_src.c_str();
    
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);
    
    check_shader_error(shader);
    
    return shader;
}

/// Public functions.
void Shader::set_shader(std::string shader_path, GLuint shader_type)
{
    std::string shader_src = utility::load_file(shader_path);
    
    this->set_shader_src(shader_src, shader_type);
}

void Shader::set_shader_src(std::string shader_src, GLuint shader_type)
{
    ShaderFile shader_file;

    shader_file.src = shader_src;
    shader_file.type = shader_type;
    
    m_shader_files.push_back(shader_file);
}

bool Shader::initialize()
{
    // Build and compile shaders.
    std::vector<GLuint> shaders;
    
    for (ShaderFile shader_file : m_shader_files)
        shaders.push_back(compile_shader(shader_file.src, shader_file.type));
    
    // Build program.
    m_program_id = glCreateProgram();
    
    for (GLuint shader : shaders)
        glAttachShader(m_program_id, shader);
    
    glLinkProgram(m_program_id);
    
    // Check for linking errors.
    check_program_error(m_program_id);
    
    // Delete shaders.
    for (GLuint shader: shaders)
        glDeleteShader(shader);
    
    return true;
}

void Shader::delete_shader()
{
    glDeleteShader(m_program_id);
}

void Shader::bind_shader()
{
    glUseProgram(m_program_id);
}

GLint Shader::get_uniform_location(std::string uniform)
{
    GLint uniform_location = glGetUniformLocation(m_program_id, uniform.c_str());
    
//    if(uniform_location == -1)
//        throw std::invalid_argument( "Uniform \"" + uniform + "\" does not exist." );
    
    return uniform_location;
}

void Shader::set_uniform(std::string uniform, glm::mat4 value)
{
    GLint uniformLocation = get_uniform_location(uniform);
    
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_uniform(std::string uniform, glm::vec3 value)
{
    GLint uniformLocation = get_uniform_location(uniform);
    
    glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
}

void Shader::set_uniform(std::string uniform, glm::vec4 value)
{
    GLint uniformLocation = get_uniform_location(uniform);
    
    glUniform4fv(uniformLocation, 1, glm::value_ptr(value));
}

void Shader::set_uniform(std::string uniform, unsigned int value)
{
    GLint uniformLocation = get_uniform_location(uniform);
    
    glUniform1i(uniformLocation, value);
}

