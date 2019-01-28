#ifndef VERTEX_ARRAY_OBJECT_H
#define VERTEX_ARRAY_OBJECT_H

#include <glad/glad.h>
#include <vector>

class VertexArrayObject
{
    private:
        GLuint _vaoId;
        GLuint _iboId;
        std::vector<GLuint> _vbos;

    public:
        VertexArrayObject();

        GLuint* getID();
        GLuint* getIBOID();

        void storeDataInAttributeList(int index, GLfloat* data, size_t& dataSize, int dimension);
        void storeIndicesList(GLuint* data, size_t& dataSize, int indicesAmount);

        void bind();
        void unbind();

};

#endif