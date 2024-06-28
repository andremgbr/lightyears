#include "weapon/ThreeWayShooter.h"

namespace ly {
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTimer, const sf::Vector2f& localOffset) 
		: Shooter{ owner },
		mShooterLeft{ owner, cooldownTimer, localOffset + sf::Vector2f{10,-10}, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
		mShooterMid{ owner, cooldownTimer, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mShooterRight{ owner, cooldownTimer, localOffset + sf::Vector2f{10,10}, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mTopLevelShooterLeft{ owner, cooldownTimer, localOffset + sf::Vector2f{10,10}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mTopLevelShooterRight{ owner, cooldownTimer, localOffset + sf::Vector2f{10,-10}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" } {

	}

	void ThreeWayShooter::SetCurrentLevel(int amt)
	{
		Shooter::SetCurrentLevel(amt);
		mShooterLeft.SetCurrentLevel(amt);
		mShooterMid.SetCurrentLevel(amt);
		mShooterRight.SetCurrentLevel(amt);

		mTopLevelShooterLeft.SetCurrentLevel(amt);
		mTopLevelShooterRight.SetCurrentLevel(amt);
	}

	void ThreeWayShooter::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);
		mShooterLeft.IncrementLevel(amt);
		mShooterMid.IncrementLevel(amt);
		mShooterRight.IncrementLevel(amt);

		mTopLevelShooterLeft.IncrementLevel(amt);
		mTopLevelShooterRight.IncrementLevel(amt);
	}

	void ThreeWayShooter::ShootImpl()
	{
		mShooterLeft.Shoot();
		mShooterMid.Shoot();
		mShooterRight.Shoot();

		if (GetCurrentLevel() == GetMaxLevel()) {
			mTopLevelShooterLeft.Shoot();
			mTopLevelShooterRight.Shoot();
		}
	}

}


