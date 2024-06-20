#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"
#include "widgets/HUD.h"

namespace ly{
  World::World(Application* owningApp)
    : mOwningApp{owningApp},
    mBeganPlay{false},
    mActors{},
    mPendingActors{},
    mCurrentStage{mGameStages.end()},
    mGameStages{}
{

}

void World::BeginPlayInternal(){
  if(!mBeganPlay){
    mBeganPlay = true;
    BeginPlay();
    InitGameStages();
    StartStages();
  }
}

sf::Vector2u World::GetWindowSize() const
{
    return mOwningApp->GetWindowSize();
}

void World::CleanCycle()
{
    for (auto iter = mActors.begin(); iter != mActors.end();) {
        if (iter->get()->IsPendingDestory()) {
            iter = mActors.erase(iter);
        }
        else {
            ++iter;
        }
    }

}

void World::AddState(const shared<GameStage>& newStage)
{
    mGameStages.push_back(newStage);
}

bool World::DispathEvent(const sf::Event& event)
{
    if (mHUD) {
        return mHUD->HandleEvent(event);
    }
}

void World::BeginPlay(){
  LOG("Began Play");
}

void World::Tick(float deltaTime){

}

void World::RenderHUD(sf::RenderWindow& window)
{
    if (mHUD) {
        mHUD->Draw(window);
    }
}


void World::InitGameStages()
{
}

void World::AllGameStageFinished()
{
    LOG("All Stages Finished");
}

void World::NextGameStage()
{
    mCurrentStage = mGameStages.erase(mCurrentStage);
    if (mCurrentStage != mGameStages.end()) {
        mCurrentStage->get()->StartStage();
        mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
    }
    else {
        AllGameStageFinished();
    }
}

void World::StartStages()
{
    mCurrentStage = mGameStages.begin();
    mCurrentStage->get()->StartStage();
    mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
;}

void World::TickInternal(float deltaTime){

  for(shared<Actor> actor : mPendingActors){
    mActors.push_back(actor);
    actor->BeginPlayInternal();
  }

  mPendingActors.clear();

  for(auto iter = mActors.begin(); iter != mActors.end();){

      iter->get()->TickInternal(deltaTime);
      ++iter;

  }

  if (mCurrentStage != mGameStages.end()) {
      mCurrentStage->get()->TickStage(deltaTime);
    }

  Tick(deltaTime);

  if (mHUD && mHUD->HasInit()) {
      mHUD->NativeInit(mOwningApp->GetWindow());
  }

}

void World::Render(sf::RenderWindow& window){
  for (auto& actor: mActors){
    actor->Render(window);
  }

  RenderHUD(window);

}

World::~World(){

}

}
