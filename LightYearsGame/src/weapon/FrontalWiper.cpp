#include "weapon/FrontalWiper.h"

namespace ly {
	FrontalWiper::FrontalWiper(Actor* owner, float cooldownTimer, const sf::Vector2f& localOffset, float width)
		:Shooter{ owner },
		mWidth{width},
		mShooter1{ owner, cooldownTimer, {localOffset.x, localOffset.y - width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
		mShooter2{ owner, cooldownTimer, {localOffset.x, localOffset.y - width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		mShooter3{ owner, cooldownTimer, {localOffset.x, localOffset.y + width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		mShooter4{ owner, cooldownTimer, {localOffset.x, localOffset.y + width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter5{ owner, cooldownTimer/1.5f, {localOffset.x, localOffset.y + width / 1.5f}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter6{ owner, cooldownTimer/ 1.5f, {localOffset.x, localOffset.y - width / 1.5f}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" } {
	}
	void FrontalWiper::SetCurrentLevel(int amt)
	{
		Shooter::SetCurrentLevel(amt);
		mShooter1.SetCurrentLevel(amt);
		mShooter2.SetCurrentLevel(amt);
		mShooter3.SetCurrentLevel(amt);
		mShooter4.SetCurrentLevel(amt);
		mShooter5.SetCurrentLevel(amt);
		mShooter6.SetCurrentLevel(amt);
	}
	void FrontalWiper::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);
		mShooter1.IncrementLevel(amt);
		mShooter2.IncrementLevel(amt);
		mShooter3.IncrementLevel(amt);
		mShooter4.IncrementLevel(amt);
		mShooter5.IncrementLevel(amt);
		mShooter6.IncrementLevel(amt);
	}
	void FrontalWiper::ShootImpl()
	{
		mShooter1.Shoot();
		mShooter2.Shoot();
		mShooter3.Shoot();
		mShooter4.Shoot();

		if (GetCurrentLevel() == GetMaxLevel()) {

			mShooter5.Shoot();
			mShooter6.Shoot();
		}
	}
}


