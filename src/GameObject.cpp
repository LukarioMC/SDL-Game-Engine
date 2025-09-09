#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *path, float x, float y, float velocity) : xPos(x), yPos(y), xVel(velocity), yVel(velocity), texture(TextureManager::load(path))
{
    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 32;
}

GameObject::~GameObject()
{
    if (texture)
        SDL_DestroyTexture(texture);
}

void GameObject::update(float deltaTime)
{
    xPos += xVel * deltaTime;
    yPos += yVel * deltaTime;
    dstRect.x = xPos;
    dstRect.y = yPos;
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;
}

void GameObject::draw()
{
    TextureManager::draw(texture, srcRect, dstRect);
}