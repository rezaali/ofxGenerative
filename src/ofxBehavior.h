#pragma once

#include "ofMain.h"

class ofxRParticle; 

class ofxBehavior           //Affects the Particle, could be a field, attractor, spring, etc. [add acceleration to Particle]
{
public: 
    ofxBehavior();
    virtual ~ofxBehavior();
    void init();
    virtual void update();
    virtual void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);

    bool isEnabled();
    
    bool *getEnabledPtr();
    void setEnabledPtr(bool *_bEnabled);
    bool getEnabled();
    void setEnabled(bool _bEnabled);

    float *getMagnitudePtr();
    void setMagnitudePtr(float *_magnitude);
    float getMagnitude();
    void setMagnitude(float _magnitude);
    
    void addFloatParam(string key, float value, float min = 0.0, float max = 1.0);
    void removeFloatParam(string key);
    void setFloatParam(string key, float value);
    void setFloatParamPtr(string key, float *value);
    float getFloatParam(string key);
    float *getFloatParamPtr(string key);
    ofVec2f getFloatParamRange(string key);
    map<string, float *> &getFloatParams();
    map<string, ofVec2f> &getFloatParamsRanges();
    void setFloatParams(map<string, float *> &params);
    void deleteFloatParams();
    
protected:
    bool bAllocatedEnabled;
    bool *bEnabled;

    bool bAllocatedMagnitude;
    float *magnitude;
    
    map<string, float *> floatParams;
    map<string, ofVec2f> floatParamsRanges;
    map<string, bool> floatParamsAllocation;
};
