#pragma once
#include <string>
/*
CLASS TOKEN:
Rôle: Contenir UN expression,le nom du commande à executer, et les parametres du commande. 
 */
class Token{
    protected:
        std::string expr; //expression du commande
        int value; // parametre 1
        int Token_ID;// ID de l'execution
        int y;// parametre 2
        int width;// parametre 3
        int height;// parametre 4
    public:
        Token(const std::string _expr=nullptr, const int _value=0, const int _Token_ID=0,const int _y=0, const int _width=0, const int _height =0):
        expr(_expr),value(_value),Token_ID(_Token_ID),y(_y),width(_width),height(_height){};
        /*
            Les methodes suivants sont des assesseurs qui permet de lire des parametres
         */
        int get_value()
        {
            return this->value;
        }
        std::string get_expr()
        {
            return expr;
        }
        int get_Token_ID()
        {
            return this->Token_ID;
        }
        void decrementer()
        {
            this->value--;
        }
        ~Token()
        {
        }
        int gety()
        {
            return this->y;
        }
        int get_width()
        {
            return this->width;
        }
        int get_height()
        {
            return this->height;
        }
};