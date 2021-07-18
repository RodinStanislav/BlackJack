#pragma once

struct Point2 {
	int x = 0;
	int y = 0;

	Point2() : x(0), y(0) {};
	Point2(int _x, int _y) : x(_x), y(_y) {};
	Point2& operator=(const Point2& point) {
		this->x = point.x;
		this->y = point.y;
		return *this;
	}
};