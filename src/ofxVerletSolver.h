#pragma once

#include "ofxSolver.h"

class ofxVerletSolver : public ofxSolver
{
public:
    ofxVerletSolver();
    ~ofxVerletSolver();
    void update(ofxRParticle* particle);
protected:
};
