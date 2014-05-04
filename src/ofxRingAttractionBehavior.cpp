#include "ofxRingAttractionBehavior.h"

ofxRingAttractionBehavior::ofxRingAttractionBehavior() : ofxSphericalAttractionBehavior()
{
    setup();
}

ofxRingAttractionBehavior::~ofxRingAttractionBehavior()
{
    if(bAllocatedOrientation)
    {
        delete orientation;
    }

    delete normal;
}

void ofxRingAttractionBehavior::setup()
{
    bAllocatedNormal = true;
    normal = new ofVec3f(0,0,1);    
    bAllocatedOrientation = true;
    orientation = new ofQuaternion(0.0, *normal);
}

void ofxRingAttractionBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    ofVec3f deltaPos = pos - *position;
    float deltaPosLength = deltaPos.length();
    float dot = (deltaPos/deltaPosLength).dot(*normal);
    float delta = deltaPosLength*dot;
    ofVec3f pointOnPlane = pos - delta*(*normal);
    ofVec3f pointOnRing = pointOnPlane - (*position);
    pointOnRing = pointOnRing.normalize()*(*radius) + *position;
    acc-=(pos-pointOnRing)*(*magnitude)*dt;
}

void ofxRingAttractionBehavior::update()
{
    float angle;
    orientation->getRotate(angle, *normal);
    normal->normalize();
}

ofQuaternion *ofxRingAttractionBehavior::getOrientationPtr()
{
    return orientation;
}

void ofxRingAttractionBehavior::setOrientationPtr(ofQuaternion *_orientation)
{
    if(bAllocatedOrientation)
    {
        delete orientation;
        bAllocatedOrientation = false;
    }
    orientation = _orientation;
}

ofQuaternion& ofxRingAttractionBehavior::getOrientation()
{
    return *orientation;
}

void ofxRingAttractionBehavior::setOrientation(ofQuaternion _orientation)
{
    *orientation = _orientation;
}

ofVec3f *ofxRingAttractionBehavior::getNormalPtr()
{
    return normal;
}

void ofxRingAttractionBehavior::setNormalPtr(ofVec3f *_normal)
{
    if(bAllocatedNormal)
    {
        delete normal;
        bAllocatedNormal = false;
    }
    normal = _normal;
}

ofVec3f& ofxRingAttractionBehavior::getNormal()
{
    return *normal;
}

void ofxRingAttractionBehavior::setNormal(ofVec3f _normal)
{
    *normal = _normal;
}