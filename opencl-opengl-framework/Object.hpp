//
//  Object.hpp
//  OpenGLTest
//
//  Created by Samuel Hall on 24/07/2016.
//
//

#ifndef Object_hpp
#define Object_hpp

#include <vector>

#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera;

class Object : public std::enable_shared_from_this<Object>
{
protected:
    
    glm::vec3 m_position;
    glm::quat m_orientation;
    glm::vec3 m_scale = glm::vec3(1.0f);;
    
    glm::mat4 m_model_matrix;
    
    std::weak_ptr<Object> m_parent;
    std::vector<std::shared_ptr<Object>> m_children;
    
    virtual void update_model_matrix();
    
public:
    
    void set_position(glm::vec3 new_position);
    glm::vec3 get_position();
    
    void set_orientation(glm::quat new_orientation);
    glm::quat get_orientation();
    
    void set_scale(glm::vec3 new_scale);
    
    glm::mat4 get_model_matrix();
    
    void add_child(std::shared_ptr<Object> child);
    
    void set_parent(std::shared_ptr<Object> parent);
    
    virtual void draw(std::shared_ptr<Camera> camera);
};

#endif /* Object_hpp */
