#pragma once

#define PI 3.14159265

#include <iostream>
#include<cmath>

class Point {
    private:
        double x_r,y_a;
    public:
        Point(double a=0, double b=0) : x_r(a), y_a(b) {}

        double getX_R() const{
            return this->x_r;
        }

        double getY_A() const{
            return this->y_a;
        }

        void setX_R(double x_r){
            this->x_r=x_r;
        }

        void setY_A(double y_a){
            this->y_a=y_a;
        }

        /*
        But: Convertit les variables membres de Point en coordonnees cartesiennes
        Antecedent: Point instancie avec coordonnees polaires
        */
        void conversionCartesien(){
            double temp=this->x_r;
            this->x_r=this->x_r*cos((90+y_a)*PI/180.0);
            this->y_a=temp*sin((90+this->y_a)*PI/180.0);
        }

        /*
        But: Convertit les variables membres de Point en coordonnees polaires
        Antecedent: Point instancie avec coordonnees cartesiennes
        */
        void conversionPolaire(){
            this->x_r=sqrt(pow(this->x_r,2)+pow(this->y_a,2));
            this->y_a=acos((this->y_a/this->x_r)*PI/180)*180/PI;
        }

        /*
        But: Calcule la distance entre deux Point en coordonnees cartesiennes
        Antecedent: Point en coordonnees cartesiennes
        Consequent: distance entre l'objet Point et le Point en parametre
        */
        double distanceCartesien(const Point &p) const{
            return sqrt(pow(this->x_r-p.getX_R(),2)+pow(this->y_a-p.getY_A(),2));
        }

        //surcharge de operateur +=
        void operator+=(const Point &p){
            this->x_r=this->x_r+p.x_r;
            this->y_a=this->y_a+p.y_a;
        }

        //surcharge de operateur +
        Point &operator+(const Point &p){
            this->x_r=this->x_r+p.x_r;
            this->y_a=this->y_a+p.y_a;
            return *this;
        }

        //surcharge de operateur /
        Point &operator/(const double div){
            this->x_r=this->x_r/div;
            this->y_a=this->y_a/div;
            return *this;
        }

        //surcharge de operateur <<
        friend std::ostream&operator<<(std::ostream &f, const Point &p){
            return f << "(" << p.x_r << "," << p.y_a << ")";
        }     
};