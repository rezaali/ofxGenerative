#pragma once

#include "ofMain.h"
#include "ofxSolver.h"
#include "ofxRParticle.h"
#include "ofxRParticleRenderer.h"

class ofxRParticleSystem
{    
public:
    ofxRParticleSystem();
    ~ofxRParticleSystem();
    
    void clear();
    
    void init();
    void update();
    void draw();
    
    void addBehavior(ofxBehavior *b);
    void addParticle(ofxRParticle* p);

    void setDt(float _dt);
    void setDtPtr(float *_dt);
    float *getDtPtr();
    float getDt();
    
    void setDamping(float _damping);
    void setDampingPtr(float *_damping);
    float *getDampingPtr();
    float getDamping();
    
    void setRestitution(float _restitution);
    void setRestitutionPtr(float *_restitution);
    float *getRestitutionPtr();
    float getRestitution();
    
    void setVelocityLimit(float _vlimit);
    void setVelocityLimitPtr(float *_vlimit);
    float *getVelocityLimitPtr();
    float getVelocityLimit();    
    
    void setAccerationLimit(float _alimit);
    void setAccerationLimitPtr(float *_alimit);
    float *getAccelerationLimitPtr();
    float getAccelerationLimit();
    
    int getCount();
    
    ofxRParticle * removeParticle(ofxRParticle *particle); 
    
    vector<ofxRParticle *> &getParticles();
    vector<ofxRParticle *> *getParticlesPtr();
    ofxRParticle* getParticle(int index);
    
    void setRendererPtr(ofxRParticleRenderer *_renderer);
    ofxRParticleRenderer *getRendererPtr();
    
    void setSolver(ofxSolver *_solver);
    ofxSolver *getSolver();
    
    void randomize(float magnitude);
    void randomize2D(float magnitude); 
    
protected:
    vector<ofxRParticle *> particles;
    vector<ofxBehavior *> behaviors;
    
    bool bAllocatedRenderer;
    ofxRParticleRenderer *renderer;

    bool bAllocatedSolver;
    ofxSolver *solver;
    
    bool bAllocatedDt;
    float *dt;
    
    bool bAllocatedDamping;
	float *damping;
    
    bool bAllocatedRestitution;
    float *restitution;
    
    bool bAllocatedAccLimit;
	float *accLimit;

    bool bAllocatedVelLimit;
    float *velLimit;
};