#include "Enemy/Boss.h"
#include "gameplay/HealthComponent.h"

namespace ly {
	Boss::Boss(World* world)
		:EnemySpaceship{ world, "SpaceShooterRedux/PNG/Enemies/boss.png"},
		mSpeed{ 100.f },
		mBaseSpeed{100.f},
		mSwitchDistanceToEdge{ 100.f },
		mBaseShooterLeft{ this, 1.f,{50.f, -50.f} },
		mBaseShooterRigth{ this, 1.f,{50.f, 50.f} },
		mThreeWayshooter{ this, 4.f,{100.f, 0.f} },
		mFrontalWiperLeft{ this, 5.f, {80.f, -100.f} },
		mFrontalWiperRight{ this, 5.f, {80.f, 100.f} },
		mFinalStageShooterLeft{ this, 0.3f, {50, -150.f} },
		mFinalStageShooterRight{ this, 0.3f, {50, 150.f} },
		mStage{ 1 } {

		SetActorRotation(90.f);
		SetVelocity({ mSpeed, 0.f });
		SetRewardSpawnWeight(0.f);
	}
	void Boss::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		ShootBaseShooters();
		ShootFrontalWiper();
		ShootThreeWayShooter();
		if (mStage == 4) {
			mFinalStageShooterLeft.Shoot();
			mFinalStageShooterRight.Shoot();
		}
		CheckMove();
	}
	void Boss::BeginPlay()
	{
		EnemySpaceship::BeginPlay();
		HealthComponent& healthComp = GetHealthComp();
		healthComp.SetInitialHealth(3000.f, 3000.f);
		healthComp.onHealthChanged.BindAction(GetWeakRef(), &Boss::HealthChanged);
		
	}
	void Boss::CheckMove()
	{
		if (GetActorLocation().x > GetWindowSize().x - mSwitchDistanceToEdge) {
			SetVelocity({ -mSpeed, 0.f });
		}
		else if (GetActorLocation().x < mSwitchDistanceToEdge) {
			SetVelocity({ mSpeed, 0.f });
		}
	}
	void Boss::ShootBaseShooters()
	{
		mBaseShooterLeft.Shoot();
		mBaseShooterRigth.Shoot();
	}
	void Boss::ShootThreeWayShooter()
	{
		mThreeWayshooter.Shoot();
	}
	void Boss::ShootFrontalWiper()
	{
		mFrontalWiperLeft.Shoot();
		mFrontalWiperRight.Shoot();
	}
	void Boss::HealthChanged(float amt, float currentHealth, float maxHealth)
	{
		float percentLeft = currentHealth / maxHealth;
		if (percentLeft < 0.7f && percentLeft > 0.5f) {
			SetStage(2);
		}

		if (percentLeft < 0.5f && percentLeft > 0.3f) {
			SetStage(3);
		}

		if (percentLeft < 0.3f) {
			SetStage(4);
		}
		
	}
	void Boss::SetStage(int newStage)
	{
		mStage = newStage;
		mBaseShooterLeft.SetCurrentLevel(mStage);
		mBaseShooterRigth.SetCurrentLevel(mStage);
		mFrontalWiperLeft.SetCurrentLevel(mStage);
		mFrontalWiperRight.SetCurrentLevel(mStage);
		mThreeWayshooter.SetCurrentLevel(mStage);
		mSpeed = mStage * mBaseSpeed;
	}
}