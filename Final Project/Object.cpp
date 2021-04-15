#include "Object.h"

Object::Object(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
{
    pos = position;
    s = scale;
    rot = rotation;
}

void Object::draw()
{
    //TODO: update all shaders model matrices for use in this object
    //  Create Model matrix //TODO: calculate model matrix in obj
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));
    model = glm::rotate(model, glm::radians(rot.x), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(rot.y), glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, glm::radians(rot.z), glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, glm::vec3(s.x, s.y, s.z));

    ShaderHandler::updateModelMatrix(model);
    drawObject();
}

void Object::drawObject()
{
    std::cout << "an object does not have a drawObject() function." << std::endl;
}

void Object::VBOInit()
{
    std::cout << "an object does not have a VBOInit() function." << std::endl;
}