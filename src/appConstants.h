//
//  appConstants.h
//  rawVisual
//
//  Created by alp tugan on 31/01/16.
//
//

#ifndef rawVisual_appConstants_h
#define rawVisual_appConstants_h

#define BUFFER_SIZE_RAW 512

class appConstants {
public:
};

static int scene1FontSize = 160;
static string fontPath = "fonts/AdventPro-Regular.ttf";
static int scene2ParticleSize = 20;

static int appBgColorHex = 0x000000;


static int appWinCenterX;
static int appWinCenterY;

static int appWinH;
static int appWinW;

static int bassLowRange = 0;
static int bassHiRange  = 80;

static int midLowRange  = 80;
static int midHiRange   = 100;

static int trebleLowRange = 100;
static int trebleHiRange  = 139;

static float bassLevel,midLevel,trebleLevel;


#endif
