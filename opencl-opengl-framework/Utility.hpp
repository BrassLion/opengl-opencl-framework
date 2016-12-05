//
//  Utility.hpp
//  OpenGLTest
//
//  Created by Samuel Hall on 10/08/2016.
//
//

#ifndef Utility_hpp
#define Utility_hpp

#include "Mesh.hpp"

#include <OpenCL/OpenCL.h>

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <fstream>
#include <sstream>

#ifdef DEBUG
#define CL_CHECK(error) \
utility::check_opencl_error(error, __FILE__, __LINE__);
#else
#define CL_CHECK(error)
#endif

namespace utility
{
    std::ifstream get_file_stream(std::string file_path);
    std::string load_file(std::string file_path);
    
    template<typename T>
    std::vector<T> load_file_to_values(std::string file_path)
    {
        std::ifstream ifs = get_file_stream(file_path);
        std::vector<T> result;
        
        std::string file_line;
        
        while ( std::getline(ifs, file_line, ',') ) {
            
            std::istringstream is(file_line);
            
            T value;
            
            if ( is >> value )
                result.push_back(value);
        }
        
        return result;
    }
    
    class profiler
    {
    private:
        std::chrono::high_resolution_clock m_clock;
        std::chrono::high_resolution_clock::time_point m_start;
        std::chrono::high_resolution_clock::time_point m_split;
        
    public:
        void start();
        void split();
        void stop();
    };
    
    class DebugAxis : public Mesh
    {
    private:
        std::vector<GLfloat> m_vertices = {
            // x axis.
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            // y axis.
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            // z axis.
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
        };
        
        std::string m_vert_shader = "#version 330 core \
         \
        layout (location = 0) in vec3 position; \
        layout (location = 1) in vec3 color; \
         \
        uniform mat4 mvpMatrix; \
        uniform mat4 model_matrix; \
         \
        out vec3 frag_color; \
         \
        void main() \
        { \
            frag_color = color; \
         \
            gl_PointSize = 20.0; \
            gl_Position = mvpMatrix * vec4(position, 1.0); \
        }";

        std::string m_frag_shader = "#version 330 core \
         \
        in vec3 frag_color; \
         \
        out vec4 color; \
         \
        void main() \
        { \
            color = vec4(frag_color, 1.0); \
        }";
        
        std::shared_ptr<Shader> m_shader;
        std::shared_ptr<Material> m_material;
        
    public:
        void initialize() {
            
            this->Mesh::initialize(m_vertices, std::vector<unsigned int>({ 3, 3 }));
            
            m_shader = std::make_shared<Shader>();
            
            m_shader->set_shader_src(m_vert_shader, GL_VERTEX_SHADER);
            m_shader->set_shader_src(m_frag_shader, GL_FRAGMENT_SHADER);
            m_shader->initialize();
            
            m_material = std::make_shared<Material>(m_shader);
            
            this->set_rendering_mode(GL_LINES);
            
            this->set_material(m_material);
        }
    };
    
    const char *get_opencl_error_string(cl_int error);
    void check_opencl_error(cl_int error, const char* fname, int line);
}

#endif /* Utility_hpp */
