#include "gameFramework/GameApplication.h"
#include "framework/Actor.h"
#include "framework/World.h"

ly::Application* GetApplication(){
  return new ly::GameApplication{};
}

namespace ly{

GameApplication::GameApplication()
  :Application{600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}{
  weak<World> newWorld = LoadWorld<World>();
  newWorld.lock()->SpawnActor<Actor>();
  actorToDestory = newWorld.lock()->SpawnActor<Actor>();
  actorToDestory.lock()->SetTexture("/home/andre/dev/cpp/lightyears/LightYearsGame/assets/SpaceShooterRedux/PNG/playerShip1_blue.png");
  counter = 0;
}

void GameApplication::Tick(float deltaTime){
  counter += deltaTime;
  if(counter > 2.f){
    if(!actorToDestory.expired()){
      actorToDestory.lock()->Destory();
    }
  }
}
}
