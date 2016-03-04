#ifndef PCH_h
#define PCH_h

// 标准c++库
#include <fstream>
#include <string.h>
#include <map>
#include <list>
#include <sstream>
#include <algorithm>
#include <vector>
#include <exception>
#include <array>

// 标准c库文件
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory>
#include <assert.h>

#include "Windows.h"

#define SAFE_RELEASE(x)	{if(x) {x}->Release(); (x) = NULL;}
#define SAFE_DELETE(x)	{if(x) {delete (x); (x) = NULL;}}
#define SAFE_DELETE_ARRAY(x) {if(x){delete[] x; (x) = NULL;}}

#define SAND_PI 3.14159265f

#define GET_X_LPARAM(lp)	((int)(short)((WORD)(((DWORD_PTR)(lp)) & 0xffff)))
#define GET_Y_LPARAM(lp)	((int)(short)((WORD)((((DWORD_PTR)(lp)) >> 16) & 0xffff)))

#define CLEAR_DEPTH		1
#define CLEAR_COLOR		2

#define ConvertToRadius(fDegree)	(fDegree) * (SAND_PI / 180.0f)

inline int Ceiling( float x )
{
	if ( x < 0 )
	{
		return ( int )x;
	}
	else if ( ( int )x < x )
	{
		return ( int )x + 1;
	}
}

#endif