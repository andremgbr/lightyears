#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "framework/Actor.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceship.h"

namespace ly {

	GameLevelOne::GameLevelOne(Application* owingApp)
		: World{ owingApp } {

		testePlayerSpaceship = SpawnActor<PlayerSpaceship>();
		testePlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		testePlayerSpaceship.lock()->SetActorRotation(-90.f);

		weak<Vanguard> testeSpaceship = SpawnActor<Vanguard>();
		testeSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });

	}

}
