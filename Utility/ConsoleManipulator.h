#pragma once

#include <Windows.h>
#include <string>
#include "Point2.h"
#include "ConsoleColor.h"

class ConsoleManipulator {
public:
	static ConsoleManipulator& instance();

	void setTextColor(ConsoleColor color);
	void setBackgroundColor(ConsoleColor color);
	ConsoleColor getTextColor() const;
	ConsoleColor getBackgroundColor() const;

	// По какой-то странной неведомой причине иногда 
	// настройки консоли сбрасываются.
	// Данный метод нужен для возврата настроек у нужным
	void updateConsole();

	void putString(const std::string& string);
	
	void setCursorPosition(Point2 cursorPos);
	Point2 getCursorPosition() const;
	RECT getConsoleRect() const;
	void clear() const;
	void showCursor(bool);

	~ConsoleManipulator();

private:

	COORD getCoord();

	ConsoleManipulator();

	HANDLE m_consoleOutputHandle;
	HANDLE m_consoleInputHandle;
	ConsoleColor m_backgroundColor;
	ConsoleColor m_textColor;
	Point2 m_cursorPos;

	DWORD m_oldMode;
};