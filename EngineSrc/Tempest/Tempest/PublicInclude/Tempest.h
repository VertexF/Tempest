#ifndef TEMPEST_HDR
#define TEMPEST_HDR

//Core
#include "Tempest/Core/Application.h"
#include "Tempest/Core/Layer.h"
#include "Tempest/Core/Core.h"
#include "Tempest/ImGui/ImGUILayer.h"
#include "Tempest/Core/Random.h"
#include "Tempest/Core/TimeStep.h"

//Events
#include "Tempest/Core/Input.h"
#include "Tempest/Core/KeyCodes.h"
#include "Tempest/Core/MouseButtonCodes.h"

#include "Tempest/Renderer/OrthoCameraController.h"

//RenderingAPI
#include "Tempest/Renderer/Buffer.h"
#include "Tempest/Renderer/GraphicsContext.h"
#include "Tempest/Renderer/OrthographicCamera.h"
#include "Tempest/Renderer/Renderer.h"
#include "Tempest/Renderer/RendererAPI.h"
#include "Tempest/Renderer/RendererCommands.h"
#include "Tempest/Renderer/Shader.h"
#include "Tempest/Renderer/VertexArray.h"
#include "Tempest/Renderer/Texture.h"
#include "Tempest/Renderer/SubTexture2D.h"
#include "Tempest/Renderer/Framebuffer.h"
#include "Tempest/Renderer/Renderer2D.h"

#include "Tempest/Renderer/TextRenderer.h"

//Effects
#include "Tempest/Renderer/ParticalSystem.h"

//Audio
#include "Tempest/Audio/OpenALSoundDevice.h"
#include "Tempest/Audio/SoundSource.h"
#include "Tempest/Audio/SoundBuffer.h"
#include "Tempest/Audio/Audio.h"

//Collision
#include "Tempest/Collision/Rect.h"
#include "Tempest/Collision/AABBCollision.h"

//Entities
// #include "Tempest/Entity/MovingEntity.h"
// #include "Tempest/Entity/SteeringBehavior.h"
// #include "Tempest/Entity/GameWorld.h"
// #include "Tempest/Entity/Telegram.h"

#endif // !TEMPEST_HDR