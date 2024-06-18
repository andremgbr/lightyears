#pragma once

#include "framework/Actor.h"
#include <functional>

namespace ly {
	class PlayerSpaceship;
	using RewardFunc = std::function<void(PlayerSpaceship*)>;
	class Reward : public Actor {
	public:
		Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed = 200.f);
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
	private:
		virtual void OnActorBeginOverlap(Actor* otherActor);
		float mSpeed;
		RewardFunc mRewardFunc;
	};
}