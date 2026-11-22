/**
 * Intersection.hpp
 */
 
#pragma once

#include <vector>

#include "Point.hpp"
#include "MazeCell.hpp"

enum class Edge {
	HORIZONTAL, 
	VERTICAL
};

class Intersection {
public:
	Intersection(
		const DoublePoint &point,
		const Edge edge	
	):
		point_(point),
		edge_(edge)
	{
	}

	double getA() const { return a_; }
	double getDx() const { return dx_; }
	double getDy() const { return dy_; }
	double getDistance() const { return distance_; }
	MazeCell *getCell() const { return cell_; }
	
	double getTextureX() const;
	
	void enrich(
        	double a,
        	double dx,
        	double dy,
        	MazeCell *cell,
	        double distance	
	);
	
	DoublePoint getPoint() const { return point_; }
	
	static std::vector<Intersection> getEdgesIntersection(
		const MazeCell &cell,
        	const DoublePoint &src,
        	const double dx,
        	const double dy
    	);

private:
    	double getOffset() const;
    	double getEdgeStart() const;

	double a_;
	double dx_;
	double dy_;
	double distance_;
	const DoublePoint point_;
	const Edge edge_;
	MazeCell *cell_;	
	
};
