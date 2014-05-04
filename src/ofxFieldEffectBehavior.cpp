#include "ofxFieldEffectBehavior.h"
#include "ofxRParticle.h"

ofxFieldEffectBehavior::ofxFieldEffectBehavior() : ofxBehavior()
{
    setup();
}

ofxFieldEffectBehavior::~ofxFieldEffectBehavior()
{

}

void ofxFieldEffectBehavior::setup()
{

}

void ofxFieldEffectBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    acc+=field->getVector(pos.x, pos.y).limited(particle->getAccerationLimit())*(*magnitude)*dt;
}

void ofxFieldEffectBehavior::setField(ofxField2D *_field)
{
    field = _field;
}

ofxField2D* ofxFieldEffectBehavior::getField()
{
    return field;
}