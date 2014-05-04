#pragma once

#include "ofImage.h"
#include "ofEasyCam.h"
#include "ofVec3f.h"
#include "ofx1DExtruder.h"
#include "ofxRParticleRenderer.h"

class ofxRParticleGlowieRenderer : public ofxRParticleRenderer
{
public:
    ofxRParticleGlowieRenderer();
    virtual ~ofxRParticleGlowieRenderer();
    virtual void setup();
    virtual void draw();
    void setCamPtr(ofEasyCam *_cam);
    void setAxisAngleOffsets(ofx1DExtruder *_xAxis, ofx1DExtruder *_yAxis, ofx1DExtruder *_zAxis); 
    void billBoard(); 
    void setGlowImage(ofImage *_glow);
    
protected:
    ofImage *glow;
    ofVec3f objectLookAt; 
    ofEasyCam *cam;
    ofx1DExtruder *xAxis;
    ofx1DExtruder *yAxis;
    ofx1DExtruder *zAxis;
};
