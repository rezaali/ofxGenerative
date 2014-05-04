#pragma once

#include "ofxBehavior.h"

class ofxVortexBehavior : public ofxBehavior
{
public:
    ofxVortexBehavior();
    ~ofxVortexBehavior();
    
    void setup();
    void update();
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);
    
    void setStartPt(ofVec3f _startPt);
    ofVec3f &getStartPt(); 
    ofVec3f *getStartPtPtr();
    void setStartPtPtr(ofVec3f *_startPt);
    bool bAllocatedStartPt;
    ofVec3f *startPt;

    void setEndPt(ofVec3f _endPt);
    ofVec3f &getEndPt();
    ofVec3f *getEndPtPtr();
    void setEndPtPtr(ofVec3f *_endPt);
    bool bAllocatedEndPt;
    ofVec3f *endPt;

    void setVaryAlongAxis(bool _bVaryAlongAxis);
    bool getVaryAlongAxis();
    void setVaryAlongAxisPtr(bool *_bVaryAlongAxis);
    bool *getVaryAlongAxisPtr();
    bool bAllocatedVaryAlongAxis;
    bool *bVaryAlongAxis;

    void setVaryFrequency(float _varyFrequency);
    float getVaryFrequency();
    void setVaryFrequencyPtr(float *_varyFrequency);
    float *getVaryFrequencyPtr();
    bool bAllocatedVaryFrequency;
    float *varyFrequency;
    
    
    void setSpeed(float _speed);
    float getSpeed();
    void setSpeedPtr(float *_speed);
    float *getSpeedPtr();
    bool bAllocatedSpeed;
    float *speed;

    void setTheta(float _theta);
    float theta;

private:
    ofVec3f se;
    ofVec3f sen;
    float dim;
};