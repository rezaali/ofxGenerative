#pragma once

#include "ofMain.h"

class ofx1DExtruder
{
public:
	ofx1DExtruder()
	{
		init(); 
	}
	
	ofx1DExtruder(float _pos)
	{
		initWith(_pos);
	}
	
	void init()
	{
		home = 0; 
		pos = 0; 
		vel = 0; 
		acc = 0;
        delta = fabs(pos-home);
		damping = .75;
		extForce = 0; 
		extForceInQue = false; 
		accLimit = .050; 
		velLimit = .20; 		
	}
	
	void initWith(float _pos)
    {
        init(); 
        home = _pos; 
        pos = _pos;
        delta = fabs(pos-home);
    }
	
	void setPhysics(float _damping, float _accLimit, float _velLimit)
	{
		damping = _damping; 
		accLimit = _accLimit;
		velLimit = _velLimit; 
	}
    
    void setDamping(float _damping)
    {
        damping = _damping;         
    }

    void setAccLimit(float _accLimit)
    {
        accLimit = _accLimit;         
    }

    void setVelLimit(float _velLimit)
    {
        velLimit = _velLimit;         
    }

    float getDamping()    
    {
        return damping;         
    }

    float getVelLimit()
    {
        return velLimit;         
    }

    float getAccLimit()
    {
        return accLimit;         
    }    
    
	void update()
	{
		acc = 0; 
		acc+=goHome(); 		
		if(extForceInQue)
		{	
			acc+=extForce; 
			extForceInQue = false; 
			extForce = 0; 
		}
		acc-=vel*damping; 
		if(fabs(acc) > accLimit)
		{
			if(acc > 0)
			{
				acc = accLimit; 
			}
			else {
				acc = -accLimit; 
			}
		}
		vel+=acc; 
		if(fabs(vel) > velLimit)
		{
			if(vel > 0)
			{
				vel = velLimit; 
			}
			else {
				vel = -velLimit; 
			}
		}		
		pos+=vel; 		
	}
	
	float goHome()
	{
		float temp = pos-home;
        delta = fabs(temp);
		temp*=.15;  
		float tempvel = vel; 
		tempvel *= .17;
		temp -=tempvel; 
		temp*=-1.0; 
		return temp; 		
	}	
    
	void draw()
	{
		ofSetColor(255,0,0); 
		ofLine(pos,ofGetHeight()*.5, home, ofGetHeight()*.5); 

		ofSetColor(0,0,255); 		
		ofEllipse(home, ofGetHeight()*.5, 10, 10); 

		ofSetColor(0,255,0); 		
		ofEllipse(pos, ofGetHeight()*.5, 10, 10); 

	}
	
	float getPos()
    {
        return pos;
    }
	
    float *getPosPtr()
    {
        return &pos;
    }
    
	void setPos(float _pos)
	{
		pos = _pos; 
	}

	void setHome(float _home)
	{
		home = _home; 
	}
    
    float getHome()
    {
        return home;
    }

    float *getHomePtr()
    {
        return &home;
    }
    
    void setPosAndHome(float _home)
    {
        home = _home; 
        pos = _home;
        delta = fabs(pos-home);
    }
	
	void addForce(float _extForce)
	{
		extForceInQue = true; 
		extForce += _extForce; 
	}
	
    float getDelta()
    {
        return delta;
    }
    
protected:
    float delta;
	float home; 
	float pos; 
	float vel; 
	float acc; 
	float damping; 	
	float extForce;
	float velLimit; 
	float accLimit; 
	bool extForceInQue; 
}; 