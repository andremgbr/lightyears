#pragma once
#include "spaceship/Spaceship.h"
#include "SFML/Graphics.hpp"

namespace ly {
	class BulletShooter;
	class PlayerSpaceship : public Spaceship {
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
		virtual void Tick(float deltaTime);
		void SetSpeed(float newSpeed) { mSpeed = newSpeed; };
		float GetSpeed() const { return mSpeed; };
		virtual void Shoot() override;
	private:
		void HandleInput();
		void NormalizaInput();
		void ClampInputOnEdge();
		void ConsumeInput(float deltaTime);
		sf::Vector2f mMoveInput;
		float mSpeed;

		unique<BulletShooter> mShooter;

	};
}