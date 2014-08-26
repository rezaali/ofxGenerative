#pragma once

#include "ofxBehavior.h"

class ofxBufferEffectorBehavior : public ofxBehavior
{
public:
    ofxBufferEffectorBehavior();
    virtual ~ofxBufferEffectorBehavior();
    virtual void setup();
    virtual void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt);
    void setBuffer(float *_buffer, int _bufferSize);
    float *getBuffer();
    int getBufferSize();
    float *buffer;
    int bufferSize;
};
