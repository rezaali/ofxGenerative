#include "ofApp.h"

class ofxColorChangingBehavior : public ofxBehavior
{
    void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
    {
        ofVec3f &home = particle->getHome();
        ofVec3f delta = home - pos;
        ofColor clr = ofColor::red;
        float len = delta.length()*2.0;
        clr.setHsb(len, 255, 255);
        particle->setColor(clr);
    }
};

//--------------------------------------------------------------
void ofApp::setup()
{
    ps = new ofxRParticleSystem();
    renderer = ps->getRendererPtr();
    renderer->setAdditiveBlending(true);
    renderer->setPointSize(10.0);
    
    interval = 8;
    width = ofGetWidth();
    height = ofGetHeight();

    for(float y = 0; y <= height; y+=interval)
    {
        for(float x = 0; x <= width; x+=interval)
        {
            ps->addParticle( new ofxRParticle( ofVec3f( x, y, 0 ) ) );
        }
    }
    
    ps->setAccerationLimit(2);
    ps->setVelocityLimit(10);
    
    ofxHomingBehavior *homing = new ofxHomingBehavior();
    homing->setMagnitude(0.175);
    ps->addBehavior(homing);
    
    damper = new ofxDamperBehavior();
    damper->setMagnitude(0.95);
    ps->addBehavior(damper);
    
    distorter = new ofxDistorterBehavior();
    distorter->setPosition( ofVec3f( ofGetWidth()*0.5, ofGetHeight()*0.5,0.0 ) );
    distorter->setRadius(1000);
    distorter->setExpFactor(2.0);
    ps->addBehavior(distorter);
    
    ps->addBehavior(new ofxColorChangingBehavior());
}

//--------------------------------------------------------------
void ofApp::update()
{
    distorter->setMagnitude(distorter->getMagnitude()*0.5);
    ps->update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    ofDisableDepthTest();
    ofEnableAlphaBlending();
    
    ps->draw();
}

void ofApp::exit()
{
    delete ps;
}

void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    distorter->setMagnitude(100);
    distorter->setPosition(ofVec3f(x, y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    distorter->setMagnitude(100);
    distorter->setPosition(ofVec3f(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
