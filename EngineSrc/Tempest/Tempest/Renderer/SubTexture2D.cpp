#include "PreComp.h"
#include "SubTexture2D.h"

namespace Tempest 
{
    SubTexture2D::SubTexture2D(const ref<Texture2D>& texture, const glm::vec2& minBound, const glm::vec2& maxBound) :
        _texture(texture)
    {
        _texCoord[0] = { minBound.x, minBound.y };
        _texCoord[1] = { maxBound.x, minBound.y };
        _texCoord[2] = { maxBound.x, maxBound.y };
        _texCoord[3] = { minBound.x, maxBound.y };
    }

    ref<SubTexture2D> SubTexture2D::createFromCoords(const ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize)
    {
        glm::vec2 min = { (coords.x * spriteSize.x) / texture->getWidth(), (coords.y * spriteSize.y) / texture->getHeight() };
        glm::vec2 max = { ((coords.x + 1) * spriteSize.x) / texture->getWidth(), (coords.y * spriteSize.y) / texture->getHeight() };

        return ref<SubTexture2D>(texture, min, max);
    }
}