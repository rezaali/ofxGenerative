#pragma once

#include "ofxBehavior.h"

class ofxLorentzBehavior : public ofxBehavior
{
public:
    ofxLorentzBehavior();
    ~ofxLorentzBehavior();
    void setup();
    void update(); 
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);
    
    float *getCurrentPtr();
    void setCurrentPtr(float *_current);
    bool bAllocatedCurrent;
    float *current;

    ofVec3f *getStartPtPtr();
    void setStartPtPtr(ofVec3f *_startPt);
    bool bAllocatedStartPt;
    ofVec3f *startPt;

    ofVec3f *getEndPtPtr();
    void setEndPtPtr(ofVec3f *_endPt);
    bool bAllocatedEndPt;
    ofVec3f *endPt;

    float *getThetaPtr();
    void setThetaPtr(float *_theta);
    bool bAllocatedTheta;
    float *theta;

    float *getSpeedPtr();
    void setSpeedPtr(float *_speed);
    bool bAllocatedSpeed;
    float *speed;
    
    ofVec3f se;
    ofVec3f sen;
};