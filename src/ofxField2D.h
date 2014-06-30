#pragma once

#include "ofMain.h"

class ofxField2D {
	
public: 
    
    ofxField2D(); 
    ~ofxField2D(); 

    void init(int xRes, int yRes, int width, int height); 
	void resize(int w, int h); 
    void reset(); 
    void input(float x, float y, float px, float py, float intensity=1.0); 
    void randomize(); 
	
    void update(); 
    void draw(); 
	
	void setViscosity(float v);
	void setDensityDecay(float dd);
	void setDifferential(float d);
	void setDt(float dt);
	void setIterations(int i);
	void setPointSize(float _pointSize);
    void setLineWidth(float _lineWidth);
    
    void setRenderType(int _renderType);
    
	// get vector at position 
	ofPoint getVector(int x, int y, bool averaged=false);
	float getDensity(int x, int y);
	int getRenderType();
    int *getRenderTypePtr();

    float &getViscosity();
    float &getDensityDecay();
	float &getDifferential();
	float &getDt();
	int &getIterations();
	float &getPointSize();
    float &getLineWidth();
    
	// create fluid field from pixels
	void adaptFromImage(ofPixels & pix, float amt);
    
    void setColor(ofColor _color); 
    //Drawing Field Functions
    //Drawing Density Functions
    virtual void drawDensity();    
    virtual void drawField();
    virtual void drawFieldGrid();
    virtual void drawFieldGridWire();
    virtual void drawFieldMesh();
    virtual void drawFieldVectorMesh();
    virtual void drawFieldLinesVertical();
    virtual void drawFieldVelocityVertical();
    virtual void drawFieldLinesHorizontal();
    virtual void drawFieldVelocityHorizontal();
    virtual void drawFieldAroundMe(float radius, ofVec2f loc, ofVec3f color);
    
	// size
	int getWidth();
	int getHeight();
    
protected:
	
	//Get a specific cell
    int IX(int x, int y) { return (x+(dimX+2)*(y)); }   
	
	//Fluid Solver Steps    
    void vel_step(int DX, int DY, float* u, float* v, float* u0, float* v0, float visc, float dt);
    void dens_step( int DX, int DY, float* x, float* x0, float* u, float* v, float diff, float dt);
    
    //Fluid Solver Functions    
    void diffuse(int DX, int DY, int b, float* x, float* x0, float diff, float dt);     
    void advect(int DX, int DY, int b, float* d, float* d0, float* u, float* v, float dt);
    void project(int DX, int DY, float* u, float* v, float* p, float* dv); 
	//    void swap(float*&x0, float *&x);
    void set_bnd(int DX, int DY, int b, float* x);     
    
    void add_source(int DX, int DY, float* x, float* s, float dt); 
    void decay_density(int DX, int DY, float* x, float* s, float dt);
	
    int dimX, dimY, size;
    float xInterval, yInterval; 
    float pointSize;
    float lineWidth;
    int renderType;
    float visc, diff, dt;
    float densityDecayFactor;
    int iterations; 
    float* u;               //x_vel
    float* v;               //y_vel    
    float* u_prev;          //x_vel_prev
    float* v_prev;          //y_vel_prev
    float* dens;            //dens
    float* dens_prev;       //dens_prev
	
	float w, h;

    ofFloatColor color;
}; 