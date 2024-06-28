#pragma once
#include <SFML/Graphics.hpp>
#include "weapon/BulletShooter.h"

namespace ly{
	class FrontalWiper : public Shooter {
	public:
		FrontalWiper(Actor* owner, 
			float cooldownTimer = 0.3f, 
			const sf::Vector2f& localOffset = { 0.f, 0.f },
			float width = 60.f);

		virtual void SetCurrentLevel(int amt)override;
		virtual void IncrementLevel(int amt = 1) override;

	private:
		virtual void ShootImpl() override;

		float mWidth;

		BulletShooter mShooter1;
		BulletShooter mShooter2;
		BulletShooter mShooter3;
		BulletShooter mShooter4;

		BulletShooter mShooter5;
		BulletShooter mShooter6;

	};
}