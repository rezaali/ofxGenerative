#pragma once

#include "ofxHomingBehavior.h"

class ofx2DHomingBehavior : public ofxHomingBehavior
{
public:
    ofx2DHomingBehavior() : ofxHomingBehavior()
    {}
    
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
    {
        ofVec3f delta = particle->getHome()-pos;
        delta.z = 0.0;
        particle->setDelta(delta);
        acc+=(delta)*(*magnitude)*dt;
    }
};