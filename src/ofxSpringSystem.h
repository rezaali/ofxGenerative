/********************************************************************************** 
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#ifndef OFX_SPRINGSYSTEM
#define OFX_SPRINGSYSTEM

#include <vector>
#include "ofxSpring.h"

class ofxSpringSystem 
{
public:
	
	ofxSpringSystem()
	{
        init();
	}
	
    void init()
    {
        uniqueIDs = 0; 
    }
    
	~ofxSpringSystem()
	{	
        clear();
    }
	
    void clear()
    {
        
        for (vector<ofxSpring * >::iterator it = springs.begin(); it != springs.end(); ++it)
        {
            ofxSpring *s = *it;
            delete s;
        }                        
        springs.clear();         
    }
    
	virtual void update(float dt = 1)
	{
		for(vector<ofxSpring*>::iterator it = springs.begin(); it != springs.end(); ++it)
		{
			(*it)->update(dt);
		}		
	}
	
	virtual void draw()
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
	
	virtual void addSpring(ofxSpring *s)
	{
		uniqueIDs++; 
		s->setID(uniqueIDs); 
		springs.push_back(s); 
	}
	
	virtual int getCount()
	{
		return (int)springs.size(); 
	}
	
	ofxSpring *getSpring(int index)
	{
		if(index < springs.size() && index >= 0)
		{
			return springs[index];
		}
		else {
			return NULL;
		}
	}
	
	void setRestDistance(float _restDist)
	{
		for(vector<ofxSpring*>::iterator it = springs.begin(); it != springs.end(); ++it)
		{
			(*it)->setRestDistance(_restDist); 
		}
	}

    void setK(float _k)
	{
		for(vector<ofxSpring*>::iterator it = springs.begin(); it != springs.end(); ++it)
		{
			(*it)->setK(_k);
		}
	}

    vector<ofxSpring*> &getSprings()
    {
        return springs; 
    }
	
    vector<ofxSpring*> springs; 
	
protected:

	int uniqueIDs; 
};

#endif
