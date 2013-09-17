/**********************************************************************************
 
 Copyright (C) 2013 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

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