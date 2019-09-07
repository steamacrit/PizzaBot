#include "T34_Timer.h"

/**
 * Intialize time value for this object.
 */
T34_Time::T34_Time()
{
    m_time = std::chrono::steady_clock::now();
}

/**
 * Return the seconds that have passed since the object was created.
 */
double T34_Time::GetElapsedSeconds()
{
	std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
	std::chrono::duration<double,std::nano> time_span = end_time - m_time;
	return double(time_span.count()) * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
}

/**
 * Return the milliseconds that have passed since the object was created.
 */
double T34_Time::GetElapsedMilliseconds()
{
	return GetElapsedSeconds() * 1000;
}


/**
 * Initialize the base class by calling base class contructor.
 */
T34_StopWatch::T34_StopWatch()
    : T34_Time()
{

}

/**
 * Updates the time (m_time) with current time.
 */
void T34_StopWatch::Start()
{
    m_time = std::chrono::steady_clock::now();
}

/**
 * Updates stop time (m_stop_time) with current time.
 */
void T34_StopWatch::Stop()
{
    m_stop_time = std::chrono::steady_clock::now();
}

/**
 * Resets time (m_time) & stop time (m_stop_time) with current time.
 */
void T34_StopWatch::Reset()
{
    m_time = m_stop_time = std::chrono::steady_clock::now();

}

/**
 * Checks if parameter time (seconds) has passed since Start() was called.
 */
bool T34_StopWatch::HasPeriodPassedSec(double time)
{
    if (GetElapsedSeconds() >= time)
        return true;

    return false;
}

/**
 * Checks if parameter time (milliseconds) has passed since Start() was called.
 */
bool T34_StopWatch::HasPeriodPassedMilli(double time)
{
    if (GetElapsedMilliseconds() >= time)
        return true;
    
    return false;
}

/**
 * Overrieds base class. Returns the delta time in seconds between m_stop_time & m_time.
 */
double T34_StopWatch::GetElapsedSeconds()
{
	std::chrono::duration<double,std::nano> time_span = m_stop_time - m_time;
	return double(time_span.count()) * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
}

/**
 * Overrieds base class. Returns the delta time in milliseconds between m_stop_time & m_time.
 */
double T34_StopWatch::GetElapsedMilliseconds()
{
	return GetElapsedSeconds() * 1000;
}



/**
 * Initialized state and starts a thread that will call 'function' every 'interval' milliseconds.
 */
T34_CallbackTimer::T34_CallbackTimer(std::function<void(void)> callback_function, uint32_t interval)
    : T34_Time()
{
	m_stop_timer.store(false);

    auto thread_function = 
        [callback_function, interval](std::atomic<bool> * stop_timer)
	    { 
            while (stop_timer->load() == false)
            { 
                auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
                callback_function();
                std::this_thread::sleep_until(x);
            }
        };
	m_thread.reset(new std::thread(thread_function, &m_stop_timer));
}

/**
 * Stops the callback timer thread. The thread cannot be restarted.
 */
void T34_CallbackTimer::Kill()
{
	if (m_thread != nullptr)
    {
		m_stop_timer.store(true);
        m_thread->detach();
    }
		
	m_thread.reset();
}



