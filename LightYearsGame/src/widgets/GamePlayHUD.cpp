#include "widgets/GamePlayHUD.h"
#include "widgets/HUD.h"

namespace ly {
	GamePlayHUD::GamePlayHUD()
		:mFrameRateText{"Frame Rate:"},
		mPlayerHealtBar{} {
		mFrameRateText.SetSize(30);
	}
	void GamePlayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mFrameRateText.NativeDraw(windowRef);
		mPlayerHealtBar.NativeDraw(windowRef);
	}
	void GamePlayHUD::Tick(float deltaTime)
	{
		int frameRate = int(1 / deltaTime);
		std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
		mFrameRateText.SetString(frameRateStr);
	}
	void GamePlayHUD::Init(const sf::RenderWindow& windowRef)
	{
		auto windowSize = windowRef.getSize();
		mPlayerHealtBar.SetWidgetLocation(sf::Vector2f{ 20.f, windowSize.y - 50.f });
		mPlayerHealtBar.UpdateValue(100.f, 200.f);
	}
}

