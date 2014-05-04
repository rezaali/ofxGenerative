#pragma once

#include "ofxElectroStaticBehavior.h"

class ofxElectroStaticNeighborBehavior : public ofxElectroStaticBehavior
{
public:
    ofxElectroStaticNeighborBehavior();
    ~ofxElectroStaticNeighborBehavior();
    
    void setup();
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);
    
    float *getDistancePtr();
    void setDistancePtr(float *_distance);
    
    bool bAllocatedDistance;
    float *distance;
};
