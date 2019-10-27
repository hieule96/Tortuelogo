#pragma once

#define PI 3.14159265

#include"../Shape/Point.hpp"
#include<cmath>

class Hitbox{
	Point pNO;
	Point pNE;
	Point pSO;
	Point pSE;
public:
	Hitbox(Point coord, double height, double width, double dir):
		pNO( createNO(coord,height,width,dir) ),
		pNE( createNE(coord,height,width,dir) ),
		pSO( createSO(coord,height,width,dir) ),
		pSE( createSE(coord,height,width,dir) )
	{}

	Point getNO() const{
		return this->pNO;
	}

	Point getNE() const{
		return this->pNE;
	}

	Point getSO() const{
		return this->pSO;
	}

	Point getSE() const{
		return this->pSE;
	}

	Point createNO(Point coord, double height, double width, double dir){
		Point p = coord;
		double rayon = sqrt(pow(width,2)+pow(height,2))/2;
		double theta = atan(width/height) * 180.0 / PI;
		double angle = ((abs(dir)<=90) ? dir : dir - 180.0)  + theta;
		Point delta = Point(rayon,angle);
		delta.conversionCartesien();
		p += delta;
		return p;
	}

	Point createNE(Point coord, double height, double width, double dir){
		Point p = coord;
		double rayon = sqrt(pow(width,2)+pow(height,2))/2;
		double theta = atan(width/height) * 180.0 / PI;
		double angle = ((abs(dir)<=90) ? dir : dir - 180.0)  - theta;
		Point delta = Point(rayon,angle);
		delta.conversionCartesien();
		p += delta;
		return p;
	}

	Point createSO(Point coord, double height, double width, double dir){
		Point p = coord;
		double rayon = sqrt(pow(width,2)+pow(height,2))/2;
		double theta = atan(width/height) * 180.0 / PI;
		double angle = ((abs(dir)>90) ? dir : dir - 180.0)  - theta;
		Point delta = Point(rayon,angle);
		delta.conversionCartesien();
		p += delta;
		return p;
	}

	Point createSE(Point coord, double height, double width, double dir){
		Point p = coord;
		double rayon = sqrt(pow(width,2)+pow(height,2))/2;
		double theta = atan(width/height) * 180.0 / PI;
		double angle = ((abs(dir)>90) ? dir : dir - 180.0)  + theta;
		Point delta = Point(rayon,angle);
		delta.conversionCartesien();
		p += delta;
		return p;
	}

	bool collision(Hitbox h){
		double pXmax=(std::max(this->pNE.getX_R(),this->pSE.getX_R()));
		double pXmin=(std::min(this->pNO.getX_R(),this->pSO.getX_R()));
		double pYmax=(std::max(this->pNO.getY_A(),this->pNE.getY_A()));
		double pYmin=(std::min(this->pSO.getY_A(),this->pSE.getY_A()));

		double hXmax=(std::max(h.getNE().getX_R(),h.getSE().getX_R()));
		double hXmin=(std::min(h.getNO().getX_R(),h.getSO().getX_R()));
		double hYmax=(std::max(h.getNO().getY_A(),h.getNE().getY_A()));
		double hYmin=(std::min(h.getSO().getY_A(),h.getSE().getY_A()));

		double pHeight=pYmax-pYmin;
		double pWidth=pXmax-pXmin;

		double hHeight=hYmax-hYmin;
		double hWidth=hXmax-hXmin;

		if(pXmin>=hXmin+hWidth || pXmin+pWidth<=hXmin || pYmin >= hYmin+hHeight || pYmin+pHeight<=hYmin){
			return false;
		}
		else{
			return true;
		}
	}

	friend std::ostream&operator<<(std::ostream &f, const Hitbox &h){
        return f << "NO: " << h.pNO << ", "
        		<< "NE: " << h.pNE << ", "
        		<< "SO: " << h.pSO << ", "
        		<< "SE: " << h.pSE << std::endl;
    }
};
