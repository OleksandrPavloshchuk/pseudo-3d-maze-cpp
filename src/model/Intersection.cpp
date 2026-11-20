/**
 * Intersection.cpp
 */
 
#include <cmath> 
 
#include "../constants.hpp"
#include "Point.hpp"
#include "Intersection.hpp"

void Intersection::enrich(
	double a,
	double dx,
        double dy,
        MazeCell *cell,
	double distance		
) {
	cell_ = cell;
	a_ = a;
	dx_ = dx;
	dy_ = dy;
	distance_ = distance;
}

double Intersection::getTextureX() const {
	return floor(getOffset() - getEdgeStart());
}

double Intersection::getOffset() const {
	return edge_ == Edge::HORIZONTAL
	        ? point_.getX()
	        : point_.getY();
}

double Intersection::getEdgeStart() const {
	return edge_ == Edge::HORIZONTAL
	        ? cell_->getCenter().getX() - TEXTURE_SIZE / 2
	        : cell_->getCenter().getY() - TEXTURE_SIZE / 2;
}

bool isOnRay(const DoublePoint &src, const DoublePoint &p, double dx, double dy) {
    return (p.getX() - src.getX()) * dx + (p.getY() - src.getY()) * dy >= 0;
}

std::vector<Intersection> calculateVerticalEdgesIntersection(const MazeCell &cell, const DoublePoint &p) {
	return {
		Intersection(DoublePoint(cell.x0(), p.getY()), Edge::VERTICAL),
		Intersection(DoublePoint(cell.x1(), p.getY()), Edge::VERTICAL)
	};
}

std::vector<Intersection> calculateHorizontalEdgesIntersection(const MazeCell &cell, const DoublePoint &p) {
	return {
		Intersection(DoublePoint(p.getX(), cell.y0()), Edge::HORIZONTAL),
		Intersection(DoublePoint(p.getX(), cell.y1()), Edge::HORIZONTAL)
	};
}

Intersection intersectVertical(
	const DoublePoint &p,
	double dx,
	double dy,
	double x
) {
	return Intersection(
		DoublePoint(x, p.getY() + (x - p.getY()) * dy / dx), 
		Edge::VERTICAL
	);
}

Intersection intersectHorizontal(
	const DoublePoint &p,
	double dx,
	double dy,
	double y
) {
	return Intersection(
		DoublePoint(p.getX() + (y - p.getX()) * dx / dy, y), 
		Edge::HORIZONTAL
	);
}

std::vector<Intersection> Intersection::getEdgesIntersection(
	const MazeCell &cell,
        const DoublePoint &src,
        const double dx,
        const double dy
) {
	if (areEqual(dx, 0)) {
		return calculateVerticalEdgesIntersection(cell, src);
	}
	if (areEqual(dy, 0)) {
		return calculateHorizontalEdgesIntersection(cell, src);
	}
	std::vector<Intersection> all;
	all.push_back(intersectVertical(src, dx, dy, cell.x0()));
	all.push_back(intersectVertical(src, dx, dy, cell.x1()));
	all.push_back(intersectHorizontal(src, dx, dy, cell.y0()));
	all.push_back(intersectHorizontal(src, dx, dy, cell.y1()));
	
	std::vector<Intersection> result;
	for (const auto& i : all) {
    		if (cell.isOnEdge(i.point_) && isOnRay(src, i.point_, dx, dy)) {
			result.push_back(i);
		}
	}
	return result;	
}
