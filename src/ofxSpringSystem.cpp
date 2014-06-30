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
    vector<ofxSpring * >::iterator it = springs.begin();
    vector<ofxSpring * >::iterator eit = springs.end();
    for (; it != eit; ++it)
    {
        delete (*it);
    }
    springs.clear();
}

void ofxSpringSystem::update(float dt)
{
    vector<ofxSpring * >::iterator it = springs.begin();
    vector<ofxSpring * >::iterator eit = springs.end();
    for (; it != eit; ++it)
    {
        (*it)->update(dt);
    }
}

void ofxSpringSystem::draw()
{
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_LINES);
    vector<ofxSpring * >::iterator it = springs.begin();
    vector<ofxSpring * >::iterator eit = springs.end();
    for (; it != eit; ++it)
    {
        mesh.addColor((*it)->getColor(0));
        mesh.addVertex((*it)->getPos(0));
        mesh.addColor((*it)->getColor(1));
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
    vector<ofxSpring * >::iterator it = springs.begin();
    vector<ofxSpring * >::iterator eit = springs.end();
    for (; it != eit; ++it)
    {
        (*it)->setRestDistance(_restDist);
    }
}

void ofxSpringSystem::setK(float _k)
{
    vector<ofxSpring * >::iterator it = springs.begin();
    vector<ofxSpring * >::iterator eit = springs.end();
    for (; it != eit; ++it)
    {
        (*it)->setK(_k);
    }
}

vector<ofxSpring*> &ofxSpringSystem::getSprings()
{
    return springs;
}