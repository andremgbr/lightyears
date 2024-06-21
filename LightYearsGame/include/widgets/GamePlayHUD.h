#pragma once
#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGuage.h"

namespace ly {
	class GamePlayHUD : public HUD {
	public:
		GamePlayHUD();

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime);

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;
		TextWidget mFrameRateText;
		ValueGuage mPlayerHealtBar;
	};
}