#include "ofxSolver.h"
#include "ofxRParticle.h"

ofxSolver::ofxSolver()
{
    init();
}

ofxSolver::~ofxSolver()
{
    if(bAllocatedDt)
    {
        delete dt;
    }
}

void ofxSolver::init()
{
    zero.dpdt.set(0);
    zero.dvdt.set(0);
    dt = new float;
    bAllocatedDt = true;
    setDt(1.0);
}

void ofxSolver::setup()
{
    
}

Derivative ofxSolver::evaluate(ofxRParticle* particle, ofVec3f &iPos, ofVec3f &iVel, float _dt, Derivative &d)
{
    ofVec3f p = iPos + d.dpdt*_dt;
    ofVec3f v = iVel + d.dvdt*_dt;
    
    Derivative output;
    output.dpdt = v;
    output.dvdt = particle->calculateAcceleration(p, v, _dt);
    return output;
}

void ofxSolver::update(ofxRParticle* particle)
{
    ofVec3f &pos = particle->getPos();
    ofVec3f &vel = particle->getVel();
    
    a = evaluate(particle, pos, vel, 0.0f, zero);
    b = evaluate(particle, pos, vel, (getDt()/2.0f), a);
    c = evaluate(particle, pos, vel, (getDt()/2.0f), b);
    d = evaluate(particle, pos, vel, getDt(), c);

    if(!particle->isFixed())
    {
        pos += (getDt()/6.0f) * (a.dpdt + 2.0f*(b.dpdt + c.dpdt) + d.dpdt);
        vel += (getDt()/6.0f) * (a.dvdt + 2.0f*(b.dvdt + c.dvdt) + d.dvdt);
        vel.limit(particle->getVelocityLimit());
    }
}

float *ofxSolver::getDtPtr()
{
    return dt;
}

float ofxSolver::getDt()
{
    return *dt;
}

void ofxSolver::setDtPtr(float *_dt)   //in case we set DT from the sketch
{
    if(bAllocatedDt)
    {
        delete dt;
        bAllocatedDt = false;
    }
    dt = _dt;
}

void ofxSolver::setDt(float _dt)
{
    *dt = _dt;
}