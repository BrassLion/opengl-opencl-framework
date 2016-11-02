//
//  Object.cpp
//  OpenGLTest
//
//  Created by Samuel Hall on 24/07/2016.
//
//

#include "Object.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

void Object::set_position(glm::vec3 new_position)
{
    m_position = new_position;
    
    update_model_matrix();
}

glm::vec3 Object::get_position()
{
    return m_position;
}

void Object::set_orientation(glm::quat new_orientation)
{
    m_orientation = new_orientation;
        
    update_model_matrix();
}

glm::quat Object::get_orientation()
{
    return m_orientation;
}

void Object::set_scale(glm::vec3 new_scale)
{
    m_scale = new_scale;
    
    update_model_matrix();
}

glm::mat4 Object::get_model_matrix()
{
    return m_model_matrix;
}

void Object::update_model_matrix()
{
    m_model_matrix = glm::mat4(1.0f);
    
    m_model_matrix = glm::translate(m_model_matrix, m_position);
    m_model_matrix = m_model_matrix * glm::mat4_cast(m_orientation);
    m_model_matrix = glm::scale(m_model_matrix, m_scale);
    
    if (!m_parent.expired())
    {
        m_model_matrix = m_parent.lock()->get_model_matrix() * m_model_matrix;
    }
    
    for (std::shared_ptr<Object> child : m_children)
        child->update_model_matrix();
}

void Object::set_parent(std::shared_ptr<Object> parent)
{
    m_parent = parent;
}

void Object::add_child(std::shared_ptr<Object> child)
{
    m_children.push_back(child);
    
    child->set_parent(shared_from_this());
    
    child->update_model_matrix();
}

void Object::draw(std::shared_ptr<Camera> camera)
{
    for(std::shared_ptr<Object> child : m_children)
        child->draw(camera);
}
