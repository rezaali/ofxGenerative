#include "ofxFieldEffectorBehavior.h"
#include "ofxRParticle.h"

ofxFieldEffectorBehavior::ofxFieldEffectorBehavior() : ofxBehavior()
{
    setup();
}

ofxFieldEffectorBehavior::~ofxFieldEffectorBehavior()
{
    if(bAllocatedDensity)
    {
        delete density;
    }
}

void ofxFieldEffectorBehavior::setup()
{
    bAllocatedDensity = true;
    density = new float;
    setDensity(1.0);
}

void ofxFieldEffectorBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    
    field->input(pos.x, pos.y, pos.x+acc.x, pos.y+acc.y, (*density)*(*magnitude));
}

void ofxFieldEffectorBehavior::setField(ofxField2D *_field)
{
    field = _field;
}

ofxField2D* ofxFieldEffectorBehavior::getField()
{
    return field;
}

float *ofxFieldEffectorBehavior::getDensityPtr()
{
    return density;
}

void ofxFieldEffectorBehavior::setDensityPtr(float *_density)
{
    if(bAllocatedDensity)
    {
        delete density;
        bAllocatedDensity = false;
    }    
    density = _density;
}

float ofxFieldEffectorBehavior::getDensity()
{
    return *density;
}

void ofxFieldEffectorBehavior::setDensity(float _density)
{
    *density = _density; 
}
