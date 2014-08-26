#pragma once

class ofxGrid
{
public:
    ofxGrid()
    {
        setup();
        generate();
    }
    
    ~ofxGrid()
    {
        deleteValues();
        deleteColors(); 
    }
    
    void setup()
    {
        numX = 31;
        numY = 17;
        numZ = 21;
        
        cellWidth = 32;
        cellHeight = 32;
        cellDepth = 32;
        
        values = NULL;
        valuesOld = NULL;
        colors = NULL;
        
        bGenerate = true;
    }
    
    void deleteColors()
    {
        if(colors != NULL)
        {
            delete[] colors;
            colors = NULL;
        }
        
        if(colorsOld != NULL)
        {
            delete[] colorsOld;
            colorsOld = NULL;
        }
    }
    
    void deleteValues()
    {
        if(values != NULL)
        {
            delete[] values;
            values = NULL;
        }
        
        if(valuesOld != NULL)
        {
            delete[] valuesOld;
            valuesOld  = NULL;
        }
    }
    
    void generate()
    {
        calculateProperties();
        
        deleteValues();
        deleteColors();
        
        numPerPlane = numX*numY;
        size = numPerPlane*numZ;
        values = new float[size];
        valuesOld = new float[size];
        colors = new ofColor[size];
        colorsOld = new ofColor[size];
        
        for(int i = 0; i < size; ++i)
        {
            colors[i] = ofColor(255);
            colorsOld[i] = ofColor(255);
            values[i] = 0.0;
            valuesOld[i] = 0.0;
        }

        bGenerate = false;
    }
    
    void calculateProperties()
    {
        width = numX*cellWidth;
        height = numY*cellHeight;
        depth = numZ*cellDepth;
        
        widthHalf = width*0.5;
        heightHalf = height*0.5;
        depthHalf = depth*0.5;
        
        offsetX = widthHalf-cellWidth*0.5;
        offsetY = heightHalf-cellHeight*0.5;;
        offsetZ = depthHalf-cellDepth*0.5;
    }
    
    void update()
    {
        if(bGenerate)
        {
            generate();
        }
        memcpy(valuesOld, values, sizeof(float) * size);
    }    
    
    ofVec3f getCellCenterFromCellID(float gid)
    {
        ofVec3f pos = getCellIndexFromID(gid);
        return getCellCenterFromCellIndex(pos);
    }
    
    ofVec3f getCellIndexFromID(float gid)
    {
        double x, xFract, xInt;
        double y, yFract, yInt;
        double z, zFract, zInt;
        
        z = gid/numPerPlane;
        zFract = modf(z ,&zInt);
        y = (zFract*numPerPlane)/numX;
        yFract = modf(y ,&yInt);
        x = yFract*numX;
        xFract = modf(x ,&xInt);

        return ofVec3f(floor(x), floor(y), floor(z));
    }
    
    ofColor getCellColorFromCellID(float gid)
    {
        ofVec3f pos = getCellIndexFromID(gid);
        return getCellColorFromCellIndex(pos);
    }
    
    ofColor &getCellColorFromCellIndex(ofVec3f &pos)
    {
        return getCellColorFromCellIndex(pos.x, pos.y, pos.z);
    }

    ofColor &getCellColorFromCellIndex(int _x, int _y, int _z)
    {
        return colors[ID(_x, _y, _z)];
    }
    
    ofColor &getCellColorFromGlobalSpace(ofVec3f &pos)
    {
        return getCellColorFromGlobalSpace(pos.x, pos.y, pos.z);
    }
    
    ofColor &getCellColorFromGlobalSpace(float _x, float _y, float _z)
    {
        if(insideGrid(_x, _y, _z))
        {
            return colors[getCellIDFromGlobalSpace(_x, _y, _z)];
        }
        return colors[getCellIDFromGlobalSpace(0,0,0)];
    }
    
    void setCellColorFromCellIndex(ofVec3f &pos, ofColor &color)
    {
        setCellColorFromCellIndex(pos.x, pos.y, pos.z, color);
    }
    
    void setCellColorFromCellIndex(int _x, int _y, int _z, ofColor &color)
    {
        colors[ID(_x, _y, _z)] = color;
        colorsOld[ID(_x, _y, _z)] = color;
    }
    
    void setCellColorFromGlobalSpace(ofVec3f &pos, ofColor &color)
    {
        setCellColorFromGlobalSpace(pos.x, pos.y, pos.z, color);
    }
    
    void setCellColorFromGlobalSpace(float _x, float _y, float _z, ofColor &color)
    {
        if(insideGrid(_x, _y, _z))
        {
            int gid = getCellIDFromGlobalSpace(_x, _y, _z);
            colors[gid] = color;
            colorsOld[gid] = color;
            return;
        }
    }
    
    ofVec3f getCellCenterFromCellIndex(ofVec3f &pos)
    {
        return getCellCenterFromCellIndex(pos.x, pos.y, pos.z);
    }
    
    ofVec3f getCellCenterFromCellIndex(int _x, int _y, int _z)
    {
        return ofVec3f(_x*cellWidth - offsetX, _y*cellHeight - offsetY, _z*cellDepth - offsetZ);
    }
    
    ofVec3f getCellCenterFromGlobalSpace(ofVec3f &pos)
    {
        return getCellCenterFromGlobalSpace(pos.x, pos.y, pos.z);
    }
    
    ofVec3f getCellCenterFromGlobalSpace(float _x, float _y, float _z)
    {
        ofVec3f gpt = getCellIndexFromGlobalSpace(_x, _y, _z);
        return getCellCenterFromCellIndex(gpt.x, gpt.y, gpt.z);
    }
    
    ofVec3f getCellIndexFromGlobalSpace(ofVec3f &pos)
    {
        return getCellIndexFromGlobalSpace(pos.x, pos.y, pos.z);
    }
    
    ofVec3f getCellIndexFromGlobalSpace(float _x, float _y, float _z)
    {
        int x = ofMap(_x, -widthHalf, widthHalf, 0, numX);
        int y = ofMap(_y, -heightHalf, heightHalf, 0, numY);
        int z = ofMap(_z, -depthHalf, depthHalf, 0, numZ);
        return ofVec3f(x, y, z);
    }
    
    int getCellIDFromGlobalSpace(ofVec3f &pos)
    {
        return getCellIDFromGlobalSpace(pos.x, pos.y, pos.z);
    }
    
    int getCellIDFromGlobalSpace(float _x, float _y, float _z)
    {
        ofVec3f gpt = getCellIndexFromGlobalSpace(_x, _y, _z);
        return ID(gpt.x, gpt.y, gpt.z);
    }
    
    bool insideGrid(ofVec3f &pos)
    {
        return insideGrid(pos.x, pos.y, pos.z);
    }
    
    bool insideGrid(float _x, float _y, float _z)
    {
        if(_x < widthHalf && _x > -widthHalf && _y > -heightHalf && _y < heightHalf && _z > -depthHalf && _z < depthHalf)
        {
            return true;
        }
        return false;
    }
    
    float getCellValueFromGlobalSpace(ofVec3f &pos)
    {
        return getCellValueFromGlobalSpace(pos.x, pos.y, pos.z);
    }
    
    float getCellValueFromGlobalSpace(float _x, float _y, float _z)
    {
        if(insideGrid(_x, _y, _z))
        {
            return values[getCellIDFromGlobalSpace(_x, _y, _z)];
        }
        return -1.0;
    }
    
    void intersectGrid(ofVec3f &pos, float value)
    {
        intersectGrid(pos.x, pos.y, pos.z, value);
    }
    
    void intersectGrid(float _x, float _y, float _z, float value)
    {
        if(insideGrid(_x, _y, _z))
        {
            int gid = getCellIDFromGlobalSpace(_x, _y, _z);
            values[gid] += value;
            valuesOld[gid] += value;
            return;
        }
    }
    
    void setCellValueFromGlobalSpace(ofVec3f &pos, float value)
    {
        setCellValueFromGlobalSpace(pos.x, pos.y, pos.z, value);
    }
    
    void setCellValueFromGlobalSpace(float _x, float _y, float _z, float value)
    {
        if(insideGrid(_x, _y, _z))
        {
            int gid = getCellIDFromGlobalSpace(_x, _y, _z);
            values[gid] = value;
            valuesOld[gid] = value;
            return;
        }
    }
    
    
    void setCellValueFromCellIndex(ofVec3f &pos, float value)
    {
        setCellValueFromCellIndex(pos.x, pos.y, pos.z, value);
    }
    
    void setCellValueFromCellIndex(float _x, float _y, float _z, float value)
    {
        values[ID(_x, _y, _z)] = value;
        valuesOld[ID(_x, _y, _z)] = value;
    }
    
    void diffuse()
    {
        for(int z = 0; z < numZ; ++z)
        {
            for(int y = 0; y < numY; ++y)
            {
                for(int x = 0; x < numX; ++x)
                {
                    int gid = ID(x,y,z);
                    int topIndex = (y-1);
                    int botIndex = (y+1);
                    int rightIndex = (x+1);
                    int leftIndex = (x-1);
                    int frontIndex = (z+1);
                    int backIndex = (z-1);
                    
                    topIndex = topIndex < 0 ? (numY-1) : topIndex;
                    botIndex = botIndex > (numY-1) ? 0 : botIndex;
                    rightIndex = rightIndex > (numX-1) ? 0 : rightIndex;
                    leftIndex = leftIndex < 0 ? (numX-1) : leftIndex;
                    frontIndex = frontIndex > (numZ-1) ? 0 : frontIndex;
                    backIndex = backIndex < 0 ? (numZ-1) : backIndex;
                    
                    values[gid] = (lookUpOld(x,y,z) +
                                       diffusionParam*(lookUpOld(rightIndex,y,z) +
                                                      lookUpOld(leftIndex,y,z) +
                                                      lookUpOld(x,topIndex,z) +
                                                      lookUpOld(x,botIndex,z) +
                                                      lookUpOld(x,y,frontIndex) +
                                                      lookUpOld(x,y,backIndex))
                                       )/(1.0 + (6.0)*diffusionParam);
                    
                    values[gid] *= decayParam;
                    values[gid] = ofClamp(values[gid], 0, 1.0);
                }
            }
        }
    }
    
    ofVec3f getCellCenterRightFromCellIndex(int x, int y, int z, int offset = 1)
    {
        return getCellCenterFromCellIndex(x+offset, y, z);
    }
    
    ofVec3f getCellCenterLeftFromCellIndex(int x, int y, int z, int offset = 1)
    {
        return getCellCenterFromCellIndex(x-offset, y, z);
    }
    
    ofVec3f getCellCenterTopFromCellIndex(int x, int y, int z, int offset = 1)
    {
        return getCellCenterFromCellIndex(x, y+offset, z);
    }
    
    ofVec3f getCellCenterBottomFromCellIndex(int x, int y, int z, int offset = 1)
    {
        return getCellCenterFromCellIndex(x, y-offset, z);
    }
    
    ofVec3f getCellCenterFrontFromCellIndex(int x, int y, int z, int offset = 1)
    {
        return getCellCenterFromCellIndex(x, y, z+offset);
    }
    
    ofVec3f getCellCenterBackFromCellIndex(int x, int y, int z, int offset = 1)
    {
        return getCellCenterFromCellIndex(x, y, z-offset);
    }
    
    ofVec3f getCellCenterRightFromCellIndex(ofVec3f &index, int offset = 1)
    {
        return getCellCenterRightFromCellIndex(index.x, index.y, index.z, offset);
    }
    
    ofVec3f getCellCenterLeftFromCellIndex(ofVec3f &index, int offset = 1)
    {
        return getCellCenterLeftFromCellIndex(index.x, index.y, index.z, offset);
    }
    
    ofVec3f getCellCenterTopFromCellIndex(ofVec3f &index, int offset = 1)
    {
        return getCellCenterTopFromCellIndex(index.x, index.y, index.z, offset);
    }
    
    ofVec3f getCellCenterBottomFromCellIndex(ofVec3f &index, int offset = 1)
    {
        return getCellCenterBottomFromCellIndex(index.x, index.y, index.z, offset);
    }
    
    ofVec3f getCellCenterFrontFromCellIndex(ofVec3f &index, int offset = 1)
    {
        return getCellCenterFrontFromCellIndex(index.x, index.y, index.z, offset);
    }
    
    ofVec3f getCellCenterBackFromCellIndex(ofVec3f &index, int offset = 1)
    {
        return getCellCenterBackFromCellIndex(index.x, index.y, index.z, offset);
    }
    
    ofVec3f getCellFrontTopRightFromCellIndex(ofVec3f &index)
    {
        return getCellFrontTopRightFromCellIndex(index.x, index.y, index.z);
    }
    
    ofVec3f getCellFrontTopRightFromCellIndex(int _x, int _y, int _z)
    {
        ofVec3f result = getCellCenterFromCellIndex(_x, _y, _z);
        result.x += cellWidth*0.5;
        result.y += cellHeight*0.5;
        result.z += cellDepth*0.5;
        return result;
    }
    
    ofVec3f getCellFrontTopLeftFromCellIndex(ofVec3f &index)
    {
        return getCellFrontTopLeftFromCellIndex(index.x, index.y, index.z);
    }
    
    ofVec3f getCellFrontTopLeftFromCellIndex(int _x, int _y, int _z)
    {
        ofVec3f result = getCellCenterFromCellIndex(_x, _y, _z);
        result.x -= cellWidth*0.5;
        result.y += cellHeight*0.5;
        result.z += cellDepth*0.5;
        return result;
    }
    
    ofVec3f getCellFrontBottomLeftFromCellIndex(ofVec3f &index)
    {
        return getCellFrontBottomLeftFromCellIndex(index.x, index.y, index.z);
    }
    
    ofVec3f getCellFrontBottomLeftFromCellIndex(int _x, int _y, int _z)
    {
        ofVec3f result = getCellCenterFromCellIndex(_x, _y, _z);
        result.x -= cellWidth*0.5;
        result.y -= cellHeight*0.5;
        result.z += cellDepth*0.5;
        return result;
    }
    
    ofVec3f getCellFrontBottomRightFromCellIndex(ofVec3f &index)
    {
        return getCellFrontBottomRightFromCellIndex(index.x, index.y, index.z);
    }
    
    ofVec3f getCellFrontBottomRightFromCellIndex(int _x, int _y, int _z)
    {
        ofVec3f result = getCellCenterFromCellIndex(_x, _y, _z);
        result.x += cellWidth*0.5;
        result.y -= cellHeight*0.5;
        result.z += cellDepth*0.5;
        return result;
    }
    
    ofVec3f getCellBackTopRightFromCellIndex(ofVec3f &index)
    {
        return getCellBackTopRightFromCellIndex(index.x, index.y, index.z);
    }
    
    ofVec3f getCellBackTopRightFromCellIndex(int _x, int _y, int _z)
    {
        ofVec3f result = getCellCenterFromCellIndex(_x, _y, _z);
        result.x += cellWidth*0.5;
        result.y += cellHeight*0.5;
        result.z -= cellDepth*0.5;
        return result;
    }
    
    ofVec3f getCellBackTopLeftFromCellIndex(ofVec3f &index)
    {
        return getCellBackTopLeftFromCellIndex(index.x, index.y, index.z);
    }
    
    ofVec3f getCellBackTopLeftFromCellIndex(int _x, int _y, int _z)
    {
        ofVec3f result = getCellCenterFromCellIndex(_x, _y, _z);
        result.x -= cellWidth*0.5;
        result.y += cellHeight*0.5;
        result.z -= cellDepth*0.5;
        return result;
    }
    
    ofVec3f getCellBackBottomLeftFromCellIndex(ofVec3f &index)
    {
        return getCellFrontBottomLeftFromCellIndex(index.x, index.y, index.z);
    }
    
    ofVec3f getCellBackBottomLeftFromCellIndex(int _x, int _y, int _z)
    {
        ofVec3f result = getCellCenterFromCellIndex(_x, _y, _z);
        result.x -= cellWidth*0.5;
        result.y -= cellHeight*0.5;
        result.z -= cellDepth*0.5;
        return result;
    }
    
    ofVec3f getCellBackBottomRightFromCellIndex(ofVec3f &index)
    {
        return getCellBackBottomRightFromCellIndex(index.x, index.y, index.z);
    }
    
    ofVec3f getCellBackBottomRightFromCellIndex(int _x, int _y, int _z)
    {
        ofVec3f result = getCellCenterFromCellIndex(_x, _y, _z);
        result.x += cellWidth*0.5;
        result.y -= cellHeight*0.5;
        result.z -= cellDepth*0.5;
        return result;
    }
    
    int ID(int x, int y, int z)
    {
        return (numPerPlane*(z%numZ)) + numX*(y%numY) + (x%numX);
    }
    
    float lookUp(int x, int y, int z)
    {
        return values[ID(x, y, z)];
    }
    
    float lookUpOld(int x, int y, int z)
    {
        return valuesOld[ID(x, y, z)];
    }
    
    void setValues(float _value)
    {
        memset(values, _value, sizeof(float) * size);
        memset(valuesOld, _value, sizeof(float) * size);
    }
    
    void setCellSize(float _w, float _h, float _d)
    {
        cellWidth = _w;
        cellHeight = _h;
        cellDepth = _d;
        calculateProperties();
    }
    
    void setResolution(int _x, int _y, int _z)
    {
        numX = _x;
        numY = _y;
        numZ = _z;
        bGenerate = true;
    }
    
    //Grid Properties
    
    bool bGenerate;
    
    float *values = NULL;
    float *valuesOld = NULL;
    ofColor *colors = NULL;
    ofColor *colorsOld = NULL;
    
    float decayParam;
    float diffusionParam;
    
    float cellWidth, cellHeight, cellDepth;
    float width, height, depth;
    float widthHalf, heightHalf, depthHalf;
    float offsetX, offsetY, offsetZ;
    
    int numX, numY, numZ;
    int numPerPlane;
    int size;
};