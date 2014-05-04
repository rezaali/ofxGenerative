#pragma once 

#include <vector>
#include "ofxSpring.h"

class ofxSpringSystem 
{
public:
	ofxSpringSystem();
	~ofxSpringSystem();
    
    void init();
    void clear();
	virtual void update(float dt = 1);
	virtual void draw();
	virtual void addSpring(ofxSpring *s);
	virtual int getCount();
	ofxSpring *getSpring(int index);
	void setRestDistance(float _restDist);
    void setK(float _k);
    vector<ofxSpring*> &getSprings();
	
    vector<ofxSpring*> springs; 
	
protected:

	int uniqueIDs; 
};