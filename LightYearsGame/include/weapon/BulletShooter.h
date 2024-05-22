#pragma once
#include "weapon/Shooter.h"
#include "SFML/System.hpp"

namespace ly {
	class BulletShooter : public Shooter {
	public:
		BulletShooter(Actor* owner, float cooldownTime = 1.0f);
		virtual bool IsOnCooldown() const override;
		
	private:
		virtual void ShootImpl() override;
		sf::Clock mCooldownClock;
		float mCooldownTime;
	};
}