#include "widgets/TextWidget.h"
#include "framework/AssetManager.h"

namespace ly {
	TextWidget::TextWidget(const std::string& textStr, const std::string& fontPath, unsigned int characterSize)
		:mFont{AssetManager::Get().LoadFont(fontPath)},
		mText{textStr, *(mFont.get()), characterSize } {

	}

	void TextWidget::SetString(const std::string& newString)
	{
		mText.setString(newString);
	}

	void TextWidget::SetSize(unsigned int newSize)
	{
		mText.setCharacterSize(newSize);
	}

	void TextWidget::LocationUpdated(const sf::Vector2f& newLocation)
	{
		mText.setPosition(newLocation);
	}

	void TextWidget::RotationUpdated(float newRotation)
	{
		mText.setRotation(newRotation);
	}

	void TextWidget::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mText);
	}

}



