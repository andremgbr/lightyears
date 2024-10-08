#include "Enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

namespace ly {

	Vanguard::Vanguard(World* owingWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceship{ owingWorld, texturePath},
		mShooter{ new BulletShooter{this, 1.f, {50.f, 0.0f}}} {
		SetVelocity(velocity);
		SetActorRotation(90.f);
	}

	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void Vanguard::Shoot()
	{
		mShooter->Shoot();
	}

}
