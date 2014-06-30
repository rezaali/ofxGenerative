#pragma once

#include "ofxBehavior.h"

class ofxForceBehavior : public ofxBehavior
{
public:
    ofxForceBehavior();
    ~ofxForceBehavior();
    void setup();
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);

    ofVec3f *getForcePtr();
    void setForcePtr(ofVec3f *_force);
    ofVec3f& getForce();
    void setForce(ofVec3f _force);
    
    bool bAllocatedForce;
    ofVec3f *force;
};
