#pragma once

#include "ofxBehavior.h"

class ofxPerlinBehavior : public ofxBehavior
{
public:
    ofxPerlinBehavior();
    ~ofxPerlinBehavior();
    
    void setup();
    virtual void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);
    
    float *getNoiseScalePtr();
    void setNoiseScalePtr(float *_noiseScale);

    bool bAllocatedNoiseScale;
    float *noiseScale;
};
