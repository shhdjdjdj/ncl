C
C	$Id: gwiclw.f,v 1.1 1993-01-09 02:09:09 fred Exp $
C
      SUBROUTINE GWICLW
C
C CLEAR WORKSTATION
C
      include 'gwiarq.h'
      include 'gksin.h'
      include 'gwiwsl.h'
      include 'gwiio.h'
      include 'gwiins.h'
      include 'gwiast.h'
      include 'gwiadf.h'
      include 'gwiopc.h'
      include 'gksenu.h'
C
      SAVE
C
C  Flush buffer.
C
      CALL GWIFLB (RERR)
      IF (RERR.NE.0)  GO TO 77
C
C  Reset all attribute deferral control variables.
C
      CALL GWPDVA
C
C  Set WSL entry "DISPLAY SURFACE EMPTY" to "EMPTY".
C
      MDEMPT = GEMPTY
C
C  Set WSL entry "NEW FRAME ACTION NECESSARY AT UPDATE" to "NO".
C
      MNFRAM = GNO
C
C  If update state is pending, set current window and viewport
C  entries to those requested.
C
      IF (MTUS .EQ. GPEND) THEN
         CWINDO(1) = RWINDO(1)
         CWINDO(2) = RWINDO(2)
         CWINDO(3) = RWINDO(3)
         CWINDO(4) = RWINDO(4)
         CWKVP(1) = RWKVP(1)
         CWKVP(2) = RWKVP(2)
         CWKVP(3) = RWKVP(3)
         CWKVP(4) = RWKVP(4)
C
C  Set workstation update state to "NOT PENDING".
C
         MTUS = GNPEND
      ENDIF
C
   77 RETURN
C
      END
