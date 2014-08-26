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

void ofxBehavior::addFloatParam(string key, float value, float min, float max)
{
    floatParams[key] = new float();
    floatParamsRanges[key] = ofVec2f(min, max);
    floatParamsAllocation[key] = true;
    setFloatParam(key, value);
}

void ofxBehavior::removeFloatParam(string key)
{
    map<string, float *>::iterator it = floatParams.find(key);
    if(it != floatParams.end())
    {
        if(floatParamsAllocation[key])
        {
            float *param = it->second;
            delete param;
            floatParams.erase(it);
            floatParamsAllocation[key] = false;
        }
    }
}

void ofxBehavior::setFloatParam(string key, float value)
{
    map<string, float *>::iterator it = floatParams.find(key);
    if(it != floatParams.end())
    {
        *(it->second) = value;
    }
}

void ofxBehavior::setFloatParamPtr(string key, float *value)
{
    if(floatParams.find(key) != floatParams.end())
    {
        if(floatParamsAllocation[key])
        {
            float *param = floatParams[key];
            delete param;
            floatParams[key] = NULL;
            floatParamsAllocation[key] = false;
        }
        floatParams[key] = value;
    }
}

float ofxBehavior::getFloatParam(string key)
{
    if(floatParams.find(key) != floatParams.end())
    {
        return *floatParams[key];
    }
    return 0.0;
}

ofVec2f ofxBehavior::getFloatParamRange(string key)
{
    if(floatParamsRanges.find(key) != floatParamsRanges.end())
    {
        return floatParamsRanges[key];
    }
    return ofVec2f(0.0, 1.0);
}

float *ofxBehavior::getFloatParamPtr(string key)
{
    if(floatParams.find(key) != floatParams.end())
    {
        return floatParams[key];
    }
    return NULL;
}

map<string, float *> &ofxBehavior::getFloatParams()
{
    return floatParams;
}

map<string, ofVec2f> &ofxBehavior::getFloatParamsRanges()
{
    return floatParamsRanges;
}

void ofxBehavior::setFloatParams(map<string, float *> &params)
{
    map<string, float *>::iterator it = params.begin();
    map<string, float *>::iterator eit = params.end();
    for(; it != eit; ++it)
    {
        setFloatParamPtr(it->first, it->second);
    }
}

void ofxBehavior::deleteFloatParams()
{
    map<string, float *>::iterator it = floatParams.begin();
    map<string, float *>::iterator eit = floatParams.end();
    for(; it != eit; ++it)
    {
        string key = it->first;
        if(floatParamsAllocation[key])
        {
            float *param = floatParams[key];
            delete param;
            floatParams[key] = NULL;
            floatParamsAllocation[key] = false;
        }
    }
    floatParams.clear();
    floatParamsAllocation.clear();
    floatParamsRanges.clear();
}