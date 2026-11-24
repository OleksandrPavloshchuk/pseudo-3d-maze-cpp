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

struct IntersectionBase {
	IntersectionBase(
		const DoublePoint &point,
		const Edge edge	
	):
		point_(point),
		edge_(edge)
	{
	}
	
	bool isHorizontal() const { return edge_==Edge::HORIZONTAL; }
	
	const DoublePoint point_;
	const Edge edge_;
};

class Intersection {
public:
	Intersection(
		const IntersectionBase &base,
		const MazeCell &cell,
		double a,
		double dx, 
		double dy,
		double distance
	):
		base_(base),
		a_(a),
		dx_(dx),
		dy_(dy),
		distance_(distance),
		cell_(cell)
	{
	}

	double getA() const { return a_; }
	double getDx() const { return dx_; }
	double getDy() const { return dy_; }
	double getDistance() const { return distance_; }
	const MazeCell& getCell() const { return cell_; }
	
	double getTextureX() const;
	
	DoublePoint getPoint() const { return base_.point_; }
	
	static std::vector<IntersectionBase> getEdgesIntersection(
		const MazeCell &cell,
        	const DoublePoint &src,
        	const double dx,
        	const double dy
    	);

private:
    	double getOffset() const;
    	double getEdgeStart() const;
    	
    	const IntersectionBase base_;

	double a_;
	double dx_;
	double dy_;
	double distance_;
	const MazeCell cell_;	
	
};
