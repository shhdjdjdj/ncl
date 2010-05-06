/*
 *      $Id: vartree.h,v 1.2 2000-03-21 02:35:55 dbrown Exp $
 */
/************************************************************************
*									*
*			     Copyright (C)  1996			*
*	     University Corporation for Atmospheric Research		*
*			     All Rights Reserved			*
*									*
************************************************************************/
/*
 *	File:		vartree.h
 *
 *	Author:		David I. Brown
 *			National Center for Atmospheric Research
 *			PO 3000, Boulder, Colorado
 *
 *	Date:		Thu Apr 24 14:37:14 MDT 1997
 *
 *	Description:	
 */
#ifndef	_NG_VARTREE_H
#define	_NG_VARTREE_H

#include <ncarg/ngo/go.h>
#include <ncarg/ngo/ncl.h>

/*
 * Public api
 */
typedef void (*vtGeoNotifyFunc) (
        NhlPointer data
        );

typedef struct _NgVarTree 
{
        Widget		tree;
        vtGeoNotifyFunc	geo_notify;
        NhlPointer	geo_data;
} NgVarTree;
                
extern NgVarTree *NgCreateVarTree
(
	int			go_id,
        Widget			parent,
        NrmQuark 		qfileref,
        NrmQuark		qvar,
        NclApiDataList		*dlist
        );

extern NhlErrorTypes NgUpdateVarTree
(
        NgVarTree		*var_tree,
        NrmQuark		qfileref,
        NrmQuark		qvar,
        NclApiDataList		*dlist
        );

extern NgVarTree *NgDupVarTree
(
	int			go_id,
        Widget			parent,
        NrmQuark 		qfileref,
        NrmQuark		qvar,
        NclApiDataList		*dlist,
	NgVarTree		*to_var_tree,
        NgVarTree		*from_var_tree
        );

extern void NgDestroyVarTree
(
        NgVarTree		*var_tree
        );
        

#endif	/* _NG_VARTREE_H */