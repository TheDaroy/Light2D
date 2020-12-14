#include "GameManger.h"
#include "Engine/GameSystems.h"


void GameManager::Setup()
{
	
}
void GameManager::UpdateLoop()
{
	while (!quit)
	{
		Timer->Update();
		while (SDL_PollEvent(&mEvents)) {

			if (mEvents.type == SDL_QUIT) {

				quit = true;
			}
		}
		Timer->Reset();		
	    windowResource->ClearBackBuffer();
		Input->Update();

		EarlyUpdate();
		Update();
		LateUpdate();

		windowResource->Render();

	}
}
void GameManager::EarlyUpdate()
{
	
}


void GameManager::Update()
{
	Systems::Collision::Update(EntityManager.get(), ComponentManager.get(),collisionLayerManager->GetCollisionDataArray());
}
void GameManager::LateUpdate()
{

	Systems::Graphics::Update(EntityManager.get(),ComponentManager.get(),windowResource.get());
}

