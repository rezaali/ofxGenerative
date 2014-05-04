#pragma once

#include "ofxBehavior.h"

class ofxDistorterBehavior : public ofxBehavior
{
public:
    ofxDistorterBehavior();
    ~ofxDistorterBehavior();
    void setup();
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);

    ofVec3f *getPositionPtr();
    void setPositionPtr(ofVec3f *_position);
    ofVec3f& getPosition();
    void setPosition(ofVec3f _position);
    
    float *getRadiusPtr();
    void setRadiusPtr(float *_radius);
    float getRadius();
    void setRadius(float _radius);

    float *getExpFactorPtr();
    void setExpFactorPtr(float *_expFactor);
    float getExpFactor();
    void setExpFactor(float _expFactor);

    
    bool bAllocatedPosition;
    ofVec3f *position;

    bool bAllocatedRadius;
    float *radius;

    bool bAllocatedExpFactor;
    float *expFactor;
};