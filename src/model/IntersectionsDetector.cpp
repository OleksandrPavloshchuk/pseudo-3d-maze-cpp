/**
 * IntersectionsDetector.cpp
 */
 
#include <cmath> 
#include <optional> 
 
#include "IntersectionsDetector.hpp"

double pow2(double n) {
	return n * n;
}

double IntersectionsDetector::distance(const DoublePoint &p) {
	return sqrt(pow2(p.getX() - player_.position_.getX()) + pow2(p.getY() - player_.position_.getY()));
}


std::vector<Intersection> IntersectionsDetector::calculate() {
	std::vector<Intersection> result;
	
	for (double a = -player_.viewAngleHalfWidth_; a <= player_.viewAngleHalfWidth_; a += player_.viewAngleStep_) {
            const double dx = cos(a + player_.viewAngleMiddle_);
            const double dy = sin(a + player_.viewAngleMiddle_);
            
            std::optional<Intersection> min;	
            for (const auto &c : maze_.getField()) {
            	std::vector<Intersection> intersections = Intersection::getEdgesIntersection(c, player_.position_, dx, dy);
            	for (const auto &i : intersections) {
            		if (c.isWall() && (!min || min->getDistance() > i.getDistance())) {
            			min.emplace(i);
            		}
            	}
            }
            if (min) {
            	result.push_back(*min);
            }
	}
	
	return result;
}
