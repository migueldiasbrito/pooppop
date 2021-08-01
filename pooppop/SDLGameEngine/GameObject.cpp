#include "GameObject.h"
#include "Renderer.h"

namespace engine = ::pooppop::sdl_game_engine;

engine::GameObject::GameObject(float x, float y, float width, float height,
	std::string textureFilename) : x(x), y(y), width(width), height(height)
{
	if (textureFilename != "")
	{
		myTexture = Renderer::GetInstance()->RequestTexture(textureFilename);
		textShared = false;
	}
}

engine::GameObject::GameObject(float x, float y, float width, float height, int red,
	int green, int blue, int alpha) : x(x), y(y), width(width), height(height),
	red(red), green(green), blue(blue), alpha(alpha)
{
	textShared = false;
}

/*engine::GameObject::GameObject(float x, float y, std::string fontFilename, int size,
	std::string text, int red, int green, int blue) : x(x), y(y)
{
	myTexture = Renderer::GetInstance()->RequestFontTexture(text,
		fontFilename, size, red, green, blue, &width, &height);
	this->x -= width / 2;
	this->y -= height / 2;
	textShared = false;
}*/

engine::GameObject::~GameObject()
{
	if (!textShared)
		delete myTexture;
}

void engine::GameObject::Draw()
{
	// If we have a texture, we draw the texture
	if (myTexture != NULL)
	{
		myTexture->DrawAt(x, y, width, height);
	}
	// Else, draw a rect with the object color
	else
	{
		Renderer::GetInstance()->DrawRect(x, y, width, height,
			red, green, blue, alpha, true);
	}
}

bool engine::GameObject::Update(float elapsedTime)
{
	return true;
}

float engine::GameObject::GetX()
{
	return x;
}

float engine::GameObject::GetY()
{
	return y;
}

float engine::GameObject::GetWidth()
{
	return width;
}

float engine::GameObject::GetHeight()
{
	return height;
}

void engine::GameObject::SetTexture(Texture* newTexture, bool shared, bool deleteCurr)
{
	if (deleteCurr)
	{
		delete myTexture;
	}
	myTexture = newTexture;
	textShared = shared;
}
