#pragma once

#include "ofxBehavior.h"
#include "ofxField2D.h"

class ofxFieldEffectorBehavior : public ofxBehavior
{
public:
    ofxFieldEffectorBehavior();
    ~ofxFieldEffectorBehavior();
    void setup();
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);
    void setField(ofxField2D *_field);
    ofxField2D* getField();
    
    float *getDensityPtr();
    void setDensityPtr(float *_density);
    float getDensity();
    void setDensity(float _density);

    ofxField2D* field;
    bool bAllocatedDensity;
    float *density;
};

