#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/messagedialog.h> 

#include "Vue.hpp"
#include "Canvas.hpp"
#include "Info.hpp"


class Controleur;

class VueGraphique:public Vue{
    private:
        // Boutons
        Gtk::Button bExit;
        Gtk::Button bHelp;
        Gtk::Button bGetCommande;
        Gtk::Button bGetFile;
        Gtk::Entry EntryCode;
        // Espace de dessin
        Canvas ActiveZone;
        // Box de rangement
        Gtk::Box ButtonBox,EntryBox,MainBox;
    public:
        VueGraphique();

        void on_button_close() override;

        void on_button_help() override;

        void addHelpListener(Controleur *c) override;
        
        void addExitListener(Controleur *c) override;

        void addGetCommandeListener(Controleur *c) override;

        void addGetfileListener(Controleur *c) override;

        void setArea(double height, double width) override;

        void update(std::vector<Info> info) override;
        std::string getText() const override{
            Glib::ustring text=EntryCode.get_text();
            return text.c_str();
        }
        //le destructeur
        virtual ~VueGraphique();
};