//
//  Shader.hpp
//  OpenGLTest
//
//  Created by Samuel Hall on 23/07/2016.
//
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

class Shader
{
private:
    
    GLuint m_program_id;
    
    struct ShaderFile {
        std::string path;
        GLenum type;
    };

    std::vector<ShaderFile> m_shader_files;
    
    GLint get_uniform_location(std::string uniform);
    
public:
    
    ~Shader() {
        delete_shader();
    }
    
    bool initialize();
    void delete_shader();
    void set_shader(std::string shader_path,  GLuint shader_type);
    void bind_shader();
    
    void set_uniform(std::string uniform, glm::mat4 value);
    void set_uniform(std::string uniform, glm::vec3 value);
    void set_uniform(std::string uniform, glm::vec4 value);
    void set_uniform(std::string uniform, unsigned int value);
};

#endif /* Shader_hpp */
