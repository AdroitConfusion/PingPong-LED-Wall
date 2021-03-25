
class BreakoutBlock
{
  public:
    int breakOutX[6]; 
    int breakOutY[6]; 
    int color;

    BreakoutBlock () {};
    
    BreakoutBlock(int iX, int iY, int color)
    {           
        setXY(iX, iY, color);
    };

    void setXY(int iX, int iY, int color)
    {
        this->color=color;
        breakOutX[0] = iX;
        breakOutX[1] = iX+1;
        breakOutX[2] = iX+2;
        breakOutX[3] = iX;
        breakOutX[4] = iX+1;
        breakOutX[5] = iX+2;

        breakOutY[0] = iY;
        breakOutY[1] = iY;
        breakOutY[2] = iY;
        breakOutY[3] = iY+1;
        breakOutY[4] = iY+1;
        breakOutY[5] = iY+1;
    };

};
