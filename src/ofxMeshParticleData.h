#pragma once

#include <deque>
#include "ofxVertex.h"
#include "ofxParticlePathData.h"

class ofxMeshParticleData : public ofxParticlePathData
{
public:
    ofxMeshParticleData(ofxVertex *_vertex) : ofxParticlePathData()
    {
        vertex = _vertex;
    }
    
    ~ofxMeshParticleData()
    {
        
    }
    
    ofxVertex * getVertex()
    {
        return vertex;
    }
    
    void setVertex(ofxVertex *_vertex)
    {
        vertex = _vertex;
    }
    
    ofxVertex *vertex;
};