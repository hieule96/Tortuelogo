#include "VueTerminal.hpp"
#include"Controleur.hpp"


	VueTerminal::VueTerminal():boxVert(Gtk::ORIENTATION_VERTICAL),boxHori(Gtk::ORIENTATION_HORIZONTAL),bCelsius("Celcius"),bFahrenheit("Fahrenheit"),bExit("Exit"){
		boxHori.pack_start(bCelsius);
		boxHori.pack_start(bFahrenheit);
		boxHori.pack_start(bExit);

		set_size_request(200,50);
		set_title("Convertisseur");

		TextEntry.set_max_length(50);
		TextEntry.set_text("Tapez ici");
		TextEntry.select_region(0,TextEntry.get_text_length());

		boxVert.pack_start(TextEntry);
		boxVert.pack_start(boxHori);
		add(boxVert);
		show_all_children();
	};
	double VueTerminal::getDegres() const{
		Glib::ustring text=TextEntry.get_text();
		return atof(text.c_str());
	};

	void VueTerminal::setDegres(double d){
		Glib::ustring text=Glib::ustring::format(std::fixed,d);
		TextEntry.set_text(text);

	};

	void VueTerminal::update(double d){
		setDegres(d);
	};

	void VueTerminal::on_button_close() {hide();};

	void VueTerminal::addCelsiusListener(Controleur *c){
		bCelsius.signal_clicked().connect(sigc::mem_fun(*c,&Controleur::on_button_celsius));
	};

	void VueTerminal::addFahrenheitListener(Controleur *c){
		bFahrenheit.signal_clicked().connect(sigc::mem_fun(*c,&Controleur::on_button_fahrenheit));
	};

	void VueTerminal::addExitListener(Controleur *c){
		bExit.signal_clicked().connect(sigc::mem_fun(*c,&Controleur::on_button_exit));
	};

	//le destructeur
	VueTerminal::~VueTerminal() {};