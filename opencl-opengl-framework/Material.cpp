
//
//  Material.cpp
//  OpenGLTest
//
//  Created by Samuel Hall on 11/09/2016.
//
//

#include "Material.hpp"

void Material::set_mesh(std::shared_ptr<Mesh> mesh)
{
    m_mesh = mesh;
}

void Material::apply(std::shared_ptr<Object> object, std::shared_ptr<Camera> camera)
{
    m_shader->bind_shader();
    
    m_shader->set_uniform("mvpMatrix", camera->get_projection_matrix() * camera->get_view_matrix() * object->get_model_matrix());
    m_shader->set_uniform("model_matrix", object->get_model_matrix());
}
