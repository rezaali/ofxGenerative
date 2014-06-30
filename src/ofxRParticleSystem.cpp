#include "ofxRParticleSystem.h"
#include "ofxRParticle.h"
#include "ofxVerletSolver.h"

ofxRParticleSystem::ofxRParticleSystem()
{
    init();
}

ofxRParticleSystem::~ofxRParticleSystem()
{
    if(bAllocatedDt)
    {
        delete dt;
    }
    
    if(bAllocatedDamping)
    {
        delete damping;
    }
    
    if(bAllocatedRestitution)
    {
        delete restitution;
    }
    
    if(bAllocatedAccLimit)
    {
        delete accLimit;
    }
    
    if(bAllocatedVelLimit)
    {
        delete velLimit;
    }
    
    if(bAllocatedCount)
    {
        delete count;
    }

    delete solver;
    if(bAllocatedRenderer)
    {
        delete renderer;
    }
    
    vector<ofxBehavior *>::iterator bit = behaviors.begin();
    vector<ofxBehavior *>::iterator ebit = behaviors.end();
    for(; bit != ebit; ++bit)
    {
        delete (*bit);
    }
    behaviors.clear();
    
    clear();
}

void ofxRParticleSystem::clear()
{
    vector<ofxRParticle *>::iterator it = particles.begin();
    vector<ofxRParticle *>::iterator eit = particles.end();
    for(; it != eit; ++it)
    {
        delete (*it);
    }
    particles.clear();
    uniqueIDs = 0;
}

void ofxRParticleSystem::init()
{
    uniqueIDs = 0;
    bAllocatedCount = true;
    count = new int;

    bAllocatedDamping = true;
    damping = new float;
    
    bAllocatedRestitution = true;
    restitution = new float;

    bAllocatedAccLimit = true;
    accLimit = new float;

    bAllocatedVelLimit = true;
    velLimit = new float;

    bAllocatedDt = true;
    dt = new float;
    
    setDt(1.0);
    setCount(0);
    setDamping(.25);
    setRestitution(1.0);
    setAccerationLimit(5.0);
    setVelocityLimit(10.0);

    bAllocatedRenderer = true;
    renderer = new ofxRParticleRenderer();
    renderer->setParticlesPtr(&particles);

    solver = NULL;
    setSolver(new ofxVerletSolver());
    solver->setDtPtr(dt);
}

void ofxRParticleSystem::update()
{
    vector<ofxBehavior *>::iterator bit = behaviors.begin();
    vector<ofxBehavior *>::iterator ebit = behaviors.end();
    for(; bit != ebit; ++bit)
    {
        (*bit)->update();
    }
    int id = 0;
    vector<ofxRParticle *>::iterator it = particles.begin();
    vector<ofxRParticle *>::iterator eit = particles.end();
    for(; it != eit; ++it)
    {
        if((*it)->isDead())
        {
            ofxRParticle *p = (*it);
            particles.erase(it);
            delete p;
            uniqueIDs--;
            setCount(uniqueIDs); 
        }
        else
        {
            solver->update(*it);            
            (*it)->setID(id);            
            id++;
        }
    }
}

void ofxRParticleSystem::draw()
{
    renderer->draw();
}

void ofxRParticleSystem::addBehavior(ofxBehavior *b)
{
    behaviors.push_back(b);
}

void ofxRParticleSystem::addParticle(ofxRParticle* p)
{
    uniqueIDs++;
    p->setID(uniqueIDs);
    p->setDampingPtr(damping);
    p->setRestitutionPtr(restitution);
    p->setAccerationLimitPtr(accLimit);
    p->setVelocityLimitPtr(velLimit);
    p->setBehaviorVectorPtr(&behaviors);
    particles.push_back(p);
    setCount(uniqueIDs);
}

void ofxRParticleSystem::setDt(float _dt)
{
    *dt = _dt;
}

void ofxRParticleSystem::setDtPtr(float *_dt)
{
    if(bAllocatedDt)
    {
        delete dt;
        bAllocatedDt = false;
    }
    dt = _dt;
    solver->setDtPtr(dt);
}

float* ofxRParticleSystem::getDtPtr()
{
    return dt;
}

float ofxRParticleSystem::getDt()
{
    return *dt;
}

void ofxRParticleSystem::setDamping(float _damping)
{
    *damping = _damping;
}

void ofxRParticleSystem::setDampingPtr(float *_damping)
{
    if(bAllocatedDamping)
    {
        delete damping;
        bAllocatedDamping = false;
    }
    damping = _damping;
}

float ofxRParticleSystem::getDamping()
{
    return *damping;
}

float* ofxRParticleSystem::getDampingPtr()
{
    return damping;
}

void ofxRParticleSystem::setRestitution(float _restitution)
{
    *restitution = _restitution;
}

void ofxRParticleSystem::setRestitutionPtr(float *_restitution)
{
    if(bAllocatedRestitution)
    {
        delete restitution;
        bAllocatedRestitution = false;
    }
    restitution = _restitution;
}

float* ofxRParticleSystem::getRestitutionPtr()
{
    return restitution;
}

float ofxRParticleSystem::getRestitution()
{
    return *restitution;
}

void ofxRParticleSystem::setVelocityLimit(float _vlimit)
{
    *velLimit = _vlimit;
}

void ofxRParticleSystem::setVelocityLimitPtr(float *_vlimit)
{
    if(bAllocatedVelLimit)
    {
        delete velLimit;
        bAllocatedVelLimit = false;
    }
    velLimit = _vlimit;
}

float* ofxRParticleSystem::getVelocityLimitPtr()
{
    return velLimit;
}

float ofxRParticleSystem::getVelocityLimit()
{
    return *velLimit;
}

void ofxRParticleSystem::setAccerationLimit(float _alimit)
{
    *accLimit = _alimit;
}

void ofxRParticleSystem::setAccerationLimitPtr(float *_alimit)
{
    if(bAllocatedAccLimit)
    {
        delete accLimit;
        bAllocatedAccLimit = false;
    }
    accLimit = _alimit;
}

float* ofxRParticleSystem::getAccelerationLimitPtr()
{
    return accLimit;
}

float ofxRParticleSystem::getAccelerationLimit()
{
    return *accLimit;
}

void ofxRParticleSystem::setCount(int _count)
{
    *count = _count;
}

void ofxRParticleSystem::setCountPtr(int *_count)
{
    if(bAllocatedCount)
    {
        delete count;
        bAllocatedCount = false;
    }
    count = _count;
}

int* ofxRParticleSystem::getCountPtr()
{
    return count;
}

int ofxRParticleSystem::getCount()
{
    return *count;
}

ofxRParticle * ofxRParticleSystem::removeParticle(ofxRParticle *particle)
{
    vector<ofxRParticle *>::iterator it = particles.begin();
    vector<ofxRParticle *>::iterator eit = particles.end();
    for(; it != eit; ++it)
    {
        ofxRParticle *p = (*it);
        if(p == particle)
        {
            uniqueIDs--;
            setCount(uniqueIDs);
            particles.erase(it);
            return p; 
        }
    }
}

vector<ofxRParticle *>& ofxRParticleSystem::getParticles()
{
    return particles;
}

vector<ofxRParticle *>* ofxRParticleSystem::getParticlesPtr()
{
    return &particles; 
}

ofxRParticle* ofxRParticleSystem::getParticle(int index)
{
    if(index < particles.size() && index >= 0)
    {
        return particles[index];
    }
    else
    {
        return particles[0];
    }
}

void ofxRParticleSystem::setRendererPtr(ofxRParticleRenderer *_renderer)
{
    if(bAllocatedRenderer)
    {
        if(renderer != NULL)
        {
            delete renderer;
        }
        bAllocatedRenderer = false;
    }
    renderer = _renderer;
    renderer->setParticlesPtr(&particles);
}

ofxRParticleRenderer* ofxRParticleSystem::getRendererPtr()
{
    return renderer;
}

void ofxRParticleSystem::setSolver(ofxSolver *_solver)
{
    if(solver != NULL)
    {
        delete solver;
    }
    solver = _solver;
    solver->setDtPtr(dt);
}

ofxSolver* ofxRParticleSystem::getSolver()
{
    return solver;
}

void ofxRParticleSystem::randomize(float magnitude)
{
    vector<ofxRParticle *>::iterator it = particles.begin();
    vector<ofxRParticle *>::iterator eit = particles.end();
    for(; it != eit; ++it)
    {
        ofVec3f pos = (*it)->getPos();
        (*it)->setPpos(pos + ofVec3f(ofRandom(-magnitude, magnitude), ofRandom(-magnitude, magnitude), ofRandom(-magnitude, magnitude)));
    }
}

void ofxRParticleSystem::randomize2D(float magnitude)
{
    vector<ofxRParticle *>::iterator it = particles.begin();
    vector<ofxRParticle *>::iterator eit = particles.end();
    for(; it != eit; ++it)
    {
        ofVec3f pos = (*it)->getPos();
        (*it)->setPpos(pos + ofVec3f(ofRandom(-magnitude, magnitude), ofRandom(-magnitude, magnitude), 0));
    }
}