#include <stdio.h>

/*
 * The following are the required NCAR Graphics include files.
 * They should be located in ${NCARG_ROOT}/include.
 */
#include "wrapper.h"
#include "Machine.h"
#include "NclAtt.h"
#include <ncarg/ncl/NclVar.h>
#include "DataSupport.h"
#include "AttSupport.h"
#include "VarSupport.h"
#include "NclCoordVar.h"
#include <ncarg/ncl/NclCallBacksI.h>
#include <math.h>

extern void NGCALLF(waveleti,WAVELETI)(int *n, double *y, double *dt, 
                                       int *mother, double *param, 
                                       double *s0, double *dj, int *jtot,
                                       int *npad, int *noise,
                                       int *isigtest, double *siglvl,
                                       double *nadof, double *wave,
                                       double *scale, double *period, 
                                       double *coi, double *dof,
                                       double *ffttheor, double *signif,
                                       double *gws, double *ymean, 
                                       double *ysd, double *lag1,
                                       double *cdelta, double *psi0,
                                       double *power, double *phase,
                                       double *r1);

NhlErrorTypes wavelet_W( void )
{
/*
 * Input array variables
 */
  void *y, *dt, *param, *s0, *dj, *siglvl, *nadof;
  int *mother, *jtot, *npad, *noise, *isigtest;
  double *tmp_y, *tmp_dt, *tmp_param, *tmp_s0, *tmp_dj;
  double *tmp_siglvl, *tmp_nadof;
  int dsizes_y[NCL_MAX_DIMENSIONS], dsizes_nadof[1];
  NclBasicDataTypes type_y, type_dt, type_param, type_s0, type_dj;
  NclBasicDataTypes type_siglvl, type_nadof;
/*
 * Attribute variables
 */
  int att_id;
  int dsizes[NCL_MAX_DIMENSIONS];
  NclMultiDValData att_md, return_md;
  NclVar tmp_var;
  NclStackEntry return_data;
/*
 * Output array variables
 */
  void *wave, *scale, *period, *coi, *dof, *ffttheor, *signif, *gws;
  void *power, *phase, *r1, *mean, *st_dev, *lag1, *cdelta, *psi0;
  double *tmp_wave, *tmp_scale, *tmp_period, *tmp_coi, *tmp_dof; 
  double *tmp_ffttheor, *tmp_signif, *tmp_gws, *tmp_power, *tmp_phase;
  double *tmp_r1;
  double *tmp_mean, *tmp_st_dev, *tmp_lag1, *tmp_cdelta, *tmp_psi0, var;
  int ndims_wave = 3, dsizes_wave[3]; 
  NclBasicDataTypes type_wave;
  NclObjClass type_output;
/*
 * Declare various variables for random purposes.
 */
  int i, n, size_wave, size_output; 
/*
 * Retrieve parameters
 *
 * Note that any of the pointer parameters can be set to NULL,
 * which implies you don't care about its value.
 *
 * Retrieve argument #1
 */
  y = (void*)NclGetArgValue(
          0,
          12,
          NULL,
          dsizes_y,
          NULL,
          NULL,
          &type_y,
          2);

  mother = (int*)NclGetArgValue(
          1,
          12,
          NULL,
          NULL,
          NULL,
          NULL,
          NULL,
          2);

  dt = (void*)NclGetArgValue(
          2,
          12,
          NULL,
          NULL,
          NULL,
          NULL,
          &type_dt,
          2);

  param = (void*)NclGetArgValue(
          3,
          12,
          NULL,
          NULL,
          NULL,
          NULL,
          &type_param,
          2);

  s0 = (void*)NclGetArgValue(
          4,
          12,
          NULL,
          NULL,
          NULL,
          NULL,
          &type_s0,
          2);

  dj = (void*)NclGetArgValue(
          5,
          12,
          NULL,
          NULL,
          NULL,
          NULL,
          &type_dj,
          2);

  jtot = (int*)NclGetArgValue(
          6,
          12,
          NULL,
          NULL,
          NULL,
          NULL,
          NULL,
          2);

  npad = (int*)NclGetArgValue(
          7,
          12,
          NULL,
          NULL,
          NULL,
          NULL,
          NULL,
          2);

  noise = (int*)NclGetArgValue(
          8,
          12,
          NULL,
          NULL,
          NULL,
          NULL,
          NULL,
          2);

  isigtest = (int*)NclGetArgValue(
          9,
          12,
          NULL,
          NULL,
          NULL,
          NULL,
          NULL,
          2);

  siglvl = (void*)NclGetArgValue(
          10,
          12,
          NULL,
          NULL,
          NULL,
          NULL,
          &type_siglvl,
          2);

  nadof = (void*)NclGetArgValue(
          11,
          12,
          NULL,
          dsizes_nadof,
          NULL,
          NULL,
          &type_nadof,
          2);
/*
 * We haven't implemented isigtest = 2, so default to 0 if it isn't.
 */
  if(*isigtest != 0 && *isigtest != 1) {
    NhlPError(NhlWARNING,NhlEUNKNOWN,"wavelet: Only isigtest = 0 or 1 has been implmented. Defaulting to 0");
    *isigtest = 0;
  }

  if(dsizes_nadof[0] != *jtot) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"wavelet: nadof must be of length jtot");
    return(NhlFATAL);
  }
/*
 * Get size of input array.
 */
  n = dsizes_y[0];
/*
 * Coerce input if necessary.
 */
  tmp_y      = coerce_input_double(y,type_y,n,0,NULL,NULL);
  tmp_dt     = coerce_input_double(dt,type_dt,1,0,NULL,NULL);
  tmp_param  = coerce_input_double(param,type_param,1,0,NULL,NULL);
  tmp_s0     = coerce_input_double(s0,type_s0,1,0,NULL,NULL);
  tmp_dj     = coerce_input_double(dj,type_dj,1,0,NULL,NULL);
  tmp_siglvl = coerce_input_double(siglvl,type_siglvl,1,0,NULL,NULL);
  tmp_nadof  = coerce_input_double(nadof,type_nadof,dsizes_nadof[0],0,
                                   NULL,NULL);

  if(  tmp_y    == NULL || tmp_dt == NULL ||  tmp_param == NULL || 
      tmp_s0    == NULL || tmp_dj == NULL || tmp_siglvl == NULL ||
      tmp_nadof == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"wavelet: Unable to coerce input to double precision");
    return(NhlFATAL);
  }

/*
 * Allocate space for output array and attributes.
 *
 * Also, set size for output array (wave).
 */
  dsizes_wave[0] = 2;
  dsizes_wave[1] = *jtot;
  dsizes_wave[2] = n;
  size_wave = *jtot * 2 * n;

  if(type_y == NCL_double) {
    type_wave   = NCL_double;
    type_output = nclTypedoubleClass;
    size_output = sizeof(double);
  }
  else {
    type_wave   = NCL_float;
    type_output = nclTypefloatClass;
    size_output = sizeof(float);
  }
  wave     = (void*)calloc(size_wave,size_output);
  scale    = (void*)calloc(*jtot,size_output);
  period   = (void*)calloc(*jtot,size_output);
  coi      = (void*)calloc(n,size_output);
  dof      = (void*)calloc(*jtot,size_output);
  ffttheor = (void*)calloc(*jtot,size_output);
  signif   = (void*)calloc(*jtot,size_output);
  gws      = (void*)calloc(*jtot,size_output);
  power    = (void*)calloc(*jtot*n,size_output);
  phase    = (void*)calloc(*jtot*n,size_output);
  r1       = (void*)calloc(1,size_output);
  mean     = (void*)calloc(1,size_output);
  st_dev   = (void*)calloc(1,size_output);
  lag1     = (void*)calloc(1,size_output);
  cdelta   = (void*)calloc(1,size_output);
  psi0     = (void*)calloc(1,size_output);

  tmp_wave     = coerce_output_double(wave,type_wave,size_wave);
  tmp_scale    = coerce_output_double(scale,type_wave,*jtot);
  tmp_period   = coerce_output_double(period,type_wave,*jtot);
  tmp_coi      = coerce_output_double(coi,type_wave,n);
  tmp_dof      = coerce_output_double(dof,type_wave,*jtot);
  tmp_ffttheor = coerce_output_double(ffttheor,type_wave,*jtot);
  tmp_signif   = coerce_output_double(signif,type_wave,*jtot);
  tmp_gws      = coerce_output_double(gws,type_wave,*jtot);
  tmp_power    = coerce_output_double(power,type_wave,*jtot*n);
  tmp_phase    = coerce_output_double(phase,type_wave,*jtot*n);
  tmp_r1       = coerce_output_double(r1,type_wave,1);
  tmp_mean     = coerce_output_double(mean,type_wave,1);
  tmp_st_dev   = coerce_output_double(st_dev,type_wave,1);
  tmp_lag1     = coerce_output_double(lag1,type_wave,1);
  tmp_cdelta   = coerce_output_double(cdelta,type_wave,1);
  tmp_psi0     = coerce_output_double(psi0,type_wave,1);
      
  if(   tmp_wave == NULL || tmp_scale == NULL ||   tmp_period == NULL || 
         tmp_coi == NULL ||   tmp_dof == NULL || tmp_ffttheor == NULL ||
      tmp_signif == NULL ||   tmp_gws == NULL ||     tmp_mean == NULL ||
       tmp_power == NULL || tmp_phase == NULL ||   tmp_st_dev == NULL ||
        tmp_lag1 == NULL ||tmp_cdelta == NULL ||     tmp_psi0 == NULL ||
          tmp_r1 == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"wavelet: Unable to allocate memory for output variables");
    return(NhlFATAL);
  }
/*
 * Call the Fortran routine.
 */
  NGCALLF(waveleti,WAVELETI)(&n,tmp_y,tmp_dt,mother,tmp_param,tmp_s0,tmp_dj,
                             jtot,npad,noise,isigtest,tmp_siglvl,tmp_nadof,
                             tmp_wave,tmp_scale,tmp_period,tmp_coi,tmp_dof,
                             tmp_ffttheor,tmp_signif,tmp_gws,tmp_mean,
                             tmp_st_dev,tmp_lag1,tmp_cdelta,tmp_psi0,
                             tmp_power,tmp_phase,tmp_r1);
  if(type_wave == NCL_float) {
    coerce_output(wave,tmp_wave,size_wave,0);
    coerce_output(scale,tmp_scale,*jtot,0);
    coerce_output(period,tmp_period,*jtot,0);
    coerce_output(coi,tmp_coi,n,0);
    coerce_output(dof,tmp_dof,*jtot,0);
    coerce_output(ffttheor,tmp_ffttheor,*jtot,0);
    coerce_output(signif,tmp_signif,*jtot,0);
    coerce_output(gws,tmp_gws,*jtot,0);
    coerce_output(power,tmp_power,*jtot*n,0);
    coerce_output(phase,tmp_phase,*jtot*n,0);
    coerce_output(r1,tmp_r1,1,0);
    coerce_output(mean,tmp_mean,1,0);
    coerce_output(st_dev,tmp_st_dev,1,0);
    coerce_output(lag1,tmp_lag1,1,0);
    coerce_output(cdelta,tmp_cdelta,1,0);
    coerce_output(psi0,tmp_psi0,1,0);
  }
/*
 * Free memory.
 */
  if(type_y        != NCL_double) NclFree(tmp_y);
  if(type_dt       != NCL_double) NclFree(tmp_dt);
  if(type_param    != NCL_double) NclFree(tmp_param);
  if(type_s0       != NCL_double) NclFree(tmp_s0);
  if(type_dj       != NCL_double) NclFree(tmp_dj);
  if(type_siglvl   != NCL_double) NclFree(tmp_siglvl);
  if(type_nadof    != NCL_double) NclFree(tmp_nadof);

  if(type_wave != NCL_double) {
    NclFree(tmp_wave);
    NclFree(tmp_scale);
    NclFree(tmp_period);
    NclFree(tmp_coi);
    NclFree(tmp_dof);
    NclFree(tmp_ffttheor);
    NclFree(tmp_signif);
    NclFree(tmp_gws);
    NclFree(tmp_power);
    NclFree(tmp_phase);
    NclFree(tmp_r1);
    NclFree(tmp_mean);
    NclFree(tmp_st_dev);
    NclFree(tmp_lag1);
    NclFree(tmp_cdelta);
    NclFree(tmp_psi0);
  }
/*
 * Set up variable to return.
 */
  return_md = _NclCreateVal(
                            NULL,
                            NULL,
                            Ncl_MultiDValData,
                            0,
                            wave,
                            NULL,
                            ndims_wave,
                            dsizes_wave,
                            TEMPORARY,
                            NULL,
                            type_output
                            );
/*
 * Set up attributes to return.
 */
  att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);

  dsizes[0] = *jtot;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         scale,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "scale",
             att_md,
             NULL
             );

  dsizes[0] = *jtot;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         period,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "period",
             att_md,
             NULL
             );

  dsizes[0] = n;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         coi,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "coi",
             att_md,
             NULL
             );


  dsizes[0] = *jtot;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         dof,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "dof",
             att_md,
             NULL
             );

  dsizes[0] = *jtot;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         ffttheor,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "fft_theor",
             att_md,
             NULL
             );

  dsizes[0] = *jtot;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         signif,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "signif",
             att_md,
             NULL
             );
  
  dsizes[0] = *jtot;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         gws,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "gws",
             att_md,
             NULL
             );
  
  dsizes[0] = *jtot*n;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         power,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "power",
             att_md,
             NULL
             );

  dsizes[0] = *jtot*n;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         phase,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "phase",
             att_md,
             NULL
             );

  dsizes[0] = 1;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         r1,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "r1",
             att_md,
             NULL
             );

  dsizes[0] = 1;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         mean,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "mean",
             att_md,
             NULL
             );

  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         st_dev,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "stdev",
             att_md,
             NULL
             );

  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         lag1,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "lag1",
             att_md,
             NULL
             );

  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         cdelta,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "cdelta",
             att_md,
             NULL
             );

  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         psi0,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "psi0",
             att_md,
             NULL
             );

  tmp_var = _NclVarCreate(
                          NULL,
                          NULL,
                          Ncl_Var,
                          0,
                          NULL,
                          return_md,
                          NULL,
                          att_id,
                          NULL,
                          RETURNVAR,
                          NULL,
                          TEMPORARY
                          );
/*
 * Return output grid and attributes to NCL.
 */
  return_data.kind = NclStk_VAR;
  return_data.u.data_var = tmp_var;
  _NclPlaceReturn(return_data);
  return(NhlNOERROR);
}


NhlErrorTypes wavelet_default_W( void )
{
/*
 * Input array variables
 */
  void *y;
  int *mother, jtot, npad, noise, isigtest;
  double *tmp_y, dt, param, s0, dj, siglvl, *nadof;
  int dsizes_y[NCL_MAX_DIMENSIONS];
  NclBasicDataTypes type_y;
/*
 * Attribute variables
 */
  int att_id;
  int dsizes[NCL_MAX_DIMENSIONS];
  NclMultiDValData att_md, return_md;
  NclVar tmp_var;
  NclStackEntry return_data;
/*
 * Output array variables
 */
  void *wave, *scale, *period, *coi, *dof, *ffttheor, *signif, *gws;
  void *power, *phase, *r1, *mean, *st_dev, *lag1, *cdelta, *psi0;
  double *tmp_wave, *tmp_scale, *tmp_period, *tmp_coi, *tmp_dof; 
  double *tmp_ffttheor, *tmp_signif, *tmp_gws, *tmp_power, *tmp_phase;
  double *tmp_r1;
  double *tmp_mean, *tmp_st_dev, *tmp_lag1, *tmp_cdelta, *tmp_psi0, var;
  int ndims_wave = 3, dsizes_wave[3]; 
  NclBasicDataTypes type_wave;
  NclObjClass type_output;
/*
 * Declare various variables for random purposes.
 */
  int i, n, size_wave, size_output; 
/*
 * Retrieve parameters
 *
 * Note that any of the pointer parameters can be set to NULL,
 * which implies you don't care about its value.
 *
 * Retrieve argument #1
 */
  y = (void*)NclGetArgValue(
          0,
          2,
          NULL,
          dsizes_y,
          NULL,
          NULL,
          &type_y,
          2);

  mother = (int*)NclGetArgValue(
          1,
          2,
          NULL,
          NULL,
          NULL,
          NULL,
          NULL,
          2);

/*
 * Get size of input array.
 */
  n = dsizes_y[0];

/*
 * Initialize.
 */
  if (*mother <= 0 || *mother > 2) {
    param = 6.0;
  }
  else if (*mother == 1) {
    param = 4.0;
  }
  else if (*mother == 2) {
    param = 2.0;
  }

  dt       = 1.0;
  s0       = 2.*dt;
  dj       = 0.25;
  jtot     = 1 + ((log(n*dt/s0))/dj)/log(2.);
  npad     = n;
  noise    = 1;
  isigtest = 0;
  siglvl   = 0.05;
  nadof    = (double*)calloc(jtot,sizeof(double));
  
/*
 * Coerce input if necessary.
 */
  tmp_y      = coerce_input_double(y,type_y,n,0,NULL,NULL);

  if( tmp_y == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"wavelet_default: Unable to coerce input to double precision");
    return(NhlFATAL);
  }

/*
 * Allocate space for output array and attributes.
 *
 * Also, set size for output array (wave).
 */
  dsizes_wave[0] = 2;
  dsizes_wave[1] = jtot;
  dsizes_wave[2] = n;
  size_wave = jtot * 2 * n;

  if(type_y == NCL_double) {
    type_wave   = NCL_double;
    type_output = nclTypedoubleClass;
    size_output = sizeof(double);
  }
  else {
    type_wave   = NCL_float;
    type_output = nclTypefloatClass;
    size_output = sizeof(float);
  }
  wave     = (void*)calloc(size_wave,size_output);
  scale    = (void*)calloc(jtot,size_output);
  period   = (void*)calloc(jtot,size_output);
  coi      = (void*)calloc(n,size_output);
  dof      = (void*)calloc(jtot,size_output);
  ffttheor = (void*)calloc(jtot,size_output);
  signif   = (void*)calloc(jtot,size_output);
  gws      = (void*)calloc(jtot,size_output);
  power    = (void*)calloc(jtot*n,size_output);
  phase    = (void*)calloc(jtot*n,size_output);
  r1       = (void*)calloc(1,size_output);
  mean     = (void*)calloc(1,size_output);
  st_dev   = (void*)calloc(1,size_output);
  lag1     = (void*)calloc(1,size_output);
  cdelta   = (void*)calloc(1,size_output);
  psi0     = (void*)calloc(1,size_output);

  tmp_wave     = coerce_output_double(wave,type_wave,size_wave);
  tmp_scale    = coerce_output_double(scale,type_wave,jtot);
  tmp_period   = coerce_output_double(period,type_wave,jtot);
  tmp_coi      = coerce_output_double(coi,type_wave,n);
  tmp_dof      = coerce_output_double(dof,type_wave,jtot);
  tmp_ffttheor = coerce_output_double(ffttheor,type_wave,jtot);
  tmp_signif   = coerce_output_double(signif,type_wave,jtot);
  tmp_gws      = coerce_output_double(gws,type_wave,jtot);
  tmp_power    = coerce_output_double(power,type_wave,jtot*n);
  tmp_phase    = coerce_output_double(phase,type_wave,jtot*n);
  tmp_r1       = coerce_output_double(r1,type_wave,1);
  tmp_mean     = coerce_output_double(mean,type_wave,1);
  tmp_st_dev   = coerce_output_double(st_dev,type_wave,1);
  tmp_lag1     = coerce_output_double(lag1,type_wave,1);
  tmp_cdelta   = coerce_output_double(cdelta,type_wave,1);
  tmp_psi0     = coerce_output_double(psi0,type_wave,1);
      
  if(   tmp_wave == NULL || tmp_scale == NULL ||   tmp_period == NULL || 
         tmp_coi == NULL ||   tmp_dof == NULL || tmp_ffttheor == NULL ||
      tmp_signif == NULL ||   tmp_gws == NULL ||     tmp_mean == NULL ||
       tmp_power == NULL || tmp_phase == NULL ||   tmp_st_dev == NULL ||
        tmp_lag1 == NULL ||tmp_cdelta == NULL ||     tmp_psi0 == NULL ||
          tmp_r1 == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"wavelet_default: Unable to allocate memory for output variables");
    return(NhlFATAL);
  }
/*
 * Call the Fortran routine.
 */
  NGCALLF(waveleti,WAVELETI)(&n,tmp_y,&dt,mother,&param,&s0,&dj,
                             &jtot,&npad,&noise,&isigtest,&siglvl,nadof,
                             tmp_wave,tmp_scale,tmp_period,tmp_coi,tmp_dof,
                             tmp_ffttheor,tmp_signif,tmp_gws,tmp_mean,
                             tmp_st_dev,tmp_lag1,tmp_cdelta,tmp_psi0,
                             tmp_power,tmp_phase,tmp_r1);
  if(type_wave == NCL_float) {
    coerce_output(wave,tmp_wave,size_wave,0);
    coerce_output(scale,tmp_scale,jtot,0);
    coerce_output(period,tmp_period,jtot,0);
    coerce_output(coi,tmp_coi,n,0);
    coerce_output(dof,tmp_dof,jtot,0);
    coerce_output(ffttheor,tmp_ffttheor,jtot,0);
    coerce_output(signif,tmp_signif,jtot,0);
    coerce_output(gws,tmp_gws,jtot,0);
    coerce_output(power,tmp_power,jtot*n,0);
    coerce_output(phase,tmp_phase,jtot*n,0);
    coerce_output(r1,tmp_r1,1,0);
    coerce_output(mean,tmp_mean,1,0);
    coerce_output(st_dev,tmp_st_dev,1,0);
    coerce_output(lag1,tmp_lag1,1,0);
    coerce_output(cdelta,tmp_cdelta,1,0);
    coerce_output(psi0,tmp_psi0,1,0);
  }
/*
 * Free memory.
 */
  if(type_y != NCL_double) NclFree(tmp_y);
  NclFree(nadof);

  if(type_wave != NCL_double) {
    NclFree(tmp_wave);
    NclFree(tmp_scale);
    NclFree(tmp_period);
    NclFree(tmp_coi);
    NclFree(tmp_dof);
    NclFree(tmp_ffttheor);
    NclFree(tmp_signif);
    NclFree(tmp_gws);
    NclFree(tmp_power);
    NclFree(tmp_phase);
    NclFree(tmp_r1);
    NclFree(tmp_mean);
    NclFree(tmp_st_dev);
    NclFree(tmp_lag1);
    NclFree(tmp_cdelta);
    NclFree(tmp_psi0);
  }
/*
 * Set up variable to return.
 */
  return_md = _NclCreateVal(
                            NULL,
                            NULL,
                            Ncl_MultiDValData,
                            0,
                            wave,
                            NULL,
                            ndims_wave,
                            dsizes_wave,
                            TEMPORARY,
                            NULL,
                            type_output
                            );
/*
 * Set up attributes to return.
 */
  att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);

  dsizes[0] = jtot;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         scale,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "scale",
             att_md,
             NULL
             );

  dsizes[0] = jtot;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         period,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "period",
             att_md,
             NULL
             );

  dsizes[0] = n;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         coi,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "coi",
             att_md,
             NULL
             );


  dsizes[0] = jtot;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         dof,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "dof",
             att_md,
             NULL
             );

  dsizes[0] = jtot;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         ffttheor,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "fft_theor",
             att_md,
             NULL
             );

  dsizes[0] = jtot;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         signif,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "signif",
             att_md,
             NULL
             );
  
  dsizes[0] = jtot;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         gws,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "gws",
             att_md,
             NULL
             );
  
  dsizes[0] = jtot*n;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         power,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "power",
             att_md,
             NULL
             );

  dsizes[0] = jtot*n;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         phase,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "phase",
             att_md,
             NULL
             );

  dsizes[0] = 1;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         r1,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "r1",
             att_md,
             NULL
             );

  dsizes[0] = 1;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         mean,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "mean",
             att_md,
             NULL
             );

  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         st_dev,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "stdev",
             att_md,
             NULL
             );

  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         lag1,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "lag1",
             att_md,
             NULL
             );

  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         cdelta,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "cdelta",
             att_md,
             NULL
             );

  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         psi0,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         type_output
                         );
  _NclAddAtt(
             att_id,
             "psi0",
             att_md,
             NULL
             );

  tmp_var = _NclVarCreate(
                          NULL,
                          NULL,
                          Ncl_Var,
                          0,
                          NULL,
                          return_md,
                          NULL,
                          att_id,
                          NULL,
                          RETURNVAR,
                          NULL,
                          TEMPORARY
                          );
/*
 * Return output grid and attributes to NCL.
 */
  return_data.kind = NclStk_VAR;
  return_data.u.data_var = tmp_var;
  _NclPlaceReturn(return_data);
  return(NhlNOERROR);
}
