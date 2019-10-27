#pragma once

#include "../Item/Item.hpp"
#include "../Shape/Point.hpp"
#include "../Hitbox/Hitbox.hpp"

class Robot:public Item{
private:
	double height;
	double width;
	Point coordonnees;
	double direction;
	Hitbox hitbox;
	DRAWINGTYPE dessin;
	Robot(double h, double w,double x_r=0, double y_a=0, double dir=0, DRAWINGTYPE dessin = LEVER):
		height(h),width(w),coordonnees(Point(x_r,y_a)),direction(dir),hitbox(Hitbox(this->coordonnees,h,w,dir)),dessin(dessin){}

public:
	//methode pour construire un singleton
	static Item *InstanceUnique(double h, double w,double x_r=0, double y_a=0, double dir=0){
		static Item *instanceUnique = new Robot(h,w,x_r,y_a,dir);
		return instanceUnique;
	}

	double getHeight() override{
		return this->height;
	}

	double getWidth() override{
		return this->width;
	}

	void setHeight(double h) override{
		this->height=h;
		//maj de hitbox
		this->hitbox = Hitbox(this->coordonnees,this->height,this->width,this->direction);
	}

	void setWidth(double w) override{
		this->width=w;
		//maj de hitbox
		this->hitbox = Hitbox(this->coordonnees,this->height,this->width,this->direction);
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
		return this->dessin;
	}

	void setDessin(DRAWINGTYPE dessin) override{
		this->dessin=dessin;
	}

	/*
    But: Modifie les coordonnees du robot pour avancer puis maj de hitbox
    Antecedent: distance en double
    */
	void avancer(double dist) override{
		//deplacement polaire
		Point delta = Point(dist,this->direction);
		//vecteur cartesien
		delta.conversionCartesien();
		//deplacment sur le vecteur
		coordonnees += delta;
		this->hitbox = Hitbox(this->coordonnees,this->height,this->width,this->direction);
	}

	/*
    But: Modifie les coordonnees du robot pour reculer puis maj de hitbox
    Antecedent: distance en double
    */
	void reculer(double dist) override{
		//deplacement polaire
		Point delta = Point(dist,this->direction+180.0);
		//vecteur cartesien
		delta.conversionCartesien();
		//deplacment sur le vecteur
		coordonnees += delta;
		this->hitbox = Hitbox(this->coordonnees,this->height,this->width,this->direction);
	}

	/*
    But: Modifie la direction du robot puis maj de hitbox
    Antecedent: angle en double
    */
	void tourner(double angle) override{
		this->direction = this->direction+angle;
		this->hitbox = Hitbox(this->coordonnees,this->height,this->width,this->direction);
	}

	/*
    But: Modifie les coordonnees du robot puis maj de hitbox
    Antecedent: x et y en double
    */
	void poser(double x_r, double y_a) override{
		coordonnees = Point(x_r, y_a);
		this->hitbox = Hitbox(this->coordonnees,this->height,this->width,this->direction);
	}

	//methode permettant d afficher tout item grace a <<
	void print(std::ostream &f) const override{
		f<<"Robot: Height("<<height<<"), Width("<<width<<")"<<std::endl;
		f << "Position: " << this->coordonnees << ", Direction: " << this->direction << std::endl;
		f << "Hitbox: " << this->hitbox << std::endl;
	}

	~Robot() {std::cout<<"delete robot"<<std::endl;}

};
