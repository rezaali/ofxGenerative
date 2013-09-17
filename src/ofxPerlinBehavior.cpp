//
//  ofxDamperBehavior.cpp
//  Rezanator
//
//  Created by Syed Reza Ali on 4/17/13.
//
//

#include "ofxPerlinBehavior.h"
#include "ofxRParticle.h"

ofxPerlinBehavior::ofxPerlinBehavior() : ofxBehavior()
{
    setup();     
}

ofxPerlinBehavior::~ofxPerlinBehavior()
{
    if(bAllocatedNoiseScale)
    {
        delete noiseScale;
    }
}

void ofxPerlinBehavior::setup()
{
    bAllocatedNoiseScale = true;
    noiseScale = new float();
    *noiseScale = 0.025;

}

void ofxPerlinBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    float nx = ofSignedNoise((pos.z + pos.x) * (*noiseScale), ofGetElapsedTimef()*.1, particle->getID()*0.001);
    float ny = ofSignedNoise((pos.x + pos.y) * (*noiseScale), ofGetElapsedTimef()*.1, particle->getID()*0.001);
    float nz = ofSignedNoise((pos.y + pos.z) * (*noiseScale), ofGetElapsedTimef()*.1, particle->getID()*0.001);
    
    acc+=ofVec3f(nx, ny, nz)*(*magnitude)*dt;
}


void ofxPerlinBehavior::setNoiseScalePtr(float *_noiseScale)
{
    if(bAllocatedNoiseScale)
    {
        delete noiseScale;
        bAllocatedNoiseScale = false;
    }
    noiseScale = _noiseScale;
}

float *ofxPerlinBehavior::getNoiseScalePtr()
{
    return noiseScale; 
}