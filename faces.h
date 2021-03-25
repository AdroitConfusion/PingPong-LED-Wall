//array for faces

//template
/*
 *
 *
 *
 *
 *
 *
 *
 */
//front face

int frontFace[23][23] = {    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {0,0,0,0,0,3,3,3,3,0,0,0,0,0,3,3,3,3,0,0,0,0,0},
                             {0,2,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,2,0},
                             {0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0},
                             {0,2,2,0,2,2,3,2,2,0,0,0,0,0,2,2,3,2,2,0,2,2,0},
                             {0,0,2,0,2,3,0,0,3,2,0,0,0,2,3,0,0,3,2,0,2,0,0},
                             {0,0,2,0,2,3,0,0,3,2,0,0,0,2,3,0,0,3,2,0,2,0,0},
                             {0,0,2,0,2,2,3,3,2,2,0,0,0,2,2,3,3,2,2,0,2,0,0},
                             {0,2,2,0,0,2,2,2,0,2,0,0,0,2,0,2,2,2,0,0,2,2,0},
                             {0,0,2,2,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,2,2,0,0},
                             {1,0,0,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,0,0,1},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
                             {1,1,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,1,1},
                             {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                             {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                             {1,1,1,0,0,0,2,2,0,0,0,0,0,0,0,2,2,0,0,0,1,1,1},
                             {1,1,1,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,1,1,1},
                             {1,1,1,1,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,1,1,1,1},
                             {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
                             {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1}
                         };
int frontBlink[23][23] = {   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {0,0,0,0,0,3,3,3,3,0,0,0,0,0,3,3,3,3,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,2,2,0,0,0,0,0,2,2,0,0,0,2,2,0,0,0,0,0,2,2,0},
                             {0,0,2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2,0,0},
                             {0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
                             {1,1,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,1,1},
                             {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                             {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                             {1,1,1,0,0,0,2,2,0,0,0,0,0,0,0,2,2,0,0,0,1,1,1},
                             {1,1,1,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,1,1,1},
                             {1,1,1,1,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,1,1,1,1},
                             {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
                             {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1}
                         };
                         
int leftFace[23][23] = {     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {0,0,0,0,3,3,3,3,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0},
                             {0,2,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,2,0},
                             {0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0},
                             {0,2,2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0},
                             {0,0,2,2,3,3,2,0,0,2,0,0,0,2,3,3,2,2,0,0,2,0,0},
                             {0,0,2,3,0,0,3,2,0,2,0,0,0,2,0,0,3,2,0,0,2,0,0},
                             {0,0,2,3,0,0,3,2,0,2,0,0,0,2,0,0,3,2,0,0,2,0,0},
                             {0,2,2,2,3,3,2,0,0,2,0,0,0,2,3,3,2,0,0,0,2,2,0},
                             {0,0,2,2,2,2,0,0,0,2,0,0,0,2,2,2,0,0,0,2,2,0,0},
                             {1,0,0,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,0,0,1},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
                             {1,1,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,1,1},
                             {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                             {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                             {1,1,1,0,0,0,2,2,0,0,0,0,0,0,0,2,2,0,0,0,1,1,1},
                             {1,1,1,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,1,1,1},
                             {1,1,1,1,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,1,1,1,1},
                             {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
                             {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1}
                         };
int leftBlink[23][23] = {    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {0,0,0,0,3,3,3,3,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,2,2,0,0,0,0,0,2,2,0,0,0,2,2,0,0,0,0,0,2,2,0},
                             {0,0,2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2,0,0},
                             {0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
                             {1,1,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,1,1},
                             {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                             {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                             {1,1,1,0,0,0,2,2,0,0,0,0,0,0,0,2,2,0,0,0,1,1,1},
                             {1,1,1,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,1,1,1},
                             {1,1,1,1,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,1,1,1,1},
                             {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
                             {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1}
                         };

int rightFace[23][23] = {    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,3,3,3,3,0,0,0,0},
                             {0,2,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,2,0},
                             {0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0},
                             {0,2,2,0,0,0,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2,2,0},
                             {0,0,2,0,0,2,2,3,3,2,0,0,0,2,0,0,2,3,3,2,2,0,0},
                             {0,0,2,0,0,2,3,0,0,2,0,0,0,2,0,2,3,0,0,3,2,0,0},
                             {0,0,2,0,0,2,3,0,0,2,0,0,0,2,0,2,3,0,0,3,2,0,0},
                             {0,2,2,0,0,0,2,3,3,2,0,0,0,2,0,0,2,3,3,2,2,2,0},
                             {0,0,2,2,0,0,0,2,2,2,0,0,0,2,0,0,0,2,2,2,2,0,0},
                             {1,0,0,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,0,0,1},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
                             {1,1,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,1,1},
                             {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                             {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                             {1,1,1,0,0,0,2,2,0,0,0,0,0,0,0,2,2,0,0,0,1,1,1},
                             {1,1,1,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,1,1,1},
                             {1,1,1,1,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,1,1,1,1},
                             {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
                             {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1}
                         };
int rightBlink[23][23] = {   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,3,3,3,3,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,2,2,0,0,0,0,0,2,2,0,0,0,2,2,0,0,0,0,0,2,2,0},
                             {0,0,2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2,0,0},
                             {0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
                             {1,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
                             {1,1,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,1,1},
                             {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                             {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                             {1,1,1,0,0,0,2,2,0,0,0,0,0,0,0,2,2,0,0,0,1,1,1},
                             {1,1,1,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,1,1,1},
                             {1,1,1,1,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,1,1,1,1},
                             {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
                             {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1}
                         };