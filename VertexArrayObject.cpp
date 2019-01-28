#include "VertexArrayObject.h"
#include "Engine.h"

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &_vaoId);
}



void VertexArrayObject::storeDataInAttributeList(int index, GLfloat* data, size_t& dataSize, int dimension)
{
    unsigned int vboId;
    glGenBuffers(1, &vboId);
    _vbos.push_back(vboId);
    
    glBindVertexArray(_vaoId);

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, dimension, GL_FLOAT, GL_FALSE, dimension * sizeof(float), (void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
}

void VertexArrayObject::storeIndicesList(GLuint* data, size_t& dataSize, int indicesAmount)
{
    glGenBuffers(1, &_iboId);
    _vbos.push_back(_iboId);

    glBindVertexArray(_vaoId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesAmount * sizeof(GLuint), data, GL_STATIC_DRAW);
}

unsigned int* VertexArrayObject::getID()
{
    return &_vaoId;
}

unsigned int* VertexArrayObject::getIBOID()
{
    return &_iboId;
}

void VertexArrayObject::bind()
{
    glBindVertexArray(_vaoId);
}

void VertexArrayObject::unbind()
{
    glBindVertexArray(0);
}