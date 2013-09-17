/**********************************************************************************
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
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

#ifndef OFXVORTEXBEHAVIOR
#define OFXVORTEXBEHAVIOR

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

#endif
