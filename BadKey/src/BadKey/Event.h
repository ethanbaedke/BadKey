#pragma once

#include "Engine.h"
#include "IPrintable.h"

#include <functional>

namespace BadKey {

	class BK_API Event : IPrintable
	{
	public:
		virtual std::string GetPrintable() const override;

	protected:
		Event();
		bool m_Handeled;

	};

	enum class ButtonInteraction : char
	{
		ButtonDown,
		ButtonUp
	};

	class BK_API KeyboardEvent : public Event
	{
	public:
		KeyboardEvent(int keyCode, ButtonInteraction interactionType);
		virtual std::string GetPrintable() const override;

	private:
		int m_KeyCode;
		ButtonInteraction m_InteractionType;
	};

	class BK_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float deltaX, float deltaY);
		virtual std::string GetPrintable() const override;

	private:
		float m_deltaX, m_deltaY;
	};

	class BK_API MouseClickEvent : public Event
	{
	public:
		MouseClickEvent(int buttonNumber, ButtonInteraction interactionType);
		virtual std::string GetPrintable() const override;

	private:
		int m_ButtonNumber;
		ButtonInteraction m_InteractionType;
	};

}

