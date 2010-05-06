/*
 * $Id: c_ccpsps2.c,v 1.5 1994-08-23 22:50:21 haley Exp $
 */

#include <stdio.h>

#include <ncarg/ncargC.h>
#include <ncarg/gks.h>

#define M    20
#define N    30
#define LRWK    3500
#define LIWK    3500
#define LZRG    2000

float x[] = {1.,  2.,  3.,  5.,  7., 11., 13., 17., 19., 23., 29., 31., 37., 
             41., 43., 47., 53., 59., 61., 67.};
#define WSTYPE SED_WSTYPE
#define WKID   1

main()
{
    float y[N], z[N][M], zreg[LZRG], rwrk[LRWK];
    int iwrk[LIWK];
    extern void getdat(), mark();

    getdat (x, y, z);
/*
 * Open GKS
 */
    gopen_gks ("stdout",0);
    gopen_ws (WKID, NULL, WSTYPE);
    gactivate_ws(WKID);
/*
 * Turn clipping off
 */
    gset_clip_ind (GIND_NO_CLIP);
/*
 * Limit viewport so there's room to mark the data points
 */
    c_cpsetr("VPR",.8);
/*
 * Initialize Conpack
 */
    c_cpsps2(x,y,(float *)z,M,M,N,rwrk,LRWK,iwrk,LIWK,zreg,LZRG);
/*
 * Draw perimiter
 */
    c_cpback(zreg, rwrk, iwrk);
/*
 * Draw Contours
 */
    c_cpcldr(zreg,rwrk,iwrk);
/*
 * Mark data points
 */
    mark (x,y);
/*
 * Close frame and close GKS
 */
    c_frame();
    gdeactivate_ws(WKID);
    gclose_ws(WKID);
    gclose_gks();
}

void getdat (x, y, z)
float *x, *y, *z;
{
    int i, j, l;
/*
 * X and Y data locations must be in increasing order.
 */
    y[0] = 1.;
    for( i = 1; i < N; i++ ) {
        y[i] = 1.1*y[i-1] + 1./(float)(i+1);
    }

    l = 0;
    for( j = 0; j < N; j++ ) {
        for( i = 0; i < M; i++ ) {
            z[l++]= 10.e-5*(-16.*(float)(x[i]*x[i]*y[j])+34.*(float)
                            (x[i]*y[j]*y[j]) - (float)(6*x[i]) + 93.);
        }
    }
    return;
}

void mark (x, y)
float *x, *y;
{
    int i, j;

    gset_marker_size(.5);

    for( i = 0; i < M; i++ ) {
        for( j = 0; j < N; j++ ) {
            c_points (&x[i], &y[j], 1, -4, 0);
        }
    }
    return;
}