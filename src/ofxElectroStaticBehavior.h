#pragma once

#include "ofxBehavior.h"
#include "ofxRParticle.h"

class ofxElectroStaticBehavior : public ofxBehavior
{
public:
    ofxElectroStaticBehavior();
    virtual ~ofxElectroStaticBehavior();
    virtual void setup();
    virtual void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);
    void setParticlesPtr(vector<ofxRParticle *> *_particles);
    vector<ofxRParticle *> *particles;
};