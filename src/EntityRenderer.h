#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H

#include "RendererBase.h"
#include "Entity.h"
#include "ShaderProgram.h"
#include "FileUtil.h"

#include <vector>
#include <string>

class EntityRenderer : public RendererBase
{
    private:
        std::vector<Entity*> _entities;
        ShaderProgram*        _shader;

    public:
        EntityRenderer();

        void update(double& deltaTime)          override;
        void draw(glm::mat4* projectionMatrix)  override;
        
        void addEntity(Entity* entity);
        void removeEntity(Entity* entity);
};

#endif