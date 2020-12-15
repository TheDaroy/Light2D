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
		SuperEarly();
		EarlyUpdate();
		Update();
		LateUpdate();
		

		Render();

	}
}
void GameManager::EarlyUpdate()
{
	
}


void GameManager::Update()
{
	
	//windowResource->DrawLine({200,200}, { 1000,1000 },{255,0,0,255});
	//windowResource->DrawSquare({300,300}, 100, { 0,0,255,255 });
	//windowResource->DrawFilledSquare({ 500,500 }, 200, { 0,0,255,255 });
	Systems::Collision::Update(EntityManager.get(), ComponentManager.get(),collisionLayerManager->GetCollisionDataArray());
}
void GameManager::LateUpdate()
{

	Systems::Graphics::Update(EntityManager.get(),ComponentManager.get(),windowResource.get());
}

