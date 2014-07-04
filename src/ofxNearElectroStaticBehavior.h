#pragma once 

#include "ofxElectroStaticBehavior.h"

class ofxNearElectroStaticBehavior : public ofxElectroStaticBehavior
{
public:
    ofxNearElectroStaticBehavior() : ofxElectroStaticBehavior()
    {
        setup();
    }
    
    ~ofxNearElectroStaticBehavior()
    {
        if(bAllocatedRadius)
        {
            delete radius;
        }
    }
    
    void setup()
    {
        radius = new float();
        bAllocatedRadius = true;
        setRadius(100.0);
    }
    
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
    {
        ofVec3f r = ofVec3f(0,0,0);
        float count = 0.0; 
        for(vector<ofxRParticle *>::iterator it = (*particles).begin(); it != (*particles).end(); it++)
        {
            if((*it)->getID() != particle->getID())
            {
                ofVec3f direction = (*it)->getPpos() - pos;
                if(direction.length() < getRadius())
                {
                    float distance = direction.length();
                    direction /= (distance*distance + 1.0);
                    r+=direction*particle->getRadius();
                    count++;
                }
            }
        }
        r /= count;
        acc-=r*(*magnitude)*dt;
    }
    
    void setRadius(float _radius)
    {
        *radius = _radius;
    }
    
    void setRadiusPtr(float *_radius)
    {
        if(bAllocatedRadius)
        {
            delete radius;
            bAllocatedRadius = false;
        }
        radius = _radius;
    }
    
    float getRadius()
    {
        return *radius;
    }
    
    float *getRadiusPtr()
    {
        return radius;
    }
    
    map<string, float*> floatPropert;
    float *radius;
    bool bAllocatedRadius;
};
