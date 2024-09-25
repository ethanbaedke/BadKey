#include "Event.h"

#define DEBUG_EVENT(typeName) std::string("Event: type = \"") + typeName + "\""

#define DEBUG_BUTTON_INTERACTION(interactionType, outString) \
	switch (interactionType) \
	{ \
	case ButtonInteraction::ButtonDown: \
		outString = "KeyDown"; \
		break; \
	case ButtonInteraction::ButtonUp: \
		outString = "KeyUp"; \
		break; \
	}

std::string BadKey::Event::GetPrintable() const
{
	return DEBUG_EVENT("Event");
}

BadKey::Event::Event()
	: m_Handeled(false)
{
}

BadKey::KeyboardEvent::KeyboardEvent(int keyCode, ButtonInteraction interactionType)
	: m_KeyCode(keyCode), m_InteractionType(interactionType)
{
}

std::string BadKey::KeyboardEvent::GetPrintable() const
{	
	std::string interaction;
	DEBUG_BUTTON_INTERACTION(m_InteractionType, interaction);
	return DEBUG_EVENT("KeyboardEvent") + ", KeyCode = " + std::to_string(m_KeyCode) + ", InteractionType = \"" + interaction + "\"";
}

BadKey::MouseMoveEvent::MouseMoveEvent(float deltaX, float deltaY)
	: m_deltaX(deltaX), m_deltaY(deltaY)
{
}

std::string BadKey::MouseMoveEvent::GetPrintable() const
{
	return DEBUG_EVENT("MouseMoveEvent") + ", DeltaX = " + std::to_string(m_deltaX) + ", DeltaY = " + std::to_string(m_deltaY);
}

BadKey::MouseClickEvent::MouseClickEvent(int buttonNumber, ButtonInteraction interactionType)
	: m_ButtonNumber(buttonNumber), m_InteractionType(interactionType)
{
}

std::string BadKey::MouseClickEvent::GetPrintable() const
{
	std::string interaction;
	DEBUG_BUTTON_INTERACTION(m_InteractionType, interaction);
	return DEBUG_EVENT("KeyboardEvent") + ", ButtonNumber = " + std::to_string(m_ButtonNumber) + ", InteractionType = \"" + interaction + "\"";
}
