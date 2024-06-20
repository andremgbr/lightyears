#include "widgets/Widget.h"

namespace ly {
	void Widget::NativeDraw(sf::RenderWindow& windowRef) {
		if (mIsVisible) {
			Draw(windowRef);
		}
	}

	bool Widget::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	void Widget::SetWidgetLocation(const sf::Vector2f& newLocation)
	{
		mWindgetTransform.setPosition(newLocation);
		LocationUpdated(newLocation);
	}

	void Widget::SetWidgetRotation(float newRotation)
	{
		mWindgetTransform.setRotation(newRotation);
		RotationUpdated(newRotation);
	}

	void Widget::SetVisiblity(bool newVisibility)
	{
		mIsVisible = newVisibility;
	}

	Widget::Widget()
		:mIsVisible{ true }, 
		mWindgetTransform{} {
	}

	void Widget::Draw(sf::RenderWindow& windowRef)
	{
	}

	void Widget::LocationUpdated(const sf::Vector2f& newLocation)
	{
	}

	void Widget::RotationUpdated(float newRotation)
	{
	}

}


