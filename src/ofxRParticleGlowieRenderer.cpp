#include "ofxRParticleGlowieRenderer.h"
#include "ofxRParticle.h"

ofxRParticleGlowieRenderer::ofxRParticleGlowieRenderer() : ofxRParticleRenderer()
{
    setup();
    setAdditiveBlending(true); 
}

ofxRParticleGlowieRenderer::~ofxRParticleGlowieRenderer()
{

}

void ofxRParticleGlowieRenderer::setup()
{
    objectLookAt = ofVec3f(0,0,1);    
}

void ofxRParticleGlowieRenderer::draw()
{
    activateBlending();
    ofSetRectMode(OF_RECTMODE_CENTER);
    billBoard();
    vector<ofxRParticle *>::iterator it = (*particles).begin();
    vector<ofxRParticle *>::iterator eit = (*particles).end();    
    for(; it != eit; ++it)
    {
        glPushMatrix();
        ofVec3f &pos = (*it)->getPos();
        glTranslatef(pos.x, pos.y, pos.z);
        ofRotate(angle, axis.x, axis.y, axis.z);
        ofSetColor((*it)->getColor());
        float r = (*it)->getRadius();
        glow->draw(0, 0, r, r);
        glPopMatrix();
    }
    ofSetRectMode(OF_RECTMODE_CORNER);
    
}

void ofxRParticleGlowieRenderer::setAxisAngleOffsets(ofx1DExtruder *_xAxis, ofx1DExtruder *_yAxis, ofx1DExtruder *_zAxis)
{
    xAxis = _xAxis;
    yAxis = _yAxis;
    zAxis = _zAxis;
}

void ofxRParticleGlowieRenderer::setCamPtr(ofEasyCam *_cam)
{
    cam = _cam; 
}

void ofxRParticleGlowieRenderer::setGlowImage(ofImage *_glow)
{
    glow = _glow;
}

void ofxRParticleGlowieRenderer::billBoard()
{
    ofVec3f camPos = cam->getPosition();
    ofQuaternion camQuat = cam->getOrientationQuat();
    
    ofVec3f objLookAt = ofVec3f(0,0,1);
    ofVec3f objPos = ofVec3f(0,0,0);
    ofQuaternion objQuat;
    objQuat.makeRotate(0, objLookAt);
    
    camQuat *= objQuat;
    camQuat.getRotate(angle, axis);
}