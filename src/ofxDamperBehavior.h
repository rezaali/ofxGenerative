#pragma once

#include "ofxBehavior.h"

class ofxDamperBehavior : public ofxBehavior
{
public:
    ofxDamperBehavior();
    ~ofxDamperBehavior();
    void setup();
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);
};
