#pragma once

#include "ofxBehavior.h"

class ofxHomingBehavior : public ofxBehavior
{
public:
    ofxHomingBehavior();
    virtual ~ofxHomingBehavior();
    void setup();
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);
};
