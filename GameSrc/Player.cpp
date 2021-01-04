#include "PreComp.h"
#include "Player.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

Player::Player() 
{
}

void Player::loadAssets() 
{
    TEMPEST_PROFILE_FUNCTION();
}

void Player::onUpdate(Tempest::TimeStep /*ts*/)
{
    TEMPEST_PROFILE_FUNCTION();
}

void Player::onRender() 
{
    TEMPEST_PROFILE_FUNCTION();
}

void Player::onImGuiRender() 
{
    TEMPEST_PROFILE_FUNCTION();
}

void Player::reset() 
{
    _position = { 0.0f, 0.0f };
    _velocity = { 0.0f, 0.0f };
}