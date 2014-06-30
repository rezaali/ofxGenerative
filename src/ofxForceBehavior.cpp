#include "ofxForceBehavior.h"
#include "ofxRParticle.h"

ofxForceBehavior::ofxForceBehavior() : ofxBehavior()
{
    setup();
}

ofxForceBehavior::~ofxForceBehavior()
{
    if(bAllocatedForce)
    {
        delete force;
    }
}

void ofxForceBehavior::setup()
{
    bAllocatedForce = true;
    force = new ofVec3f(0,0,0);
}

void ofxForceBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    acc+= (*force)*(*magnitude)*dt;
}

ofVec3f* ofxForceBehavior::getForcePtr()
{
    return force;
}

void ofxForceBehavior::setForcePtr(ofVec3f *_force)
{
    if(bAllocatedForce)
    {
        delete force;
        bAllocatedForce = false;
    }
    force = _force;
}

ofVec3f& ofxForceBehavior::getForce()
{
    return *force;
}

void ofxForceBehavior::setForce(ofVec3f _force)
{
    *force = _force;
}