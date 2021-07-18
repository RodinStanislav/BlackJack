#include "Timer.h"

Timer::Timer() {
	m_startTime = 0;
	m_isActive = false;
}

void Timer::start() {
	m_startTime = static_cast<std::size_t>(clock());
	m_isActive = true;
	return;
}

void Timer::stop() {
	m_startTime = 0;
	m_isActive = false;
	return;
}

bool Timer::loop(double delay) {
	if (static_cast<std::size_t>(clock()) >= (m_startTime + delay * 1000)) {
		m_startTime = (unsigned int)clock();
		return true;
	}

	return false;
}

std::size_t Timer::getElapsedTicks() const {
	return static_cast<std::size_t>(clock()) - m_startTime;
}

std::size_t Timer::getElapsedSeconds() const {
	return (static_cast<std::size_t>(clock()) - m_startTime) / CLOCKS_PER_SEC;
}