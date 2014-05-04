#include "ofxSpringSystem.h"
#include "ofMesh.h"

ofxSpringSystem::ofxSpringSystem()
{
    init();
}

void ofxSpringSystem::init()
{
    uniqueIDs = 0;
}

ofxSpringSystem::~ofxSpringSystem()
{
    clear();
}

void ofxSpringSystem::clear()
{
    
    for (vector<ofxSpring * >::iterator it = springs.begin(); it != springs.end(); ++it)
    {
        ofxSpring *s = *it;
        delete s;
    }
    springs.clear();
}

void ofxSpringSystem::update(float dt)
{
    for(vector<ofxSpring*>::iterator it = springs.begin(); it != springs.end(); ++it)
    {
        (*it)->update(dt);
    }
}

void ofxSpringSystem::draw()
{
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_LINES);
    for(vector<ofxSpring*>::iterator it = springs.begin(); it != springs.end(); ++it)
    {
        mesh.addColor((*it)->getColor());
        mesh.addVertex((*it)->getPos(0));
        mesh.addColor((*it)->getColor());
        mesh.addVertex((*it)->getPos(1));
    }
    mesh.drawWireframe();
}

void ofxSpringSystem::addSpring(ofxSpring *s)
{
    uniqueIDs++;
    s->setID(uniqueIDs);
    springs.push_back(s);
}

int ofxSpringSystem::getCount()
{
    return (int)springs.size();
}

ofxSpring *ofxSpringSystem::getSpring(int index)
{
    if(index < springs.size() && index >= 0)
    {
        return springs[index];
    }
    else {
        return NULL;
    }
}

void ofxSpringSystem::setRestDistance(float _restDist)
{
    for(vector<ofxSpring*>::iterator it = springs.begin(); it != springs.end(); ++it)
    {
        (*it)->setRestDistance(_restDist);
    }
}

void ofxSpringSystem::setK(float _k)
{
    for(vector<ofxSpring*>::iterator it = springs.begin(); it != springs.end(); ++it)
    {
        (*it)->setK(_k);
    }
}

vector<ofxSpring*> &ofxSpringSystem::getSprings()
{
    return springs;
}