#pragma once 

#include "ofxBoundaryBehavior.h"

class ofxToroidalBoundaryBehavior : public ofxBoundaryBehavior
{
public:
    ofxToroidalBoundaryBehavior() : ofxBoundaryBehavior()
    {
        setup();
    }
    
    ~ofxToroidalBoundaryBehavior()
    {
        if(bAllocatedSpace)
        {
            delete space;
        }
    }
    
    void setup()
    {
        space = new float();
        bAllocatedSpace = true;
        setSpace(1.0);
    }
    
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
    {
        float s = getSpace();
        bool bOutSide = false;
        
        if(pos.x > (xMax-s))
        {
            pos.x = xMin+s;
            particle->setPpos(pos);
            bOutSide = true;
        }
        else if(pos.x < (xMin+s))
        {
            pos.x = xMax-s;
            particle->setPpos(pos);
            bOutSide = true;
        }
        
        if(pos.y > (yMax-s))
        {
            pos.y = yMin+s;
            particle->setPpos(pos);
            bOutSide = true;
        }
        else if(pos.y < (yMin+s))
        {
            pos.y = yMax-s;
            particle->setPpos(pos);
            bOutSide = true;
        }
        
        if(pos.z > (zMax-s))
        {
            pos.z = zMin+s;
            particle->setPpos(pos);
            bOutSide = true;
        }
        else if(pos.z < (zMin+s))
        {
            pos.z = zMax-s;
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
        ofDrawBox(0,0,0, xMax-xMin, yMax-yMin, zMax-zMin);

        ofSetColor(255, 0, 0, 100);
        ofDrawBox(0,0,0, xMax-xMin - getSpace()*2.0, yMax-yMin - getSpace()*2.0, zMax-zMin - getSpace()*2.0);
    }

    void setSpace(float _space)
    {
        *space = _space;
    }
    
    void setSpacePtr(float *_space)
    {
        if(bAllocatedSpace)
        {
            delete space;
            bAllocatedSpace = false;
        }
        space = _space;
    }
    
    float getSpace()
    {
        return *space;
    }
    
    float *getSpacePtr()
    {
        return space;
    }
    
    float *space;
    bool bAllocatedSpace;
};