#include <iostream>
#include <string>
#include <array>
#include <vector>

#pragma once
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#ifndef __APPLE__
#include <bits/stdc++.h> 
#endif

#include "Dependencies/GLM/glm.hpp"
#include "Dependencies/GLM/gtc/matrix_transform.hpp"
#include "Dependencies/GLM/gtc/type_ptr.hpp"
using namespace glm;

#include "Dependencies/STB/stb_image.cpp"

//#define USEGLEW      // consider alternatives

// GLEW _MUST_ be included first
//#ifdef USEGLEW
//#include "Dependencies/GLEW/glew.h"    // depend only on local GLEW file
#include <GL/glew.h>
//  Get all GL prototypes
#define GL_GLEXT_PROTOTYPES
//  Select SDL, SDL2, GLFW or GLUT
#if defined(SDL2)
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#elif defined(SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#elif defined(GLFW)
//#include "Dependencies/GLFW/glfw3.h"
#include <GLFW/glfw3.h>
#elif defined(__APPLE__)
//#include "Dependencies/GLUT/glut.h"    // depend only on local GLUT file
#include <GLUT/glut.h>
#else
//#include "Dependencies/GLUT/glut.h"    // depend only on local GLUT file
#include <GL/glut.h>
#endif
//  Make sure GLU and GL are included
#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif
//  Default resolution
//  For Retina displays compile with -DRES=2
#ifndef RES
#define RES 1
#endif

//  cos and sin in degrees
#define Cos(x) cos(3.14159265f/180.0f*(x))
#define Sin(x) sin(3.14159265f/180.0f*(x))

#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void Project(double fov, double asp, double dim)
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (fov)
      gluPerspective(fov,asp,dim/16,16*dim);
   //  Orthogonal transformation
   else
      glOrtho(-asp*dim,asp*dim,-dim,+dim,-dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}