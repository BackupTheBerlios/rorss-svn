/**
 * Some GL-defines
 * 
 * @author OP
 */
#ifndef UTIL_GL_AUX_H
#define UTIL_GL_AUX_H

#include "annie/defines.h"
#ifdef HAVE_OPENGL

#include <iostream>
#include <GL/gl.h>
namespace annie {
#define E(a)	case a: std::cerr << #a; break;
inline void prGLErr(GLenum e)	{
	switch(e)	{
		E(GL_INVALID_VALUE)
		E(GL_INVALID_ENUM)
		E(GL_INVALID_OPERATION)
		E(GL_STACK_OVERFLOW)
		E(GL_STACK_UNDERFLOW)
		E(GL_OUT_OF_MEMORY)
		default: ASSERT(0);
	}
}
#undef E

#define GLE \
	{ GLenum e = glGetError();	\
		if(e)	{	\
			prGLErr(e);	\
			/*assert(0);*/	\
		}	\
	}

} // annie
#endif
#endif
