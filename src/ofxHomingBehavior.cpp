#include "ofxHomingBehavior.h"
#include "ofxRParticle.h"

ofxHomingBehavior::ofxHomingBehavior() : ofxBehavior()
{
    setup(); 
}

ofxHomingBehavior::~ofxHomingBehavior()
{
    
}

void ofxHomingBehavior::setup()
{
    
}

void ofxHomingBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    ofVec3f delta = particle->getHome()-pos;
    particle->setDelta(delta);
    acc+=(delta)*(*magnitude)*dt;
}
