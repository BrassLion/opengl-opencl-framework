//
//  Camera.cpp
//  OpenGLTest
//
//  Created by Samuel Hall on 24/07/2016.
//
//

#include <iostream>

#include "Camera.hpp"

glm::mat4 Camera::get_projection_matrix()
{
    return m_projection;
}

glm::mat4 Camera::get_view_matrix()
{
    return m_view;
}

void Camera::update_model_matrix()
{
    Object::update_model_matrix();
    
    m_view = glm::inverse(m_model_matrix);
}
