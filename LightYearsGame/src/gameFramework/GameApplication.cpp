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

  testePlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
  testePlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
  testePlayerSpaceship.lock()->SetActorRotation(-90.f);

  weak<Spaceship> testeSpaceship = newWorld.lock()->SpawnActor<Spaceship>();
  testeSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
  testeSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });
  counter = 0.f;


}

void GameApplication::Tick(float deltaTime){
    counter += deltaTime;
    if (counter > 10.f) {
        if (!testePlayerSpaceship.expired()) {
            testePlayerSpaceship.lock()->Destory();
        }
    }
}
}
