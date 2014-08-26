#pragma once

#include "ofxRParticleRenderer.h"

class ofxRParticlePathRenderer : public ofxRParticleRenderer
{
public:
    ofxRParticlePathRenderer();
    virtual ~ofxRParticlePathRenderer();
    
    virtual void setup();
    virtual void draw();
    
    void setLineWidth(float _lineWidth);
    float* getLineWidthPtr();
    void setLineWidthPtr(float *_lineWidth);
    float getLineWidth();
    
    void setMinAlpha(float _minAlpha);
    float* getMinAlphaPtr();
    void setMinAlphaPtr(float *_minAlpha);
    float getMinAlpha();
    
    bool bAllocatedLineWidth; 
    float *lineWidth;
    
    bool bAllocatedMinAlpha;
    float *minAlpha;
};