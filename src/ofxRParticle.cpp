#include "ofxRParticle.h"

ofxRParticle::ofxRParticle()
{
    init();
}

ofxRParticle::ofxRParticle(ofVec3f _pos)
{
    init();
    pos = _pos;
    ppos = pos;		//previous position
    home = pos;
}

ofxRParticle::~ofxRParticle()
{
    if(bAllocatedDamping)
    {
        delete damping;
    }
    if(bAllocatedRestitution)
    {
        delete restitution;
    }
    if(bAllocatedVelLimit)
    {
        delete velLimit;
    }
    if(bAllocatedAccLimit)
    {
        delete accLimit;
    }
    if(data != NULL)
    {
        delete data;
    }
}

void ofxRParticle::init()
{
    orientation = ofQuaternion(0.0, ofVec3f(0, 0, 1));
    pos = ofVec3f(0,0,0);           //Current Position
    ppos = ofVec3f(0,0,0);          //Previous Position
    home = ofVec3f(0,0,0);          //Original Home Position
    delta = ofVec3f(0,0,0);          //Delta Home - Pos
    vel = ofVec3f(0,0,0);           //Velocity Vector
    acc = ofVec3f(0,0,0);           //Acceleration Vector
    color = ofColor(255,0,0,255);   //Default Color: Red
    fixed = false;                  //Fixed or Dynamic
    
    data = NULL;
    
    damping = new float;
    *damping = 0.9;
    restitution = new float;
    *restitution = 0.9;    
    accLimit = new float;
    velLimit = new float;
    
    bAllocatedDamping = true;
    bAllocatedRestitution = true;
    bAllocatedAccLimit = true;
    bAllocatedVelLimit = true;
    
    setRadius(1.0);                  //Particles Radius (All Particles are spherical for now)
    mass = 1.0;                     //Mass of particle, important for f = ma
    lifeTime = 1.0;                 //How Long the Particle Lives for
    dead = false;                   //Whether the Particle is still alive
}

ofVec3f& ofxRParticle::calculateAcceleration(ofVec3f &pos, ofVec3f &vel, float dt)
{
    ppos.set(pos); 
    acc.set(0);
    vector<ofxBehavior *>::iterator bit = (*behaviors).begin();
    vector<ofxBehavior *>::iterator ebit = (*behaviors).end();
    for(; bit != ebit; ++bit)
    {
        ofxBehavior *b = (*bit);
        if(b->isEnabled())
        {
            b->actUpon(this, pos, vel, acc, dt);
        }
    }
    
    updateSpringForces();
    updateExternalForces();    
    acc.limit(*accLimit);
    return acc;
}

void ofxRParticle::updateSpringForces()
{
    vector<ofVec3f *>::iterator it = springForces.begin();
    vector<ofVec3f *>::iterator eit = springForces.end();
    for(; it != eit; ++it)
    {
        acc += *(*it)/(float)springForces.size();
    }
}

void ofxRParticle::updateExternalForces()
{
    vector<ofVec3f *>::iterator it = externalForces.begin();
    vector<ofVec3f *>::iterator eit = externalForces.end();
    for(; it != eit; ++it)
    {
        acc += *(*it)/(float)externalForces.size();
    }
}

void ofxRParticle::setRadius(float _radius)
{
    radius = _radius; hradius = .5*radius;
}

void ofxRParticle::setPos(ofVec3f _pos)
{
    pos = _pos;
}

void ofxRParticle::setPpos(ofVec3f _ppos)
{
    ppos = _ppos;
}

void ofxRParticle::setVel(ofVec3f _vel)
{
    vel = _vel;
}

void ofxRParticle::setAcc(ofVec3f _acc)
{
    acc = _acc;
}

void ofxRParticle::setHome(ofVec3f _home)
{
    home = _home;
}

void ofxRParticle::setDelta(ofVec3f _delta)
{
    delta = _delta;
}

void ofxRParticle::setHome(float _x, float _y, float _z)
{
    home.x = _x; home.y = _y; home.z = _z;
}

void ofxRParticle::setColor(ofColor _color)
{
    color = _color;
}

void ofxRParticle::setColor(ofColor _color, float _alpha)
{
    color = _color;
    setColorAlpha(_alpha);
}

void ofxRParticle::setDamping(float _damping)
{
    *damping = _damping;
}

void ofxRParticle::setDampingPtr(float *_damping)
{
    if(bAllocatedDamping)
    {
        delete damping;
        bAllocatedDamping = false;
    }
    damping = _damping;
}

float& ofxRParticle::getDamping()
{
    return *damping; 
}

void ofxRParticle::setRestitution(float _restitution)
{
    *restitution = _restitution;
}

void ofxRParticle::setRestitutionPtr(float *_restitution)
{
    if(bAllocatedRestitution)
    {
        delete restitution;
        bAllocatedRestitution = false;
    }
    restitution = _restitution;
}

float& ofxRParticle::getRestitution()
{
    return *restitution;
}

void ofxRParticle::setAccerationLimit(float _acclimit)
{
    *accLimit = _acclimit;
}

void ofxRParticle::setAccerationLimitPtr(float *_acclimit)
{
    if(bAllocatedAccLimit)
    {
        delete accLimit;
        bAllocatedAccLimit = false;
    }
    accLimit = _acclimit;
}

float& ofxRParticle::getAccerationLimit()
{
    return *accLimit;
}

void ofxRParticle::setVelocityLimit(float _vellimit)
{
    *velLimit = _vellimit;
}

void ofxRParticle::setVelocityLimitPtr(float *_vellimit)
{
    if(bAllocatedVelLimit)
    {
        delete velLimit;
        bAllocatedVelLimit = false;
    }
    velLimit = _vellimit;
}

float& ofxRParticle::getVelocityLimit()
{
    return *velLimit;
}

void ofxRParticle::clearExternalForces()
{
    externalForces.clear();
}

void ofxRParticle::addExternalForce(ofVec3f *_extforce)
{
    externalForces.push_back(_extforce);
}

void ofxRParticle::addSpringForce(ofVec3f *_extforce)
{
    springForces.push_back(_extforce);
}

void ofxRParticle::setFixed(bool _fixed)
{
    fixed = _fixed;
}

bool ofxRParticle::isFixed()
{
    return fixed;
}

void ofxRParticle::addForce(ofVec3f _force)
{
    (acc) += _force;
}

ofVec3f* ofxRParticle::getHomePtr()
{
    return &home;
}

ofVec3f* ofxRParticle::getPposPtr()
{
    return &ppos;
}

ofVec3f* ofxRParticle::getPosPtr()
{
    return &pos;
}

ofVec3f* ofxRParticle::getVelPtr()
{
    return &vel;
}

ofVec3f* ofxRParticle::getAccPtr()
{
    return &acc;
}

ofVec3f& ofxRParticle::getPos()
{
    return pos;
}

ofVec3f& ofxRParticle::getHome()
{
    return home;
}

ofVec3f& ofxRParticle::getDelta()
{
    return delta;
}

ofVec3f& ofxRParticle::getPpos()
{
    return ppos;
}

ofVec3f& ofxRParticle::getVel()
{
    return vel;
}

ofVec3f& ofxRParticle::getAcc()
{
    return acc;
}

ofColor& ofxRParticle::getColor()
{
    return color;
}

ofColor* ofxRParticle::getColorPtr()
{
    return &color;
}

void ofxRParticle::setColorAlpha(float _alpha)
{
    color.a = _alpha;
}

float ofxRParticle::getColorAlpha()
{
    return color.a;
}

float ofxRParticle::getRadius()
{
    return radius;
}

int ofxRParticle::getID()
{
    return pid;
}

void ofxRParticle::setID(int _pid)
{
    pid = _pid;
}

float ofxRParticle::getLifeTime()
{
    return lifeTime;
}

bool ofxRParticle::isDead()
{
    return dead;
}

void ofxRParticle::setDead(bool _dead)
{
    dead = _dead;
}

void ofxRParticle::setBehaviorVectorPtr(vector<ofxBehavior *> *_behaviors)
{
    behaviors = _behaviors;
}

void ofxRParticle::setData(ofxRParticleData *_data)
{
    data = _data;
}

ofxRParticleData *ofxRParticle::getData()
{
    return data; 
}

ofQuaternion &ofxRParticle::getOrientation()
{
    return orientation;
}

void ofxRParticle::setOrientation(ofQuaternion _orientation)
{
    orientation = _orientation;
}

ofQuaternion *ofxRParticle::getOrientationPtr()
{
    return &orientation;
}