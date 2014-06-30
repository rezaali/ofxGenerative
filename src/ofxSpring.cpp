#include "ofxSpring.h"
#include "ofMain.h"

ofxSpring::ofxSpring()
{
    init();
}

void ofxSpring::init()
{
    delta = 0;
    restDist = 0;
    k = 0;
    p1 = NULL;
    p2 = NULL;
    p1force = ofVec3f(0,0,0);
    p2force = ofVec3f(0,0,0);
    sid = -1;
    color1 = ofColor(255, 15);
    color2 = ofColor(255, 15);
}

ofxSpring::~ofxSpring()
{
    
}

ofxSpring::ofxSpring(ofVec3f *_p1, ofVec3f *_p2, float _restDist, float _k)
{
    init();
    p1 = _p1;
    p2 = _p2;
    restDist = _restDist;
    k = _k;
}

void ofxSpring::update(float dt)
{
    if(p1 != NULL && p2 != NULL)
    {
        float distance = p1->distance(*p2);
        ofVec3f direction = (*p1)-(*p2);
        direction.normalize();
        //            delta = 1.0 - restDist/distance;
        delta = (distance-restDist);
        direction*=k*delta*0.5;
        p2force.set(direction.x, direction.y,direction.z);
        direction*=(-1.0);
        p1force.set(direction.x, direction.y,direction.z);
    }
}

void ofxSpring::draw()
{
    if(p1 != NULL && p2 != NULL)
    {
        ofSetColor(color1);
        ofLine(p1->x,p1->y,p1->z, p2->x,p2->y,p2->z);
    }
}

ofVec3f& ofxSpring::getForce(int index)
{
    if(index == 0)
    {
        return p1force;
    }
    else
    {
        return p2force;
    }
}

ofVec3f* ofxSpring::getForcePtr(int index)
{
    if(index == 0)
    {
        return &p1force;
    }
    else
    {
        return &p2force;
    }
}

void ofxSpring::setRestDistance(float _restDist)
{
    restDist = _restDist;
}

float ofxSpring::getRestDistance()
{
    return restDist;
}

float ofxSpring::getK()
{
    return k;
}

void ofxSpring::setK(float _k)
{
    k = _k;
}

ofVec3f & ofxSpring::getPos(int index)
{
    if(index == 0)
    {
        return (*p1);
    }
    else
    {
        return (*p2);
    }
}

ofVec3f * ofxSpring::getPosPtr(int index)
{
    if(index == 0)
    {
        return p1;
    }
    else
    {
        return p2;
    }
}

void ofxSpring::setPos1(ofVec3f *_p1)
{
    p1 = _p1;
}

void ofxSpring::setPos2(ofVec3f *_p2)
{
    p2 = _p2;
}

int ofxSpring::getID()
{
    return sid;
}

void ofxSpring::setID(int _sid)
{
    sid = _sid;
}

float ofxSpring::getDelta()
{
    return delta;
}

void ofxSpring::setColor(ofColor _color, int index)
{
    if(index)
    {
        color2 = _color;
    }
    else
    {
        color1 = _color;
    }
}

ofColor& ofxSpring::getColor(int index)
{
    if(index)
    {
        return color2;
    }
    else
    {
        return color1;
    }
}

void ofxSpring::setColorAlpha(float _alpha, int index)
{
    if(index)
    {
        color2.a = _alpha;
    }
    else
    {
        color1.a = _alpha;
    }
}

float ofxSpring::getColorAlpha(int index)
{
    if(index)
    {
        return color2.a;
    }
    else
    {
        return color1.a;
    }
}
