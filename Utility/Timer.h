#pragma once 

#include <cstdint>
#include <ctime>

class Timer
{
public:
	Timer();
	void start();
	void stop();
	bool loop(double seconds);
	std::size_t getElapsedTicks() const;
	std::size_t getElapsedSeconds() const;
private:
	std::size_t m_startTime;
	bool m_isActive;
};