#pragma once 

#include "ofxBoundaryBehavior.h"

class ofxToroidalBoundaryBehavior : public ofxBoundaryBehavior
{
public:
    ofxToroidalBoundaryBehavior() : ofxBoundaryBehavior()
    {
        setup();
    }
    
    virtual ~ofxToroidalBoundaryBehavior()
    {
        if(bAllocatedCenter)
        {
            delete center;
        }
    }
    
    void setup()
    {        
        center = new ofVec3f(0,0,0);
        bAllocatedCenter = true;
    }
    
    virtual void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
    {
        float s = getSpace();
        bool bOutSide = false;
        
        if(pos.x > ((xMax-s)+center->x))
        {
            pos.x = xMin+s + center->x;
            particle->setPpos(pos);
            bOutSide = true;
        }
        else if(pos.x < ((xMin+s)+center->x))
        {
            pos.x = xMax-s + center->x;
            particle->setPpos(pos);
            bOutSide = true;
        }
        
        if(pos.y > ((yMax-s)+center->y))
        {
            pos.y = yMin+s + center->y;
            particle->setPpos(pos);
            bOutSide = true;
        }
        else if(pos.y < ((yMin+s)+center->y))
        {
            pos.y = yMax-s + center->y;
            particle->setPpos(pos);
            bOutSide = true;
        }
        
        if(pos.z > ((zMax-s)+center->z))
        {
            pos.z = zMin+s + center->z;
            particle->setPpos(pos);
            bOutSide = true;
        }
        else if(pos.z < ((zMin+s)+center->z))
        {
            pos.z = zMax-s + center->z;
            particle->setPpos(pos);
            bOutSide = true;
        }
//        if(bOutSide)
//        {
//            particle->setDead(true);
//        }
    }

    void draw()
    {
        ofNoFill();
        ofSetColor(255, 100);
        ofDrawBox(getCenter(), xMax-xMin, yMax-yMin, zMax-zMin);
        ofSetColor(255, 0, 0, 100);
        ofDrawBox(getCenter(), xMax-xMin - getSpace()*2.0, yMax-yMin - getSpace()*2.0, zMax-zMin - getSpace()*2.0);
    }
    
    void setCenter(ofVec3f _center)
    {
        *center = _center;
    }
    
    void setCenterPtr(ofVec3f *_center)
    {
        if(bAllocatedCenter)
        {
            delete center;
            bAllocatedCenter = false;
        }
        center = _center;
    }
    
    ofVec3f &getCenter()
    {
        return *center;
    }
    
    ofVec3f *getCenterPtr()
    {
        return center;
    }
    
    ofVec3f *center;
    bool bAllocatedCenter;    
};