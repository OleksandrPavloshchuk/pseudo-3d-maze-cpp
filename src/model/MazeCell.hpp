/**
 * MazeCell.hpp
 */
 
#pragma once

#include "../constants.hpp"
#include "Point.hpp"

enum class MazeCellType {
	EMPTY, 
	WALL, 
	WINDOW, 
	PICTURE, 
	EXIT_DOOR
};

class MazeCell {
public:
	MazeCell(
		const IntPoint &index,
		const DoublePoint &center,
		const MazeCellType &type
	):
		index_(index),
		center_(center),
		type_(type)
	{
	}
	
	IntPoint getIndex() const { return index_; }
	
	DoublePoint getCenter() const { return center_; }
	
	MazeCellType getType() const { return type_; }	
	
	bool isWall() const {return type_ != MazeCellType::EMPTY;}
	
	bool isCollided(const DoublePoint &pos, double gap) const;
	
    	double x0() const { return center_.getX() - TEXTURE_SIZE / 2; }
    	double x1() const { return center_.getX() + TEXTURE_SIZE / 2; }
    	double y0() const { return center_.getY() - TEXTURE_SIZE / 2; }
    	double y1() const { return center_.getY() + TEXTURE_SIZE / 2; }		
    	
    	bool isOnEdge(const DoublePoint &p) const;
	
private:
	const IntPoint index_;
	const DoublePoint center_;
	const MazeCellType type_;
};
