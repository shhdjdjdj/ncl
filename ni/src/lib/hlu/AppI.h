/*
 *      $Id: AppI.h,v 1.5 1996-05-09 23:16:12 ethan Exp $
 */
/************************************************************************
*									*
*			     Copyright (C)  1994			*
*	     University Corporation for Atmospheric Research		*
*			     All Rights Reserved			*
*									*
************************************************************************/
/*
 *	File:		AppI.h
 *
 *	Author:		Jeff W. Boote
 *			National Center for Atmospheric Research
 *			PO 3000, Boulder, Colorado
 *
 *	Date:		Fri Jul 29 16:42:28 MDT 1994
 *
 *	Description:	
 */
#ifndef	_NAppI_h
#define	_NAppI_h


#include <ncarg/hlu/hluP.h>
#include <ncarg/hlu/Callbacks.h>
#include <ncarg/hlu/App.h>

#define	_NhlNappMode	"app.Mode"
#define	_NhlCappMode	_NhlClangMode

#define	_NhlNnoAppDB	"no.App.DB"
#define	_NhlCnoAppDB	"No.App.DB"

#define	_NhlNdefApp	"def.App"
#define	_NhlCdefApp	"Def.App"

extern	NhlLayer _NhlGetCurrentApp(
#if	NhlNeedProto
	void
#endif
);

extern	int _NhlGetDefaultApp(
#if	NhlNeedProto
	void
#endif
);

extern	NrmDatabase _NhlGetResDB(
#if	NhlNeedProto
	NhlLayer	l
#endif
);

extern void _NhlSetLang(
#if	NhlNeedProto
	_NhlC_OR_F	ltype
#endif
);

extern NhlErrorTypes _NhlSortAppArgs(
#if	NhlNeedProto
	NhlLayer	l,
	_NhlArgList	args_in,
	int		nargs_in,
	_NhlArgList	*args_out,
	int		*nargs_out
#endif
);

/*
* cbdata to cbfunc will be HLU Id of app whose
* NhlNappDefaultParent resource has changed either
* from True to False or False to True
*/
extern _NhlCB  NhlSetAppDefaultChangeCB(
#if     NhlNeedProto
        NhlClass        oc,
        _NhlCBFunc      cbfunc,
        NhlArgVal       udata
#endif
);


#endif	/* _NAppI_h */
