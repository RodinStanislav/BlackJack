#include "ConsoleManipulator.h"
#include <iostream>
#include <winuser.h>

ConsoleManipulator& ConsoleManipulator::instance() {
	static ConsoleManipulator manipulator;
	return manipulator;
}

void ConsoleManipulator::setTextColor(ConsoleColor color) {
	m_textColor = color;
	SetConsoleTextAttribute(m_consoleOutputHandle, (WORD)((m_backgroundColor << 4) | m_textColor));
}

void ConsoleManipulator::setBackgroundColor(ConsoleColor color) {
	m_backgroundColor = color;
	SetConsoleTextAttribute(m_consoleOutputHandle, (WORD)((m_backgroundColor << 4) | m_textColor));
}

void ConsoleManipulator::putString(const std::string& string) {
	std::cout << string;
}

void ConsoleManipulator::updateConsole() {
	DWORD mode;
	mode = m_oldMode;
	mode |= ENABLE_WINDOW_INPUT;		// �������� �������������� � �����
	mode |= ENABLE_EXTENDED_FLAGS;		// �������� ����������� ���� (��� ������ �����������
	mode &= ~ENABLE_QUICK_EDIT_MODE;	// ��������� ����������� �����
	SetConsoleMode(m_consoleInputHandle, mode);

	CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
	GetConsoleScreenBufferInfo(m_consoleOutputHandle, &screenBuffer);

	short winWidth = screenBuffer.srWindow.Right - screenBuffer.srWindow.Left + 1;
	short winHeight = screenBuffer.srWindow.Bottom - screenBuffer.srWindow.Top + 1;

	short scrWidth = screenBuffer.dwSize.X;
	short scrHeight = screenBuffer.dwSize.Y;

	COORD newSize;
	newSize.X = scrWidth;
	newSize.Y = winHeight;

	SetConsoleScreenBufferSize(m_consoleOutputHandle, newSize);
}

ConsoleColor ConsoleManipulator::getTextColor() const {
	return m_textColor;
}

ConsoleColor ConsoleManipulator::getBackgroundColor() const {
	return m_backgroundColor;
}

void ConsoleManipulator::setCursorPosition(Point2 cursorPos) {
	// ��� ��������� �������� ������� �������, ��� �� ����� ����� �� X
	// ��� ����������� ���������� 800 �� 600 ��� ����� = 80

	m_cursorPos = cursorPos;
	SetConsoleCursorPosition(m_consoleOutputHandle, getCoord());
}

Point2 ConsoleManipulator::getCursorPosition() const {
	return m_cursorPos;
}

ConsoleManipulator::~ConsoleManipulator() {
	SetConsoleMode(m_consoleInputHandle, m_oldMode);
}

COORD ConsoleManipulator::getCoord() {
	COORD coord;
	coord.X = m_cursorPos.x;
	coord.Y = m_cursorPos.y;
	return coord;
}

void ConsoleManipulator::clear() const {
	system("cls");
}

RECT ConsoleManipulator::getConsoleRect() const {
	RECT rect;
	HWND hWnd = GetConsoleWindow();
	GetWindowRect(hWnd, &rect);
	return rect;
}

ConsoleManipulator::ConsoleManipulator() {
	// �������� ����������� �������
	// Std_input ��� ��������� ���� � ����������
	m_consoleInputHandle = GetStdHandle(STD_INPUT_HANDLE);

	// Std_output ��� ������ ������
	m_consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTitleA("BlackJack");

	// ���������� ���� �������
	int x = (GetSystemMetrics(SM_CXSCREEN) - 800) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - 600) / 2;

	HWND consoleHWnd = GetConsoleWindow();
	SetWindowPos(consoleHWnd, HWND_TOP, x, y,
				 800, 600, NULL);

	// ���������� ������ �����
	// ����� �������� ���� ���������� ��� �� ����� (� �����������)
	
	GetConsoleMode(m_consoleInputHandle, &m_oldMode);
	updateConsole();

	// �������� ������
	showCursor(false);

	m_backgroundColor = ConsoleColor::Black;
	m_textColor = ConsoleColor::White;
	m_cursorPos = Point2(0, 0);
}

void ConsoleManipulator::showCursor(bool isShow) {
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(m_consoleOutputHandle, &structCursorInfo);
	structCursorInfo.bVisible = isShow;
	SetConsoleCursorInfo(m_consoleOutputHandle, &structCursorInfo);
}


	