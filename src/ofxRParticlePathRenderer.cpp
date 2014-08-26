#include "ofxRParticlePathRenderer.h"
#include "ofxParticlePathData.h"

ofxRParticlePathRenderer::ofxRParticlePathRenderer() : ofxRParticleRenderer()
{
    setup();
    setAdditiveBlending(true);
}

ofxRParticlePathRenderer::~ofxRParticlePathRenderer()
{
    if(bAllocatedMinAlpha)
    {
        delete minAlpha;
    }
    
    if(bAllocatedLineWidth)
    {
        delete lineWidth;
    }
}

void ofxRParticlePathRenderer::setup()
{
    bAllocatedMinAlpha = true;
    minAlpha = new float();
    setMinAlpha(1.0); 

    bAllocatedLineWidth = true;
    lineWidth = new float();
    setLineWidth(1.0);
}

void ofxRParticlePathRenderer::draw()
{
    activateBlending();
    ofSetLineWidth(*lineWidth);
    for(vector<ofxRParticle *>::iterator it = (*particles).begin(); it != (*particles).end(); ++it)
    {
        ofxParticlePathData *data = (ofxParticlePathData *) (*it)->getData();
        ofColor &clr = (*it)->getColor();
        glBegin(GL_LINE_STRIP);
        int length = data->getTrailLength();
        float norm = 0;
        for(int i = 0; i < length; ++i)
        {
            norm = i/(float)length;
            ofSetColor(clr, clr.a*MAX(norm, *minAlpha));
            ofVec3f tpos = data->trail[i];
            glVertex3fv(tpos.getPtr());
        }
        glEnd();
    }
}

void ofxRParticlePathRenderer::setLineWidth(float _lineWidth)
{
    *lineWidth = _lineWidth;
}

float* ofxRParticlePathRenderer::getLineWidthPtr()
{
    return lineWidth;
}

void ofxRParticlePathRenderer::setLineWidthPtr(float *_lineWidth)
{
    if(bAllocatedLineWidth)
    {
        delete lineWidth;
        bAllocatedLineWidth = false;
    }
    lineWidth = _lineWidth;
}

float ofxRParticlePathRenderer::getLineWidth()
{
    return *lineWidth;
}

float *ofxRParticlePathRenderer::getMinAlphaPtr()
{
    return minAlpha;
}

float ofxRParticlePathRenderer::getMinAlpha()
{
    return *minAlpha;
}

void ofxRParticlePathRenderer::setMinAlphaPtr(float *_minAlpha)
{
    if(bAllocatedMinAlpha)
    {
        delete minAlpha;
        bAllocatedMinAlpha = false;
    }
    minAlpha = _minAlpha;
}

void ofxRParticlePathRenderer::setMinAlpha(float _minAlpha)
{
    *minAlpha = _minAlpha;
}