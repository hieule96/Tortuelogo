#pragma once

#include"../Shape/Point.hpp"

enum DRAWINGTYPE{
	AUTRE,
    LEVER,
    DESSIN,
    GOMME
};

class Info{
private:
	Point pO;
	Point pE;
	int size;
	double direction;
	DRAWINGTYPE dessin;
public:
	Info(Point p1 = Point(-15,0),Point p2 = Point(15,0), int size = 30, double dir = 0, DRAWINGTYPE dessin = AUTRE):
	pO(p1),pE(p2),size(size),direction(dir),dessin(dessin){}
	
	Point getPO() const{
		return this->pO;
	}

	Point getPE() const{
		return this->pE;
	}

	int getSize() const{
		return this->size;
	}

	int getDirection() const{
		return this->direction;
	}

	DRAWINGTYPE getDessin() const{
		return this->dessin;
	}
};
