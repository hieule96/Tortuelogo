#pragma once
#pragma GCC diagnostic ignored "-Wreturn-type"

#include "Singleton.hpp"
#include "Item.hpp"
#include "Obstacle.hpp"
#include "Robot.hpp"

class FabriqueItem: public Singleton<FabriqueItem>{
public:
	static FabriqueItem & getInstance(){
		return InstanceUnique();
	}

	/*
	But: Fabriquer nos objets et les obtenir
	Antecedent: string Obstacle ou Robot, height, width, x, y, direction
	Consequent: Pointeur sur Item qui l objet instancie
	*/
	Item *getItem(std::string typeItem, double h, double w,double x_r=0,double y_a=0,double dir=0){
		if(typeItem == "Obstacle") return new Obstacle(h,w,x_r,y_a,dir);

		if(typeItem == "Robot") return Robot::InstanceUnique(h,w,x_r,y_a,dir);
	}
};
