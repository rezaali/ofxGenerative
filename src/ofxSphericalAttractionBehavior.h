#pragma once

#include "ofxBehavior.h"

class ofxSphericalAttractionBehavior : public ofxBehavior
{
public:
    ofxSphericalAttractionBehavior(); 
    virtual ~ofxSphericalAttractionBehavior();
    virtual void setup();
    virtual void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);

    ofVec3f *getPositionPtr();
    void setPositionPtr(ofVec3f *_position);
    ofVec3f& getPosition();
    void setPosition(ofVec3f _position);
    
    float *getRadiusPtr();
    void setRadiusPtr(float *_radius);
    float getRadius();
    void setRadius(float _radius);
    
    bool bAllocatedPosition;
    ofVec3f *position;
    
    bool bAllocatedRadius;
    float *radius;
    
};