#include "widgets/GamePlayHUD.h"
#include "widgets/HUD.h"
#include "player/player.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "framework/Actor.h"

namespace ly {
	GamePlayHUD::GamePlayHUD()
		:mFrameRateText{"Frame Rate:"},
		mPlayerHealtBar{},
		mHealthyHealthBarColor{128,255,128,255},
		mCriticalHealthBarColor{255,0,0,255},
		mCriticalThreshold{0.3},
		mWidgetSpacing{ 10.f },
		mPlayerLifeIcon{ "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png" },
		mPlayerLifeText{""},
		mPlayerScoreIcon{ "SpaceShooterRedux/PNG/Power-ups/star_gold.png" },
		mPlayerScoreText{ "" },
		mWinLoseText{""},
		mFinalScoreText{""},
		mRestartButton{"Restart"},
		mQuitButton{"Quit"},
		mWindowSize{}
 {
		mFrameRateText.SetTextSize(30);
		mPlayerLifeText.SetTextSize(20);
		mPlayerScoreText.SetTextSize(20);

		mWinLoseText.SetVisibility(false);
		mFinalScoreText.SetVisibility(false);
		mRestartButton.SetVisibility(false);
		mQuitButton.SetVisibility(false);
	}
	void GamePlayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mWindowSize = windowRef.getSize();
		mFrameRateText.NativeDraw(windowRef);
		mPlayerHealtBar.NativeDraw(windowRef);
		mPlayerLifeIcon.NativeDraw(windowRef);
		mPlayerLifeText.NativeDraw(windowRef);
		mPlayerScoreIcon.NativeDraw(windowRef);
		mPlayerScoreText.NativeDraw(windowRef);

		mWinLoseText.NativeDraw(windowRef);
		mFinalScoreText.NativeDraw(windowRef);
		mRestartButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);

	}
	void GamePlayHUD::Tick(float deltaTime)
	{
		int frameRate = int(1 / deltaTime);
		std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
		mFrameRateText.SetString(frameRateStr);
	}
	bool GamePlayHUD::HandleEvent(const sf::Event& event)
	{
		if (mRestartButton.HandleEvent(event)) return true;
		if (mQuitButton.HandleEvent(event)) return true;

		return HUD::HandleEvent(event);
	}
	void GamePlayHUD::Init(const sf::RenderWindow& windowRef)
	{

		auto windowSize = windowRef.getSize();
		mWindowSize = windowSize;
		mPlayerHealtBar.SetWidgetLocation(sf::Vector2f{ 20.f, windowSize.y - 50.f });

		sf::Vector2f nextWidgetPos = mPlayerHealtBar.GetWidgetLocation();
		nextWidgetPos += sf::Vector2f{ mPlayerHealtBar.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerLifeIcon.SetWidgetLocation(nextWidgetPos);

		nextWidgetPos += sf::Vector2f{ mPlayerLifeIcon.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerLifeText.SetWidgetLocation(nextWidgetPos);

		nextWidgetPos += sf::Vector2f{ mPlayerLifeText.GetBound().width + mWidgetSpacing * 4, -2.f };
		mPlayerScoreIcon.SetWidgetLocation(nextWidgetPos);

		nextWidgetPos += sf::Vector2f{ mPlayerScoreIcon.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerScoreText.SetWidgetLocation(nextWidgetPos);

		RefreshHealthBar();
		ConnectPlayerStatus();
		mWinLoseText.SetTextSize(40);
		//mWinLoseText.SetString("You WIN!");
		mWinLoseText.SetWidgetLocation({ windowSize.x / 2.f - mWinLoseText.GetBound().width/2, 100.f});
		mFinalScoreText.SetTextSize(40);
		mFinalScoreText.SetWidgetLocation({ windowSize.x / 2.f - mFinalScoreText.GetBound().width / 2, 200.f });


		mRestartButton.SetWidgetLocation({ windowSize.x / 2.f - mRestartButton.GetBound().width / 2, windowSize.y / 2.f });
		mQuitButton.SetWidgetLocation(mRestartButton.GetWidgetLocation() + sf::Vector2f{ 0.f, 50.f });
		mRestartButton.onButtonClicked.BindAction(GetWeakRef(), &GamePlayHUD::RestartButtonCliked);
		mQuitButton.onButtonClicked.BindAction(GetWeakRef(), &GamePlayHUD::QuitButtonCliked);

	}
	void GamePlayHUD::PlayerHealthUpdated(float amt, float currentHealth, float maxHealth)
	{
		mPlayerHealtBar.UpdateValue(currentHealth, maxHealth);
		if (currentHealth / maxHealth < mCriticalThreshold) {
			mPlayerHealtBar.SetForgroundColor(mCriticalHealthBarColor);
		}
		else {
			mPlayerHealtBar.SetForgroundColor(mHealthyHealthBarColor);
		}
	}
	void GamePlayHUD::PlayerLifeCountUpdate(int amt)
	{
		mPlayerLifeText.SetString(std::to_string(amt));
	}
	void GamePlayHUD::PlayerScoreUpdated(int newScore)
	{
		mPlayerScoreText.SetString(std::to_string(newScore));
	}
	void GamePlayHUD::RefreshHealthBar()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player && !player->GetCurrentSpaceship().expired()) {
			weak<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
			playerSpaceship.lock()->onActorDestoryed.BindAction(GetWeakRef(), &GamePlayHUD::PlayerSpaceshipDestoryed);
			HealthComponent& healthComp = player->GetCurrentSpaceship().lock()->GetHealthComp();
			healthComp.onHealthChanged.BindAction(GetWeakRef(), &GamePlayHUD::PlayerHealthUpdated);
			PlayerHealthUpdated(0, healthComp.GetHealth(), healthComp.GetMaxHealth());
		}
	}
	void GamePlayHUD::ConnectPlayerStatus()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player) {
			int lifeCount = player->GetLifeCount();
			mPlayerLifeText.SetString(std::to_string(lifeCount));
			player->onLifeChange.BindAction(GetWeakRef(), &GamePlayHUD::PlayerLifeCountUpdate);

			int playerScore = player->GetScore();
			mPlayerScoreText.SetString(std::to_string(playerScore));
			player->onScoreChange.BindAction(GetWeakRef(), &GamePlayHUD::PlayerScoreUpdated);

		}
	}
	void GamePlayHUD::PlayerSpaceshipDestoryed(Actor* actor)
	{
		RefreshHealthBar();
	}
	void GamePlayHUD::RestartButtonCliked()
	{
		onRestartBtnClicked.Broadcast();
	}
	void GamePlayHUD::QuitButtonCliked()
	{
		onQuitBtnClicked.Broadcast();
	}
	void GamePlayHUD::GameFinished(bool playerWon)
	{
		mWinLoseText.SetVisibility(true);
		mFinalScoreText.SetVisibility(true);
		mRestartButton.SetVisibility(true);
		mQuitButton.SetVisibility(true);

		int score = PlayerManager::Get().GetPlayer()->GetScore();
		mFinalScoreText.SetString("score: " + std::to_string(score));



		if (playerWon) {
			mWinLoseText.SetString("You Win!");
		}
		else {
			mWinLoseText.SetString("You Lose!");
		}

		mWinLoseText.SetWidgetLocation({ mWindowSize.x / 2.f - mWinLoseText.GetBound().width / 2, 100.f });
		mFinalScoreText.SetWidgetLocation({ mWindowSize.x / 2.f - mFinalScoreText.GetBound().width / 2, 200.f });

	}
}

