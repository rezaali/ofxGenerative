#include "ofxRParticlePlexusRenderer.h"
#include "ofxNeighborParticleData.h"

ofxRParticlePlexusRenderer::ofxRParticlePlexusRenderer() : ofxRParticleGlowieRenderer()
{
    bAllocatedLineWidth = true;
    lineWidth = new float;
    *lineWidth = 3.0;

    bAllocatedDrawLines = true;
    bDrawLines = new bool;
    *bDrawLines = true;

    bAllocatedDrawSprites = true;
    bDrawSprites = new bool;
    *bDrawSprites = true;

    bAllocatedLineAlpha = true;
    lineAlpha = new float;
    *lineAlpha = 100.0;
    
    bAllocatedTriangleAlpha = true;
    triangleAlpha = new float;
    *triangleAlpha = 50.0;
    
    bAllocatedUpperRange = true;
    upperRange = new float;
    *upperRange = 7.0;
    
    bAllocatedLowerRange = true;
    lowerRange = new float;
    *lowerRange = 2.0;
    
    bAllocatedRadiusScalar = true;
    radiusScalar = new float;
    *radiusScalar = 1.0;
}

ofxRParticlePlexusRenderer::~ofxRParticlePlexusRenderer()
{
    if(bAllocatedTriangleAlpha)
    {
        delete triangleAlpha;
    }
    if(bAllocatedLineAlpha)
    {
        delete lineAlpha;
    }
    if(bAllocatedLineWidth)
    {
        delete lineWidth;
    }
    if(bAllocatedDrawLines)
    {
        delete bDrawLines;
    }
    if(bAllocatedUpperRange)
    {
        delete upperRange;
    }
    if(bAllocatedLowerRange)
    {
        delete lowerRange;
    }
    if(bAllocatedRadiusScalar)
    {
        delete radiusScalar;
    }
}

void ofxRParticlePlexusRenderer::draw()
{
    activateBlending(); 
    ofSetLineWidth(*lineWidth);
    billBoard(); 
    ofSetRectMode(OF_RECTMODE_CENTER);
    for(vector<ofxRParticle *>::iterator it = (*particles).begin(); it != (*particles).end(); it++)
    {
        ofxRParticle *p = (*it);
        ofColor clr = p->getColor();
        if(*bDrawSprites)
        {
            glPushMatrix();
            ofVec3f pos = p->getPos();
            glTranslatef(pos.x, pos.y, pos.z);
            ofRotate(angle, axis.x, axis.y, axis.z);
            ofSetColor(clr);
            float r = p->getRadius()*(*radiusScalar);
            glow->draw(0, 0, r, r);
            glPopMatrix();
        }
        
        if(*bDrawLines)
        {
            ofxNeighborParticleData *data = (ofxNeighborParticleData *) p->getData();
            
            int n = data->neighbors.size();
            if(n > *lowerRange && n < *upperRange)
            {
                glBegin(GL_TRIANGLE_FAN);
                ofSetColor(clr, (*triangleAlpha)*data->distances[0]);
                glVertex3fv(p->getPos().getPtr());
                int i = 0;
                for(vector<ofxRParticle *>::iterator nit = data->neighbors.begin(); nit != data->neighbors.end(); ++nit)
                {
                    ofxRParticle *other = (*nit);
                    ofSetColor(other->getColor(), (*triangleAlpha)*data->distances[i]);
                    glVertex3fv(other->getPos().getPtr());
                    i++;
                }
                glEnd();
            }
            else
            {
                glBegin(GL_LINES);
                int i = 0;
                for(vector<ofxRParticle *>::iterator nit = data->neighbors.begin(); nit != data->neighbors.end(); ++nit)
                {
                    ofSetColor(clr, (*lineAlpha)*data->distances[i]);
                    glVertex3fv(p->getPos().getPtr());
                    ofxRParticle *other = (*nit);

                    ofVec3f avg = (p->getPos() + other->getPos())/2.0;
                    ofSetColor(255, 255, 255, 0.0);
                    glVertex3fv(avg.getPtr());
                    glVertex3fv(avg.getPtr());
                    
                    ofSetColor(other->getColor(), (*lineAlpha)*data->distances[i]);
                    glVertex3fv(other->getPos().getPtr());
                    i++;
                }
                glEnd();
            }
        }
    }
    ofSetRectMode(OF_RECTMODE_CORNER);
}

void ofxRParticlePlexusRenderer::setDrawLines(bool _bDrawLines)
{
    *bDrawLines = _bDrawLines;
}

void ofxRParticlePlexusRenderer::setDrawLinesPtr(bool *_bDrawLines)
{
    if(bAllocatedDrawLines)
    {
        delete bDrawLines;
        bAllocatedDrawLines = false;
    }
    bDrawLines = _bDrawLines;
}

bool *ofxRParticlePlexusRenderer::getDrawLinesPtr()
{
    return bDrawLines; 
}

bool ofxRParticlePlexusRenderer::getDrawLines()
{
    return *bDrawLines;
}

void ofxRParticlePlexusRenderer::setLineWidth(float _lineWidth)
{
    *lineWidth = _lineWidth;
}

void ofxRParticlePlexusRenderer::setLineWidthPtr(float *_lineWidth)
{
    if(bAllocatedLineWidth)
    {
        delete lineWidth;
        bAllocatedLineWidth = false;
    }
    lineWidth = _lineWidth;
}

float *ofxRParticlePlexusRenderer::getLineWidthPtr()
{
    return lineWidth;
}

float ofxRParticlePlexusRenderer::getLineWidth()
{
    return *lineWidth;
}

void ofxRParticlePlexusRenderer::setTriangleAlpha(float _triangleAlpha)
{
    *triangleAlpha = _triangleAlpha;
}

void ofxRParticlePlexusRenderer::setTriangleAlphaPtr(float *_triangleAlpha)
{
    if(bAllocatedTriangleAlpha)
    {
        delete triangleAlpha;
        bAllocatedTriangleAlpha = false;
    }
    triangleAlpha = _triangleAlpha;
}

float *ofxRParticlePlexusRenderer::getTriangleAlphaPtr()
{
    return triangleAlpha;
}

float ofxRParticlePlexusRenderer::getTriangleAlpha()
{
    return *triangleAlpha;
}

void ofxRParticlePlexusRenderer::setLineAlpha(float _lineAlpha)
{
    *lineAlpha = _lineAlpha;
}

void ofxRParticlePlexusRenderer::setLineAlphaPtr(float *_lineAlpha)
{
    if(bAllocatedLineAlpha)
    {
        delete lineAlpha;
        bAllocatedLineAlpha = false;
    }
    lineAlpha = _lineAlpha;
}

float *ofxRParticlePlexusRenderer::getLineAlphaPtr()
{
    return lineAlpha;
}

float ofxRParticlePlexusRenderer::getLineAlpha()
{
    return *lineAlpha;
}

void ofxRParticlePlexusRenderer::setUpperRange(float _upperRange)
{
    *upperRange = _upperRange;
}

void ofxRParticlePlexusRenderer::setUpperRangePtr(float *_upperRange)
{
    if(bAllocatedUpperRange)
    {
        delete upperRange;
        bAllocatedUpperRange = false;
    }
    upperRange = _upperRange;
}

float *ofxRParticlePlexusRenderer::getUpperRangePtr()
{
    return upperRange;
}

float ofxRParticlePlexusRenderer::getUpperRange()
{
    return *upperRange;
}

void ofxRParticlePlexusRenderer::setLowerRange(float _lowerRange)
{
    *lowerRange = _lowerRange;
}

void ofxRParticlePlexusRenderer::setLowerRangePtr(float *_lowerRange)
{
    if(bAllocatedLowerRange)
    {
        delete lowerRange;
        bAllocatedLowerRange = false;
    }
    lowerRange = _lowerRange;
}

float *ofxRParticlePlexusRenderer::getLowerRangePtr()
{
    return lowerRange;
}

float ofxRParticlePlexusRenderer::getLowerRange()
{
    return *lowerRange;
}

void ofxRParticlePlexusRenderer::setRadiusScalar(float _radiusScalar)
{
    *radiusScalar = _radiusScalar;
}

void ofxRParticlePlexusRenderer::setRadiusScalarPtr(float *_radiusScalar)
{
    if(bAllocatedRadiusScalar)
    {
        delete radiusScalar;
        bAllocatedRadiusScalar = false;
    }
    radiusScalar = _radiusScalar;
}

float *ofxRParticlePlexusRenderer::getRadiusScalarPtr()
{
    return radiusScalar;
}

float ofxRParticlePlexusRenderer::getRadiusScalar()
{
    return *radiusScalar;
}

void ofxRParticlePlexusRenderer::setDrawSprites(bool _bDrawSprites)
{
    *bDrawSprites = _bDrawSprites;
}

void ofxRParticlePlexusRenderer::setDrawSpritesPtr(bool *_bDrawSprites)
{
    if(bAllocatedDrawSprites)
    {
        delete bDrawSprites;
        bAllocatedDrawSprites = false;
    }
    bDrawSprites = _bDrawSprites;
}

bool *ofxRParticlePlexusRenderer::getDrawSpritesPtr()
{
    return bDrawSprites;
}

bool ofxRParticlePlexusRenderer::getDrawSprites()
{
    return *bDrawSprites;
}