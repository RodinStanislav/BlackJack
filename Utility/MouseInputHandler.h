#pragma once

#include "Point2.h"

class MouseInputHandler {
public:
	static MouseInputHandler& instance();

	Point2 getClickedCell() const;
	bool waitInputCursorPosition();

private:
	MouseInputHandler();
	Point2 getSymbolOffset() const;
	Point2 getCursorPosition() const;

	Point2 m_lastPosition;
};