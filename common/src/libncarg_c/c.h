/*
 *	$Id: c.h,v 1.18 1994-03-09 19:07:24 clyne Exp $
 */
/***********************************************************************
*                                                                      *
*                          Copyright (C)  1990                         *
*            University Corporation for Atmospheric Research           *
*                          All Rights Reserved                         *
*                                                                      *
*                          NCAR View V3.00alpha                        *
*                                                                      *
***********************************************************************/

#ifndef	_ncarg_c_
#define	_ncarg_c_

#include <stdio.h>
#include <sys/types.h>

#ifdef	__STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif	/*	__STDC__	*/


#ifdef	__STDC__

typedef	void *	Voidptr;

#define	LABS(X)	labs(X)
#else

/*
 *	K&R C
 */
typedef	caddr_t	Voidptr;
#define	const		/* K&R C has no 'const'	*/

#define	LABS(X)	(long) (abs((int) (X)))

#endif	/*	__STDC__	*/

/*
 * C++ prototype protector
 */
#ifdef	__cpluscplus
#define	NCARG_PROTO_BEGIN	extern "C" {
#define	NCARG_PROTO_END		}
#else
#define	NCARG_PROTO_BEGIN
#define	NCARG_PROTO_END	
#endif

typedef	unsigned int	boolean;

#ifndef	TRUE
#define FALSE	0
#define TRUE	!FALSE
#endif	/* TRUE */

NCARG_PROTO_BEGIN
/*
**
**	A R G U M E N T   V E C T O R S
**
*/

extern	char	**AToArgv(
#ifdef	NeedFuncProto
	const char      *str,
	const char      *prog_name,
	int     *argc
#endif
);

extern	void	FreeArgv(
#ifdef	NeedFuncProto
	char	**argv
#endif
);

/*
**
**	E R R O R   R E P O R T I N G
**
*/
#define	E_UNKNOWN	1000

#define	ESPRINTF(A,B)	ESprintfFirstPart(A, __FILE__, __LINE__), \
				ESprintfSecondPart B

/*
 * maintain backwords compatibility
 */
#define	ErrorGetMessage	ErrGetMsg
#define	ErrorGetNumber	ErrGetNum

/*ARGSUSED2*/
extern	const char	*ESprintf(
#ifdef	NeedFuncProto
	unsigned        err_code,
	const   char    *format,
	...
#endif
);

extern	const char	*LFESprintf(
#ifdef	NeedFuncProto
	unsigned	err_code,
	const char	*file,
	int		line,
	const char	*format,
	...
#endif
);

extern	void	ESprintfFirstPart(
#ifdef	NeedFuncProto
	int		err_code,
	const char	*file,
	int		line
#endif
);

extern const char    *ESprintfSecondPart(
#ifdef	NeedFuncProto
	const char	*format,
	...
#endif
);

extern	int	ErrorList(
#ifdef	NeedFuncProto
	unsigned start,
	unsigned num,
	const char **err_list
#endif
);

extern	const char	*ErrGetMsg();
extern	int	ErrGetNum();



/*
**
**	M I S C E L L A N Y
**
*/
extern	boolean	IsAsciiInt(
#ifdef	NeedFuncProto
	const char *s
#endif
);

extern	USleep(
#ifdef	NeedFuncProto
	unsigned usec
#endif
);

/*
**
**	O P T I O N   P A R S I N G
**
*/

/*
 *	structure for describing a valid option to buildOptionTable
 */
typedef	struct	_OptDescRec {
	const char	*option;/* name of option without preceeding '-' */
	int	arg_count;	/* num args expected by option		*/
	char	*value;		/* default value for the argument	*/
	const char	*help;	/* help string for option		*/
	} OptDescRec;

/*
 *	structure for returning the value of an option
 */
typedef	struct	_Option {
	char		*option_name;	/* the options name		*/

			/* 
			 * option type converter	
			 */
	int		(*type_conv)(
#ifdef	NeedFuncProto
			const char *from, Voidptr to
#endif
			);

	Voidptr		offset;		/* offset of return address	*/ 
	int		size;		/* size of option in bytes	*/
	} Option;

typedef	struct	_EnvOpt {
	char	*option;		/* option name			*/
	char	*env_var;		/* coresponding enviroment var	*/
	} EnvOpt;

typedef	struct	Dimension2D_ {
	int	nx, ny;
	} Dimension2D;

extern	int	NCARGCvtToInt(
#ifdef	NeedFuncProto
	const char	*from,
	Voidptr		to
#endif
);

extern	int	NCARGCvtToFloat(
#ifdef	NeedFuncProto
	const char	*from,
	Voidptr		to
#endif
);

extern	int	NCARGCvtToChar(
#ifdef	NeedFuncProto
	const char	*from,
	Voidptr		to
#endif
);

extern	int	NCARGCvtToBoolean(
#ifdef	NeedFuncProto
	const char	*from,
	Voidptr		to
#endif
);

extern	int	NCARGCvtToString(
#ifdef	NeedFuncProto
	const char	*from,
	Voidptr		to
#endif
);

extern	int	NCARGCvtToDimension2D(
#ifdef	NeedFuncProto
	const char	*from,
	Voidptr		to
#endif
);

extern	int	OpenOptionTable();

extern	int	CloseOptionTable(
#ifdef	NeedFuncProto
	int	od
#endif
);

extern	int	GetOptions(
#ifdef	NeedFuncProto
	int	od,
	const Option	*options
#endif
);

extern	int	LoadOptionTable(
#ifdef	NeedFuncProto
	int	od,
	const OptDescRec	*optd
#endif
);

extern	void	RemoveOptions(
#ifdef	NeedFuncProto
	int	od,
	const OptDescRec	*optd
#endif
);

extern	int	ParseOptionTable(
#ifdef	NeedFuncProto
	int		od,
	int		*argc,
	char		**argv,
	const OptDescRec	*optds
#endif
);

extern	int	ParseEnvOptions(
#ifdef	NeedFuncProto
	int		od,
	const EnvOpt	*envv,
	const OptDescRec	*optds
#endif
);

extern	void	PrintOptionHelp(
#ifdef	NeedFuncProto
	int	od,
	FILE	*fp
#endif
);


/*
**
**	V E R S I O N
**
*/
extern	void	PrintVersion(
#ifdef	NeedFuncProto
	const char	*header
#endif
);


/*
**
**	B I T   M A N I P U L A T I O N
**
*/


#ifndef	BITSPERBYTE
#define BITSPERBYTE     8
#endif

#ifndef	BITS
#define BITS(type)      (BITSPERBYTE * (int)sizeof(type))
#endif



#define	BYTESIZE	8
#define	POWER16		65536.0		/*two to the power 16	*/
#define	POWER32		4294967300.0	/*two to the power 32	*/
#define	POWER15		32768.0
#define	POWER31		2147483650.0	/*two to the power 32	*/


	/*
	 *	Macro for extracting N bits from TARG stating at position
	 *	POSS counting from the left. E.g GETBITS(I, 4, 3) will
	 *	extract bits at bit position 4, 3, 2 right adjusted. 
	 *	This macro contains a conditional for number of bits greater
	 *	then 32 because some architechures such as Sun 4 with a sparc
	 *	cpu or pyramids cannot shift 32.
	 */

#define GETBITS(TARG,POSS,N) \
	((N)<32 ? (((TARG) >> ((POSS)+1-(N))) & ~(~0 << (N))) : \
	((TARG) >> ((POSS)+1-(N))) )

	/*
	 *	Inverse of the GETBITS macro. Place N bits from SRC into
	 *	TARG at position POSS. 
	 */
#define	PUTBITS(TARG, POSS, N, SRC) \
		(TARG) &= ~(~((~0) << (N)) << (((POSS)+1) - (N))); \
		(TARG) |= (((SRC) & ~((~0) << (N))) << (((POSS)+1) - (N))) 

#define ZERO_INDEX(X)   (X < 0 ? 0 : X)	


/*
**
**	N C A R  G   E N V I R O N M E N T
**
*/

extern	const char	*GetNCARGPath(
#ifdef	NeedFuncProto
	const char	*dir
#endif
);

/*
**
**	M I S C E L L A N E O U S
**
*/

extern char	*NmuStrdup(
#ifdef NeedFuncProto
	const char	*str
#endif
);


NCARG_PROTO_END

#endif	/* _ncarg_c_	*/
