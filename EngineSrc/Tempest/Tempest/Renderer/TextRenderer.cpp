#include "TextRenderer.h"

#include <stdio.h>

#include "Renderer2D.h"

namespace
{
    //These contain the size of the index buffers.
    const uint32_t ASCII_BUFFER = 96;
}

namespace Tempest 
{
    TextRenderer::TextRenderer(float fontSize) : _fontSize(fontSize)
    {
        init();
        TTFtoBitmap();
    }

    TextRenderer::~TextRenderer()
    {
        if (_ttfBuffer != nullptr) 
        {
            delete[] _ttfBuffer;
        }
    }

    void TextRenderer::init()
    {
        FILE* ttfFile = nullptr;
        if (fopen_s(&ttfFile, "Assets\\Fonts\\OpenSans-Regular.ttf", "rb") == 0)
        {
            fseek(ttfFile, 0, SEEK_END);
            long bufferSize = ftell(ttfFile); /* how long is the file ? */
            fseek(ttfFile, 0, SEEK_SET); /* reset */

            _ttfBuffer = new unsigned char[bufferSize];

            if (_ttfBuffer != nullptr)
            {
                if (fread_s(_ttfBuffer, bufferSize, bufferSize, 1, ttfFile) == 0)
                {
                    TEMPEST_ERROR("Failed to read from the loaded TTF file.");
                }
            }
            else
            {
                TEMPEST_ERROR("File appears to be empty");
            }

            fclose(ttfFile);
        }
        else 
        {
            TEMPEST_ERROR("Could not open TTF.");
        }
    }

    void TextRenderer::TTFtoBitmap()
    {
        _fontInfo = std::make_unique<stbtt_fontinfo>();
        _asciiBuffer = new stbtt_packedchar[ASCII_BUFFER];

        if (stbtt_InitFont(_fontInfo.get(), _ttfBuffer, 0) == 0)
        {
            delete[] _ttfBuffer;
            TEMPEST_ERROR("Failed to started up STB_TTF");
        }

        // fill bitmap atlas with packed characters
        unsigned char* bitmap = nullptr;
        while (true) 
        {
            bitmap = new unsigned char[_textureSize * _textureSize];
            stbtt_pack_context packContext;
            stbtt_PackBegin(&packContext, bitmap, _textureSize, _textureSize, 0, 1, 0);
            stbtt_PackSetOversampling(&packContext, 1, 1);

            if (stbtt_PackFontRange(&packContext, _ttfBuffer, 0, _fontSize, 32, ASCII_BUFFER, _asciiBuffer) == false)
            {
                delete[] bitmap;
                stbtt_PackEnd(&packContext);
                _textureSize *= 2;
            }
            else 
            {
                stbtt_PackEnd(&packContext);
                break;
            }
        }

        //Remember the _textureSize * _textureSize is the texture size and sizeof(uint32_t) is the channel RGBA
        const int pixelsBufferSize = _textureSize * _textureSize * sizeof(uint32_t);
        uint32_t* pixels = new uint32_t[pixelsBufferSize];

        for (uint32_t i = 0; i < _textureSize * _textureSize; ++i)
        {
            pixels[i] = bitmap[i];
            pixels[i] = pixels[i] << 24;
            pixels[i] += 0xFFFFFF;
        }
        
        _textTexture = Tempest::Texture2D::create(_textureSize, _textureSize);
        _textTexture->setData(pixels, pixelsBufferSize);

        //Text rendering stats not used in this current implementation.
        float scale = stbtt_ScaleForPixelHeight(_fontInfo.get(), _fontSize);
        stbtt_GetFontVMetrics(_fontInfo.get(), &_ascent, 0, 0);
        _baseline = static_cast<int>(_ascent * scale);
    }

    void TextRenderer::displayText(const glm::vec2& position, const glm::vec2 blockSize, const glm::vec4& textColour, const char* text)
    {
        float packQuadX = 0.f;
        float packQuadY = 0.f;
        while(*text)
        {
            if (*text >= 32 && *text < 128)
            {
                stbtt_aligned_quad textureCoords;
                stbtt_GetPackedQuad(_asciiBuffer, _textureSize, _textureSize, *text - 32, &packQuadX, &packQuadY, &textureCoords, 0);

                textureCoords.x0 = textureCoords.x0 / _fontSize;
                textureCoords.x1 = textureCoords.x1 / _fontSize;
                textureCoords.y0 = textureCoords.y0 / _fontSize;
                textureCoords.y1 = textureCoords.y1 / _fontSize;

                Renderer2D::drawText(position, blockSize, textureCoords, _textTexture, 1.f, textColour);
            }
            ++text;
        }
    }

    void TextRenderer::displayText(const glm::vec3& position, const glm::vec2 blockSize, const glm::vec4& textColour, const char* text)
    {
        float packQuadX = 0.f;
        float packQuadY = 0.f;
        while (*text)
        {
            if (*text >= 32 && *text < 128)
            {
                stbtt_aligned_quad textureCoords;
                stbtt_GetPackedQuad(_asciiBuffer, _textureSize, _textureSize, *text - 32, &packQuadX, &packQuadY, &textureCoords, 0);

                textureCoords.x0 = textureCoords.x0 / _fontSize;
                textureCoords.x1 = textureCoords.x1 / _fontSize;
                textureCoords.y0 = textureCoords.y0 / _fontSize;
                textureCoords.y1 = textureCoords.y1 / _fontSize;

                Renderer2D::drawText(position, blockSize, textureCoords, _textTexture, 1.f, textColour);
            }
            ++text;
        }
    }
}