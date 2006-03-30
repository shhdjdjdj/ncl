C
C	$Id: g01pat.f,v 1.7 2006-03-30 00:45:03 fred Exp $
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
      SUBROUTINE G01PAT
C
C  Process primitive attributes.
C
      include 'gksin.h'
      include 'g01ins.h'
      include 'g01adc.h'
C
        REAL   UP, BASE, DMAX, FACTOR
C
        GOTO (210, 220, 230, 240, 250, 260, 270, 280,
     +        290, 300, 310, 320, 330, 340, 350, 360,
     +        370, 380, 390, 400, 410, 420, 430) MCODES-20
C
C  POLYLINE INDEX
C
  210 CONTINUE
      CALL GUPDVI (ID(1), IVPLIX, 1)
      RETURN
C
C  LINETYPE
C
  220 CONTINUE
      CALL GUPDVI (ID, IVLTYP, 1)
      RETURN
C
C  LINEWIDTH SCALE FACTOR
C
  230 CONTINUE
      CALL GUPDVR (RX, IVLWSC, 1)
      RETURN
C
C  POLYLINE COLOR INDEX
C
  240 CONTINUE
      CALL GUPDVI (IC, IVPLCI, 1)
      RETURN
C
C  POLYMARKER INDEX
C
  250 CONTINUE
      CALL GUPDVI (ID, IVPMIX, 2)
      RETURN
C
C  MARKER TYPE
C
  260 CONTINUE
      CALL GUPDVI (ID, IVMTYP, 2)
      RETURN
C
C  MARKER SIZE SCALE FACTOR
C
  270 CONTINUE
      CALL GUPDVR (RX, IVMSZS, 2)
      RETURN
C
C  POLYMARKER COLOR INDEX
C
  280 CONTINUE
      CALL GUPDVI (IC, IVPMCI, 2)
      RETURN
C
C  TEXT INDEX
C
  290 CONTINUE
      CALL GUPDVI (ID, IVTXIX, 3)
      RETURN
C
C  TEXT FONT AND PRECISION
C
  300 CONTINUE
C
C  Font.
C    Convert GKS font index to CGM pointer to font list.
C
      IFP = ABS(ID(1))
      CALL GUPDVI (IFP, IVTXFO, 3)
C
C  Precision.
C
      CALL GUPDVI (ID(2), IVTXPR, 3)
      RETURN
C
C  CHARACTER EXPANSION FACTOR
C
  310 CONTINUE
      CALL GUPDVR (RX, IVCHXP, 3)
      RETURN
C
C  CHARACTER SPACING
C
  320 CONTINUE
      CALL GUPDVR (RX, IVCHSP, 3)
      RETURN
C
C  TEXT COLOR INDEX
C
  330 CONTINUE
      CALL GUPDVI (IC, IVTXCI, 3)
      RETURN
C
C  CHARACTER ORIENTATION VECTORS
C
  340 CONTINUE
C
C  Extract and process height.
C
      UP   = SQRT (RX(1)**2+RY(1)**2)
      BASE = SQRT (RX(2)**2+RY(2)**2)
      DMAX = MAX(UP,BASE)
      IF (DMAX .GT. 1.0)  THEN
C
C  A vector is longer than 1.0 NDC, scale down both vectors equally.
C
        FACTOR = 1.0/MAX(1.,DMAX)
        RX(1) = FACTOR*RX(1)
        RY(1) = FACTOR*RY(1)
        RX(2) = FACTOR*RX(2)
        RY(2) = FACTOR*RY(2)
      END IF
C
C  Fix height and process it.
C
      RTMP = 0.5+UP*REAL(MYSCAL)
      ID(1) = MAXYVD
      IF (RTMP .LT. REAL(MAXYVD)) ID(1) = INT(RTMP)
      CALL GUPDVI (ID, IVCHH, 3)
C
C  Convert NDC vectors to VDC and process.
C
      ID(1) = MIN (MAXYVD, INT (0.5 + MXSCAL*RX(1)))
      ID(2) = MIN (MAXYVD, INT (0.5 + MYSCAL*RY(1)))
      ID(3) = MIN (MAXYVD, INT (0.5 + MXSCAL*RX(2)))
      ID(4) = MIN (MAXYVD, INT (0.5 + MYSCAL*RY(2)))
      CALL GUPDVI (ID, IVCHOV, 3)
      RETURN
C
C  TEXT PATH
C
  350 CONTINUE
      CALL GUPDVI (ID, IVTXP, 3)
      RETURN
C
C  TEXT ALIGNMENT
C
  360 CONTINUE
      CALL GUPDVI (ID, IVTXAL, 3)
      RETURN
C
C  FILL AREA INDEX
C
  370 CONTINUE
      CALL GUPDVI (ID, IVFAIX, 4)
      RETURN
C
C  FILL AREA INTERIOR STYLE
C
  380 CONTINUE
      CALL GUPDVI (ID, IVFAIS, 4)
      RETURN
C
C  FILL AREA STYLE INDEX
C
  390 CONTINUE
      CALL GUPDVI (ID, IVFASI, 4)
      RETURN
C
C  FILL AREA COLOR INDEX
C
  400 CONTINUE
      CALL GUPDVI (IC, IVFACI, 4)
      RETURN
C
C  PATTERN SIZE
C
  410 CONTINUE
C
C  Truncate DX,DY to limits of NDC unit square,
C  convert to VDC, store as height and width vectors.
C
      ID(4) = 0
      ID(3) = INT(REAL(MXSCAL)*(MAX(0.,MIN(1.0,RX(1)))))
      ID(2) = INT(REAL(MYSCAL)*(MAX(0.,MIN(1.0,RY(1)))))
      ID(1) = 0
      CALL GUPDVI (ID, IVPASZ, 4)
      RETURN
C
C  PATTERN REFERENCE POINT
C
  420 CONTINUE
C
C  Truncate X,Y to limits of NDC unit square and convert to VDC.
C
      ID(1) = INT(REAL(MXSCAL)*(MAX(0.,MIN(1.0,RX(1)))))
      ID(2) = INT(REAL(MYSCAL)*(MAX(0.,MIN(1.0,RX(2)))))
      CALL GUPDVI (ID, IVPARF, 4)
      RETURN
C
C  ASPECT SOURCE FLAGS
C
  430 CONTINUE
      CALL GUPASF
C
      RETURN
      END
