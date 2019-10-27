#pragma once

#include<vector>
#include<cmath>
#include"../Item/FabriqueItem.hpp"
#include"../Item/Item.hpp"
#include"../Hitbox/Hitbox.hpp"
#include"../Shape/Point.hpp"
#include"Modele.hpp"
#include"Info.hpp"

class Modele;

class ModeleEnv2D:public Modele{
private:
	Hitbox area;
	FabriqueItem fabrique;
	Item *robot;
	std::vector<Item *> obstacles;
	std::vector<Info> dessin;
public:
	ModeleEnv2D(double h_a=100, double w_a=100,double h_r=30, double w_r=30):
		area(Hitbox(Point(w_a/2,h_a/2),h_a,w_a,0)),
		fabrique(FabriqueItem::getInstance()),
		robot(fabrique.getItem("Robot",h_r,w_r))
		{
		notification();
	}

	Item *getRobot() const{
		return robot;
	}

	std::vector<Item *> getObstacles() const{
		return obstacles;
	}

	/*
	But: Creer une info pour rendre un objet interpretable par les observateurs
	Antecedent: Pointeur sur item
	Consequent: Info associée a l objet
	*/
	Info getItemInfo(Item * i){
		Hitbox h = i->getHitbox();
		Point p1 = (h.getNO()+h.getSO())/2;
		Point p2 = (h.getNE()+h.getSE())/2;
		int size = h.getNO().distanceCartesien(h.getSO());
		double dir = i->getDirection();
		return Info(p1,p2,size,dir);
	}

	/*
	But: Creer une info pour rendre des dessins interpretables par les observateurs
	Antecedent: Hitbox de dessin et type de dessin
	Consequent: Info associée au dessin
	*/
	Info getItemInfo(Hitbox h,DRAWINGTYPE d){
		Point p1 = (h.getNO()+h.getSO())/2;
		Point p2 = (h.getNE()+h.getSE())/2;
		int size = h.getNO().distanceCartesien(h.getSO());
		return Info(p1,p2,size,0,d);
	}

	/*
	But: Notifier les observateurs avec un vecteur de info associe aux objets du modele et a leurs traces
	*/
	void notification(){
		std::vector<Info> info;
		info = this->dessin;
		Info item_info;
		for(auto o : obstacles){
			item_info = getItemInfo(o);
			info.push_back(item_info);
		}
		item_info = getItemInfo(robot);
		info.push_back(item_info);
		notifierObservateurs(info);
	}

	/*
	But: Obtenir une Hitbox couvrant toute la zone de deplacement
	Antecedent: Pointeur sur Item et distance de deplacement
	Consequent: Hitbox liee au deplacement
	*/
	Hitbox getDeplacementHitbox(Item * item, double dist) const{
		Point p1,p2;
		if(abs(item->getDirection())<90.0){
			p1=(dist>=0)?item->getHitbox().getSO():item->getHitbox().getNO();
			p2=(dist>=0)?item->getHitbox().getSE():item->getHitbox().getNE();
		}
		else{
			p1=(dist>=0)?item->getHitbox().getNO():item->getHitbox().getSO();
			p2=(dist>=0)?item->getHitbox().getNE():item->getHitbox().getSE();
		}
		Point pCentroid = (p1+p2)/2;
		Point delta = Point(abs(dist)/2+item->getHeight(), ((dist>=0)?item->getDirection():item->getDirection()+180.0));
		delta.conversionCartesien();
		pCentroid += delta;
		Hitbox h(pCentroid,dist,item->getWidth(),item->getDirection());
		return h;
	}

	/*
	But: Savoir si le deplacement de l objet est valide
	Antecedent: Pointeur sur Item et distance de deplacement
	Consequent: boolean = true si valide, false sinon
	*/
	bool deplacementValide(Item * item, double dist) const{
		Hitbox h = getDeplacementHitbox(item,dist);
		if(inArea(h)){
			if(poserValide(h)) return true;
			else return false;
		}
		else return false;
	}

	/*
	But: Deplacer le robot (jusqu au premier obstacle si obstacle sur le trajet)
	Antecedent: distance de deplacement
	Consequent: deplace le robot au bon endroit puis notification()
	*/
	void bougerRobot(double dist){
		bool ok=true;
		bool positif = (dist>=0);
		int delta=0;
		if(deplacementValide(robot,dist)){
			positif?robot->avancer(abs(dist)):robot->reculer(abs(dist));
			delta = dist;
		}
		else{
			while(ok){
				positif?robot->avancer(1):robot->reculer(1);
				positif?delta++:delta--;
				if(inArea(robot->getHitbox())){
					if(!poserValide(robot->getHitbox())) ok=false;
				}
				else ok=false;
			}
			if(positif){
				robot->reculer(1);
				delta--;
			}
			else{
				robot->avancer(1);
				delta++;
			}
		}
		if(delta!=0){
			Info i = getItemInfo(getDeplacementHitbox(robot,-delta),robot->getDessin());
			dessin.push_back(i);
			i = getItemInfo(robot->getHitbox(),robot->getDessin());
			dessin.push_back(i);
		}
		notification();
	}

	void avancerRobot(double dist) override{
		bougerRobot(dist);
	}

	void reculerRobot(double dist) override{
		bougerRobot(-dist);
	}

	/*
	But: Tourne le robot (jusqu a ce qu il percute un obstacle si obstacle sur le trajet)
	Antecedent: angle de decalage
	Consequent: tourne le robot au bon endroit puis notification()
	*/
	void tournerRobot(double angle) override{
		Info i;
		bool ok=true;
		bool sens = (angle>0);
		int pas=(sens?1:-1);
		int delta=0;
		while(ok && delta<abs(angle)){
			robot->tourner(pas);
			delta++;
			ok=poserValide(robot->getHitbox());
			if(ok){
				Info i = getItemInfo(robot->getHitbox(),robot->getDessin());
				dessin.push_back(i);
			}
		}
		robot->tourner(-pas);
		notification();
	}

	/*
	But: Savoir si un objet est dans la zone
	Antecedent: hitbox d un objet
	Consequent: boolean = true si dans la zone, false sinon
	*/
	bool inArea(Hitbox h) const{
		if(!h.collision(this->area)) return false;
		return true; 
	}

	/*
	But: Savoir si un objet est en collision dans son etat actuel
	Antecedent: hitbox d un objet
	Consequent: boolean = false si collsion avec un des obstacles, true sinon
	*/
	bool poserValide(Hitbox h) const{
		for(auto o: obstacles){
			if(h.collision(o->getHitbox())) return false;
		}
		return true; 
	}

	/*
	But: poser le robot aux coordonnees x et y
	Antecedent: coordonnees x et y en double
	Consequent: pose l objet aux coordonnees indiquees si pas collsion, message d erreur sinon
	*/
	void poserRobot(double x_r, double y_a) override{
		Point pos = robot->getCoordonnees();
		robot->poser(x_r,y_a);
		if(inArea(robot->getHitbox())){
			bool ok = poserValide(robot->getHitbox());
			if(ok){
				robot->poser(x_r,y_a);
				Info i = getItemInfo(robot->getHitbox(),robot->getDessin());
				dessin.push_back(i);
				notification();
			}
			else{
				robot->poser(pos.getX_R(),pos.getY_A());
				std::cout<<"posez pas robot sur un obstacle"<<std::endl;
			}
		}
		else{
			robot->poser(pos.getX_R(),pos.getY_A());
			std::cout<<"posez robot dans la zone"<<std::endl;
		}
	}

	/*
	But: modifie la taille du robot
	Antecedent: hauteur et largeur en double
	Consequent: modifie la taille du robot si pas collsion, message d erreur sinon
	*/
	void setSizeRobot(double h, double w) override{
		double prev_height=robot->getHeight();
		double prev_width=robot->getWidth();
		robot->setHeight(h);
		robot->setWidth(w);
		if(poserValide(robot->getHitbox())){
			notification();
		}
		else {
			robot->setHeight(prev_height);
			robot->setWidth(prev_width);
			std::cout<<"robot will collide with this size"<<std::endl;
		}
	}

	/*
	But: modifie le mode de dessin du robot
	Antecedent: mode de dessin du type enumere DRAWINGTYPE
	*/
	void setDessinRobot(DRAWINGTYPE dessin) override{
		robot->setDessin(dessin);
	}

	/*
	But: cree un obstacle
	Antecedent: hauteur, largeur, coordonnees x et y, direction en double
	Consequent: cree un obstacle si la position est valide, message d erreur sinon
	*/
	void creerObstacle(double h, double w, double x_r, double y_a, double dir) override{
		Hitbox hitboxObstacle = Hitbox(Point(x_r,y_a),h,w,dir);
		bool okObstacles = poserValide(hitboxObstacle);
		bool okRobot = ! robot->getHitbox().collision(hitboxObstacle);
		bool ok = okObstacles && okRobot;
		if(ok){
			Item *obstacle=fabrique.getItem("Obstacle",h,w);
			obstacle->poser(x_r, y_a);
			obstacles.push_back(obstacle);
			notification();
		}
		else std::cout<<"emplacement interdit pour obstacle"<<std::endl;
	}

	/*
	But: modifie la zone de travail du modele
	Antecedent: hauteur et largeur en double
	Consequent: cree l hitbox de area et 4 obstacles entourant l area
	*/
	void setArea(double height, double width) override{
        Hitbox h = Hitbox(Point(0,0),height,width,0);
        this->area = h;
        //mur du haut
        creerObstacle(1.99, width-1, 0, -(height+1)/2, 0);
        //mur de gauche
        creerObstacle(height-1, 1.99, -(width+1)/2, 0, 0);
        //mur de droite
        creerObstacle(height-1, 1.99, (width+1)/2, 0, 0);
        //mur du bas
        creerObstacle(1.99, width-1, 0, (height+1)/2, 0);
    }

	virtual ~ModeleEnv2D(){
		delete robot;
		for(auto o:obstacles) delete o;
		obstacles.clear();
		obstacles.shrink_to_fit();
	}
};
