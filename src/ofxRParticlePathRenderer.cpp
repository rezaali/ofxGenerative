#include "ofxRParticlePathRenderer.h"
#include "ofxParticlePathData.h"

ofxRParticlePathRenderer::ofxRParticlePathRenderer() : ofxRParticleRenderer()
{
    setup();
    setAdditiveBlending(true);
}

ofxRParticlePathRenderer::~ofxRParticlePathRenderer()
{
    if(bAllocatedLineWidth)
    {
        delete lineWidth;
    }
}

void ofxRParticlePathRenderer::setup()
{
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
        ofColor *clr = (*it)->getColorPtr();
        ofSetColor(*clr);
        glBegin(GL_LINE_STRIP);
        int length = data->getTrailLength();
        for(int i = 0; i < length; i++)
        {
            ofVec3f pos = data->trail[i];
            glVertex3f(pos.x,pos.y,pos.z);
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