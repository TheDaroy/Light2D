#include "Engine/EngineCore.h"
#include <SDL_events.h>

class GameManager : public LightEngine::EngineCore
{
public: 
	void Setup();

	void UpdateLoop();
	void EarlyUpdate();
	void Update();
	void LateUpdate();

private:
   void CreateStuff();
	SDL_Event mEvents;
	bool quit = false;

	
};

