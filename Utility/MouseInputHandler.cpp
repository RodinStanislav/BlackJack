#include "MouseInputHandler.h"
#include "ConsoleManipulator.h"
#include "../Utility/Point2.h"
#include <Windows.h>

MouseInputHandler& MouseInputHandler::instance() {
	static MouseInputHandler handler;
	return handler;
}

Point2 MouseInputHandler::getClickedCell() const {
	return m_lastPosition;
}

MouseInputHandler::MouseInputHandler() : m_lastPosition(0, 0) {}

Point2 MouseInputHandler::getSymbolOffset() const {
	// размер символа (примерный)
	return Point2(9, 13);
}

Point2 MouseInputHandler::getCursorPosition() const {
	POINT cursor;
	RECT rect = ConsoleManipulator::instance().getConsoleRect();
	GetCursorPos(&cursor);

	// 7:30 - непонятный стандартный оффсет
	// Конвертируем координаты мыши из пространства монитора в 
	// пространство консоли
	return Point2(cursor.x - rect.left - 7, cursor.y - rect.top - 30);
}

bool MouseInputHandler::waitInputCursorPosition() {
	while (true) {
		// Если нажата левая кнопка мыши
		if (GetKeyState(VK_LBUTTON) & 0x8000) {
			m_lastPosition = getCursorPosition();
			return true;
		}
	}
}