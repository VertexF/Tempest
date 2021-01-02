#ifndef SUB_TEXTURE_2D
#define SUB_TEXTURE_2D

#include <glm/glm.hpp>

#include "Tempest/Core/core.h"
#include "Tempest/Renderer/Texture.h"

namespace Tempest 
{
    class SubTexture2D 
    {
    public:
        SubTexture2D(const ref<Texture2D> &texture, const glm::vec2& minBound, const glm::vec2& maxBound);

        const ref<Texture2D> getTexture() const { return _texture; }
        const glm::vec2* getTexCoord() const { return _texCoord; }

        static ref<SubTexture2D> createFromCoords(const ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize);
    private:
        ref<Texture2D> _texture;

        glm::vec2 _texCoord[4];
    };
}

#endif // !SUB_TEXTURE_2D
