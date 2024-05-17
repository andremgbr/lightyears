#include "gameFramework/GameApplication.h"
#include "framework/Actor.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceship.h"
#include "config.h"

ly::Application* GetApplication(){
  return new ly::GameApplication{};
}

namespace ly{

GameApplication::GameApplication()
  :Application{600, 800, "Light Years", sf::Style::Titlebar | sf::Style::Close}{
  
    AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
    weak<World> newWorld = LoadWorld<World>();
  newWorld.lock()->SpawnActor<Actor>();
  testePlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
  testePlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));


}

void GameApplication::Tick(float deltaTime){
  
}
}
