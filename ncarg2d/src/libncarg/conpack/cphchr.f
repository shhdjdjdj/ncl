C
C $Id: cphchr.f,v 1.3 1994-03-17 01:51:04 kennison Exp $
C
      SUBROUTINE CPHCHR (RWRK,IPTX,IPTY,NXYC)
C
      DIMENSION RWRK(*)
C
C (RWRK(I),I=IPTX+1,IPTX+NXYC) and (RWRK(I),I=IPTY+1,IPTY+NXYC) contain
C the X and Y coordinates (in the user coordinate system) of points
C that define a segment of a contour line.  The function of the routine
C CPHCHR is to hachure the segment, if appropriate.
C
C
C Declare all of the CONPACK common blocks.
C
C
C CPCOM1 contains integer and real variables.
C
      COMMON /CPCOM1/ ANCF,ANHL,ANIL,ANLL,CDMX,CHWM,CINS,CINT(10)
      COMMON /CPCOM1/ CINU,CLDB(256),CLDL(256),CLDR(256)
      COMMON /CPCOM1/ CLDT(256),CLEV(256),CLWA(259),CXCF
      COMMON /CPCOM1/ CXIL,CYCF,CYIL,DBLF,DBLM,DBLN,DBLV,DFLD,DOPT
      COMMON /CPCOM1/ EPSI,FNCM,GRAV,GRSD,GSDM,HCHL,HCHS,IAIA(259)
      COMMON /CPCOM1/ IAIB(256),IBCF,IBHL,IBIL,IBLL,ICAF,ICCF
      COMMON /CPCOM1/ ICCL(259),ICFF,ICHI,ICHL,ICIL,ICLL(256)
      COMMON /CPCOM1/ ICLO,ICLP(256),ICLS,ICLU(259),ICLV,ICLW
      COMMON /CPCOM1/ IDUF,IGCL,IGLB,IGRM,IGRN,IGVS,IHCF,IHLX,IHLY
      COMMON /CPCOM1/ IIWS(2),IIWU,ILBC,IMPF,INCX(8),INCY(8)
      COMMON /CPCOM1/ INHL,INIL,INIT,INLL,IOCF,IOHL,IOLL,IPAI,IPCF
      COMMON /CPCOM1/ IPIC,IPIE,IPIL,IPLL,IRWS(4),IRWU,ISET,IWSO
      COMMON /CPCOM1/ IZD1,IZDM,IZDN,IZDS,JODP,JOMA,JOTZ,LCTM,LEA1
      COMMON /CPCOM1/ LEA2,LEA3,LEE1,LEE2,LEE3,LINS,LINT(10),LINU
      COMMON /CPCOM1/ LIWK,LIWM,LIWS(2),LNLG,LRWC,LRWG,LRWK
      COMMON /CPCOM1/ LRWM,LRWS(4),LSDD,LSDL,LSDM,LTCF,LTHI
      COMMON /CPCOM1/ LTIL,LTLO,MIRO,NCLB(256),NCLV,NDGL,NEXL
      COMMON /CPCOM1/ NEXT,NEXU,NLBS,NLSD,NLZF,NOMF,NOVS,NR04,NSDL
      COMMON /CPCOM1/ NSDR,OORV,SCFS,SCFU,SEGL,SVAL,T2DS,T3DS,UCMN
      COMMON /CPCOM1/ UCMX,UVPB,UVPL,UVPR,UVPS,UVPT,UWDB,UWDL,UWDR
      COMMON /CPCOM1/ UWDT,UXA1,UXAM,UYA1,UYAN,WCCF,WCHL,WCIL,WCLL
      COMMON /CPCOM1/ WLCF,WLHL,WLIL,WLLL,WOCH,WODA,WTCD,WTGR,WTNC
      COMMON /CPCOM1/ WTOD,WWCF,WWHL,WWIL,WWLL,XAT1,XATM,XLBC,XVPL
      COMMON /CPCOM1/ XVPR,XWDL,XWDR,YAT1,YATN,YLBC,YVPB,YVPT,YWDB
      COMMON /CPCOM1/ YWDT,ZDVL,ZMAX,ZMIN
      EQUIVALENCE (IIWS(1),II01),(LIWS(1),LI01)
      EQUIVALENCE (IIWS(2),II02),(LIWS(2),LI02)
      EQUIVALENCE (IRWS(1),IR01),(LRWS(1),LR01)
      EQUIVALENCE (IRWS(2),IR02),(LRWS(2),LR02)
      EQUIVALENCE (IRWS(3),IR03),(LRWS(3),LR03)
      EQUIVALENCE (IRWS(4),IR04),(LRWS(4),LR04)
      SAVE   /CPCOM1/
C
C CPCOM2 holds character parameters.
C
      COMMON /CPCOM2/ CHEX,CLBL(256),CLDP(259),CTMA,CTMB,FRMT
      COMMON /CPCOM2/ TXCF,TXHI,TXIL,TXLO
      CHARACTER*13 CHEX
      CHARACTER*40 CLBL
      CHARACTER*128 CLDP
      CHARACTER*500 CTMA,CTMB
      CHARACTER*8 FRMT
      CHARACTER*40 TXCF
      CHARACTER*20 TXHI
      CHARACTER*100 TXIL
      CHARACTER*20 TXLO
      SAVE   /CPCOM2/
C
C Define required constants.
C
      DATA DTOR / .017453292519943 /
      DATA RTOD / 57.2957795130823 /
C
C Determine whether or not hachuring is to be done for this segment.
C
      IF (ABS(IHCF).GT.1) THEN
C
        IF (RWRK(IPTX+NXYC).NE.RWRK(IPTX+1).OR.RWRK(IPTY+NXYC).NE.RWRK(I
     +PTY+1)) THEN
          IF (IOCF.NE.0) GO TO 101
          IF (ABS(IHCF).EQ.2) GO TO 101
          IF (ABS(IHCF).EQ.3) RETURN
          ANGN=RTOD*ARRAT2(RWRK(IPTY+2)-RWRK(IPTY+1),
     +                     RWRK(IPTX+2)-RWRK(IPTX+1))
        ELSE
C
          ANGN=RTOD*ARRAT2(RWRK(IPTY+NXYC)-RWRK(IPTY+NXYC-1),
     +                     RWRK(IPTX+NXYC)-RWRK(IPTX+NXYC-1))
        END IF
C
        ANGT=0.
C
        DO 10001 I=1,NXYC-1
          ANGO=ANGN
          ANGN=RTOD*ARRAT2(RWRK(IPTY+I+1)-RWRK(IPTY+I),
     +                     RWRK(IPTX+I+1)-RWRK(IPTX+I))
          IF (ABS(ANGN-ANGO).GT.180.) ANGO=ANGO+SIGN(360.,ANGN-ANGO)
          ANGT=ANGT+ANGN-ANGO
10001   CONTINUE
C
        IF ((MIRO.EQ.0.AND.ANGT.LT.0.).OR.(MIRO.NE.0.AND.ANGT.GT.0.)) TH
     +EN
          IF (IHCF.GT.0) RETURN
        ELSE
          IF (IHCF.LT.0) RETURN
        END IF
C
      END IF
C
C Convert all the X and Y coordinates to the fractional system.
C
  101 CONTINUE
      DO 10002 I=1,NXYC
        RWRK(IPTX+I)=CUFX(RWRK(IPTX+I))
        IF (ICFELL('CPHCHR',1).NE.0) RETURN
        RWRK(IPTY+I)=CUFY(RWRK(IPTY+I))
        IF (ICFELL('CPHCHR',2).NE.0) RETURN
10002 CONTINUE
C
C Compute the total length of the polyline.
C
      TLEN=0.
C
      DO 10003 I=1,NXYC-1
        TLEN=TLEN+SQRT((RWRK(IPTX+I+1)-RWRK(IPTX+I))**2+
     +                 (RWRK(IPTY+I+1)-RWRK(IPTY+I))**2)
10003 CONTINUE
C
C Decide how long the hachures ought to be and on which side of the
C polyline they ought to go.
C
      HCHD=HCHL*(XVPR-XVPL)
      IF (MIRO.NE.0) HCHD=-HCHD
      IF ((XWDL.LT.XWDR.AND.YWDB.GT.YWDT).OR.
     +    (XWDL.GT.XWDR.AND.YWDB.LT.YWDT)) HCHD=-HCHD
C
C Draw hachures along the polyline.
C
      TEMP=REAL(INT(TLEN/(HCHS*(XVPR-XVPL))))
      IF (TEMP.LE.0.) RETURN
      DBHM=TLEN/TEMP
      PNHM=DBHM/2.
C
      I=0
      CLEN=0.
C
10004 CONTINUE
      IF (.NOT.(I.LT.NXYC-1)) GO TO 10005
        I=I+1
        SLEN=SQRT((RWRK(IPTX+I+1)-RWRK(IPTX+I))**2+
     +            (RWRK(IPTY+I+1)-RWRK(IPTY+I))**2)
10006   CONTINUE
        IF (.NOT.(PNHM.LT.CLEN+SLEN)) GO TO 10007
          FRCT=(PNHM-CLEN)/SLEN
          XCP1=RWRK(IPTX+I)+FRCT*(RWRK(IPTX+I+1)-RWRK(IPTX+I))
          YCP1=RWRK(IPTY+I)+FRCT*(RWRK(IPTY+I+1)-RWRK(IPTY+I))
          CALL PLOTIF (XCP1,YCP1,0)
          IF (ICFELL('CPHCHR',3).NE.0) RETURN
          XCP2=XCP1-HCHD*(RWRK(IPTY+I+1)-RWRK(IPTY+I))/SLEN
          YCP2=YCP1+HCHD*(RWRK(IPTX+I+1)-RWRK(IPTX+I))/SLEN
          CALL PLOTIF (XCP2,YCP2,1)
          IF (ICFELL('CPHCHR',4).NE.0) RETURN
          PNHM=PNHM+DBHM
        GO TO 10006
10007   CONTINUE
        CLEN=CLEN+SLEN
      GO TO 10004
10005 CONTINUE
C
C Done.
C
      RETURN
C
      END
