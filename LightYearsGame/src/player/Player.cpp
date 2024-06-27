#include "player/Player.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"

namespace ly {
    Player::Player() 
        : mLifecount{ 3 },
        mScore{ 0 },
        mCurrentPlayerSpaceship{} {

    }

    weak<PlayerSpaceship> Player::SpawnSpaceship(World* world)
    {
        if (mLifecount > 0) {
            --mLifecount;
            auto windowSize = world->GetWindowSize();
            mCurrentPlayerSpaceship = world->SpawnActor<PlayerSpaceship>();
            mCurrentPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(windowSize.x/2, windowSize.y - 100.f));
            mCurrentPlayerSpaceship.lock()->SetActorRotation(-90.f);
            onLifeChange.Broadcast(mLifecount);
            return mCurrentPlayerSpaceship;
        }
        else {
            mCurrentPlayerSpaceship = weak<PlayerSpaceship>{};
            onLifeExhausted.Broadcast();
        }
        return weak<PlayerSpaceship>{};
    }
    void Player::AddLifeCount(unsigned int count)
    {
        if (count > 0) {
            mLifecount += count;
            onLifeChange.Broadcast(mLifecount);
        }
    }
    void Player::AddScore(unsigned int amt)
    {
        if (amt > 0) {
            mScore += amt;
            onScoreChange.Broadcast(mScore);
        }
    }
}


