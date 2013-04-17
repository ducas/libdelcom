#ifndef _libdelcom_h_

#define _libdelcom_h_

#define DELCOM_COLOR_GREEN 0x01
#define DELCOM_COLOR_RED 0x02
#define DELCOM_COLOR_BLUE 0x04
#define DELCOM_COLOR_OFF 0x00

int delcom_OpenDevice();

unsigned int delcom_GetColor();

int delcom_SetColor(unsigned int);

int delcom_CloseDevice();

#endif