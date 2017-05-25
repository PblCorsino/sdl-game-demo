#ifndef __TextureManager__
#define __TextureManager__

#include<iostream>
#include<map>
#include<SDL.h>
#include<SDL_image.h>

class TextureManager {
public:
  // Load image in a renderer
  bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

  // Draw
  void draw(std::string id, int x, int y, int width, int height
            , SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

  // Draw Frame
  void drawFrame(std::string id, int x, int y, int width, int height
                 , int currentRow, int currentFrame
                 , SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
  // Map of pointers to texture objects
  std::map<std::string, SDL_Texture*> m_textureMap;
};

#endif
