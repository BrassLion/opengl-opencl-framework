//
//  Viewport.cpp
//  OpenGLTest
//
//  Created by Samuel Hall on 29/07/2016.
//
//

#include "Viewport.hpp"

#include <GLFW/glfw3.h>

void Viewport::draw(std::shared_ptr<Object> root_node)
{
    glViewport(m_x, m_y, m_width, m_height);
    
    for(std::shared_ptr<Camera> camera : m_cameras) {
        
        root_node->draw(camera);
    }
}

void Viewport::add_camera(std::shared_ptr<Camera> camera)
{
    m_cameras.push_back(camera);
}
