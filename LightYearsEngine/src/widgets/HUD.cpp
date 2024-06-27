#include "widgets/HUD.h"

namespace ly {
	void HUD::NativeInit(const sf::RenderWindow& windowsRef)
	{
		if (!mAlreadyInit) {
			mAlreadyInit = true;
			Init(windowsRef);
		}
	}
	bool HUD::HandleEvent(const sf::Event& event)
	{
		return false;
	}
	HUD::HUD()
		: mAlreadyInit{ false } {
	}
	void HUD::Init(const sf::RenderWindow& windowRef)
	{
	}
	void HUD::Tick(float deltaTime) {

	}
}
