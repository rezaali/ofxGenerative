#pragma once

#include "ofxBehavior.h"
#include "ofxSphericalAttractionBehavior.h"

class ofxRingAttractionBehavior : public ofxSphericalAttractionBehavior
{
public:
    ofxRingAttractionBehavior();
    ~ofxRingAttractionBehavior();
    void setup();
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);
    void update();    
  
    ofQuaternion *getOrientationPtr();
    void setOrientationPtr(ofQuaternion *_orientation);
    ofQuaternion& getOrientation();
    void setOrientation(ofQuaternion _orientation);
    
    bool bAllocatedOrientation;
    ofQuaternion *orientation;

    ofVec3f *getNormalPtr();
    void setNormalPtr(ofVec3f *_normal);
    ofVec3f& getNormal();
    void setNormal(ofVec3f _normal);
    
    bool bAllocatedNormal;
    ofVec3f *normal; 
};
