
/*
 *      $Id: NclMultiDValHLUObjData.h,v 1.3 1995-01-28 01:51:46 ethan Exp $
 */
/************************************************************************
*									*
*			     Copyright (C)  1994			*
*	     University Corporation for Atmospheric Research		*
*			     All Rights Reserved			*
*									*
************************************************************************/
/*
 *	File:		
 *
 *	Author:		Ethan Alpert
 *			National Center for Atmospheric Research
 *			PO 3000, Boulder, Colorado
 *
 *	Date:		Thu Jan 13 14:55:46 MST 1994
 *
 *	Description:	
 */
#ifndef NclMultiDValHLUObjData_h
#define NclMultiDValHLUObjData_h
#include "defs.h"
#include "NclMultiDValData.h"



typedef struct _NclMultiDValHLUObjDataPart {
	char *space_holder;
}NclMultiDValHLUObjDataPart;

typedef struct _NclMultiDValHLUObjDataRec {
	NclObjPart	obj;
	NclDataPart	data;
	NclMultiDValDataPart multidval;
	NclMultiDValHLUObjDataPart multi_obj;
}NclMultiDValHLUObjDataRec;

typedef struct _NclMultiDValHLUObjDataClassPart {
	char *foo;
}NclMultiDValHLUObjDataClassPart;

typedef struct _NclMultiDValHLUObjDataClassRec {
	NclObjClassPart	obj_class;
	NclDataClassPart data_class;
	NclMultiDValDataClassPart multid_class;
	NclMultiDValHLUObjDataClassPart multid_obj_class;
}NclMultiDValHLUObjDataClassRec;

typedef struct _NclMultiDValHLUObjDataRec* NclMultiDValHLUObjData;
typedef struct _NclMultiDValHLUObjDataClassRec* NclMultiDValHLUObjDataClass;


extern NclObjClass nclMultiDValHLUObjDataClass;
extern NclMultiDValHLUObjDataClassRec nclMultiDValHLUObjDataClassRec;

extern struct _NclMultiDValDataRec *_NclMultiDValHLUObjDataCreate(
#if	NhlNeedProto
NclObj          /* inst */,
NclObjClass     /* theclass */,
NclObjTypes     /* obj_type */,
unsigned int    /* obj_type_mask */,
void *          /* val */,
NclScalar *     /*missing_value*/,
int             /*n_dims*/,
int *           /*dim_sizes*/,
NclStatus       /*status*/,
NclSelectionRecord * /*sel_rec*/
#endif
);



#endif /*NclMultiDValHLUObjData_h */
