#include "Coin.h"

#include "../../Helpers/TextureManager.h"

Coin::Coin(int x, int y) : Tile("../graphics/tiles/coin.png", x, y, {0,0,32,32})
{
    animation_textures = TextureManager::LoadAnimationTextures("../graphics/tiles/silver/", 4);
    animation_frame_num = 0;
}


Coin::~Coin() 
{
    TextureManager::DestroyAnimationTextures(animation_textures);
    cout << "Coin dest" << endl;
}


void Coin::Update()
{
    animation_frame_num += ANIMATION_SPEED;
    if (animation_frame_num >= animation_textures.size())
        animation_frame_num = 0;
    xpos = destRect.x;
    ypos = destRect.y;
    // Добавляем объект в буфер рендерера.
    SDL_RenderCopy(Game::renderer, animation_textures[static_cast<int>(animation_frame_num)], &srcRect, &destRect);
}