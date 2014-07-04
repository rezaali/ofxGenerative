#pragma once

#include "ofxRParticle.h"

struct Derivative
{
    ofVec3f dpdt;          // derivative of position: velocity
    ofVec3f dvdt;          // derivative of velocity: acceleration
};

class ofxSolver             //Solves the Particle's Physical Simulation
{
public:
    ofxSolver();
    virtual ~ofxSolver();
    virtual void init();
    virtual void setup(); 
    virtual Derivative evaluate(ofxRParticle* particle, ofVec3f &iPos, ofVec3f &iVel, float _dt, Derivative &d);
    virtual void update(ofxRParticle* particle);

    float *getDtPtr();
    float getDt();
    void setDtPtr(float *_dt);
    void setDt(float _dt);

protected:
    bool bAllocatedDt;
    float *dt;
    Derivative zero, a, b, c, d; 
};
