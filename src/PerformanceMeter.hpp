/**
 * PerromanceMeter.hpp
 */
 
#pragma once

#include <algorithm>
#include <cmath>
#include <vector>

class PerformanceMeter {
public:
	static void init();
	static void startTimeTracking();
	static void stopTimeTracking();	
	static void printReport();
};
