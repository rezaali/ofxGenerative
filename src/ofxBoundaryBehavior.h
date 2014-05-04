#pragma once

#include "ofxBehavior.h"

class ofxBoundaryBehavior : public ofxBehavior
{
public:
    ofxBoundaryBehavior();
    ~ofxBoundaryBehavior();
    void setup();
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);
    void setBoundary(float _left, float _right, float _top, float _bottom, float _near = 0, float _far = 0);
    float left;
    float right;
    float top;
    float bottom;
    float far;
    float near;
};
