#pragma once

#include "ECS/ComponentManager.h"
#include "ECS/EntityManager.h"
#include "ECS/ECS-Types.h"
#include "ECS/View.h"
#include "Resources/Timer.h"
#include "Resources/InputResource.h"
#include "Resources/WindowResource.h"
#include "Math/Vector2.h"
#include <memory>
#include "CollisionSettings.h"




namespace LightEngine
{
	class EngineCore
	{
	protected:

		EngineCore();	
		
		std::unique_ptr<ECS::EntityManager> EntityManager;
		std::unique_ptr<ECS::ComponentManager> ComponentManager;
		std::unique_ptr<CollisionLayerManager> collisionLayerManager;
		std::unique_ptr<Resource::Timer> Timer;
		std::unique_ptr<Resource::InputResource> Input;
		std::unique_ptr<WindowResource> windowResource;
	private:
		void MakePointers();
		void RegisterComponents();
		void SetCollisionLayers();
	};
}