#include "ofxDamperBehavior.h"

ofxDamperBehavior::ofxDamperBehavior() : ofxBehavior()
{
    setup(); 
}

ofxDamperBehavior::~ofxDamperBehavior()
{

}

void ofxDamperBehavior::setup()
{

}

void ofxDamperBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    acc -= vel*(*magnitude)*dt;
}