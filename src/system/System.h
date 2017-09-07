/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef IVSYSTEM_H_
#define IVSYSTEM_H_

#ifdef WIN32
	//#include <winsock2.h> // must be included before windows.h
	//#include <windows.h>
	//#include <sys/timeb.h>
#else
	#include <sys/time.h>
#endif

namespace any_fw {

class System {
public:
	virtual ~System() {}

	static void initialize() { instance(); }
	static double getTime(bool absolute = false);

protected:
	static System& instance();

private:
	System();

	void initTime();
	double time(bool absolute);

	double initialTime;
#ifdef WIN32
	//LARGE_INTEGER timeStart;
	//LARGE_INTEGER counterFrequency;
#else
	struct timeval start;
#endif
};

} /* namespace any_fw */



#endif /* IVSYSTEM_H_ */
