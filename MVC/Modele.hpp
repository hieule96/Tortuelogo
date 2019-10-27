#pragma once

#include<vector>
#include "Observable.hpp"
#include"Info.hpp"

//interface modele
class Modele:public Observable<std::vector<Info>> {
public:

	virtual void avancerRobot(double dist)=0;

	virtual void reculerRobot(double dist)=0;

	virtual void tournerRobot(double angle)=0;

	virtual void poserRobot(double x_r, double y_a)=0;

	virtual void setSizeRobot(double h, double w)=0;

	virtual void setDessinRobot(DRAWINGTYPE dessin)=0;

	virtual void creerObstacle(double h, double w, double x_r, double y_a, double dir)=0;

	virtual void setArea(double height, double width)=0;

	virtual ~Modele(){};
};
