#include "token_list.hpp"
#include "vector"
#include "string.h"
void Token_list::queue(const std::string commande,const int value,const int ID){
    this->list_queue.push_back(Token(commande,value,ID));
}

void Token_list::queue(const std::string commande, const int x, const int y, const int width, const int height, const int ID)
{
    this->list_queue.push_back(Token(commande,x,ID,y,width,height));
}

void Token_list::translate(Token &t)
{
    std::cout<<"ID:"<<t.get_Token_ID()<<" ";
    if (t.get_expr()=="AV")
    {
        std::cout<<"Avancer de " << t.get_value() <<std::endl;
        m->avancerRobot(t.get_value());
    }
    if (t.get_expr()=="RC")
    {
        std::cout<<"Reculer de " << t.get_value() <<std::endl;
        m->reculerRobot(t.get_value());
    }
    if (t.get_expr()=="TG")
    {
        std::cout<<"Tourner a Gauche de " << t.get_value() <<std::endl;
        m->tournerRobot(-t.get_value());
    }
    if (t.get_expr()=="TD")
    {
        std::cout<<"Tourner a Droite de " << t.get_value() <<std::endl;
        m->tournerRobot(t.get_value());
    }
    if (t.get_expr()=="REPETER")
    {
        std::cout<<"Repeter " << t.get_value()<<" fois"<<std::endl;
    }
    if (t.get_expr()=="END")
    {
        std::cout<<"Boucle Terminee"<<std::endl;
    }
    if (t.get_expr()=="ACTIVE")
    {
        this->dessin = t.get_value();
    }
    if (t.get_expr()=="DESACTIVE")
    {
        this->dessin=t.get_value();
        m->setDessinRobot(LEVER);
    }
    if (t.get_expr()=="ECRITURE")
    {
        if (this->dessin)
        {
            this->trace=t.get_value();
            m->setDessinRobot(DESSIN);
        }
        else
        {
            std::cerr << "WARNING: ACTIVEE LE MODE DESSIN D'ABORD"<<std::endl;
        }
    }
    if (t.get_expr()=="EFFACER")
    {
        this->trace=t.get_value();
        m->setDessinRobot(GOMME);
    }
    if (t.get_expr()=="OBSTACLE")
    {
        std::cout << t.get_expr() << " a " <<t.get_value()<< " "<<t.gety() <<" "<< t.get_width()<<" "<< t.get_height()<<std::endl;
        m->creerObstacle(t.get_height(), t.get_width(), t.get_value(), t.gety(), 0);
    }
    if (t.get_expr()=="TAILLE")
    {
        std::cout<<t.get_expr()<<"height:"<<t.get_height() <<"width: "<<t.get_width();
        m->setSizeRobot(t.get_height(), t.get_width());
    }
    sleep();
}

void Token_list::sleep(){
    std::this_thread::sleep_for(std::chrono::milliseconds(temps_entre_instruction));
}


void Token_list::repeter(std::list<Token>::iterator &it)
{
    auto p=std::find_if(it,this->list_queue.end(),IsEnd);
    if (p!=list_queue.end())
    {
        while (it->get_value()>0)
        {
            for (std::list<Token>::iterator interne_it=it;interne_it!=p;interne_it++)
            {
                translate(*interne_it);
            }
            it->decrementer();
        }
    }
    else
    {
        std::cerr<<"la boucle sans fin"<<std::endl;
        exit(1);
    }
}
void Token_list::execute()
{
    if(!list_queue.empty())
    {
    this->pos=0;
    std::cout<<"Executing"<<std::endl;
    std::cout<<"Nombre d'instruction:"<<list_queue.size()<<std::endl;

    for (std::list<Token>::iterator it=this->list_queue.begin();it!=this->list_queue.end();it++)
    {
        if (it->get_expr()=="REPETER")
        { 
            repeter(it);  
        }
        this->translate(*it);
    }
    list_queue.clear();
    }
    else
    {
        std::cerr << " La liste est vide ";
        exit(1);
    }
}
bool Token_list::get_dessin_state(){
    return this->dessin;
}
bool Token_list::get_trace_state(){
    return this->trace;
}
        /*Retourner les chiffres */
int Token_list::number(const std::string &s)
{
    std::string number;
    for (auto i:s)
        {
            if(isdigit(i))
            {
                number+=i;
            }
        }
    assert(!number.empty());
    return std::stoi(number); 
}
/*Lecture les commandes */
void Token_list::read(std::string s)
{
    std::cout<<s<<std::endl;
    pos++;
    if (s.compare(0,2,"AV",2)==0)
    {
        queue("AV",number(s),pos);
    }
    else if (s.compare(0,2,"RC",2)==0)
    {
        queue("RC",number(s),pos);
    }
    else if (s.compare(0,2,"TD",2)==0)
    {
        queue("TD",number(s),pos);
    }
    else if (s.compare(0,2,"TG",2)==0)
    {
        queue("TG",number(s),pos);
    }
    else if(s.compare(0,7,"REPETER",7)==0)
    {
        queue("REPETER",number(s),pos);
        
    }
    else if (s.compare(0,6,"ACTIVE",6)==0)
    {
        queue("ACTIVE",1,pos);
    }
    else if (s.compare(0,9,"DESACTIVE",9)==0)
    {
        queue("DESACTIVE",0,pos);
    }
    else if (s.compare(0,7,"ECRITURE",7)==0)
    {
        queue("ECRITURE",1,pos);
    }
    else if(s.compare(0,7,"EFFACER",7)==0)
    {
        queue("EFFACER",0,pos);
    }
    else if(s.compare(0,3,"END",3)==0)
    {
        queue("END",0,pos);
    }
    else if(s.compare(0,8,"OBSTACLE",8)==0)
    {
        int i=0;
        bool valide=true;
        std::vector <std::string> parameter(4);
        std::string num;
        for (auto it:s)
        {
            if (isdigit(it)||it=='-')
            {
                num+=it;
            }
            if (it==',')
            {
                parameter[i] = num;
                i++;
                std::cout<<num<<std::endl;
                num="";
                if (i>3)
                {
                    std::cerr << "Commande Non adapte: OBSTACLE x,y,width,height"<<std::endl;
                    valide=false;
                    i=0;
                }
            }
        }
        std::cout << i <<std::endl;
        if (num.length()>0&&i==3)
        {
            parameter[3] = num;
        }
        else
        {
            valide = false;
            std::cerr << "Commande Non adapte: OBSTACLE x,y,width,height"<<std::endl;
        }
        if (valide==true)
        {
            queue("OBSTACLE",std::stoi(parameter[0]),std::stoi(parameter[1]),std::stoi(parameter[2]),std::stoi(parameter[3]),pos);
        }
    }
    else if(s.compare(0,5,"TAILLE"))
    {
        int i=0;
        bool valide=true;
        std::vector <std::string> parameter(2);
        std::string num;
        for (auto it:s)
        {
            if (isdigit(it))
            {
                num+=it;
            }
            if (it==',')
            {
                parameter[i] = num;
                i++;
                std::cout<<num<<std::endl;
                num="";
                if (i>2)
                {
                    std::cerr << "Commande Non adapte: TAILLE height,width"<<std::endl;
                    valide=false;
                    i=0;
                }
            }
        }
        std::cout << i <<std::endl;
        if (num.length()>0&&i==1)
        {
            parameter[1] = num;
        }
        else
        {
            valide = false;
            std::cerr << "Commande Non adapte: TAILLE height,width"<<std::endl;
        }
        if (valide==true)
        {
            queue("TAILLE",0,0,std::stoi(parameter[0]),std::stoi(parameter[1]),pos);
        }
    }
    else
    {
        std::cerr<<"Commande non valide ligne " << pos<<std::endl;
    }
}
int Token_list::get_size() const {
    return this->list_queue.size();
}
/*Lecture du fichier */
void Token_list::readfiles(const std::string &filename)
{
    std::ifstream fichier (filename,std::ios::in);
    if(fichier)
    {
        std::string contenu;
        while(getline(fichier,contenu))
        {
            this->read(contenu);
        }
    }
    else
    {
        std::cout<<"Fichier non trouve" <<std::endl;
    }
}