#pragma once
#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly {
	class VanguardStage : public GameStage {
	public:
		VanguardStage(World* world);
		virtual void StartStage() override;
	private:
		float mSpawnInterval;
		float mSwitchInterval;
		float mSpawnDistanceToEdge;

		sf::Vector2f mLeftSpawLoc;
		sf::Vector2f mRightSpawLoc;
		sf::Vector2f mSpawLoc;

		TimerHandle mSpawTimerHandle;
		TimerHandle mSwitchTimerHandle;

		int mRowsToSpawn;
		int mRowSpawnCount;

		int mVanguarsPerRow;
		int mCurrentRowVanguardCount;

		virtual void StageFinished() override;
		void SpawnVguard();
		void SwithRow();

	};
}