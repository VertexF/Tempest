#ifndef TEXT_RENDERER_HDR
#define TEXT_RENDERER_HDR

//Includes stb_truetype.h
#include "PreComp.h"
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"

namespace Tempest 
{
    class TextRenderer 
    {
    public:
        TextRenderer(float fontSize);
        ~TextRenderer();

        void displayText(const glm::vec2& position, const glm::vec2 blockSize, const glm::vec4& textColour, const char* text);
        void displayText(const glm::vec3& position, const glm::vec2 blockSize, const glm::vec4& textColour, const char* text);
    private:
        void init();
        void TTFtoBitmap();

        unsigned char* _ttfBuffer;
        stbtt_packedchar* _asciiBuffer;

        uint32_t _textureSize = 32;
        int _ascent = 0;
        int _baseline = 0;
        float _fontSize;

        Tempest::ref<Tempest::Texture2D> _textTexture;
        Tempest::scope<stbtt_fontinfo> _fontInfo;
    };
}

#endif // !TEXT_RENDERER_HDR
