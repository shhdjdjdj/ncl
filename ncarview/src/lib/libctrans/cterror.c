/*
 *	$Id: cterror.c,v 1.12 1992-06-24 21:05:03 clyne Exp $
 */
/***********************************************************************
*                                                                      *
*                          Copyright (C)  1990                         *
*            University Corporation for Atmospheric Research           *
*                          All Rights Reserved                         *
*                                                                      *
*                      NCAR View V3.01 - UNIX Release                  *
*                                                                      *
***********************************************************************/
/*LINTLIBRARY*/
/*	cerror.c:
 *
 *	Author:		John Clyne
 * 
 *	Date:		Fri Jan 13 17:30:08 MST 1989
 *
 *		This is the error handling module for ctrans. By default
 *	the module reports all error messages and causes termination if 
 *	necessary. These defaults may be overwritten by the functions 
 *	"set_report_err" and "set_action_err." (documentation on them
 *	follows). This module is intialized by the first call to init_ctrans
 *	of ctrans. If you are writing a driver (main not device) you may
 *	use the module in your driver if you intialize it first.
 *	ct_error must also be closed in order to print out error message
 *	since the messages are stored in a temporary file until termination.
 *	This is necessary when in graphcap mode since error messages would
 *	otherwise be interpreted as graphics instructions.
 *
 */

#include	<stdio.h>

#include	<fcntl.h>

#define	_cerror_
#include	<ncarv.h>
#include	<cgm_tools.h>
#include	"cgmc.h"
#include	<cterror.h>
#include	"devices.h"

#define	PRINT_E(X) (void) fprintf(errfile, X)

extern	char *mktemp(), *strcpy(), *strcat();
extern	struct	device	devices[];
extern	Ct_err	(*cmdtab[][MAXCLASS+1][MAXFUNCPERCLASS+1])();
extern	int	currdev;

static	CGMC	cgmc;
static	FILE	*errfile;
static	char    tempFile[80];

char	*program_name;
static	Report	report = ALL;	/* level of error report		*/
static	Action	action = ACT;	/* terminate ctrans on a fatal error?	*/

#ifndef TMPDIR
#define TMPDIR "/tmp"
#endif

#define TMPFILE         "/ctrans.XXXXXX"

/*
 *	Prints the error message and an usage statement 
 */
static	void usage(message)
char	*message;
{
	int	i;
	extern	int	optionDesc;

	(void) fprintf(errfile,"%s\n",message);
	(void) fprintf(
		errfile, 
		"Usage: %s -d <device> -f <font> [options] [device-specific options] [ - | metafile... ]\n", program_name
	);
	PrintOptionHelp(optionDesc, errfile);
}



	/*	ct_error:
	 *	PUBLIC
	 * 
	 *	print out appropriate error message. If "action" is set to ACT
	 *	and the error is fatal the ct_error will close ctrans.
	 *
	 * on entry:
	 *	error		: an error defined in cterror.h
	 *	message		: additional error message. must at least be ""
	 */	
	ct_error(error, message)
		Ct_err	error;
		char	*message;
	{

		/*
		 *	see if error is fatal or not
		 */
		if ((int) error <= END_NT) {

			pre_err = SICK;		/* error not fatal. 
						 * record not fatal
						 */

			if (report != ALL && report != NON_TERM)
				return;

			(void) fprintf(errfile, "%s: ", program_name); 
			if (message && strlen(message)) {
				(void) fprintf(errfile,"%s :", message);
			}

			switch (error) {

			/*
			 *	general non_fatal errors
			 */
			case NT_MALLOC	: 
				PRINT_E("memory allocation error");
				break;

			case NT_NULL	: 
				PRINT_E("");
				break;

			/*
			 *	input errors
			 */
			case NT_NNCGM	: 
				PRINT_E("non NCAR CGM record format");
				break;

			case NT_IOUE	: 
				PRINT_E("illegal or unsupported element");
				break;

			case NT_UCGMDF	: 
				PRINT_E("unsupported CGM data format");
				break;

			/*
			 *	graphcap errors
			 */
			case NT_GFEE	: 
				PRINT_E("graphcap format or encoding error");
				break;

			/*
			 *	interpretation errors
			 */
			case NT_UFONT	: 
				PRINT_E("unknown font");
				break;

			case NT_CAE	: 
				PRINT_E("error allocating colours");
				break;

			case NT_ICE	: 
				PRINT_E("error creating icon from bitmap");
				break;

			case NT_ILSM	: 
				PRINT_E("invalid line specification mode");
				break;

			case NT_IIP	: 
				PRINT_E("invalid integer precision");
				break;

			case NT_IFP	: 
				PRINT_E("invalid floating point precision");
				break;

			case NT_UPMT	: 
				PRINT_E("unsupported polymarker type");
				break;

			case NT_UPFS	: 
				PRINT_E("unsupported polygon fill style");
				break;

			case NT_UPLS	: 
				PRINT_E("unsupported polyline style");
				break;

			case NT_CAFE	: 
				PRINT_E("cell array format error");
				break;

			case NT_ICTI	: 
				PRINT_E("undefined colour table index");
				break;

			case NT_ITA	: 
				PRINT_E("invalid text attribute");
				break;

			case NT_FLTB	: 
				PRINT_E("font list to big");
				break;

			case NT_PBTS	: 
				PRINT_E("point buffer too small");
				break;

			/*
			 *	X11 specific errors
			 */
			case NT_X11CRME	: 
				PRINT_E("X11 color resource manager error");
				break;

			default	:
				/* invalid error message	*/
				break;
			}
			(void) fprintf(stderr, "\n");

		}
		else {

			/*
			 *	terminal errors
			 */
			pre_err = DIE;


			if (report == ALL || report == TERMINAL) {

				(void) fprintf(errfile, "%s: ", program_name); 
				if (message && strlen(message)) {
					(void) fprintf(errfile,"%s :", message);
				}

				switch (error) {

				/*
				 *	general errors
				 */
				case  T_CNOD:
					PRINT_E ("can not open device");
					break;

				case  T_MALLOC:
					PRINT_E ("memory allocation error");
					break;

				case  T_EE:
					PRINT_E ("error in CGM encoding");
					break;

				/*
				 *	input errors
				 */
				case  T_FOE:
					PRINT_E ("file open error");
					break;

				case  T_FRE:
					PRINT_E ("file read error");
				break;

				case  T_FSE:
					PRINT_E ("file seek error");
					break;

				/*
				 *	control errors
				 */

				case  T_MM:
				usage ("missing metafile");
				break;

			case  T_MD:
				usage ("missing device");
				break;

			case  T_MF:
				usage ("missing font");
				break;

			case  T_MR:
				usage ("missing record number");
				break;

			case  T_NSO:
				usage ("no such option");
				break;

			case  T_NULL:
				usage("");
				break;

			/*
			 *	X11 specific errors
			 */
			case  T_X11DEVNS:
				PRINT_E ("DISPLAY environment variable not set");
				break;

			default:
				/* invalid error message	*/
				break;
			}

			(void) fprintf(errfile, "\n");
		}

		/*
		 * clean up and exit
		 */
		if (action == ACT) {

			if (currdev >= 0) {	/* do we have a device? */
				int	devnum;
				/*
				 * execute the coresponding CGM End Metafile 
				 * function for the device
				 */
				devnum = devices[currdev].number;
				(void)
				(*cmdtab[devnum][DEL_ELEMENT][END_MF])(&cgmc);
				if (devices[currdev].usegcap) 
					flush();
			}

			close_ct_error();
			exit(1);
		}
	}
}

/*	set_report_err:
 *	PUBLIC
 *	
 *		Set level of error messages reported
 * on entry:
 *	status		: one of (ALL, TERMINAL, NON_TERM)
 * on exit
 *	report		: set to status
 *				ALL => report all errors
 *				TERMINAL => report only terminal messages
 *				NON_TERM => report only non terminal messages
 */
set_report_err(status)
	Report	status;
{
	report = status;
}

/*	set_action:
 *	PUBLIC
 *		Set action 
 * on entry:
 *	status		: one of (ACT, NO_ACT)
 * on exit
 *	action		: set to status
 *				ACT => terminate on terminal error
 *				NO_ACT => do not terminate on terminals
 */
set_action_err(status)
	Action	status;
{
	action = status;
}
	

/*	init_ct_error:
 *	PUBLIC
 *
 *		intialize ct_error
 * on entry:
 *	prog_name	: program name to be used in error messages
 */
init_ct_error(prog_name, file_)
	char	*prog_name;
	boolean	file_;
{

	program_name = prog_name;

	(void) strcpy(tempFile, TMPDIR);
	(void) strcat(tempFile, TMPFILE);

	/*
	 *	Open the error file. 
	 */
	if (file_) {
		(void) mktemp(tempFile);
		if ((errfile = fopen(tempFile,"w")) == NULL) {
			perror(program_name);
			errfile = stderr;
		}
		setbuf(errfile, NULL);	/* turn off buffered i/o	*/
	}
	else
		errfile = stderr;
}


#define BUFSIZE 80
/*	close_ct_error
 *	PUBLIC
 *
 *		close ct_error. print out error messages. exit ctrans.
 * on entry 
 *
 */
close_ct_error()
{

	int	i;
	int	fd;
        char    buffer[BUFSIZE];


	/* 
	 * make sure errfile was successfuly opened
	 */
	if (errfile == stderr) 
		return;

	(void)fclose(errfile);

	/*
	 *	read the errors and print them out to stderr
	 */
	if ((fd = open(tempFile,O_RDONLY)) > -1) {
		while ((i=read(fd,buffer,BUFSIZE)) != 0)
			(void)write(2,buffer,i);
		(void)close(fd);
	}

	/*
	 *	clean up 
	 */
	(void)unlink(tempFile);

}