#include "ofxBoundaryBehavior.h"
#include "ofxRParticle.h"

ofxBoundaryBehavior::ofxBoundaryBehavior() : ofxBehavior()
{
    setup();
}

ofxBoundaryBehavior::~ofxBoundaryBehavior()
{
    if(bAllocatedSpace)
    {
        delete space;
    }
}

void ofxBoundaryBehavior::setup()
{
    space = new float();
    bAllocatedSpace = true;
    setSpace(0.0);
    setBoundary(0, ofGetWidth(), 0, ofGetHeight());
}

void ofxBoundaryBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{    
    if(pos.x < xMin)
    {
        pos.x = xMin;
        vel.x *= particle->getRestitution();
    }
    else if(pos.x > xMax)
    {
        pos.x = xMax;
        vel.x *= particle->getRestitution();
    }
    
    if(pos.y > yMax)
    {
        pos.y = yMax;
        vel.y *= particle->getRestitution();
    }
    else if(pos.y < yMin)
    {
        pos.y = yMin;
        vel.y *= particle->getRestitution();
    }
    
    if(pos.z > zMax)
    {
        pos.z = zMax;
        vel.z *= (*particle->restitution);
    }
    else if(pos.z < zMin)
    {
        pos.z = zMin;
        vel.z *= (*particle->restitution);
    }
}

void ofxBoundaryBehavior::setBoundary(float _xMin, float _xMax, float _yMin, float _yMax, float _zMin, float _zMax)
{
    xMin = _xMin;
    xMax = _xMax;
    
    yMin = _yMin;
    yMax = _yMax;
    
    zMin = _zMin;
    zMax = _zMax;
    
//    cout << "xMin: " << xMin << endl;
//    cout << "xMax: " << xMax << endl;
//    
//    cout << "yMin: " << yMin << endl;
//    cout << "yMax: " << yMax << endl;
//    
//    cout << "zMin: " << zMin << endl;
//    cout << "zMax: " << zMax << endl;
}

void ofxBoundaryBehavior::draw()
{
    ofNoFill();
    ofSetColor(255, 100);
    ofDrawBox(0,0,0, xMax-xMin, yMax-yMin, zMax-zMin);
    ofSetColor(255, 0, 0, 100);
    ofDrawBox(0,0,0, xMax-xMin - getSpace()*2.0, yMax-yMin - getSpace()*2.0, zMax-zMin - getSpace()*2.0);
}

void ofxBoundaryBehavior::setSpace(float _space)
{
    *space = _space;
}

void ofxBoundaryBehavior::setSpacePtr(float *_space)
{
    if(bAllocatedSpace)
    {
        delete space;
        bAllocatedSpace = false;
    }
    space = _space;
}

float ofxBoundaryBehavior::getSpace()
{
    return *space;
}

float *ofxBoundaryBehavior::getSpacePtr()
{
    return space;
}
