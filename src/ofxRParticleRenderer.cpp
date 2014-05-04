#include "ofxRParticleRenderer.h"

ofxRParticleRenderer::ofxRParticleRenderer()
{
    init();
}

void ofxRParticleRenderer::init()
{
    bAllocatedPointSize = true;
    pointSize = new float;
    setPointSize(1.0);
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
    //
////    glDisable(GL_DEPTH_TEST);
////    glEnableClientState( GL_VERTEX_ARRAY );
////    glEnableClientState( GL_COLOR_ARRAY );
////    glVertexPointer( 3, GL_FLOAT, sizeof(ofxRParticle *), &(*particles)[0]->pos);
////    glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(ofxRParticle *),  &(*particles)[0]->color );
//    glPointSize(*pointSize);
////    glDrawArrays( GL_POINTS, 0, (*particles).size() );
////    
////    glDisableClientState( GL_VERTEX_ARRAY );
////    glDisableClientState( GL_COLOR_ARRAY );

    glPointSize(*pointSize);
    glBegin(GL_POINTS);
    for(vector<ofxRParticle *>::iterator it = (*particles).begin(); it != (*particles).end(); ++it)
    {
        ofVec3f *pos = (*it)->getPosPtr();     
        ofColor *clr = (*it)->getColorPtr();
        ofSetColor(*clr);
        glNormal3f((*it)->getRadius()*(*pointSize)*10.0,0,0);
        glVertex3f(pos->x,pos->y,pos->z);
    }
    glEnd();
    
        
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