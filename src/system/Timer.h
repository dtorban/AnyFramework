/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "System.h"

namespace IVGFX {

class Timer {
public:
	Timer();
	virtual ~Timer() {}

	virtual void reset();
	virtual void start();
	virtual void stop();
	virtual double getLastDuration() const;
	virtual double getAverageDuration() const;
	virtual double getTotalTime() const;
	virtual long getNumIterations() const;

private:
	double startTime;
	double lastDuration;
	long numIterations;
	double totalTime;
};

inline IVGFX::Timer::Timer() {
	reset();
}

inline void IVGFX::Timer::start() {
	startTime = System::getTime();
}

inline void IVGFX::Timer::stop() {
	double stopTime = System::getTime();
	lastDuration = stopTime - startTime;
	totalTime += lastDuration;
	numIterations++;
}

inline double IVGFX::Timer::getLastDuration() const {
	return lastDuration;
}

inline double IVGFX::Timer::getAverageDuration() const {
	return totalTime / (1.0*numIterations);
}

inline double Timer::getTotalTime() const {
	return totalTime;
}

inline void Timer::reset() {
	startTime = 0.0;
	numIterations = 0;
	totalTime = 0.0;
	lastDuration = 0.0;
}

inline long Timer::getNumIterations() const {
	return numIterations;
}

} /* namespace IVGFX */



#endif /* TIMER_H_ */
