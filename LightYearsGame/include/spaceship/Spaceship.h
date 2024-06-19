#pragma once
#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"

namespace ly {
	class Spaceship : public Actor {
	public:
		Spaceship(World* owningWorld, const std::string& texturePath = "paceShooterRedux/PNG/playerShip1_blue.png");
		virtual void Tick(float deltaTime) override;
		void SetVelocity(const sf::Vector2f& newVel);
		sf::Vector2f GetVelocity() const {return mVelocity;};
		virtual void Shoot();
		virtual void BeginPlay() override;
		virtual void ApplyDamage(float amt) override;
		HealthComponent& GetHealthComp() { return mHealthComp; };
	private:
		void Blink();

		void UpdateBlink(float deltaTime);

		virtual void OnHealthChanged(float amt, float health, float maxHealth);
		virtual void OnTakenDamage(float amt, float health, float maxHealth);
		virtual void Blow();
		virtual void Blew();
		sf::Vector2f mVelocity;
		HealthComponent mHealthComp;

		float mBlinkTime;
		float mBlinkDuration;
		sf::Color mBlinkColorOffset;
	};
}