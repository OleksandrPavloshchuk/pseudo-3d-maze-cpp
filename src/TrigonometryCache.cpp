/**
 * TrigonometryCache.cpp
 */
 
#include "TrigonometryCache.hpp"

#include <map>
#include <cmath>

using DoubleMap = std::map<double, double>;

DoubleMap cosMap;
DoubleMap sinMap;

typedef double DoubleToDouble(double);

double getCached(double key, DoubleMap &map, DoubleToDouble func) {

	DoubleMap::const_iterator pos = map.find(key);
	if (pos == map.end()) {
		double val = func(key);
		map[key] = val;
		return val;
	} else {
		return pos->second;
	}
}

double cachedSin(double n) {
	return getCached(n, sinMap, std::sin);
}

double cachedCos(double n) {
	return getCached(n, cosMap, std::cos);
}
