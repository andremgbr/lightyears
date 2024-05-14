#pragma once
#include <SFML/Graphics.hpp>

#include "framework/Object.h"
#include "framework/Core.h"


namespace ly{
class World;
class Actor : public Object{
public:
  Actor(World* owningWorld, const std::string& texturePath= "");
  virtual ~Actor();

  void BeginPlayInternal();
  virtual void BeginPlay();
  virtual void Tick(float deltaTime);
  void TickInternal(float deltaTime);
  void SetTexture(const std::string& texturePath);
  void Render(sf::RenderWindow& window);

private:

  World* mOwningWolrd; 
  bool mHasBeganPlay;


  sf::Sprite mSprite;
  sf::Texture mTexture;
};
}
