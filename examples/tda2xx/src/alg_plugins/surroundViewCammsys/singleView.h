/*
 * singleView.h
 *
 *  Created on: Nov 18, 2015
 *      Author: craven
 */

#ifndef EXAMPLES_TDA2XX_SRC_ALG_PLUGINS_FULLVIEW_SINGLEVIEW_H_
#define EXAMPLES_TDA2XX_SRC_ALG_PLUGINS_FULLVIEW_SINGLEVIEW_H_

#ifndef RESTRICT
#ifdef BUILD_DSP
#define RESTRICT restrict
#else
#define RESTRICT
#endif
#endif

#define AVM_LUT_INTEGER_BITS			10
#define AVM_LUT_FRACTION_BITS			6

typedef struct
{
	UInt8 y;
	UInt8 uv;
}yuyv;
#if 0
typedef struct
{
	UInt16 width;
	UInt16 height;
	UInt16 startX;
	UInt16 startY;
	UInt16 pitch;
}ViewInfo;
#endif

typedef struct {
	unsigned short xFraction:AVM_LUT_FRACTION_BITS;
	unsigned short xInteger:AVM_LUT_INTEGER_BITS;
	unsigned short yFraction:AVM_LUT_FRACTION_BITS;
	unsigned short yInteger:AVM_LUT_INTEGER_BITS;
} ViewLUT_Packed;

typedef struct {
	unsigned char pos:8;
	unsigned char y_b:8;
	unsigned char cb_g:8;
	unsigned char cr_r_overlay:8;
} MaskLUT_Packed;

#define HD720P_WIDTH	1280
#define HD1080P_WIDTH	1920
typedef yuyv yuvHD720P[HD720P_WIDTH];
typedef yuyv yuvHD1080P[HD1080P_WIDTH];

#define ONE_PER_AVM_LUT_FRACTION_BITS	1<<AVM_LUT_FRACTION_BITS

#define LinearInterpolation(x,q1,q2,perFraction,fractionBits)\
	((perFraction-x)*q1 + x*q2)>>fractionBits

#define _X	lut->xFraction
#define _Y lut->yFraction
///https://en.wikipedia.org/wiki/Bilinear_interpolation
#define BilinearInterpolation(q, lut, Q,  pitch)\
{\
	UInt16 R1,R2;\
	R1 = LinearInterpolation(_X,q[0].y,q[1].y,63,AVM_LUT_FRACTION_BITS);\
	R2 = LinearInterpolation(_X,q[pitch].y,q[pitch+1].y,63,AVM_LUT_FRACTION_BITS);\
	Q = LinearInterpolation(_Y,R1,R2,63,AVM_LUT_FRACTION_BITS);\
}
///https://en.wikipedia.org/wiki/Bilinear_interpolation
#define BilinearInterpolationUV(q, lut, Q, pitch)\
{\
	UInt16 R1,R2;\
	R1 = LinearInterpolation(_X,q[0].uv,q[2].uv,63,AVM_LUT_FRACTION_BITS);\
	R2 = LinearInterpolation(_X,q[pitch].uv,q[pitch+2].uv,63,AVM_LUT_FRACTION_BITS);\
	Q = LinearInterpolation(_Y,R1,R2,63,AVM_LUT_FRACTION_BITS);\
}


static inline Int32 makeSingleView720P(  UInt32       *RESTRICT inPtr,
                           	   UInt32           *RESTRICT outPtr,
							   UInt32			*RESTRICT viewLUTPtr,
							   AlgorithmLink_SurroundViewLutInfo			*RESTRICT viewInfo,
							   AlgorithmLink_SurroundViewLutInfo			*RESTRICT childViewInfoLUT
                          )
{
	UInt16 rowIdx;
    UInt16 colIdx;

    yuvHD720P* iPtr;
    yuvHD720P* oPtr;

    UInt16 startX = viewInfo->startX + childViewInfoLUT->startX;
    UInt16 width = childViewInfoLUT->width + startX;
    UInt16 height = childViewInfoLUT->height;

    ViewLUT_Packed *lut = ((ViewLUT_Packed*)viewLUTPtr) + (childViewInfoLUT->pitch * childViewInfoLUT->startY);

    iPtr  = (yuvHD720P*)inPtr;
    oPtr = ((yuvHD720P*)outPtr) + viewInfo->startY + childViewInfoLUT->startY;

#ifdef BUILD_DSP
#pragma UNROLL(2);
#pragma MUST_ITERATE(500,720, 2);
#endif
    for(rowIdx = 0; rowIdx < height ; rowIdx++)
    {
    	ViewLUT_Packed *lutbak;
#ifdef BUILD_DSP
#pragma UNROLL(4);
#pragma MUST_ITERATE(500,1280, 4);
#endif
        for(colIdx = startX, lutbak = lut + childViewInfoLUT->startX; colIdx < width ; colIdx++, lutbak++)
        {
        	yuyv *q = &iPtr[lutbak->yInteger][lutbak->xInteger];

        	BilinearInterpolation(q, lutbak, oPtr[rowIdx][colIdx].y, HD720P_WIDTH);
        }
#if 1
#ifdef BUILD_DSP
#pragma UNROLL(2);
#pragma MUST_ITERATE(350,640, 2);
#endif
        for(colIdx = startX, lutbak = lut + childViewInfoLUT->startX; colIdx < width ; colIdx+=2, lutbak+=2)
        {
        	yuyv *q = &iPtr[lutbak->yInteger][lutbak->xInteger & 0xfffe];
        	///U
        	BilinearInterpolationUV(q, lutbak, oPtr[rowIdx][colIdx].uv, HD720P_WIDTH);
        	///V
        	q ++;
        	BilinearInterpolationUV(q, lutbak, oPtr[rowIdx][colIdx+1].uv, HD720P_WIDTH);
        }
#endif
    	lut += childViewInfoLUT->pitch;
    }
    return SYSTEM_LINK_STATUS_SOK;
}


#define makeSingleView makeSingleView720P

#if 0
static inline Int32 makeSingleView(  UInt32       	*RESTRICT inPtr,
                           	   UInt32           *RESTRICT outPtr,
							   UInt32			*RESTRICT viewLUTPtr,
							   AlgorithmLink_SurroundViewLutInfo			*RESTRICT viewInfo,
							   AlgorithmLink_SurroundViewLutInfo			*RESTRICT childViewInfoLUT
                          )
{
/*
	viewInfo->width = viewInfo->width < childViewInfoLUT->width + childViewInfoLUT->startX ? viewInfo->width : childViewInfoLUT->width + childViewInfoLUT->startX;
	viewInfo->height = viewInfo->height < childViewInfoLUT->height + childViewInfoLUT->startY ? viewInfo->height : childViewInfoLUT->height+ childViewInfoLUT->startY;
*/
	makeSingleView720P(inPtr, outPtr, viewLUTPtr, viewInfo, childViewInfoLUT);

    return SYSTEM_LINK_STATUS_SOK;
}
#endif



#endif /* EXAMPLES_TDA2XX_SRC_ALG_PLUGINS_FULLVIEW_SINGLEVIEW_H_ */
