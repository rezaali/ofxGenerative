#pragma once 

#include "ofxRParticleGlowieRenderer.h"

class ofxRParticlePlexusRenderer : public ofxRParticleGlowieRenderer
{
public:
    ofxRParticlePlexusRenderer();
    ~ofxRParticlePlexusRenderer();
    
    void draw();
        
    void setDrawLines(bool _bDrawLines);
    void setDrawLinesPtr(bool *_bDrawLines);
    bool *getDrawLinesPtr();
    bool getDrawLines();

    void setLineWidth(float _lineWidth);
    void setLineWidthPtr(float *_lineWidth);
    float *getLineWidthPtr();
    float getLineWidth();

    void setTriangleAlpha(float _triangleAlpha);
    void setTriangleAlphaPtr(float *_triangleAlpha);
    float *getTriangleAlphaPtr();
    float getTriangleAlpha();

    void setLineAlpha(float _lineAlpha);
    void setLineAlphaPtr(float *_lineAlpha);
    float *getLineAlphaPtr();
    float getLineAlpha();

    void setUpperRange(float _upperRange);
    void setUpperRangePtr(float *_upperRange);
    float *getUpperRangePtr();
    float getUpperRange();
    
    void setLowerRange(float _lowerRange);
    void setLowerRangePtr(float *_lowerRange);
    float *getLowerRangePtr();
    float getLowerRange();
    
    void setRadiusScalar(float _radiusScalar);
    void setRadiusScalarPtr(float *_radiusScalar);
    float *getRadiusScalarPtr();
    float getRadiusScalar();
    
    void setDrawSprites(bool _bDrawSprites);
    void setDrawSpritesPtr(bool *_bDrawSprites);
    bool *getDrawSpritesPtr();
    bool getDrawSprites();
    
    bool bAllocatedDrawSprites;
    bool *bDrawSprites;
    
    bool bAllocatedDrawLines;
    bool *bDrawLines;
    
    bool bAllocatedLineWidth;
    float *lineWidth;
    
    bool bAllocatedTriangleAlpha;
    float *triangleAlpha;
    
    bool bAllocatedLineAlpha;
    float *lineAlpha;
    
    bool bAllocatedUpperRange;
    float *upperRange;
    
    bool bAllocatedLowerRange;
    float *lowerRange;

    bool bAllocatedRadiusScalar;
    float *radiusScalar;
};