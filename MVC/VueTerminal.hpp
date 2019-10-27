#pragma once

#include"Vue.hpp"
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <string>

class VueTerminal:public Vue{
private:
	Gtk::Box boxVert;
	Gtk::Box boxHori;
	Gtk::Entry TextEntry;
	Gtk::Button bCelsius;
	Gtk::Button bFahrenheit;
	Gtk::Button bExit;
public:
	VueTerminal();
	double getDegres() const;

	void setDegres(double d);

	void update(double d) override;

	void on_button_close() override;

	void addCelsiusListener(Controleur *c) override;

	void addFahrenheitListener(Controleur *c) override;

	void addExitListener(Controleur *c) override;
	//le destructeur
	virtual ~VueTerminal();
};