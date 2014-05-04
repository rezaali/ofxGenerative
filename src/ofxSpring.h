#pragma once

#include "ofColor.h"
#include "ofVec3f.h"

class ofxSpring 
{	
public:
	ofxSpring(ofVec3f *_p1, ofVec3f *_p2, float _restDist, float _k);
	ofxSpring();
    ~ofxSpring();

    void init();
	void update(float dt = 1);
	void draw();
	
	ofVec3f& getForce(int index);
	ofVec3f* getForcePtr(int index);
	
	void setRestDistance(float _restDist);
    float getRestDistance();
    
    float getK();
    void setK(float _k);
    
    ofVec3f & getPos(int index);
    ofVec3f * getPosPtr(int index);

    void setPos1(ofVec3f *_p1);
    void setPos2(ofVec3f *_p2);
    
	int getID();
	void setID(int _sid);

    float getDelta();
	void setColor(ofColor _color);
	ofColor& getColor();
	void setColorAlpha(float _alpha);
	float getColorAlpha();

protected:
	float restDist;
    float delta; 
	float k; 
	ofVec3f *p1; 
	ofVec3f *p2; 
	ofVec3f p1force;
	ofVec3f p2force;	    
	int sid; 
    ofColor color; 
};