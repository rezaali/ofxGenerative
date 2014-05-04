#pragma once

#include "ofxRParticleData.h"
#include "ofxRParticle.h"

class ofxNeighborParticleData : public ofxRParticleData
{
public:
    ofxNeighborParticleData() : ofxRParticleData()
    {
        
    }
    
    ~ofxNeighborParticleData()
    {
        clearNeighbors();
    }
    
    void clearNeighbors()
    {
        neighbors.clear();
        distances.clear();
    }
    
    void addNeighbor(ofxRParticle *n, float d)
    {
        neighbors.push_back(n);
        distances.push_back(d);
    }
    
    bool hasNeighbor(ofxRParticle *n)
    {
        for(vector<ofxRParticle *>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
        {
            if((*it)->getID() == n->getID())
            {
                return true;
                break;
            }
        }
        return false;
    }
    
    vector<ofxRParticle *> neighbors;
    vector<float> distances;
};