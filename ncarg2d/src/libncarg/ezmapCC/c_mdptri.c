/*
 *      $Id: c_mdptri.c,v 1.2 2008-07-23 16:16:51 haley Exp $
 */
/************************************************************************
*                                                                       *
*                Copyright (C)  2000                                    *
*        University Corporation for Atmospheric Research                *
*                All Rights Reserved                                    *
*                                                                       *
*    The use of this Software is governed by a License Agreement.       *
*                                                                       *
************************************************************************/

#include <ncarg/ncargC.h>

extern void NGCALLF(mdptri,MDPTRI)(double*,double*,double*,double*);

void c_mdptri
#ifdef NeedFuncProto
(
    double uval,
    double vval,
    double *rlat,
    double *rlon
)
#else
(uval,vval,rlat,rlon)
    double uval;
    double vval;
    double *rlat;
    double *rlon;
#endif
{
    NGCALLF(mdptri,MDPTRI)(&uval,&vval,rlat,rlon);
}
