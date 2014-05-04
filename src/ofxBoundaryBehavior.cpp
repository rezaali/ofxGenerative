#include "ofxBoundaryBehavior.h"
#include "ofxRParticle.h"

ofxBoundaryBehavior::ofxBoundaryBehavior() : ofxBehavior()
{
    setup();
}

ofxBoundaryBehavior::~ofxBoundaryBehavior()
{
    
}
void ofxBoundaryBehavior::setup()
{
    setBoundary(0, 0, ofGetWidth(), ofGetHeight());
}

void ofxBoundaryBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    if(pos.x < left){
        pos.x = left;
        vel.x *= particle->getRestitution();
    }
    else if(pos.x > right)
    {
        pos.x = right;
        vel.x *= particle->getRestitution();
    }
    
    if(pos.y < top){
        pos.y = top;
        vel.y *= particle->getRestitution();
    }
    else if(pos.y > bottom)
    {
        pos.y = bottom;
        vel.y *= particle->getRestitution();
    }
    
    if(pos.z > near)
    {
        pos.z = near;
        vel.z *= (*particle->restitution);
    }
    else if(pos.z < far)
    {
        pos.z = far;
        vel.z *= (*particle->restitution);
    }
}

void ofxBoundaryBehavior::setBoundary(float _left, float _top, float _right, float _bottom, float _near, float _far)
{
    left = _left;
    right = _right;
    top = _top;
    bottom = _bottom;
    near = _near;
    far = _far;
}
