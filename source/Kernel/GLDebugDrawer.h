#ifndef GL_DEBUG_DRAWER_H
#define GL_DEBUG_DRAWER_H

#ifdef WIN32
#include <windows.h>
#endif

#include <LinearMath/btIDebugDraw.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <Kernel/Logger.h>
#include <iostream>


/*extern "C"
{
#include <OpenGLES/EAGL.h>
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
}*/

class GLDebugDrawer : public btIDebugDraw
{
        int m_debugMode;

   public:

        GLDebugDrawer();

        virtual void   drawLine(const btVector3& from,const btVector3& to,const btVector3& color);

        virtual void   drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);

        virtual void   reportErrorWarning(const char* warningString);

        virtual void   draw3dText(const btVector3& location,const char* textString);

        virtual void   setDebugMode(int debugMode);

        virtual int      getDebugMode() const { return m_debugMode;}

};
#endif
