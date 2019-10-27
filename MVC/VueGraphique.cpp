#include "VueGraphique.hpp"
#include "Controleur.hpp"

VueGraphique::VueGraphique():
    bExit("EXIT"),
    bHelp("Aide"),
    bGetCommande("RUN"),
    bGetFile("Ouvrir le script"),
    ButtonBox(Gtk::ORIENTATION_HORIZONTAL),
    EntryBox(Gtk::ORIENTATION_VERTICAL),
    MainBox(Gtk::ORIENTATION_VERTICAL)
    {
        set_title("Tortue Robot");
        EntryBox.pack_start(ActiveZone);
        EntryBox.pack_start(EntryCode);
        ButtonBox.add(bExit);
        ButtonBox.add(bGetCommande);
        ButtonBox.add(bGetFile);
        ButtonBox.add(bHelp);
        MainBox.add(EntryBox);
        MainBox.add(ButtonBox);
        add(MainBox);
        show_all_children();
    };

    void VueGraphique::on_button_close(){
        this->hide();
    }

    void VueGraphique::on_button_help()
    {
        Gtk::MessageDialog dialog(*this, "Guide d'utilisation");
        dialog.set_secondary_text("Coordonnee par defaut du robot est (0,0) direction bas (0), coordonnees croissent de gauche à droite (-150 à 150) et de haut à bas (idem)\nLes instructions de controle [(parameter) est un nombre entier]:\nAVnombre_de_pas: Avancer de (nombre_de_pas)\nTDangle: Tourner a droite de (angle)\nTGangle: Tourner a Gauche de (angle)\nRCnombre_de_pas: Reculer de (nombre_de_pas)\nACTIVE:Activer le mode de dessin\nDESACTIVE: Desactiver le mode de dessin\nECRITURE: Tracer sur le sol\nEFFACER: effacer la trace sur le sol\nOBSTACLE (x),(y),(width),(height): creer un obstacle aux coordonnees centrales (x),(y) et de taille (width),(height)\nTAILLE (width),(height): modifier la taille du robot.\nStructure de boucle(!ATTENTION PAS EN COMMANDE SEULE!):\nREPETERnombre_de_repetition\ncommande1\ncommande2\n...\ncommandex\nEND\n\nEntrez la commande dans la zone de texte et cliquez sur run pour executer la commande une fois.\nEntrez le path du fichier de commande a executer puis Ouvrir le script pour executer sequentiellement les commandes.\nExemple:\nACTIVE\nECRITURE\nRC 20\nREPETER 10\nAV 20\nTG 50\nEND\nTD 60");
        dialog.run();
    }

    void VueGraphique::addHelpListener(Controleur *c)
    {
        this->bHelp.signal_clicked().connect(sigc::mem_fun(*c,&Controleur::on_button_help));
    }

    void VueGraphique::addGetfileListener(Controleur *c)
    {
        this->bGetFile.signal_clicked().connect(sigc::mem_fun(*c,&Controleur::on_button_getfile));
    }

    void VueGraphique::addGetCommandeListener(Controleur *c){
        this->bGetCommande.signal_clicked().connect(sigc::mem_fun(*c,&Controleur::on_button_getcommande));
    };

    void VueGraphique::addExitListener(Controleur *c){
        this->bExit.signal_clicked().connect(sigc::mem_fun(*c,&Controleur::on_button_exit));
    }

    void VueGraphique::setArea(double height, double width){
        this->ActiveZone.set_size_request(width,height);
    }

    void VueGraphique::update(std::vector<Info> info){
        this->ActiveZone.setInfo(info);
        this->ActiveZone.show();
    };
        
    //le destructeur
    VueGraphique::~VueGraphique(){};
