#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly{
Actor::Actor(World* owningWorld, const std::string& texturePath)
  : mOwningWolrd{owningWorld},
  mHasBeganPlay{false},
  mTexture{}{
  
  SetTexture(texturePath);
}

Actor::~Actor(){

}

void Actor::BeginPlayInternal(){
  if(!mHasBeganPlay){
    mHasBeganPlay = true;
    BeginPlay();
  }
}

void Actor::BeginPlay(){
  LOG("Actor begin play");
}

 void Actor::Tick(float deltaTime){
  LOG("Actor Ticking");
}

void Actor::TickInternal(float deltaTime){
  if(!IsPendingDestory()){
    Tick(deltaTime);
  }
}

void Actor::SetTexture(const std::string& texturePath){
  mTexture.loadFromFile(texturePath);
  mSprite.setTexture(mTexture);

  int textureWidth = mTexture.getSize().x;
  int textureHeight = mTexture.getSize().y;
  mSprite.setTextureRect(sf::IntRect{sf::Vector2i {}, sf::Vector2i{textureWidth, textureHeight}});
}

void Actor::Render(sf::RenderWindow& window){
  if(IsPendingDestory())
    return;

  window.draw(mSprite);
}
}
