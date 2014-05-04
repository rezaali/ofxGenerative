#include "ofxElectroStaticNeighborBehavior.h"
#include "ofxNeighborParticleData.h"

ofxElectroStaticNeighborBehavior::ofxElectroStaticNeighborBehavior()
{
    setup();
}

ofxElectroStaticNeighborBehavior::~ofxElectroStaticNeighborBehavior()
{
    if(bAllocatedDistance)
    {
        delete distance;
    }
}

void ofxElectroStaticNeighborBehavior::setup()
{
    ofxElectroStaticBehavior::setup();
    bAllocatedDistance = true;
    distance = new float();
    *distance = 100.0;
}

void ofxElectroStaticNeighborBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    ofVec3f r = ofVec3f(0,0,0);
    ofxNeighborParticleData *data = (ofxNeighborParticleData *) particle->getData();
    data->clearNeighbors();
    for(vector<ofxRParticle *>::iterator it = (*particles).begin(); it != (*particles).end(); it++)
    {
        ofxRParticle *other = (*it);
        ofxNeighborParticleData *otherData = (ofxNeighborParticleData *) other->getData();
        if(other->getID() != particle->getID())
        {
            ofVec3f direction = other->getPpos() - pos;
            float dist = direction.length();
            if(dist < (*distance) && !otherData->hasNeighbor(particle))
            {
                data->addNeighbor(other, ((*distance)-dist)/(*distance));
            }
            direction /= dist*dist;
            r+=direction*particle->getRadius();
        }
    }
    r /= ((float)particles->size());
    acc-=r*(*magnitude)*dt;
}

float *ofxElectroStaticNeighborBehavior::getDistancePtr()
{
    return distance;
}

void ofxElectroStaticNeighborBehavior::setDistancePtr(float *_distance)
{
    if(bAllocatedDistance)
    {
        delete distance;
        bAllocatedDistance = false;
    }
    distance = _distance;
}