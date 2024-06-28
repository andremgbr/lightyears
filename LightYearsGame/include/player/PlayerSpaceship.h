#pragma once
#include "spaceship/Spaceship.h"
#include "SFML/Graphics.hpp"
#include "framework/TimerManager.h"

namespace ly {
	class Shooter;
	class PlayerSpaceship : public Spaceship {
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
		virtual void Tick(float deltaTime);
		void SetSpeed(float newSpeed) { mSpeed = newSpeed; };
		float GetSpeed() const { return mSpeed; };
		virtual void Shoot() override;
		void SetShooter(unique<Shooter>&& newShooter);
		virtual void ApplyDamage(float amt) override;
		virtual void BeginPlay() override;
	private:
		void HandleInput();
		void NormalizaInput();
		void ClampInputOnEdge();
		void ConsumeInput(float deltaTime);
		void StopInvulnerable();
		void UpdateInvulnerable(float detaTime);
		sf::Vector2f mMoveInput;
		float mSpeed;

		unique<Shooter> mShooter;

		float mInvulnerableTime;
		TimerHandle mInvulnerableTimerHandle;
		bool mInvulnerable;

		float mInvulnerableFlashInterval;
		float mInvulnerableFlashTimer;
		float mInvulnerableFlashDir;

	};
}