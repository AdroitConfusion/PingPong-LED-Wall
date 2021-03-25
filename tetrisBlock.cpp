#include <FastLED.h>

class TetrisBlock
{
  public:

    int iX;
    int iY;
    int x[4];
    int y[4];
    int color;
    int blockType;
   
    TetrisBlock(int iX, int iY, int type)
    {
      blockType = type;
      switch(blockType)
      {
        case 0: // T-Block
          color = 195;
         
          x[0] = iX;
          x[1] = x[0]-1;
          x[2] = x[0]+1;
          x[3] = x[0];
         
          y[0] = iY;
          y[1] = y[0];
          y[2] = y[0];
          y[3] = y[0]-1;
          break;
        case 1: // O-Block
          color = 55;

         
          x[0] = iX;
          x[1] = x[0];
          x[2] = x[0]+1;
          x[3] = x[0]+1;
         
          y[0] = iY;
          y[1] = y[0]+1;
          y[2] = y[0];
          y[3] = y[0]+1;
          break;
        case 2: // I-Block
          color = 130;
             
          x[0] = iX;
          x[1] = x[0]+1;
          x[2] = x[0]+2;
          x[3] = x[0]-1;
         
          y[0] = iY;
          y[1] = y[0];
          y[2] = y[0];
          y[3] = y[0];
          break;
        case 3: // S-Block
          color = 100;
         
          x[0] = iX;
          x[1] = x[0]-1;
          x[2] = x[0];
          x[3] = x[0]+1;
         
          y[0] = iY;
          y[1] = y[0];
          y[2] = y[0]-1;
          y[3] = y[0]-1;
          break;
        case 4: // L-Block
          color = 275;

          x[0] = iX;
          x[1] = x[0];
          x[2] = x[0];
          x[3] = x[0]+1;
         
          y[0] = iY;
          y[1] = y[0]-1;
          y[2] = y[0]+1;
          y[3] = y[0]+1;
          break;
        case 5: // Z-Block
          color = 255;
         
          x[0] = iX;
          x[1] = x[0]-1;
          x[2] = x[0];
          x[3] = x[0]+1;
         
          y[0] = iY;
          y[1] = y[0];
          y[2] = y[0]+1;
          y[3] = y[0]+1;
          break;
        case 6: // J-Block
          color = 160;

          x[0] = iX;
          x[1] = x[0];
          x[2] = x[0];
          x[3] = x[0]-1;
         
          y[0] = iY;
          y[1] = y[0]-1;
          y[2] = y[0]+1;
          y[3] = y[0]+1;
          break;
        default:
          break;
      }
    };
};
