#pragma once
#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGuage.h"
#include "widgets/ImageWidget.h"
#include "widgets/Button.h"

namespace ly {
	class Actor;
	class GamePlayHUD : public HUD {
	public:
		GamePlayHUD();

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime);
		virtual bool HandleEvent(const sf::Event& event) override;

		void GameFinished(bool playerWon);

		Delegate<> onRestartBtnClicked;
		Delegate<> onQuitBtnClicked;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;
		void PlayerHealthUpdated(float amt, float currentHealth, float maxHealth);
		void PlayerLifeCountUpdate(int amt);
		void PlayerScoreUpdated(int newScore);
		void RefreshHealthBar();
		void ConnectPlayerStatus();
		void PlayerSpaceshipDestoryed(Actor* actor);

		void RestartButtonCliked();
		void QuitButtonCliked();

		TextWidget mFrameRateText;
		ImageWidget mPlayerLifeIcon;
		TextWidget mPlayerLifeText;

		ImageWidget mPlayerScoreIcon;
		TextWidget mPlayerScoreText;

		ValueGuage mPlayerHealtBar;
		sf::Color mHealthyHealthBarColor;
		sf::Color mCriticalHealthBarColor;
		float mCriticalThreshold;

		float mWidgetSpacing;

		TextWidget mWinLoseText;
		TextWidget mFinalScoreText;
		Button mRestartButton;
		Button mQuitButton;

		sf::Vector2u mWindowSize;

	};
}