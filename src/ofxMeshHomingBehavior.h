#ifndef OFX_MESH_HOMING_BEHAVIOR
#define OFX_MESH_HOMING_BEHAVIOR

#include "ofVec3f.h"
#include "ofxMesh.h"
#include "ofxEdge.h"
#include "ofxHomingBehavior.h"
#include "ofxMeshParticleData.h"

class ofxMeshHomingBehavior : public ofxHomingBehavior
{
public:
    ofxMeshHomingBehavior(ofxMesh *_mesh) : ofxHomingBehavior()
    {
        setup(_mesh);
    }
    
    ~ofxMeshHomingBehavior()
    {
        if(bAllocatedActivate)
        {
            delete bActivate;
        }
        if(bAllocatedFftThreshold)
        {
            delete fftThreshold;
        }
        if(bAllocatedDistanceThreshold)
        {
            delete distanceThreshold;
        }
        if(bAllocatedUseFft)
        {
            delete bUseFft;
        }
        if(bAllocatedTarget)
        {
            delete target;
        }
        if(bAllocatedTargetPoint)
        {
            delete bTargetPoint;
        }
    }
    
    void setup(ofxMesh *_mesh)
    {
        fftBuffer = NULL;
        fftBufferSize = 0;
        setMesh(_mesh);
        bAllocatedActivate = true;
        bActivate = new bool();
        *bActivate = true;
        
        distanceThreshold = new float();
        *distanceThreshold = 0.01;
        bAllocatedDistanceThreshold = true;
        fftThreshold = new float();
        bAllocatedFftThreshold = true;
        *fftThreshold = 0.1;
        
        bAllocatedUseFft = true;
        bUseFft = new bool();
        *bUseFft = true;
        
        bAllocatedTarget = true;
        target = new ofVec3f(0,0,0);
        
        bAllocatedTargetPoint = true;
        bTargetPoint = new bool();
        *bTargetPoint = false;
    }
    
    void setMesh(ofxMesh *_mesh)
    {
        mesh = _mesh;
    }
    
    virtual void actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
    {
        ofxMeshParticleData *data = (ofxMeshParticleData *) particle->getData();
        ofxVertex *v = data->getVertex();
        particle->setHome(v->getPos());
        ofVec3f delta = particle->getHome()-pos;
        data->addToTrail(pos);
        
        float fftLevel = 1.0;
        if(*bUseFft)
        {
            fftLevel = fftBuffer[particle->getID()%fftBufferSize];
        }
        
        if(delta.lengthSquared() < *distanceThreshold && (*bActivate) && fftLevel > *fftThreshold)
        {         
            if(*bTargetPoint)
            {
                ofxVertex *other = v->getClosestNeighborFrom(*target);
                particle->setHome(other->getPos());
                data->setVertex(other);
            }
            else
            {
                ofxEdge *e = v->getEdge(ofRandom(v->getNumEdges()));
                
                ofxVertex *v1 = e->getVertex(0);
                ofxVertex *v2 = e->getVertex(1);
                
                if(v1->getID() != v->getID())
                {
                    particle->setHome(v1->getPos());
                    data->setVertex(v1);
                }
                else
                {
                    particle->setHome(v2->getPos());
                    data->setVertex(v2);
                }
            }
        }
        acc+=(delta)*(*magnitude)*dt;
    }
    
    void setTargetPoint(bool _bTargetPoint)
    {
        *bTargetPoint = _bTargetPoint;
    }
    
    bool *getTargetPointPtr()
    {
        return bTargetPoint;
    }
    
    void setTargetPointPtr(bool *_bTargetPoint)
    {
        if(bTargetPoint)
        {
            delete bTargetPoint;
            bTargetPoint = false;
        }
        bTargetPoint = _bTargetPoint;
    }
    
    ofVec3f *getTargetPtr()
    {
        return target;
    }
    
    void setTargetPtr(ofVec3f *_target)
    {
        if(bAllocatedTarget)
        {
            delete target;
            bAllocatedTarget = false;
        }
        target = _target;
    }
    
    float *getDistanceThresholdPtr()
    {
        return distanceThreshold;
    }
    
    float *getFftThresholdPtr()
    {
        return fftThreshold;
    }
    
    bool *getActivatePtr()
    {
        return bActivate;
    }
    
    bool *getUseFftPtr()
    {
        return bUseFft;
    }
    
    void setFftThresholdPtr(float *_fftThreshold)
    {
        if(bAllocatedFftThreshold)
        {
            delete fftThreshold;
            bAllocatedFftThreshold = false;
        }
        fftThreshold = _fftThreshold;
    }
    
    void setDistanceThresholdPtr(float *_distanceThreshold)
    {
        if(bAllocatedDistanceThreshold)
        {
            delete distanceThreshold;
            bAllocatedDistanceThreshold = false;
        }
        distanceThreshold = _distanceThreshold;
    }
    
    void setActivatePtr(bool *_bActivate)
    {
        if(bAllocatedActivate)
        {
            delete bActivate;
            bAllocatedActivate = false;
        }
        bActivate = _bActivate;
    }
    
    void setUseFftPtr(bool *_bUseFft)
    {
        if(bAllocatedUseFft)
        {
            delete bUseFft;
            bAllocatedUseFft = false;
        }
        bUseFft = _bUseFft;
    }
    
    void setFFTBuffer(float *_fftBuffer)
    {
        fftBuffer = _fftBuffer;
    }
    
    void setFFTBufferSize(int _fftBufferSize)
    {
        fftBufferSize = _fftBufferSize;
    }
    
protected:
    float *fftBuffer;
    int fftBufferSize;
    ofxMesh *mesh;
    
    bool bAllocatedActivate;
    bool *bActivate;
    
    bool bAllocatedUseFft;
    bool *bUseFft;
    
    bool bAllocatedFftThreshold;
    bool bAllocatedDistanceThreshold;
    float *distanceThreshold;
    float *fftThreshold;
    
    bool bAllocatedTarget;
    ofVec3f *target;
    
    bool bAllocatedTargetPoint;
    bool *bTargetPoint;
};

#endif
