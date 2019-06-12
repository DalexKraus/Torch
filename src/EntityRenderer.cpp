#include "EntityRenderer.h"
#include <iostream>
#include <algorithm>

class EntityShader : public ShaderProgram
{
    public:
        EntityShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
        : ShaderProgram(vertexShaderCode, fragmentShaderCode) {}

    protected:
        virtual void bindAttributes() override;
};

void EntityShader::bindAttributes()
{
    bindAttribute(0, "aPos");
    std::cout << "Set Attributes" << std::endl;
}

EntityRenderer::EntityRenderer()
{
    std::string vertexShaderCode = FileUtil::readFile("shaders/shader.vsh");
    std::string fragmentShaderCode = FileUtil::readFile("shaders/shader.fsh");
    _shader = new EntityShader(vertexShaderCode, fragmentShaderCode);
}

void EntityRenderer::update(double& deltaTime)
{
    
}

void EntityRenderer::draw(glm::mat4* projectionMatrix)
{
    Engine::EngineInstance* engineInstance = Engine::EngineInstance::getInstance();

    for (auto& entity : _entities)
    {
        _shader->start();

	    unsigned int projectionMatrixLocation = _shader->getUniformLocation("projectionMatrix");
        unsigned int viewMatrixLocation = _shader->getUniformLocation("viewMatrix");
        unsigned int transformationMatrixLocation = _shader->getUniformLocation("transformationMatrix");

	    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(*projectionMatrix));
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(*engineInstance->getCamera()->getViewMatrix()));
        glUniformMatrix4fv(transformationMatrixLocation, 1, GL_FALSE, glm::value_ptr(*entity->getTransformationMatrix()));

        entity->getVAO()->bind();
        glEnableVertexAttribArray(0);
        glDrawElements(GL_TRIANGLES, *entity->getIndexCount(), GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(0);
        entity->getVAO()->unbind();
        _shader->stop();
    }
}

void EntityRenderer::addEntity(Entity* entity)
{
    _entities.push_back(entity);
}

void EntityRenderer::removeEntity(Entity* entity)
{
    _entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
}
