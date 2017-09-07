#include "system/System.h"
#include <iostream>

#if defined(WIN32)
#include <windows.h>
DWORD     g_starttime2 = GetTickCount();
;
float getElapsedSeconds() {
	DWORD now = GetTickCount();
	DWORD elapsed = now - g_starttime2;
	return (float)((double)elapsed / (double)1000.0);
}
#endif

namespace IVGFX {

	// Adapted from G3D (https://sourceforge.net/p/g3d/code/HEAD/tree/G3D10/G3D.lib/source/System.cpp#l915)
	void System::initTime() {
#if defined(WIN32)
		/* if (QueryPerformanceFrequency(&counterFrequency)) {
		QueryPerformanceCounter(&timeStart);
		}

		struct _timeb t;
		_ftime(&t);

		initialTime = (double)t.time - t.timezone * 60 + (t.dstflag ? 60*60 : 0);*/

#else
		gettimeofday(&start, NULL);
		// "sse" = "seconds since epoch".  The time
		// function returns the seconds since the epoch
		// GMT (perhaps more correctly called UTC).
		time_t gmt = ::time(NULL);

		// No call to free or delete is needed, but subsequent
		// calls to asctime, ctime, mktime, etc. might overwrite
		// local_time_vals.
		tm* localTimeVals = localtime(&gmt);

		time_t local = gmt;

		if (localTimeVals) {
			// tm_gmtoff is already corrected for daylight savings.
			local = local + localTimeVals->tm_gmtoff;
		}

		initialTime = local;
#endif
	}

	// Adapted from G3D (https://sourceforge.net/p/g3d/code/HEAD/tree/G3D10/G3D.lib/source/System.cpp#l915)
	double System::time(bool absolute) {
		double timeOffset = 0.0;
		if (absolute) {
			timeOffset = initialTime;
		}

#if defined(WIN32)


		/* LARGE_INTEGER now;
		QueryPerformanceCounter(&now);

		return ((double)(now.QuadPart - timeStart.QuadPart) /
		counterFrequency.QuadPart) + timeOffset;*/
		return getElapsedSeconds();
#else
		// Linux resolution defaults to 100Hz.
		// There is no need to do a separate RDTSC call as gettimeofday
		// actually uses RDTSC when on systems that support it, otherwise
		// it uses the system clock.
		struct timeval now;
		gettimeofday(&now, NULL);

		return (now.tv_sec - start.tv_sec) +
			(now.tv_usec - start.tv_usec) / 1e6 + timeOffset;
#endif
	}

	double System::getTime(bool absolute) {
		return instance().time(absolute);
	}

	System& System::instance() {
		static System system;
		return system;
	}

	System::System() {
		initTime();
	}
}
