#pragma once

#include "ofxBehavior.h"

class ofxSuperShapeBehavior : public ofxBehavior
{
public:
    ofxSuperShapeBehavior() : ofxBehavior()
    {
        setup();
    }
    
    ~ofxSuperShapeBehavior()
    {
        deleteFloatParams();
    }
    
    void setup()
    {
        addFloatParam("RADIUS1", 10.0, 0.0, 50.0);
        addFloatParam("A1", 1.0, 0.0, 5.0);
        addFloatParam("B1", 1.0, 0.0, 20.0);
        addFloatParam("M1", 0.0, 0.0, 20.0);
        addFloatParam("N11", 2.0, -100, 100);
        addFloatParam("N21", 4.0, -100, 100);
        addFloatParam("N31", 8.0, -100, 100);
        
        addFloatParam("RADIUS2", 10.0, 0.0, 50.0);
        addFloatParam("A2", 1.0, 0.0, 5.0);
        addFloatParam("B2", 1.0, 0.0, 20.0);
        addFloatParam("M2", 0.0, 0.0, 20.0);
        addFloatParam("N12", 2.0, -100, 100);
        addFloatParam("N22", 4.0, -100, 100);
        addFloatParam("N32", 8.0, -100, 100);
    }
    
    void update()
    {
        iRadius1 = getFloatParam("RADIUS1");
        a1 = getFloatParam("A1");
        b1 = getFloatParam("B1");
        m1 = getFloatParam("M1");
        n11 = getFloatParam("N11");
        n21 = getFloatParam("N21");
        n31 = getFloatParam("N31");
        
        iRadius2 = getFloatParam("RADIUS2");
        a2 = getFloatParam("A2");
        b2 = getFloatParam("B2");
        m2 = getFloatParam("M2");
        n12 = getFloatParam("N12");
        n22 = getFloatParam("N22");
        n32 = getFloatParam("N32");
    }
    
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
    {
        ofxMeshParticleData *data = (ofxMeshParticleData *) particle->getData();
        ofVec2f texcoord = data->getVertex()->getTexcoord();
        
        float theta = -PI + TWO_PI*texcoord.x;
        float phi = -HALF_PI + PI*texcoord.y;
        
        float raux1 = powf(fabs((1.0/a1)*(cos((m1*theta/4.0)))),n21) + powf(fabs((1.0/b1)*(sin(m1*theta/4.0))),n31);
        float r1 = iRadius1*powf((raux1),(-1.0/n11));
        float raux2 = powf(fabs((1.0/a2)*(cos((m2*phi/4.0)))),n22) + powf(fabs((1.0/b2)*(sin(m2*phi/4.0))),n32);
        float r2 = iRadius2*powf((raux2),(-1.0/n12));
        
        ofVec3f delta = ofVec3f(r1*cos(theta)*r2*cos(phi), r1*sin(theta)*r2*cos(phi), r1*r2*sin(phi));
        delta -= pos;
        acc+=(delta)*(*magnitude)*dt;
    }
    
    float iRadius1; //UI:0.0,50.0,10.0
    float a1;		//UI:0.0,5.0,1.0
    float b1;		//UI:0.0,5.0,1.0
    float m1;		//UI:0.0,20.0,0.0
    float n11; 		//UI:-100.0,100.0,2.0
    float n21; 		///UI:-100.0,100.0,4.0
    float n31;		//UI:-100.0,100.0,8.0
    
    float iRadius2; //UI:0.0,50.0,10.0
    float a2;		//UI:0.0,5.0,1.0
    float b2;		//UI:0.0,5.0,1.0
    float m2;		//UI:0.0,20.0,0.0
    float n12; 		//UI:-100.0,100.0,2.0
    float n22; 		//UI:-100.0,100.0,8.0
    float n32;		//UI:-100.0,100.0,4.0
};