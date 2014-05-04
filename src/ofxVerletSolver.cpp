#include "ofxVerletSolver.h"
#include "ofxRParticle.h"

ofxVerletSolver::ofxVerletSolver() : ofxSolver()
{
    
}

ofxVerletSolver::~ofxVerletSolver()
{

}

void ofxVerletSolver::update(ofxRParticle* particle)
{
    if(!particle->isFixed())
    {
        ofVec3f *ppos = particle->getPposPtr();
        ofVec3f *pos = particle->getPosPtr();
        ofVec3f *vel = particle->getVelPtr();
        ofVec3f *acc = particle->getAccPtr();
        vel->set((*pos - *ppos));    
        ppos->set(*pos);
        vel->limit(particle->getVelocityLimit());
        particle->calculateAcceleration(*pos, *vel, *dt);
        *pos += *vel + *acc;
    }
}