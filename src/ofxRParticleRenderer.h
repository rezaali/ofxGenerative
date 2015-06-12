#pragma once

#include "ofxRParticle.h"

class ofxRParticleRenderer   //Renderers the particle(s)...
{
public:
    ofxRParticleRenderer();
    virtual ~ofxRParticleRenderer();
    void init();
    virtual void setup(); 
    virtual void draw();
    void setParticlesPtr(vector<ofxRParticle *> *_particles);
  
    virtual void activateBlending();
    void setPointSize(float _pointSize);
    void setPointSizePtr(float *_pointSize);
    float *getPointSizePtr();
    float getPointSize();
    
    void setParticleAlpha(float _alpha);
    void setAdditiveBlending(bool _bAdditiveBlending);
    void setAdditiveBlendingPtr(bool *_bAdditiveBlending);
    bool *getAdditiveBlendingPtr();
    bool getAdditiveBlending();
    
    void setDepthTesting(bool _bDepthTesting);
    void setDepthTestingPtr(bool *_bDepthTesting);
    bool *getDepthTestingPtr();
    bool getDepthTesting();

    
protected:
    vector<ofxRParticle *> *particles;
    
    bool bAllocatedAdditiveBlending;
    bool *bAdditiveBlending;

    bool bAllocatedDepthTesting;
    bool *bDepthTesting;

    bool bAllocatedPointSize;
    float *pointSize;
};