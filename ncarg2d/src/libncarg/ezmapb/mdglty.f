C
C $Id: mdglty.f,v 1.1 2001-08-16 23:10:45 kennison Exp $
C
C                Copyright (C)  2000
C        University Corporation for Atmospheric Research
C                All Rights Reserved
C
C This file is free software; you can redistribute it and/or modify
C it under the terms of the GNU General Public License as published
C by the Free Software Foundation; either version 2 of the License, or
C (at your option) any later version.
C
C This software is distributed in the hope that it will be useful, but
C WITHOUT ANY WARRANTY; without even the implied warranty of
C MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
C General Public License for more details.
C
C You should have received a copy of the GNU General Public License
C along with this software; if not, write to the Free Software
C Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
C USA.
C
      SUBROUTINE MDGLTY (IARG)
C
        INTEGER IARG
C
C This routine may be called by a user from the line-processing routine
C specified as the final argument in a call to MDLNDM in order to obtain
C the type of the line being processed.
C
        COMMON /MAPCMZ/  NNMS,ILTY,IAIL,IAIR,BLAG,SLAG,BLOG,SLOG,
     +                   PNTS(200)
        INTEGER          NNMS,ILTY,IAIL,IAIR
        REAL             BLAG,SLAG,BLOG,SLOG,PNTS
        SAVE   /MAPCMZ/
C
        IARG=ILTY
C
        RETURN
C
      END
