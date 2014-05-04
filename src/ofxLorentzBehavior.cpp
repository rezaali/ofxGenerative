#include "ofxLorentzBehavior.h"
#include "ofxRParticle.h" 

ofxLorentzBehavior::ofxLorentzBehavior() : ofxBehavior()
{
    setup();
}

ofxLorentzBehavior::~ofxLorentzBehavior()
{
    if(bAllocatedCurrent)
    {
        delete current;
    }
    
    if(bAllocatedStartPt)
    {
        delete startPt;
    }
    
    if(bAllocatedEndPt)
    {
        delete endPt;
    }
    
    if(bAllocatedTheta)
    {
        delete theta;
    }
    
    if(bAllocatedSpeed)
    {
        delete speed;
    }
}

void ofxLorentzBehavior::setup()
{
    bAllocatedCurrent = true;
    bAllocatedStartPt = true;
    bAllocatedEndPt = true;
    bAllocatedTheta = true;
    bAllocatedSpeed = true;
    
    current = new float();
    startPt = new ofVec3f();
    endPt = new ofVec3f();
    theta = new float();
    speed = new float();

    float dim = 1000.0;
    *theta = 0.0;
    *speed = .00;
    *current = cos(*theta);
    
    startPt->x = 0.0;
    startPt->y = 0.0;
    startPt->z = -dim;
    
    endPt->x = 0.0;
    endPt->y = 0.0;
    endPt->z = dim;
}

void ofxLorentzBehavior::update()
{
    *theta+= *speed;
    *current = cos(*theta);
    se = (*startPt) - (*endPt);
    sen = se.getNormalized(); 
}

void ofxLorentzBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    ofVec3f sp = (*startPt) - pos;              //start point minus particle position
    ofVec3f spn = sp.getNormalized();                 //normalized direction of: s->e
    
    float t = spn.dot(sen) * se.length();
    
    ofVec3f closestPointOnWire = *startPt + t*sen;
    ofVec3f rv = closestPointOnWire - pos;
    ofVec3f rvn = rv.getNormalized();
    float disPts = rv.length();
    
    float b = (*current)/(TWO_PI*disPts);     //if disPts = 0, this blows up...
    ofVec3f bv = sen.getCrossed(rvn)*b;
    ofVec3f f = particle->radius*vel.getCrossed(bv);
    acc+=f*(*magnitude)*dt;
}

float *ofxLorentzBehavior::getCurrentPtr()
{
    return current;
}

void ofxLorentzBehavior::setCurrentPtr(float *_current)
{
    if(bAllocatedCurrent)
    {
        delete current;
        bAllocatedCurrent = false;
    }
    current = _current;
}

ofVec3f *ofxLorentzBehavior::getStartPtPtr()
{
    return startPt;
}

void ofxLorentzBehavior::setStartPtPtr(ofVec3f *_startPt)
{
    if(bAllocatedStartPt)
    {
        delete startPt;
        bAllocatedStartPt = false;
    }
    startPt = _startPt;
}

ofVec3f *ofxLorentzBehavior::getEndPtPtr()
{
    return endPt; 
}

void ofxLorentzBehavior::setEndPtPtr(ofVec3f *_endPt)
{
    if(bAllocatedEndPt)
    {
        delete endPt;
        bAllocatedEndPt = false;
    }
    endPt = _endPt;
}

float *ofxLorentzBehavior::getThetaPtr()
{
    return theta; 
}

void ofxLorentzBehavior::setThetaPtr(float *_theta)
{
    if(bAllocatedTheta)
    {
        delete theta;
        bAllocatedTheta = false;
    }
    theta = _theta;
}

float *ofxLorentzBehavior::getSpeedPtr()
{
    return speed; 
}

void ofxLorentzBehavior::setSpeedPtr(float *_speed)
{
    if(bAllocatedSpeed)
    {
        delete speed;
        bAllocatedSpeed = false;
    }
    speed = _speed;
}