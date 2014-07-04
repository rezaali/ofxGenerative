#include "ofxBoundaryBehavior.h"
#include "ofxRParticle.h"

ofxBoundaryBehavior::ofxBoundaryBehavior() : ofxBehavior()
{
    setup();
}

ofxBoundaryBehavior::~ofxBoundaryBehavior()
{
    
}
void ofxBoundaryBehavior::setup()
{
    setBoundary(0, 0, ofGetWidth(), ofGetHeight());
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
//    cout << "yMin: " << yMin << endl;
//    cout << "yMax: " << yMax << endl;
//    cout << "zMin: " << zMin << endl;
//    cout << "zMax: " << zMax << endl;
}
