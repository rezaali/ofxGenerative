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

#ifndef OFX_BOIDSYSTEM
#define OFX_BOIDSYSTEM

#include <vector>
#include "ofxParticleSystem.h"

class ofxBoidSystem : public ofxParticleSystem
{
public:	
	ofxBoidSystem() : ofxParticleSystem()
	{
        initBoidSystem();
	}
    
    ~ofxBoidSystem()
    {
        cout << "DELETTING BOID SYSTEM" << endl; 
        delete drawDebug;
        delete drawVelocities;
        delete drawAccelerations;

        delete zoneRadiusHalf;
        delete zoneRadiusSqrd;
        delete zoneRadius;
        delete threshLow;
        delete threshHigh;
        delete centerForceConstant; 
        delete attractForceConstant;
        delete repelForceConstant;
        delete alignForceConstant;
        delete cohesionForceConstant;
        delete perlinForceConstant;
        delete noiseScale; 
        delete velLimitLow;
        delete accLimitLow; 
        delete velLimit;
        delete accLimit; 
        delete damping;
        
        delete bWidth;
        delete bHeight;
        delete bDepth; 
    }
    

    void initBoidSystem()
    {
        cout << "CREATING BOID SYSTEM" << endl;
        
        drawDebug = new bool();
        drawVelocities = new bool();
        drawAccelerations = new bool();
        
        zoneRadius = new float();
        zoneRadiusHalf = new float(); 
        zoneRadiusSqrd = new float(); 

        threshLow = new float();
        threshHigh = new float();
        centerForceConstant = new float(); 
        attractForceConstant = new float();
        repelForceConstant = new float();
        alignForceConstant = new float();
        cohesionForceConstant = new float();
        perlinForceConstant = new float();
        noiseScale = new float(); 
        velLimitLow = new float();
        accLimitLow = new float(); 
        velLimit = new float();
        accLimit = new float();
        damping = new float(); 
        
        bWidth = new float();
        bHeight = new float();
        bDepth = new float();
        
        *zoneRadius = 80.4487;
        *zoneRadiusHalf = (*zoneRadius)*.5;
        *zoneRadiusSqrd = (*zoneRadius)*(*zoneRadius); 
        
        *threshLow = 0.772436;
        *threshHigh = 0.836538;
        *attractForceConstant = 0.0184295;
        *repelForceConstant = 0.0198301;
        *alignForceConstant = 0.01099039;
        *cohesionForceConstant = 0.0112692;
        *perlinForceConstant = 0.05084295;
        *accLimit = 9.03846;
        *velLimit = 9.07051;
        *velLimitLow = 3.33333;
        *accLimitLow = 0.0; 
        *damping = 0.108683;
        
        *bWidth = 512.0;
        *bHeight = 512.0;
        *bDepth = 512.0;
        
        *drawDebug = false;
        *drawVelocities = false;
        *drawAccelerations = false;
    }
    
    void draw()
	{
        if((*drawDebug) == true)
        {
            for(int i = 0; i < particles.size(); i++)
            {
                ofxBoidParticle *bp = (ofxBoidParticle *) particles[i];
                bp->drawDebug();            
            }
        }
        if((*drawVelocities) == true)
        {
            ofMesh mesh;
            mesh.setMode(OF_PRIMITIVE_LINES);
            for(int i = 0; i < particles.size(); i++)
            {
                ofxBoidParticle *bp = (ofxBoidParticle *) particles[i];
                mesh.addColor(bp->getColor());                
                mesh.addVertex(bp->getPos());
                mesh.addColor(ofColor(255,0,0));
                mesh.addVertex(bp->getPos()+ofVec3f(bp->getVel())*4.0);
            }            
            mesh.draw();
        }
        if((*drawAccelerations) == true)
        {
            ofMesh mesh;
            mesh.setMode(OF_PRIMITIVE_LINES);
            for(int i = 0; i < particles.size(); i++)
            {
                ofxBoidParticle *bp = (ofxBoidParticle *) particles[i];
                mesh.addColor(bp->getColor());                
                mesh.addVertex(bp->getPos());
                mesh.addColor(ofColor(255,0,255));
                mesh.addVertex(bp->getPos()+ofVec3f(bp->getAcc())*4.0);
            }            
            mesh.draw();            
        }

//        glPointSize(5);
//        ofMesh mesh; 
//        mesh.setMode(OF_PRIMITIVE_POINTS);            
        ofMesh triangles; 
        triangles.setMode(OF_PRIMITIVE_TRIANGLES);
        
        for(int i = 0; i < particles.size(); i++)
        {
            ofxBoidParticle *bp = (ofxBoidParticle *) particles[i];
            
            float offset = bp->getRadius();
            ofVec3f p1 = ofVec3f(0,offset,0);
            ofVec3f p2 = ofVec3f(-offset*.5, -offset,0);
            ofVec3f p3 = ofVec3f(offset*.5, -offset,0);
            
            ofVec3f dir = ofVec3f(0,1,0);
            
            float angle = angleSigned(dir, bp->getVel());
            
            p1.rotate(angle, ofVec3f(0,0,1));
            p2.rotate(angle, ofVec3f(0,0,1));
            p3.rotate(angle, ofVec3f(0,0,1));
            
            p1+=bp->getPos();
            p2+=bp->getPos();
            p3+=bp->getPos();            
        
            
            ofColor clr = bp->getColor(); 
            clr.a = 150; 
        
        
//            mesh.addColor(clr);
//            mesh.addVertex(bp->getPos());            
            
            
            triangles.addColor(clr);
            triangles.addVertex(p1);
            triangles.addColor(clr);
            triangles.addVertex(p2);
            triangles.addColor(clr);
            triangles.addVertex(p3);
        }
        
        
//        mesh.draw();
//        triangles.drawWireframe();
        triangles.draw();
        
    }

    float angleSigned( ofVec3f& vec1, ofVec3f& vec2 )
    {
        ofVec3f n1 = vec1.normalized();
        ofVec3f n2 = vec2.normalized();
        return (float)(atan2(n2.y,n2.x) - atan2(n1.y,n1.x))*RAD_TO_DEG;
    }

    virtual void addParticle(ofxBoidParticle *p)
	{
		uniqueIDs++; 
		p->setID(uniqueIDs); 
        p->threshLow = threshLow;        
        p->threshHigh = threshHigh;                
        p->zoneRadius = zoneRadius;
        p->zoneRadiusHalf = zoneRadiusHalf;
        p->zoneRadiusSqrd = zoneRadiusSqrd; 
        p->velLimitLow = velLimitLow;
        p->velLimit = velLimit; 
        p->accLimit = accLimit;
        p->accLimitLow = accLimitLow;
        p->centerForceConstant = centerForceConstant; 
        p->attractForceConstant = attractForceConstant; 
        p->repelForceConstant = repelForceConstant;
        p->alignForceConstant = alignForceConstant; 
        p->cohesionForceConstant = cohesionForceConstant; 
        p->perlinForceConstant = perlinForceConstant;
        p->noiseScale = noiseScale; 
        p->damping = damping;
        p->bWidth = bWidth;
        p->bHeight = bHeight;
        p->bDepth = bDepth;
        particles.push_back(p);         
	}
    
    void printSettings()
    {
        cout <<         "zoneRadius = "             << *zoneRadius << ";" << endl;
        cout <<         "threshLow = "              << *threshLow << ";" << endl;
        cout <<         "threshHigh = "             << *threshHigh << ";" << endl;
        cout <<         "attractForceConstant = "   << *attractForceConstant << ";" << endl;
        cout <<         "repelForceConstant = "     << *repelForceConstant << ";" << endl;
        cout <<         "alignForceConstant = "     << *alignForceConstant << ";" << endl;
        cout <<         "cohesionForceConstant = "  << *cohesionForceConstant << ";" << endl;
        cout <<         "perlinForceConstant = "    << *perlinForceConstant << ";" << endl;
        cout <<         "accLimit = "               << *accLimit << ";" << endl;
        cout <<         "velLimit = "               << *velLimit << ";" << endl;
        cout <<         "velLimitLow = "            << *velLimitLow << ";" << endl;
        cout <<         "damping = "                << *damping << ";" << endl; 
    }
    
    bool *drawDebug;
    bool *drawVelocities;
    bool *drawAccelerations;

    float *zoneRadiusHalf;
    float *zoneRadiusSqrd;
    float *zoneRadius;
    float *threshLow;
    float *threshHigh;
    float *centerForceConstant;
    float *attractForceConstant;
    float *repelForceConstant;
    float *alignForceConstant;
    float *cohesionForceConstant;
    float *perlinForceConstant;
    float *noiseScale;
    float *velLimitLow;
    float *accLimitLow;
    float *velLimit;
    float *accLimit; 
    float *damping;
    
    float *bWidth;
    float *bHeight;
    float *bDepth;
};


#endif
