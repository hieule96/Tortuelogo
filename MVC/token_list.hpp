#pragma once

#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <chrono>
#include <thread>
#include <fstream>
#include "token.hpp"
#include "Modele.hpp"

/*
* Token list est un list des Tokens, autrement dit, 
la liste des commande, cela permet de stocker les commande et d'executer sequentiellement,
l'execution se fait par le parcours du liste.
les commandes connecte avec le avec le controller controler le modele
 */
class Token_list
{
    private:
        Modele * m;
        std::list <Token> list_queue;
        bool dessin;
        bool trace;
        int temps_entre_instruction; // in ms
        int pos;
    public:
        Token_list(Modele *mm,const std::list<Token> c=std::list<Token>(),const bool _dessin=false, const bool _trace=false, const int _temps_entre_instruction=100,const int _pos=0):
        m(mm),list_queue(c),dessin(_dessin),trace(_trace),temps_entre_instruction(_temps_entre_instruction),pos(_pos){
        };
        // Ajouter des taches simple a 1 parametres
        void queue(const std::string commande,const int value,const int ID);
        // Ajouter des taches a 4 parametres
        void queue(const std::string commande, const int x, const int y, const int width, const int height, const int ID);
        // Traduire le token
        void translate(Token &t);
        //delay l'execution
        void sleep();
        static bool IsEnd(Token t)
        {
            return (t.get_expr()=="END");
        }
        // Instruction de repetion
        void repeter(std::list<Token>::iterator &it);
        // Executer tous les intruction
        void execute();
        // la taille de la liste
        int get_size()const;
        bool get_dessin_state();
        bool get_trace_state();
        // convertir en numero
        int number(const std::string &s);
        // lire une ligne simple
        void read(std::string s);
        // lire un fichier
        void readfiles(const std::string &filename);
};
