#pragma once

#include"../Hitbox/Hitbox.hpp"
#include"../Shape/Point.hpp"


//Interface Item
class Item{
public:
	virtual double getHeight()=0;
	virtual double getWidth()=0;
	virtual void setHeight(double h)=0;
	virtual void setWidth(double w)=0;
	virtual double getDirection()=0;
	virtual Hitbox getHitbox()=0;
	virtual Point getCoordonnees()=0;
	virtual DRAWINGTYPE getDessin()=0;
	virtual void setDessin(DRAWINGTYPE dessin)=0;
	virtual void avancer(double dist)=0;
	virtual void reculer(double dist)=0;
	virtual void tourner(double angle)=0;
	virtual void poser(double x_r, double y_a)=0;
	virtual void print(std::ostream &f) const=0;
	friend std::ostream&operator<<(std::ostream &f, const Item *i){
		i->print(f);
    	return f;
	}
	virtual ~Item(){}
};
