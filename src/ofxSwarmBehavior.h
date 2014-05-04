#pragma once

#include "ofxBehavior.h"

class ofxSwarmBehavior : public ofxBehavior
{
public:
    ofxSwarmBehavior();
    ~ofxSwarmBehavior();
    void setup();
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);
};