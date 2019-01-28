#ifndef ENTITY_H
#define ENTITY_H

#include "Engine.h"
#include "VertexArrayObject.h"

class Entity
{
    private:
        VertexArrayObject         _vao;
        int                       _indexCount;

        glm::mat4                 _transformationMatrix;

    public:
        Entity(VertexArrayObject vao, int& indexCount);
        
        VertexArrayObject*        getVAO();
        int*                      getIndexCount();
        glm::mat4*                getTransformationMatrix();

        void                      translate(glm::vec3& translation);
        void                      rotate(float& xRot, float& yRot, float& zRot);
        void                      scale(glm::vec3& scale);

};

#endif