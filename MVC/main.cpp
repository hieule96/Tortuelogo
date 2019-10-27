//https://www.developpez.net/forums/d1079490/general-developpement/alm/design-patterns/mvc-update-observable-s-object-o/

#include <gtkmm/application.h>

#include "Vue.hpp"
#include "VueGraphique.hpp"
#include "Modele.hpp"
#include "ModeleEnv2D.hpp"
#include "Controleur.hpp"
#include "token.hpp"

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.robot");

	Modele *m = new ModeleEnv2D();
	Vue *vg = new VueGraphique(); //la vue graphique

	m->ajouterObservateur(vg); //la vue graphique observe la modele

	Token_list *i = new Token_list(m);

	new Controleur(m,vg,i);
	
	return app->run(*vg);
}