/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef PROFILER_H_
#define PROFILER_H_

#include "Timer.h"
#include <string>
#include <map>

namespace IVGFX {

class Profiler {
public:
	Profiler();
	virtual ~Profiler();

	virtual Timer& getTimer(const std::string& name);
	virtual void reset();
	virtual void printStats() const;

private:
	std::map<std::string, Timer*> timers;
};

} /* namespace IVGFX */

inline IVGFX::Profiler::Profiler() {
}

inline IVGFX::Profiler::~Profiler() {
	for (std::map<std::string, Timer*>::iterator it = timers.begin(); it != timers.end(); it++) {
		delete it->second;
	}
}

inline IVGFX::Timer& IVGFX::Profiler::getTimer(const std::string& name) {
	std::map<std::string, Timer*>::iterator it = timers.find(name);
	if (it == timers.end()) {
		Timer* timer = new Timer();
		timers[name] = timer;
		return *timer;
	}

	return *it->second;
}

inline void IVGFX::Profiler::reset() {
	for (std::map<std::string, Timer*>::const_iterator it = timers.begin(); it != timers.end(); it++) {
		it->second->reset();
	}
}

inline void IVGFX::Profiler::printStats() const {
	for (std::map<std::string, Timer*>::const_iterator it = timers.begin(); it != timers.end(); it++) {
		Timer* timer = it->second;
		std::cout << it->first << " "
				<< timer->getTotalTime() << " "
				<< timer->getNumIterations() << " "
				<< timer->getAverageDuration() << " "
				<< timer->getLastDuration() << std::endl;
	}
}

#endif /* PROFILER_H_ */
