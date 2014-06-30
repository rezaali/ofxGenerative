#pragma once

#include "ofxRParticleData.h"

class ofxParticlePathData : public ofxRParticleData
{
public:
    ofxParticlePathData() : ofxRParticleData()
    {}
    
    ~ofxParticlePathData()
    {
        trail.clear();
    }
    
    void setTailLengthPtr(int *_tailLength)
    {
        tailLength = _tailLength;
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
    int *tailLength;
};