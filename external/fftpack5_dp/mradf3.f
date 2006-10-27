CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C
C   FFTPACK 5.0
C   Copyright (C) 1995-2004, Scientific Computing Division,
C   University Corporation for Atmospheric Research
C   Licensed under the GNU General Public License (GPL)
C
C   Authors:  Paul N. Swarztrauber and Richard A. Valent
C
C   $Id: mradf3.f,v 1.1 2006-10-27 16:34:10 haley Exp $
C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE MRADF3(M,IDO,L1,CC,IM1,IN1,CH,IM2,IN2,WA1,WA2)
      DOUBLE PRECISION ARG
      DOUBLE PRECISION TAUR
      DOUBLE PRECISION TAUI
      DOUBLE PRECISION CH(IN2,IDO,3,L1),CC(IN1,IDO,L1,3),WA1(IDO),
     +                 WA2(IDO)
C
      M1D = (M-1)*IM1 + 1
      M2S = 1 - IM2
      ARG = 2.D0*4.D0*ATAN(1.0D0)/3.D0
      TAUR = COS(ARG)
      TAUI = SIN(ARG)
      DO 101 K = 1,L1
          M2 = M2S
          DO 1001 M1 = 1,M1D,IM1
              M2 = M2 + IM2
              CH(M2,1,1,K) = CC(M1,1,K,1) + (CC(M1,1,K,2)+CC(M1,1,K,3))
              CH(M2,1,3,K) = TAUI* (CC(M1,1,K,3)-CC(M1,1,K,2))
              CH(M2,IDO,2,K) = CC(M1,1,K,1) +
     +                         TAUR* (CC(M1,1,K,2)+CC(M1,1,K,3))
 1001     CONTINUE
  101 CONTINUE
      IF (IDO.EQ.1) RETURN
      IDP2 = IDO + 2
      DO 103 K = 1,L1
          DO 102 I = 3,IDO,2
              IC = IDP2 - I
              M2 = M2S
              DO 1002 M1 = 1,M1D,IM1
                  M2 = M2 + IM2
                  CH(M2,I-1,1,K) = CC(M1,I-1,K,1) +
     +                             ((WA1(I-2)*CC(M1,I-1,K,
     +                             2)+WA1(I-1)*CC(M1,I,K,2))+
     +                             (WA2(I-2)*CC(M1,I-1,K,
     +                             3)+WA2(I-1)*CC(M1,I,K,3)))
                  CH(M2,I,1,K) = CC(M1,I,K,1) +
     +                           ((WA1(I-2)*CC(M1,I,K,2)-WA1(I-1)*CC(M1,
     +                           I-1,K,2))+ (WA2(I-2)*CC(M1,I,K,
     +                           3)-WA2(I-1)*CC(M1,I-1,K,3)))
                  CH(M2,I-1,3,K) = (CC(M1,I-1,K,1)+
     +                             TAUR* ((WA1(I-2)*CC(M1,I-1,K,
     +                             2)+WA1(I-1)*CC(M1,I,K,
     +                             2))+ (WA2(I-2)*CC(M1,I-1,K,
     +                             3)+WA2(I-1)*CC(M1,I,K,3)))) +
     +                             (TAUI* ((WA1(I-2)*CC(M1,I,K,
     +                             2)-WA1(I-1)*CC(M1,I-1,K,
     +                             2))- (WA2(I-2)*CC(M1,I,K,
     +                             3)-WA2(I-1)*CC(M1,I-1,K,3))))
                  CH(M2,IC-1,2,K) = (CC(M1,I-1,K,1)+
     +                              TAUR* ((WA1(I-2)*CC(M1,I-1,K,
     +                              2)+WA1(I-1)*CC(M1,I,K,
     +                              2))+ (WA2(I-2)*CC(M1,I-1,K,
     +                              3)+WA2(I-1)*CC(M1,I,K,3)))) -
     +                              (TAUI* ((WA1(I-2)*CC(M1,I,K,
     +                              2)-WA1(I-1)*CC(M1,I-1,K,
     +                              2))- (WA2(I-2)*CC(M1,I,K,
     +                              3)-WA2(I-1)*CC(M1,I-1,K,3))))
                  CH(M2,I,3,K) = (CC(M1,I,K,1)+
     +                           TAUR* ((WA1(I-2)*CC(M1,I,K,
     +                           2)-WA1(I-1)*CC(M1,I-1,K,
     +                           2))+ (WA2(I-2)*CC(M1,I,K,
     +                           3)-WA2(I-1)*CC(M1,I-1,K,3)))) +
     +                           (TAUI* ((WA2(I-2)*CC(M1,I-1,K,
     +                           3)+WA2(I-1)*CC(M1,I,K,
     +                           3))- (WA1(I-2)*CC(M1,I-1,K,
     +                           2)+WA1(I-1)*CC(M1,I,K,2))))
                  CH(M2,IC,2,K) = (TAUI* ((WA2(I-2)*CC(M1,I-1,K,
     +                            3)+WA2(I-1)*CC(M1,I,K,
     +                            3))- (WA1(I-2)*CC(M1,I-1,K,
     +                            2)+WA1(I-1)*CC(M1,I,K,2)))) -
     +                            (CC(M1,I,K,1)+TAUR*
     +                            ((WA1(I-2)*CC(M1,I,K,
     +                            2)-WA1(I-1)*CC(M1,I-1,K,
     +                            2))+ (WA2(I-2)*CC(M1,I,K,
     +                            3)-WA2(I-1)*CC(M1,I-1,K,3))))
 1002         CONTINUE
  102     CONTINUE
  103 CONTINUE
      RETURN
      END
