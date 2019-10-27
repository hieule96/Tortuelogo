#pragma once

#include "Item.hpp"
#include "../Hitbox/Hitbox.hpp"
#include "../Shape/Point.hpp"

class Obstacle:public Item{
private:
	double height;
	double width;
	Point coordonnees;
	double direction;
	Hitbox hitbox;
public:
	Obstacle(double h,double w,double x_r=0,double y_a=0,double dir=0):
		height(h),width(w),coordonnees(Point(x_r,y_a)),direction(dir),hitbox(Hitbox(this->coordonnees,h,w,dir)){}

	double getHeight() override{
		return this->height;
	}

	double getWidth() override{
		return this->width;
	}

	void setHeight(double h) override{
		std::cout<<"obstacles can not change their height"<<std::endl;
	}

	void setWidth(double w) override{
		std::cout<<"obstacles can not change their width"<<std::endl;
	}

	double getDirection() override{
		return this->direction;
	}

	Hitbox getHitbox() override{
		return this->hitbox;
	}

	Point getCoordonnees() override{
		return this->coordonnees;
	}

	DRAWINGTYPE getDessin() override{
		return LEVER;
	}

	//on pourra rajouter cette fonctionnalite aux obstacles si on veut
	void setDessin(DRAWINGTYPE dessin) override{
		std::cout<<"obstacles can not draw"<<std::endl;
	}
	
	//on pourra rajouter cette fonctionnalite aux obstacles si on veut
	void avancer(double dist)override{
		std::cout<<"obstacles can not move"<<std::endl;
	};

	//on pourra rajouter cette fonctionnalite aux obstacles si on veut
	void reculer(double dist)override{
		std::cout<<"obstacles can not move"<<std::endl;
	};

	//on pourra rajouter cette fonctionnalite aux obstacles si on veut
	void tourner(double angle)override{
		std::cout<<"obstacles can not turn"<<std::endl;
	};

	//on pourra rajouter cette fonctionnalite aux obstacles si on veut
	void poser(double x_r, double y_a) override{
		this->coordonnees = Point(x_r, y_a);
		hitbox = Hitbox(this->coordonnees,this->height,this->width,this->direction);
	}

	//methode permettant d afficher tout item grace a <<
	void print(std::ostream &f) const override{
		f<<"Obstacle: Height("<<height<<"), Width("<<width<<")"<<std::endl;
		f << "Position: " << this->coordonnees << ", Direction: " << this->direction << std::endl;
		f << "Hitbox: " << this->hitbox << std::endl;
	}

	~Obstacle() {std::cout<<"delete obstacle"<<std::endl;}
};
