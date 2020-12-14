#pragma once
#include <SDL_image.h>
#include <SDL.h>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <cassert>

class WindowResource
{
public:
	WindowResource();
	~WindowResource();
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	void ClearBackBuffer();
	void Render();
	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip);

	// Loads Texture from asset in designated asset folder with filename. 
	// Also saves texture with given name.
	void LoadNewTexture(std::string path, const char* textureName);
	SDL_Texture* GetTexture(const char* textureName);
	const std::uint32_t SCREEN_WIDTH = 1280;
	const std::uint32_t SCREEN_HEIGHT = 720;
	const char* windowName = "Light2D";
	const std::string graphicsFolderPath = "Assets/Graphics/";
private:
	SDL_Texture* LoadTexture(std::string path);
	SDL_Renderer* renderer;
	SDL_Window* window;
	std::unordered_map<const char*, SDL_Texture*> Texturemap;
};

