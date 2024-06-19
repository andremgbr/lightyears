#pragma once

#include "weapon/BulletShooter.h"
#include <SFML/Graphics.hpp>

namespace ly {
	class ThreeWayShooter : public Shooter {
	public:
		ThreeWayShooter(Actor* owner, float cooldownTimer = 0.3f, const sf::Vector2f& localOffset = { 0.f, 0.f });
		
		BulletShooter mShooterLeft;
		BulletShooter mShooterMid;
		BulletShooter mShooterRight;

		BulletShooter mTopLevelShooterLeft;
		BulletShooter mTopLevelShooterRight;

		virtual void IncrementLevel(int amt = 1) override;

	private :
		virtual void ShootImpl();
	};

}