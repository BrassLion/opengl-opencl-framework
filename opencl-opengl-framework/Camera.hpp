//
//  Camera.hpp
//  OpenGLTest
//
//  Created by Samuel Hall on 24/07/2016.
//
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object.hpp"

class Camera : public Object
{
private:
    glm::mat4 m_projection;
    glm::mat4 m_view;
    
    glm::vec3 m_target = glm::vec3(0.0f);
    glm::vec3 m_up = glm::normalize( glm::vec3(0.0f, 0.5f, 0.5f) );
    
protected:
    
    void update_model_matrix();
    
public:
    
    Camera(float fov, float width, float height, float near, float far)
    {
        m_projection = glm::perspectiveFov(fov, width, height, near, far);
    }
    
    glm::mat4 get_projection_matrix();
    glm::mat4 get_view_matrix();
};

#endif /* Camera_hpp */
