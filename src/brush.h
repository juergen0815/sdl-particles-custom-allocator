/*
 * brush.h
 *
 *  Created on: Jan 19, 2013
 *      Author: Jurgen
 */

#ifndef BRUSH_H_
#define BRUSH_H_

struct Brush {
    unsigned int   m_Width;
    unsigned int   m_Height;
    unsigned int   m_BytesPerPixel; /* 3:RGB, 4:RGBA */
    const char    *m_Pixels;
};

#endif /* BRUSH_H_ */
