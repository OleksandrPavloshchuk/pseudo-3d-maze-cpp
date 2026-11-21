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
	
	T getX() const { return x_; }
	T getY() const { return y_; }
	
	void setX(T x) { x_ = x; }
	void setY(T y) { y_ = y; }

private:
	T x_;
	T y_;	
};

using IntPoint = Point<int>;
using DoublePoint = Point<double>;

bool areEqual(double a, double b);
