C
C $Id: pcgetc.f,v 1.10 1994-03-17 18:44:30 kennison Exp $
C
      SUBROUTINE PCGETC (WHCH,CVAL)
C
      CHARACTER*(*) WHCH,CVAL
C
C The subroutine PCGETC may be used to get PLCHHQ parameters which have
C values of type CHARACTER.
C
C COMMON block declarations.
C
      COMMON /PCPRMS/ ADDS,CONS,DSTB,DSTL,DSTR,DSTT,HPIC(3),IBXC(3),
     +                IBXF,ICEN,IORD,IOUC,IOUF,IPCC,IQUF,ISHC,ISHF,ITEF,
     +                JCOD,LSCI(16),NFCC,NODF,RBXL,RBXM,RBXX,RBXY,ROLW,
     +                RPLW,RSLW,SHDX,SHDY,SIZA,SSIC,SSPR,SUBS,VPIC(3),
     +                WPIC(3),XBEG,XCEN,XEND,XMUL(3),YBEG,YCEN,YEND,
     +                YMUL(3)
      SAVE   /PCPRMS/
C
      COMMON /PCFNNO/ LFNO(43),LFNL
      SAVE   /PCFNNO/
C
      COMMON /PCFNNM/ LFNM(43,2)
      CHARACTER*18 LFNM
      SAVE   /PCFNNM/
C
C Declare the BLOCK DATA routine external to force it to load.
C
      EXTERNAL PCBLDA
C
C Check for an uncleared prior error.
C
      IF (ICFELL('PCGETC - UNCLEARED PRIOR ERROR',1).NE.0) RETURN
C
C There are only two possibilities:  In the case of the function-code
C character, take into account that what is really stored is the index
C of the character in the local collating sequence; provide for the
C case that the parameter had not been initialized yet.
C
      IF (WHCH(1:2).EQ.'FC'.OR.WHCH(1:2).EQ.'fc') THEN
        IF (NFCC.LT.0) NFCC=ICHAR(':')
        CVAL=CHAR(NFCC)
      ELSE IF (WHCH(1:2).EQ.'FN'.OR.WHCH(1:2).EQ.'fn') THEN
        DO 101 I=1,LFNL
          IF (NODF.EQ.LFNO(I)) THEN
            CVAL=LFNM(I,1)
            GO TO 102
          END IF
  101   CONTINUE
        CVAL='!FONT NOT DEFINED!'
      ELSE
        CALL SETER ('PCGETC - UNRECOGNIZED PARAMETER NAME',2,1)
        RETURN
      END IF
C
C Done.
C
  102 RETURN
C
      END
