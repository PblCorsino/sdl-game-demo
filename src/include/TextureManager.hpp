#ifndef __TextureManager__
#define __TextureManager__

#include<iostream>
#include<map>
#include<SDL.h>
#include<SDL_image.h>

class TextureManager {
public:
  static TextureManager* Instance() {
    if (s_pInstance == 0) {
      s_pInstance = new TextureManager();
      return s_pInstance;
    }
    return s_pInstance;
  }

  // Load image in a renderer
  bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

  // Draw
  void draw(std::string id, int x, int y, int width, int height
            , SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

  // Draw Frame
  void drawFrame(std::string id, int x, int y, int width, int height
                 , int currentRow, int currentFrame
                 , SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

  // Clear from textureID
  void clearFromTextureMap(std::string id);

private:
  // Constructor is private to make a singleton class
  TextureManager() {}
  static TextureManager* s_pInstance;

  // Map of pointers to texture objects
  std::map<std::string, SDL_Texture*> m_textureMap;
};

typedef TextureManager TheTextureManager;

#endif
