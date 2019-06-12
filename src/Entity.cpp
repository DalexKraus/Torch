#include "Entity.h"

Entity::Entity(VertexArrayObject vao, int& indexCount)
{
    _vao = vao;
    _indexCount = indexCount;
}

void Entity::translate(glm::vec3& translation)
{
    _transformationMatrix = glm::translate(_transformationMatrix, translation);
}

void Entity::rotate(float& xRot, float& yRot, float& zRot)
{
    _transformationMatrix = glm::rotate(_transformationMatrix, glm::radians(xRot), glm::vec3(1.0f, 0.0f, 0.0f));
    _transformationMatrix = glm::rotate(_transformationMatrix, glm::radians(yRot), glm::vec3(0.0f, 1.0f, 0.0f));
    _transformationMatrix = glm::rotate(_transformationMatrix, glm::radians(zRot), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Entity::scale(glm::vec3& scale)
{
    _transformationMatrix = glm::scale(_transformationMatrix, scale);
}

VertexArrayObject* Entity::getVAO()
{
    return &_vao;
}

int* Entity::getIndexCount()
{
    return &_indexCount;
}

glm::mat4* Entity::getTransformationMatrix()
{
    return &_transformationMatrix;
}