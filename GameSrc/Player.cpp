#include "PreComp.h"
#include "Player.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

Player::Player() 
{
    //Smoke
    _smokeParticalProps.position = {0.f, 0.f};

    _smokeParticalProps.velocity = { -2.f, 0.f };
    _smokeParticalProps.velocityVariation = { 4.f, 2.f };

    _smokeParticalProps.beginSize = 0.35f;
    _smokeParticalProps.endSize = 0.0f;
    _smokeParticalProps.sizeVarition = 0.15f;

    _smokeParticalProps.colourBegin = {0.8f, 0.8f, 0.8f, 1.f};
    _smokeParticalProps.colourEnd = { 0.6f, 0.6f, 0.6f, 1.f };

    _smokeParticalProps.lifeTime = 4.f;

    //fire
    _fireParticalProps.position = { 0.f, 0.f };

    _fireParticalProps.velocity = { -2.f, 0.f };
    _fireParticalProps.velocityVariation = { 3.f, 1.f };

    _fireParticalProps.beginSize = 0.5f;
    _fireParticalProps.endSize = 0.0f;
    _fireParticalProps.sizeVarition = 0.3f;

    _fireParticalProps.colourBegin = { 254.f / 255.f, 109.f / 255.f, 41.f / 255.f, 1.f };
    _fireParticalProps.colourEnd = { 254.f / 255.f, 212.f / 255.f, 123.f / 255.f , 1.f };

    _fireParticalProps.lifeTime = 1.f;
}

void Player::loadAssets() 
{
    _shipTexture = Tempest::Texture2D::create("Assets/Textures/Ship.png");
}

void Player::onUpdate(Tempest::TimeStep ts)
{
    _time += ts;

    if (Tempest::Input::isKeyPressed(TEMP_KEY_SPACE))
    {
        _velocity.y += _enginePower;
        if (_velocity.y < 0.f)
        {
            _velocity.y += _enginePower * 2.f;
        }

        glm::vec2 emissionPoint = { 0.f, -0.6f };
        float rotation = glm::radians(getRotation());
        glm::vec4 rotated = glm::rotate(glm::mat4x4(1.f), rotation, { 0.f, 0.f, 1.f }) * glm::vec4(emissionPoint, 0.f, 1.f);
        _fireParticalProps.position = _position + glm::vec2{ rotated.x, rotated.y };
        _fireParticalProps.velocity.y = -_velocity.y * 0.2f - 0.2f;
        _particalSystem.emit(_fireParticalProps);
    }
    else 
    {
        _velocity.y -= _gravity;
    }

    _velocity.y = glm::clamp(_velocity.y, -20.f, 20.f);
    _position += _velocity * static_cast<float>(ts);

    if (_time > _smokeEmitTime) 
    {
        _smokeParticalProps.position = _position;
        _particalSystem.emit(_smokeParticalProps);
        _smokeEmitTime += _smokeInterval;
    }

    _particalSystem.onUpdate(ts);
}

void Player::onRender() 
{
    _particalSystem.onRender();
    Tempest::Renderer2D::drawRotatedQuad({ _position.x, _position.y, -0.5f}, {1.f, 1.3f}, glm::radians(getRotation()), _shipTexture);
}

void Player::onImGuiRender() 
{
    ImGui::DragFloat("Engine Power", &_enginePower, -0.1f);
    ImGui::DragFloat("Gravity Power", &_gravity, -0.1f);
}

void Player::reset() 
{
    _position = { -10.0f, 0.0f };
    _velocity = { 5.0f, 0.0f };
}