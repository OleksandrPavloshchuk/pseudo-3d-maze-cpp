/**
 * Intersection.cpp
 */
 
#include <cmath> 
#include <iostream>
 
#include "../constants.hpp"
#include "Point.hpp"
#include "Intersection.hpp"

double Intersection::getTextureX() const {
	return floor(getOffset() - getEdgeStart());
}

double Intersection::getOffset() const {
	return base_.isHorizontal()
	        ? base_.point_.getX()
	        : base_.point_.getY();
}

double Intersection::getEdgeStart() const {
	return base_.isHorizontal()
	        ? cell_.getCenter().getX() - TEXTURE_SIZE / 2
	        : cell_.getCenter().getY() - TEXTURE_SIZE / 2;
}

std::vector<IntersectionBase> calculateVerticalEdgesIntersection(const MazeCell &cell, const DoublePoint &p) {
	return {
		IntersectionBase(DoublePoint(cell.x0(), p.getY()), Edge::VERTICAL),
		IntersectionBase(DoublePoint(cell.x1(), p.getY()), Edge::VERTICAL)
	};
}

std::vector<IntersectionBase> calculateHorizontalEdgesIntersection(const MazeCell &cell, const DoublePoint &p) {
	return {
		IntersectionBase(DoublePoint(p.getX(), cell.y0()), Edge::HORIZONTAL),
		IntersectionBase(DoublePoint(p.getX(), cell.y1()), Edge::HORIZONTAL)
	};
}

IntersectionBase intersectVertical(
	const DoublePoint &p,
	double dx,
	double dy,
	double x
) {
	return IntersectionBase(
		DoublePoint(x, p.getY() + (x - p.getX()) * dy / dx), 
		Edge::VERTICAL
	);
}

IntersectionBase intersectHorizontal(
	const DoublePoint &p,
	double dx,
	double dy,
	double y
) {
	return IntersectionBase(
		DoublePoint(p.getX() + (y - p.getY()) * dx / dy, y), 
		Edge::HORIZONTAL
	);
}

bool isOnRay(const DoublePoint &src, const DoublePoint &p, double dx, double dy) {
	return (p.getX() - src.getX()) * dx + (p.getY() - src.getY()) * dy >= 0;
}

std::vector<IntersectionBase> Intersection::getEdgesIntersection(
	const MazeCell &cell,
        const DoublePoint &src,
        const double dx,
        const double dy
) {
	std::vector<IntersectionBase> all;
	if (areEqual(dx, 0)) {
		all = calculateHorizontalEdgesIntersection(cell, src);
	} else if (areEqual(dy, 0)) {
		all = calculateVerticalEdgesIntersection(cell, src);
	} else {
		all.push_back(intersectVertical(src, dx, dy, cell.x0()));
		all.push_back(intersectVertical(src, dx, dy, cell.x1()));
		all.push_back(intersectHorizontal(src, dx, dy, cell.y0()));
		all.push_back(intersectHorizontal(src, dx, dy, cell.y1()));
	}
	
	std::vector<IntersectionBase> result;
	for (const auto& i : all) {
    		if (cell.isOnEdge(i.point_) && isOnRay(src, i.point_, dx, dy)) {
			result.push_back(i);
		}
	}
	return result;	
}
