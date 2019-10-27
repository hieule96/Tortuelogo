#pragma once

#include<vector>
#include"Observateur.hpp"
#include <gtkmm/window.h>
#include"../Shape/Point.hpp"
#include"Info.hpp"

class Controleur;

class Vue:public Gtk::Window, public Observateur<std::vector<Info>>{
public:

	//controleur to vue through listener

	virtual void on_button_close()=0;

	virtual void on_button_help()=0;

	//listeners

	virtual void addHelpListener(Controleur *c)=0;

	virtual void addExitListener(Controleur *c)=0;
	
	virtual void addGetCommandeListener(Controleur *c)=0;
	
	virtual void addGetfileListener(Controleur *c)=0;

	//modifie la zone de travail de la vue (taille de la Drawing Area)

	virtual void setArea(double height, double width)=0;

	//renvoie le texte contenu dans la zone de texte

	virtual std::string getText() const =0;

	virtual ~Vue(){};
};
