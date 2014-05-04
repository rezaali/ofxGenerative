#pragma once

#include "ofxBehavior.h"
#include "ofxField2D.h"

class ofxFieldEffectBehavior : public ofxBehavior
{
public:
    ofxFieldEffectBehavior();
    ~ofxFieldEffectBehavior();
    void setup();
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);
    void setField(ofxField2D *_field);
    ofxField2D* getField();
    ofxField2D* field;
};

