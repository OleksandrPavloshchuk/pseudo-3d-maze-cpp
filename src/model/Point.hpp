/**
 * Point.hpp
 */
 
#pragma once

template <typename T> class Point {
public:
	Point(
		T x,
		T y
	):
		x_(x),
		y_(y)
	{}
	
	inline T getX() const { return x_; }
	inline T getY() const { return y_; }
	
	inline void setX(T x) { this.x_ = x; }
	inline void setY(T y) { this.y_ = y; }

private:
	T x_;
	T y_;	
};

using IntPoint = Point<int>;
using DoublePoint = Point<double>;

bool areEqual(double a, double b);
