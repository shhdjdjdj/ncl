C
C $Id: pcsetr.f,v 1.4 1992-11-17 18:46:58 kennison Exp $
C
C
C ---------------------------------------------------------------------
C
      SUBROUTINE PCSETR (WHCH,RVAL)
C
      CHARACTER*(*) WHCH
C
C The subroutine PCSETR may be used to set PLCHHQ parameters which have
C values of type REAL.
C
C COMMON block declarations.
C
      COMMON /PCPRMS/ ADDS,CONS,DSTB,DSTL,DSTR,DSTT,HPIC(3),ICEN,IOUC,
     +                IOUF,
     +                IQUF,ISHC,ISHF,ITEF,JCOD,NFCC,NFNT,SHDX,SHDY,
     +                SIZA,SSIC,SSPR,SUBS,VPIC(3),WPIC(3),XBEG,XCEN,
     +                XEND,XMUL(3),YBEG,YCEN,YEND,YMUL(3)
      SAVE   /PCPRMS/
C
      COMMON /PCPFMQ/ IMAP,RHTW
      SAVE   /PCPFMQ/
C
C Declare the BLOCK DATA routine external to force it to load.
C
      EXTERNAL PCBLDA
C
C Set the selected parameter.
C
      IF      (WHCH(1:2).EQ.'AS'.OR.WHCH(1:2).EQ.'as') THEN
        ADDS=RVAL
      ELSE IF (WHCH(1:2).EQ.'BF'.OR.WHCH(1:2).EQ.'bf') THEN
        CALL BZSETR ('FTL',RVAL)
      ELSE IF (WHCH(1:2).EQ.'CD'.OR.WHCH(1:2).EQ.'cd') THEN
        JCOD=MAX(0,MIN(1,INT(RVAL)))
      ELSE IF (WHCH(1:2).EQ.'CE'.OR.WHCH(1:2).EQ.'ce') THEN
        ICEN=MAX(0,MIN(1,INT(RVAL)))
      ELSE IF (WHCH(1:2).EQ.'CH'.OR.WHCH(1:2).EQ.'ch') THEN
        HPIC(3)=MAX(0.,RVAL)
        YMUL(3)=HPIC(3)/9.
      ELSE IF (WHCH(1:2).EQ.'CS'.OR.WHCH(1:2).EQ.'cs') THEN
        CONS=RVAL/2.
      ELSE IF (WHCH(1:2).EQ.'CV'.OR.WHCH(1:2).EQ.'cv') THEN
        VPIC(3)=MAX(0.,RVAL)
      ELSE IF (WHCH(1:2).EQ.'CW'.OR.WHCH(1:2).EQ.'cw') THEN
        WPIC(3)=MAX(0.,RVAL)
        XMUL(3)=WPIC(3)/8.
      ELSE IF (WHCH(1:2).EQ.'FN'.OR.WHCH(1:2).EQ.'fn') THEN
        NFNT=ABS(INT(RVAL))
        IF ((NFNT.GE. 23.AND.NFNT.LE. 24).OR.
     +      (NFNT.GE. 27.AND.NFNT.LE. 28).OR.
     +      (NFNT.GE. 31.AND.NFNT.LE. 32).OR.
     +      (NFNT.GE. 38.AND.NFNT.LE.120).OR.
     +      (NFNT.GE.123.AND.NFNT.LE.124).OR.
     +      (NFNT.GE.127.AND.NFNT.LE.128).OR.
     +      (NFNT.GE.131.AND.NFNT.LE.132).OR.NFNT.GE.138) NFNT=1
      ELSE IF (WHCH(1:2).EQ.'HW'.OR.WHCH(1:2).EQ.'hw') THEN
        RHTW=RVAL
      ELSE IF (WHCH(1:2).EQ.'IH'.OR.WHCH(1:2).EQ.'ih') THEN
        HPIC(2)=MAX(0.,RVAL)
        YMUL(2)=HPIC(2)/13.
      ELSE IF (WHCH(1:2).EQ.'IS'.OR.WHCH(1:2).EQ.'is') THEN
        SSIC=MAX(0.,RVAL)
      ELSE IF (WHCH(1:2).EQ.'IV'.OR.WHCH(1:2).EQ.'iv') THEN
        VPIC(2)=MAX(0.,RVAL)
      ELSE IF (WHCH(1:2).EQ.'IW'.OR.WHCH(1:2).EQ.'iw') THEN
        WPIC(2)=MAX(0.,RVAL)
        XMUL(2)=WPIC(2)/12.
      ELSE IF (WHCH(1:2).EQ.'MA'.OR.WHCH(1:2).EQ.'ma') THEN
        IMAP=MAX(0,INT(RVAL))
      ELSE IF (WHCH(1:2).EQ.'OC'.OR.WHCH(1:2).EQ.'oc') THEN
        IOUC=INT(RVAL)
      ELSE IF (WHCH(1:2).EQ.'OF'.OR.WHCH(1:2).EQ.'of') THEN
        IOUF=MAX(0,MIN(1,INT(RVAL)))
      ELSE IF (WHCH(1:2).EQ.'PH'.OR.WHCH(1:2).EQ.'ph') THEN
        HPIC(1)=MAX(0.,RVAL)
        YMUL(1)=HPIC(1)/21.
      ELSE IF (WHCH(1:2).EQ.'PS'.OR.WHCH(1:2).EQ.'ps') THEN
        SSPR=MAX(0.,RVAL)
      ELSE IF (WHCH(1:2).EQ.'PV'.OR.WHCH(1:2).EQ.'pv') THEN
        VPIC(1)=MAX(0.,RVAL)
      ELSE IF (WHCH(1:2).EQ.'PW'.OR.WHCH(1:2).EQ.'pw') THEN
        WPIC(1)=MAX(0.,RVAL)
        XMUL(1)=WPIC(1)/16.
      ELSE IF (WHCH(1:2).EQ.'QU'.OR.WHCH(1:2).EQ.'qu') THEN
        IQUF=MAX(0,MIN(2,INT(RVAL)))
      ELSE IF (WHCH(1:2).EQ.'SA'.OR.WHCH(1:2).EQ.'sa') THEN
        SIZA=MAX(0.,RVAL)
      ELSE IF (WHCH(1:2).EQ.'SC'.OR.WHCH(1:2).EQ.'sc') THEN
        ISHC=INT(RVAL)
      ELSE IF (WHCH(1:2).EQ.'SF'.OR.WHCH(1:2).EQ.'sf') THEN
        ISHF=MAX(0,MIN(1,INT(RVAL)))
      ELSE IF (WHCH(1:2).EQ.'SS'.OR.WHCH(1:2).EQ.'ss') THEN
        SUBS=RVAL
      ELSE IF (WHCH(1:2).EQ.'SX'.OR.WHCH(1:2).EQ.'sx') THEN
        SHDX=RVAL
      ELSE IF (WHCH(1:2).EQ.'SY'.OR.WHCH(1:2).EQ.'sy') THEN
        SHDY=RVAL
      ELSE IF (WHCH(1:2).EQ.'TE'.OR.WHCH(1:2).EQ.'te') THEN
        ITEF=MAX(0,MIN(1,INT(RVAL)))
      ELSE
        CALL SETER ('PCSETR - UNRECOGNIZED PARAMETER NAME',1,2)
      END IF
C
C Done.
C
      RETURN
C
      END
