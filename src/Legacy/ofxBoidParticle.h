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

#ifndef OFXBOIDPARTICLE
#define OFXBOIDPARTICLE

#include "ofMain.h"
#include "ofxParticle.h"

class ofxBoidParticle : public ofxParticle
{
public:
    ofxBoidParticle() : ofxParticle()
    {
        initBoid();   
    }
    
    ofxBoidParticle(ofVec3f _pos) : ofxParticle(_pos)
    {
        initBoid();
    }
    
    void initBoid()
    {
        color.set(0,0, 255);
        flockCentroid.set(0); 
        neighborCentroid.set(0); 
        numNeighbors = 0; 
        
        float offset = radius*2.0;
        front = ofVec3f(0,offset,0);
        left = ofVec3f(-offset*.5, -offset,0);
        right = ofVec3f(offset*.5, -offset,0);   
    }
        
    void update(float dt = 1)
	{
        
//        cout << "zoneRadius: " << *zoneRadius << endl;
//        cout << "zoneRadiusHalf: " << *zoneRadiusHalf << endl;
//        cout << "zoneRadiusSqrd: " << *zoneRadiusSqrd << endl;
//        cout << "threshLow: " << *threshLow << endl;
//        cout << "threshHigh: " << *threshHigh << endl;
//        cout << "accLimitLow: " << *accLimitLow << endl;
//        cout << "velLimitLow: " << *velLimitLow << endl;
//        cout << "attractForceConstant: " << *attractForceConstant << endl;
//        cout << "repelForceConstant: " << *repelForceConstant << endl;
//        cout << "alignForceConstant: " << *alignForceConstant << endl;
//        cout << "cohesionForceConstant: " << *cohesionForceConstant << endl;
//        cout << "perlinForceConstant: " << *perlinForceConstant << endl;
//        cout << "damping: " << *damping << endl;
//        cout << "velLimit: " << *velLimit << endl;
//        cout << "accLimit: " << *accLimit << endl; 
        
		if(!fixed)
		{
			ppos = pos;
            for(int i = 0; i < externalForces.size(); i++)
            {
            	acc+=(*externalForces[i]); 
			}
            separation();
            
			acc.limit((*accLimit)); 
			acc -=vel*(*damping); 

			vel+=acc; 
			
            vel.limit((*velLimit)); 
            if(vel.lengthSquared() < (*velLimitLow))
            {
                vel.normalize(); 
                vel*=(*velLimitLow); 
            }
        
			pos += vel; 		
			acc.set(0);        
            borders();            
		}		
	}
    
    void separation()
    {
        flockCentroid.set(0);
        neighborCentroid.set(0); 
        numNeighbors = 0; 
        
        for(int i = 0; i < particles->size(); i++)
        {
            ofxParticle *p = (ofxParticle *)(*particles)[i]; 
            if(p->getID() != pid)                
            {
                ofVec3f dir = p->getPos() - pos; 
                float dis = dir.length();
                
                if(dis < (*zoneRadius))
                {
                    if(dis < 1)
                    {
                        dis = 5;
                    }
                    float percent = dis/(*zoneRadius);
                    addNeighborPos(p->getPos());
                    
                    if(percent < (*threshLow))        //repel
                    {
                        float F = ( (*threshLow) / percent - 1.0f ) * (*repelForceConstant);
                        dir.normalize(); 
                        dir*=F;
                        acc -= dir;
                        p->getAcc() += dir;                    
                    }
                    else if(percent < (*threshHigh))
                    {
                        float threshDelta = (*threshHigh) - (*threshLow); 
                        float adjustedPercent = ( percent - (*threshLow) )/threshDelta;
                        float F = ( 0.5f - cos( adjustedPercent * M_PI * 2.0f ) * 0.5f + 0.5f ) * (*alignForceConstant);
                                        
                        acc += ofVec3f(p->getVel()).normalize()*F;
                        p->getAcc() += ofVec3f(vel).normalize()*F;
                    }
                    else
                    {                    
                        float threshDelta = 1.0f - (*threshHigh); 
                        float adjustedPercent = ( percent - (*threshHigh) )/threshDelta;
                        float F = ( 1.0 - ( cos( adjustedPercent * M_PI*2.0f ) * -0.5f + 0.5f ) ) * (*attractForceConstant); 
                        dir.normalize(); 
                        dir*= F;
                        acc += dir;
                        p->getAcc() -= dir;
                    }
                }
                flockCentroid += p->getPos();   
            }
        }         
    
         if(numNeighbors > 0 )
         { 
             ofVec3f neighborAveragePos = ( neighborCentroid/numNeighbors );
             acc += ( neighborAveragePos - pos ) * (*cohesionForceConstant);
         }
        color.setHue(numNeighbors);

		float time = ofGetElapsedTimeMillis()*(*noiseScale);
		ofVec3f perlin = ofVec3f(ofSignedNoise(pos.x*(*noiseScale), time), ofSignedNoise(pos.y*(*noiseScale), time),ofSignedNoise(pos.z*(*noiseScale), time));
        acc+=perlin*((*perlinForceConstant)*(*accLimit));
    }
	
	virtual void draw()
	{
        ofFill();
		ofSetColor(color); 
		ofEllipse(pos.x, pos.y, radius, radius); 
	}

    void drawDebug()
    {
        ofNoFill();
        
        ofSetColor(0,255,0,50);
        ofCircle(pos.x, pos.y, *zoneRadiusHalf);
        
        ofSetColor(0,0,255,50);
        ofCircle(pos.x, pos.y, (*threshHigh)*(*zoneRadiusHalf));
        
        ofSetColor(255,0,0,50);
        ofCircle(pos.x, pos.y, (*threshLow)*(*zoneRadiusHalf));
 
    }

    void setParticlesRef(vector<ofxParticle*> *_particles) 
    { 
        particles = _particles; 
    }
    
    virtual void borders()
	{
//        if(pos.x >= ofGetWidth()-radius*.5)
//        {
//            pos.x = radius*.5; 
//        }
//        else if(pos.x < -radius*.5)
//        {
//            pos.x = ofGetWidth()-radius*.5; 
//        }
//        
//        if(pos.y > ofGetHeight()+radius*.5)
//        {
//            pos.y = -radius*.5; 
//        }
//        else if(pos.y < -radius*.5)
//        {            
//            pos.y = ofGetHeight()-radius*.5;
//        }
        float w = *bWidth;
        float h = *bHeight;
        float d = *bDepth;
        
        if(pos.x > w)
        {
            pos.x = 1;
//            vel*=-1.0;
        }
        else if(pos.x < -w)
        {   
            pos.x = w-1;
//            vel*=-1.0;
        }
        if(pos.y > h)
        {
            pos.y = -h+1;
//            vel*=-1.0;
        }
        else if(pos.y < -h)
        {
            pos.y = h-1;
//            vel*=-1.0;
        }
        
        if(pos.z > d)
        {
            pos.z = -d+1;
        }
        else if(pos.z < -d)
        {
            pos.z = d-1;
        }

        
    }
    
    void addNeighborPos(ofVec3f _pos)
    {
        neighborCentroid+=_pos;
        numNeighbors++;
    }
    
  	vector<ofxParticle*> *particles; 
    ofVec3f flockCentroid; 
    ofVec3f neighborCentroid; 
    ofVec3f front;
    ofVec3f left;
    ofVec3f right;

    float numNeighbors;
    
    float *zoneRadius;
    float *zoneRadiusHalf;
    float *zoneRadiusSqrd;
    float *threshLow;
    float *threshHigh;
  	float *accLimitLow;
    float *velLimitLow;
    float *centerForceConstant; 
    float *attractForceConstant;
    float *repelForceConstant;
    float *alignForceConstant;
    float *cohesionForceConstant;
    float *perlinForceConstant;
    float *noiseScale; 
    float *damping;
    float *velLimit;
    float *accLimit;
    float *bWidth;
    float *bHeight;
    float *bDepth;
};

#endif