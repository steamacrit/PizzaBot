#pragma once

#include <ctime>
#include <chrono>
#include <atomic>
#include <thread>
#include <functional>

typedef struct T34_TIMER T34_TIMER;

class T34_Time 
{
public: // PUBLIC METHODS
    T34_Time();

	
	virtual double GetElapsedSeconds();
	virtual double GetElapsedMilliseconds();

protected: // PROTECTED DATA
    std::chrono::steady_clock::time_point m_time;
};

class T34_StopWatch : public T34_Time
{
public: 
    T34_StopWatch();

    void Start();
    void Stop();
    void Reset();
    bool HasPeriodPassedSec(double time);
    bool HasPeriodPassedMilli(double time);

	double GetElapsedSeconds() override;
	double GetElapsedMilliseconds() override;

protected: // PROTECTED DATA
    std::chrono::steady_clock::time_point m_stop_time;
};

class T34_CallbackTimer : public T34_Time
{
public: // PUBLIC METHODS
	T34_CallbackTimer(std::function<void(void)> callback_function, uint32_t interval);

	void Kill();

	
private:
   	std::atomic<bool> m_stop_timer;
	std::unique_ptr<std::thread> m_thread;
};