#include "ofxVortexBehavior.h"
#include "ofxRParticle.h"

ofxVortexBehavior::ofxVortexBehavior() : ofxBehavior()
{
    setup();
}

ofxVortexBehavior::~ofxVortexBehavior()
{
    
}

void ofxVortexBehavior::setup()
{
    bAllocatedStartPt = true;
    bAllocatedEndPt = true;
    bAllocatedVaryAlongAxis = false;
    bAllocatedVaryFrequency = true;
    bAllocatedSpeed = true;

    varyFrequency = new float();
    bVaryAlongAxis = new bool();
    startPt = new ofVec3f();
    endPt = new ofVec3f();
    speed = new float();
    theta = 0.0;
    
    *bVaryAlongAxis = false;
    *varyFrequency = 0.0;
    *speed = 0.01;
    
    dim = 1000.0;
    startPt->x = 0.0;
    startPt->y = 0.0;
    startPt->z = dim*.5;
    
    endPt->x = 0.0;
    endPt->y = 0.0;
    endPt->z = -dim*.5;
}

void ofxVortexBehavior::update()
{
    se = (*startPt) - (*endPt);
    sen = se.getNormalized();
    dim = se.length();
    theta += (*speed); 
}

void ofxVortexBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    ofVec3f sp = (*startPt) - pos;
    float length = sp.dot(sen);
    ofVec3f ptOnWire = length*-sen+(*startPt);
    ofVec3f rv = pos - ptOnWire;
    ofVec3f rvn = rv.getNormalized();
    ofVec3f f = (rv.getCrossed(se)/powf(rv.length(), 2.0))*(*magnitude)*dt;
    
    if(*bVaryAlongAxis)
    {
        acc += sin((*varyFrequency)*length/dim+theta)*f;
    }
    else
    {
        acc += f;
    }
}

void ofxVortexBehavior::setStartPt(ofVec3f _startPt)
{
    *startPt = _startPt;
}

ofVec3f &ofxVortexBehavior::getStartPt()
{
    return *startPt;
}

ofVec3f *ofxVortexBehavior::getStartPtPtr()
{
    return startPt;
}

void ofxVortexBehavior::setStartPtPtr(ofVec3f *_startPt)
{
    if(bAllocatedStartPt)
    {
        delete startPt;
        bAllocatedStartPt = false;
    }
    startPt = _startPt;
}

void ofxVortexBehavior::setEndPt(ofVec3f _endPt)
{
    *endPt = _endPt;
}

ofVec3f &ofxVortexBehavior::getEndPt()
{
    return *endPt;
}


ofVec3f *ofxVortexBehavior::getEndPtPtr()
{
    return endPt;
}

void ofxVortexBehavior::setEndPtPtr(ofVec3f *_endPt)
{
    if(bAllocatedEndPt)
    {
        delete endPt;
        bAllocatedEndPt = false;
    }
    endPt = _endPt;
}

void ofxVortexBehavior::setVaryAlongAxis(bool _bVaryAlongAxis)
{
    *bVaryAlongAxis = _bVaryAlongAxis;
}

bool ofxVortexBehavior::getVaryAlongAxis()
{
    return *bVaryAlongAxis;
}

void ofxVortexBehavior::setVaryAlongAxisPtr(bool *_bVaryAlongAxis)
{
    if(bAllocatedVaryAlongAxis)
    {
        delete bVaryAlongAxis;
        bAllocatedVaryAlongAxis = false;
    }
    bVaryAlongAxis = _bVaryAlongAxis;
}

bool *ofxVortexBehavior::getVaryAlongAxisPtr()
{
    return bVaryAlongAxis;
}

void ofxVortexBehavior::setVaryFrequency(float _varyFrequency)
{
    *varyFrequency = _varyFrequency; 
}

float ofxVortexBehavior::getVaryFrequency()
{
    return *varyFrequency;
}

float *ofxVortexBehavior::getVaryFrequencyPtr()
{
    return varyFrequency;
}

void ofxVortexBehavior::setVaryFrequencyPtr(float *_varyFrequency)
{
    if(bAllocatedVaryFrequency)
    {
        delete varyFrequency;
        bAllocatedVaryFrequency = false;
    }
    varyFrequency = _varyFrequency;
}

void ofxVortexBehavior::setSpeed(float _speed)
{
    *speed = _speed;
}

float ofxVortexBehavior::getSpeed()
{
    return *speed;
}

void ofxVortexBehavior::setSpeedPtr(float *_speed)
{
    if(bAllocatedSpeed)
    {
        delete speed;
        bAllocatedSpeed = false;
    }
    speed = _speed;
}

float *ofxVortexBehavior::getSpeedPtr()
{
    return speed;
}

void ofxVortexBehavior::setTheta(float _theta)
{
    theta = _theta;
}