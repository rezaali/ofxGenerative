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

#ifndef OFXLORENTZBEHAVIOR
#define OFXLORENTZBEHAVIOR

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

#endif
