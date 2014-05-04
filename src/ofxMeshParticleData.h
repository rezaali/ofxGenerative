#pragma once

#include <deque>
#include "ofxVertex.h"
#include "ofxRParticleData.h"

class ofxMeshParticleData : public ofxRParticleData
{
public:
    ofxMeshParticleData(ofxVertex *_vertex) : ofxRParticleData()
    {
        vertex = _vertex;
    }
    
    ~ofxMeshParticleData()
    {
        trail.clear();
    }
    
    ofxVertex * getVertex()
    {
        return vertex;
    }
    
    void setTailLengthPtr(int *_tailLength)
    {
        tailLength = _tailLength;
    }
    
    void setVertex(ofxVertex *_vertex)
    {
        vertex = _vertex;
    }
    
    void addToTrail(ofVec3f &pos)
    {
        trail.push_front(pos);
        while(trail.size() > *tailLength)
        {
            trail.pop_back();
        }
    }
    
    int getTrailLength()
    {
        return trail.size();
    }
    
    void clearTrail()
    {
        trail.clear();
    }
    
    void setTrailPos(ofVec3f &pos)
    {
        int length = trail.size();
        for(int i = 0; i < length; i++)
        {
            trail[i] = pos;
        }
    }
    
    deque<ofVec3f> trail;
    ofxVertex *vertex;
    int *tailLength;
};