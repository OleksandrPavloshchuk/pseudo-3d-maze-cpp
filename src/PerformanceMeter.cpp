/**
 * PerromanceMeter.cpp
 */
 
#include "PerformanceMeter.hpp"

#include <chrono>
#include <vector>
#include <iostream>

using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::_V2::steady_clock::time_point;

std::vector<double> samples;

TimePoint startTime;

void PerformanceMeter::init() {

}

void PerformanceMeter::startTimeTracking() {
	startTime = Clock::now();
}

void PerformanceMeter::stopTimeTracking() {
	const auto endTime = Clock::now();
	const auto elapsed = std::chrono::duration<double, std::milli>(endTime - startTime).count();
	samples.push_back(elapsed);

}

double median() {
        auto sorted = samples;
        std::sort(sorted.begin(), sorted.end());

        const size_t middle = sorted.size() / 2;

        if (sorted.size() % 2 == 0) {
            return (sorted[middle - 1] + sorted[middle]) / 2.0;
        }

        return sorted[middle];
    }

void PerformanceMeter::printReport() {
	std::cout << "Summary statistics:" << std::endl;
	std::cout << "- median rendering time (ms): " << median() << std::endl;
}
