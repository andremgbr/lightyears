#include "Enemy/VanguardStage.h"
#include "Enemy/Vanguard.h"
#include "framework/World.h"
#include "Enemy/TwinBlade.h"

#include "Enemy/Hexagon.h"

namespace ly {
	VanguardStage::VanguardStage(World* world)
		:GameStage{ world },
		mSpawnInterval{ 1.5f },
		mSwitchInterval{ 5.f },
		mSpawnDistanceToEdge{ 100.f },
		mLeftSpawLoc{ 0.0f, 0.0f },
		mRightSpawLoc{ 0.0f, 0.0f },
		mRowsToSpawn{ 2 },
		mRowSpawnCount{ 0 },
		mVanguarsPerRow{ 5 },
		mCurrentRowVanguardCount{ 0 } {
	}
	void VanguardStage::StartStage()
	{
		auto windowSize = GetWorld()->GetWindowSize();
		mLeftSpawLoc = sf::Vector2f{ mSpawnDistanceToEdge, -100.f };
		mRightSpawLoc = sf::Vector2f{ windowSize.x - mSpawnDistanceToEdge, -100.f };

		SwithRow();
	}
	void VanguardStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawTimerHandle);
		TimerManager::Get().ClearTimer(mSwitchTimerHandle);
	}
	void VanguardStage::SpawnVguard()
	{
		weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetActorLocation(mSpawLoc);
		++mCurrentRowVanguardCount;
		if (mCurrentRowVanguardCount == mVanguarsPerRow) {
			TimerManager::Get().ClearTimer(mSpawTimerHandle);
			mSwitchTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwithRow, mSwitchInterval, false);
			mCurrentRowVanguardCount = 0;
		}
	}
	void VanguardStage::SwithRow()
	{
		if (mRowSpawnCount == mRowsToSpawn) {
			FinishStage();
			return;
		}

		if (mSpawLoc == mLeftSpawLoc) {
			mSpawLoc = mRightSpawLoc;
		}
		else {
			mSpawLoc = mLeftSpawLoc;
		}

		mSpawTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVguard, mSpawnInterval, true);

		++mRowSpawnCount;
	}
}