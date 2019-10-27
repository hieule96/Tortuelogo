#pragma once

#define PI 3.14159265

#include <gtkmm/drawingarea.h>
#include <iostream>
#include<vector>
#include"Info.hpp"

class Canvas:public Gtk::DrawingArea
{
private:
    std::vector<Info> info;
protected:

    //dessine l observation du modele (vecteur info)
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override
    {
        Gtk::Allocation allocation = get_allocation();
        const int width = allocation.get_width();
        const int height = allocation.get_height();
        cr->translate(width/2, height/2);

        cr->save();
	    auto dessin = info[0].getDessin();
        for(auto it=info.begin(); it<info.end()-1; it++){
    		dessin = it->getDessin();
    		switch(dessin){
    		    case DESSIN: {
    		        cr->set_source_rgb(1,0.8,0.1);
    		        break;
    		    }
    		    case GOMME: {
    		        cr->set_source_rgb(0.949,0.945,0.941);
    		        break;
    		    }
    		    default: {
    		        cr->set_source_rgb(0.2,0.8,0.1);
    		        break;
    		    }
    		}
            if(dessin != LEVER){
        		cr->set_line_width(it->getSize());
        		cr->move_to(it->getPO().getX_R(),it->getPO().getY_A());
        		cr->line_to(it->getPE().getX_R(),it->getPE().getY_A());
        		cr->stroke();
            }
        }
        cr->restore();
        cr->save();
	    auto robot = info.end()-1;

        cr->set_line_width(robot->getSize());

        cr->set_source_rgb(0.1,0.2,0.8);
        cr->move_to(int(robot->getPO().getX_R()),int(robot->getPO().getY_A()));
        cr->line_to(int(robot->getPE().getX_R()),int(robot->getPE().getY_A()));
        cr->stroke();
        cr->restore();
        cr->save();
        cr->set_source_rgb(1,0,0);
        cr->set_line_width(3);
        auto center=(robot->getPO()+robot->getPE())/2;
        cr->arc(center.getX_R(),center.getY_A(),robot->getSize()/2,robot->getDirection()*PI/180.0,(robot->getDirection()+180)*PI/180.0);
        cr->stroke();
        cr->restore();
        return true;
    };

public:
    Canvas(const int height=100, const int width=100){
        Info defaultInfo = Info();
        info.push_back(defaultInfo);
        set_size_request(width,height);
        queue_draw();
    };

    //modifie le vecteur d info et affiche la modification grace a queue_draw() qui appelle on_draw()
    void setInfo(std::vector<Info> info){
        this->info=info;
        queue_draw();
    }

    virtual ~Canvas(){
        info.clear();
        info.shrink_to_fit();
    };
};
