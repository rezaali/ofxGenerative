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
    ofVec3f &ppos = particle->getPpos();
    ofVec3f &pos = particle->getPos();
    ofVec3f &vel = particle->getVel();
    ofVec3f &acc = particle->getAcc();
    vel.set((pos - ppos));
    vel.limit(particle->getVelocityLimit());
    particle->calculateAcceleration(pos, vel, getDt());
    if(!particle->isFixed())
    {
        pos += vel + acc;
    }
}