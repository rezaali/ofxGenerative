#include "ofxBehavior.h"
#include "ofxRParticle.h"

ofxBehavior::ofxBehavior()
{
    init();
}

ofxBehavior::~ofxBehavior()
{
    if(bAllocatedMagnitude)
    {
        delete magnitude;
    }
    if(bAllocatedEnabled)
    {
        delete bEnabled;
    }
}

void ofxBehavior::init()
{
    bAllocatedEnabled = true;
    bEnabled = new bool;
    setEnabled(true);
    
    bAllocatedMagnitude = true;
    magnitude = new float;
    setMagnitude(1.0);
}

void ofxBehavior::update()
{
    
}

void ofxBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
 
}

bool *ofxBehavior::getEnabledPtr()
{
    return bEnabled;
}

void ofxBehavior::setEnabledPtr(bool *_bEnabled)
{
    if(bAllocatedEnabled)
    {
        delete bEnabled;
        bAllocatedEnabled = false;
    }
    bEnabled = _bEnabled;
}

bool ofxBehavior::getEnabled()
{
    return *bEnabled;
}

void ofxBehavior::setEnabled(bool _bEnabled)
{
    *bEnabled = _bEnabled;
}

bool ofxBehavior::isEnabled()
{
    return *bEnabled;
}

float* ofxBehavior::getMagnitudePtr()
{
    return magnitude;
}

void ofxBehavior::setMagnitudePtr(float *_magnitude)
{
    if(bAllocatedMagnitude)
    {
        delete magnitude;
        bAllocatedMagnitude = false;
    }
    magnitude = _magnitude;
}

float ofxBehavior::getMagnitude()
{
    return *magnitude; 
}

void ofxBehavior::setMagnitude(float _magnitude)
{
    *magnitude = _magnitude; 
}