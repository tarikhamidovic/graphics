double angle=0.0;
double factor=1.0;
static float MoveOnX = 0.0;
static float MoveOnY = 0.0;
float aspectRatio;
float viewRatio = 80;
static float scaleTheCamera = 0.6;
GLfloat translate_right=0.0;
GLfloat translate_left=0.0;
int counter1=0;
int counter2=0;
int counter3=0;
int path1=0;
int path2=1;
int path3=1;

GLboolean translate=false;
GLboolean rotate=false;
GLboolean scale=false;
GLboolean rotate_state=false;
GLboolean translate_state=false;
GLboolean scaling_state=false;
GLboolean angle_path=false;
GLboolean material=false;
int materialcount=0;



 GLfloat no_light[] = {0,0,0,0}; 
  GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};