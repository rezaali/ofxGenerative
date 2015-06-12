#include "ofxRParticleRenderer.h"

ofxRParticleRenderer::ofxRParticleRenderer()
{
    init();
}

void ofxRParticleRenderer::init()
{
    bAllocatedPointSize = true;
    pointSize = new float;
    setPointSize(5.0);
    bAllocatedAdditiveBlending = true;
    bAdditiveBlending = new bool;
    setAdditiveBlending(true);

    bAllocatedDepthTesting = true;
    bDepthTesting = new bool;
    setDepthTesting(false);
}

void ofxRParticleRenderer::setup()
{

}

ofxRParticleRenderer::~ofxRParticleRenderer()
{
    if(bAllocatedPointSize)
    {
        delete pointSize;
    }
    if(bAllocatedAdditiveBlending)
    {
        delete bAdditiveBlending;
    }
    if(bAllocatedDepthTesting)
    {
        delete bDepthTesting;
    }
}

void ofxRParticleRenderer::draw()
{
    activateBlending(); 
    glPointSize(getPointSize());
    glBegin(GL_POINTS);
    vector<ofxRParticle *>::iterator it = (*particles).begin();
    vector<ofxRParticle *>::iterator eit = (*particles).end();
    for(; it != eit; ++it)
    {
        ofxRParticle *p = (*it);
        ofVec3f &pos = p->getPos();
        ofColor &clr = p->getColor();
        ofSetColor(clr);
        glNormal3f(p->getRadius()*(getPointSize())*10.0,0,0);
        glVertex3fv(pos.getPtr());
    }
    glEnd();
}

void ofxRParticleRenderer::setParticleAlpha(float _alpha)
{
    vector<ofxRParticle *>::iterator it = (*particles).begin();
    vector<ofxRParticle *>::iterator eit = (*particles).end();
    for(; it != eit; ++it)
    {
        ofxRParticle *p = (*it);
        p->setColorAlpha(_alpha);
    }
}

void ofxRParticleRenderer::activateBlending()
{
    if(*bAdditiveBlending)
    {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
    }
    else
    {
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    }
    ofSetDepthTest(*bDepthTesting);
}

void ofxRParticleRenderer::setParticlesPtr(vector<ofxRParticle *> *_particles)
{
    particles = _particles;
}

void ofxRParticleRenderer::setPointSize(float _pointSize)
{
    *pointSize = _pointSize;
}

void ofxRParticleRenderer::setPointSizePtr(float *_pointSize)
{
    if(bAllocatedPointSize)
    {
        delete pointSize;
        bAllocatedPointSize = false;
    }
    pointSize = _pointSize;
}

float *ofxRParticleRenderer::getPointSizePtr()
{
    return pointSize;
}

float ofxRParticleRenderer::getPointSize()
{
    return *pointSize;
}

void ofxRParticleRenderer::setAdditiveBlending(bool _bAdditiveBlending)
{
    *bAdditiveBlending = _bAdditiveBlending;
}

void ofxRParticleRenderer::setAdditiveBlendingPtr(bool *_bAdditiveBlending)
{
    if(bAllocatedAdditiveBlending)
    {
        delete bAdditiveBlending;
        bAllocatedAdditiveBlending = false;
    }
    bAdditiveBlending = _bAdditiveBlending;
}

bool *ofxRParticleRenderer::getAdditiveBlendingPtr()
{
    return bAdditiveBlending;
}

bool ofxRParticleRenderer::getAdditiveBlending()
{
    return *bAdditiveBlending;
}

void ofxRParticleRenderer::setDepthTesting(bool _bDepthTesting)
{
    *bDepthTesting = _bDepthTesting;
}

void ofxRParticleRenderer::setDepthTestingPtr(bool *_bDepthTesting)
{
    if(bAllocatedDepthTesting)
    {
        delete bDepthTesting;
        bAllocatedDepthTesting = false;
    }
    bDepthTesting = _bDepthTesting;
   
}

bool *ofxRParticleRenderer::getDepthTestingPtr()
{
    return bDepthTesting;
}

bool ofxRParticleRenderer::getDepthTesting()
{
    return *bDepthTesting;
}