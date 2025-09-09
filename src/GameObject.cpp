#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *path, int x, int y) : xPos(x), yPos(y), texture(TextureManager::load(path))
{
    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 32;
}

GameObject::~GameObject()
{
    if (texture)
        SDL_DestroyTexture(texture);
}

void GameObject::update()
{
    // Move object by 1 pixel
    xPos++;
    yPos++;

    dstRect.x = static_cast<float>(xPos);
    dstRect.y = static_cast<float>(yPos);
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;
}

void GameObject::draw()
{
    TextureManager::draw(texture, srcRect, dstRect);
}