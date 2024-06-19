#pragma once
#include "weapon/Shooter.h"
#include "SFML/System.hpp"

namespace ly {
	class BulletShooter : public Shooter {
	public:
		BulletShooter(Actor* owner, 
			float cooldownTime = 1.0f, 
			const sf::Vector2f& localPositionOffset = {0.f, 0.f}, 
			float localRotationOffset = 0,
			const std::string& bulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png"
			);
		virtual bool IsOnCooldown() const override;

		void SetBulletTexturePath(const std::string& bulletTexturePath);

		virtual void IncrementLevel(int amt = 1) override;
		
	private:
		virtual void ShootImpl() override;
		sf::Clock mCooldownClock;
		float mCooldownTime;
		sf::Vector2f mLocalPositionOffset;
		float mLocalRotationOffset;
		std::string mBulletTexturePath;
	};
}