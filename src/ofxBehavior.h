#pragma once

#include "ofMain.h"

class ofxRParticle; 

class ofxBehavior           //Affects the Particle, could be a field, attractor, spring, etc. [add acceleration to Particle]
{
public: 
    ofxBehavior();
    virtual ~ofxBehavior();
    void init();
    virtual void update();
    virtual void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);

    bool isEnabled();
    
    bool *getEnabledPtr();
    void setEnabledPtr(bool *_bEnabled);
    bool getEnabled();
    void setEnabled(bool _bEnabled);

    float *getMagnitudePtr();
    void setMagnitudePtr(float *_magnitude);
    float getMagnitude();
    void setMagnitude(float _magnitude);
    
protected:
    bool bAllocatedEnabled;
    bool *bEnabled;

    bool bAllocatedMagnitude;
    float *magnitude;
};
