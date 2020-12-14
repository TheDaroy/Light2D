#pragma once

#include "ECS/View.h"
#include "Components/Components.h"
#include "Resources/WindowResource.h"
#include "Resources/InputResource.h"
#include "CollisionLayer.h"

namespace Systems::Graphics
{
	void Update(LightEngine::ECS::EntityManager* entMgr, LightEngine::ECS::ComponentManager* compMgr, WindowResource* winResource)
	{
		auto view = LightEngine::ECS::View<GraphicsComponent, TransformComponent>(compMgr, entMgr);


		for (auto entity : view)
		{
			GraphicsComponent& comp = compMgr->GetComponent<GraphicsComponent>(entity);
			TransformComponent& transformComp = compMgr->GetComponent<TransformComponent>(entity);
			comp.rect.x = (int)(transformComp.position.x - 200 * 0.5f);
			comp.rect.y = (int)(transformComp.position.y - 200 * 0.5f);
			winResource->DrawTexture(comp.texture, NULL, &comp.rect, 0.f, SDL_FLIP_NONE);

		}
	}
}



namespace Systems::Collision
{
	namespace 
	{
		bool BoxVsBox(const BoxCollider& rect1, const TransformComponent& pos1, const BoxCollider& rect2, const TransformComponent& pos2)
		{
			return (pos1.position.x < pos2.position.x + rect2.size.x
				&& pos1.position.x + rect1.size.x > pos2.position.x

				&& pos1.position.y < pos2.position.y + rect2.size.y
				&& pos1.position.y + rect1.size.y > pos2.position.y);
		}
	}
	void Update(LightEngine::ECS::EntityManager* entMgr, LightEngine::ECS::ComponentManager* compMgr, const std::array<CollisionSet,COLLISION_LAYER_AMOUNT> collisionDataArray)
	{
		
		auto view = LightEngine::ECS::View<TransformComponent, BoxCollider>(compMgr, entMgr);

		std::vector<Entity> entetiesToRemove;

		for (auto entity : view)
		{
			TransformComponent& transformComp = compMgr->GetComponent<TransformComponent>(entity);
			BoxCollider& colliderComp = compMgr->GetComponent<BoxCollider>(entity);

			colliderComp.collisionData.clear();
			colliderComp.hit = false;

			for (auto otherEntity : view)
			{
				if (otherEntity == entity )
				{
					continue;
				}
				TransformComponent& otherTransformComp = compMgr->GetComponent<TransformComponent>(otherEntity);
				BoxCollider& otherColliderComp = compMgr->GetComponent<BoxCollider>(otherEntity);
				if (collisionDataArray[colliderComp.layer][otherColliderComp.layer] == true)
				{
					if (BoxVsBox(colliderComp, transformComp, otherColliderComp, otherTransformComp))
					{
						colliderComp.hit = true;
						CollisionData newData;
						newData.entityHit = otherEntity;
						colliderComp.collisionData.push_back(newData);													
					}

				}
			}
		}
	}


}




namespace Systems::Player
{
	namespace
	{
		bool OnCollision(BoxCollider& collider)
		{
			if (collider.hit)
			{
				return true;// destroy
			}
			return false;
		}
		void Move(TransformComponent& transform, PlayerComponent& playerComp, LightEngine::Resource::InputResource* input, const float deltaTime)
		{
			if (input->KeyDown(SDL_SCANCODE_W))
			{
				//std::cout << "Right" << std::endl;
				transform.position.y -= playerComp.MoveSpeed * deltaTime;
			}
			if (input->KeyDown(SDL_SCANCODE_S))
			{
				//std::cout << "Left" << std::endl;
				transform.position.y += playerComp.MoveSpeed * deltaTime;
			}
			if (input->KeyDown(SDL_SCANCODE_A))
			{
				//std::cout << "Up" << std::endl;
				transform.position.x -= playerComp.MoveSpeed * deltaTime;
			}
			if (input->KeyDown(SDL_SCANCODE_D))
			{
				//std::cout << "Down" << std::endl;
				transform.position.x += playerComp.MoveSpeed * deltaTime;
			}
		}
		
	}

	void Update( LightEngine::ECS::EntityManager* entMgr, LightEngine::ECS::ComponentManager* compMgr,  LightEngine::Resource::InputResource* input, const float deltaTime)
	{
		auto view = LightEngine::ECS::View<PlayerComponent>(compMgr, entMgr);
		for (auto entity : view)
		{
			BoxCollider& colliderComp = compMgr->GetComponent<BoxCollider>(entity);
			if (OnCollision(colliderComp))
			{
				colliderComp.hit = false;
				colliderComp.collisionData.clear();
				entMgr->DestroyEntity(entity);
				continue;
			}
			TransformComponent& transfComponent = compMgr->GetComponent<TransformComponent>(entity);
			PlayerComponent& playerComp = compMgr->GetComponent<PlayerComponent>(entity);
			

			Move(transfComponent,playerComp, input,deltaTime);
			
		}
	}
}

