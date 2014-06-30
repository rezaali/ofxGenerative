#pragma once

#include "ofMain.h"
#include "ofxRParticleData.h"
#include "ofxBehavior.h"

class ofxRParticle
{
public:
	ofxRParticle();
	ofxRParticle(ofVec3f _pos);
	virtual ~ofxRParticle();	
	virtual void init();
    ofVec3f& calculateAcceleration(ofVec3f &pos, ofVec3f &vel, float dt);
    virtual void updateSpringForces();
    virtual void updateExternalForces();

	void setRadius(float _radius);
    void setPos(ofVec3f _pos);
    void setPpos(ofVec3f _ppos);
    void setVel(ofVec3f _vel);
    void setAcc(ofVec3f _acc);
    void setHome(ofVec3f _home);
    void setDelta(ofVec3f _delta);
    void setHome(float _x, float _y, float _z);
    void setColor(ofColor _color);
    void setColor(ofColor _color, float _alpha);
    void setDamping(float _damping);
    void setDampingPtr(float *_damping);
    float& getDamping(); 
    void setRestitution(float _restitution);
    void setRestitutionPtr(float *_restitution);
    float& getRestitution();
    void setAccerationLimit(float _acclimit);
    void setAccerationLimitPtr(float *_acclimit);
    float& getAccerationLimit();
    void setVelocityLimit(float _vellimit);
    void setVelocityLimitPtr(float *_vellimit);
    float& getVelocityLimit();
    void clearExternalForces();
    void addExternalForce(ofVec3f *_extforce);
    void addSpringForce(ofVec3f *_extforce);
    void setFixed(bool _fixed);
    bool isFixed();
    void addForce(ofVec3f _force);

    ofQuaternion &getOrientation();
    void setOrientation(ofQuaternion _orientation);
    ofQuaternion *getOrientationPtr();
    
	ofVec3f* getHomePtr();
    ofVec3f* getPposPtr(); 
    ofVec3f* getPosPtr();
    ofVec3f* getVelPtr();
    ofVec3f* getAccPtr();
	ofVec3f& getPos();
	ofVec3f& getHome();
    ofVec3f& getPpos();
    ofVec3f& getDelta();
    ofVec3f& getVel();
	ofVec3f& getAcc();
	ofColor& getColor();
    ofColor* getColorPtr();
    void setColorAlpha(float _alpha);
    float getColorAlpha();
    float getRadius();
	int getID();
    void setID(int _pid);
    float getLifeTime();
    bool isDead();
    void setDead(bool _dead);
    void setBehaviorVectorPtr(vector<ofxBehavior *> *_behaviors);
    void setData(ofxRParticleData *_data);
    ofxRParticleData *getData(); 
    
    vector<ofxBehavior *> *behaviors;    //Pointer to Dynamic Behaviors
    ofQuaternion orientation;
	ofVec3f pos;
    ofVec3f vel;
    ofVec3f acc;
    ofVec3f home;
    ofVec3f ppos;  //Properties
    ofVec3f delta;
    
    vector<ofVec3f *> externalForces;
    vector<ofVec3f *> springForces;

    ofxRParticleData *data;
    
    //Per Particle Properties
   	int pid;                            //Particle ID
    int type;                           //Base, verse, etc.
    bool dead;
	bool fixed;
	float radius;
    float hradius;
	float mass;
    float lifeTime;
	ofColor color;
    
    bool bAllocatedDamping;
    bool bAllocatedRestitution;
    bool bAllocatedAccLimit;
    bool bAllocatedVelLimit;

    //Global Particle Properties
    float *damping;
    float *restitution;
	float *accLimit;
    float *velLimit;
};