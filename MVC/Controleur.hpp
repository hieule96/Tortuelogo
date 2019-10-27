#pragma once

#include "Modele.hpp"
#include "Vue.hpp"
#include "token_list.hpp"

class Controleur {
private:
	Modele *m;
	Vue *v;
	Token_list *s;
public:
	Controleur(Modele *mm, Vue *vv, Token_list *ss) : m(mm), v(vv),s(ss) {
		v->addExitListener(this);
		v->addGetCommandeListener(this);
		v->addGetfileListener(this);
		v->addHelpListener(this);
		v->setArea(300,300);
		m->setArea(300,300);
		m->setSizeRobot(30, 30);
		m->poserRobot(0, 0);
		m->setDessinRobot(LEVER);
	}

	//donne l aide
	//controle le bouton associe
	void on_button_help()
	{
		v->on_button_help();
	}

	//execute la commande entree dans la zone de texte
	//controle le bouton associe
	void on_button_getcommande()
	{
		if(v->getText()!="")
		{
			s->read(v->getText());
			if(s->get_size()>0)
			{
				s->execute();
			}
		}
	}

	//execute le script contenu dans le fichier dont le nom est dans la zone de texte
	//controle le bouton associe
	void on_button_getfile()
	{
		if(v->getText()!="")
		{
			s->readfiles(v->getText());
			if(s->get_size()>0)
			{
				s->execute();
			}
		}
	}

	//quitte le jeu
	//controle le bouton associe
	void on_button_exit(){
		v->on_button_close();
	}
};
