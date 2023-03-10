/*
 * untitled.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "untitled".
 *
 * Model version              : 1.1
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Fri Mar 10 11:37:13 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "untitled.h"
#include "untitled_private.h"

/* Block signals (default storage) */
B_untitled_T untitled_B;

/* Block states (default storage) */
DW_untitled_T untitled_DW;

/* Real-time model */
static RT_MODEL_untitled_T untitled_M_;
RT_MODEL_untitled_T *const untitled_M = &untitled_M_;

/* Model step function */
void untitled_step(void)
{
  real_T rtb_donotdeletethisgain;
  real_T rtb_donotdeletethisgain_p;
  boolean_T AND6_tmp;
  boolean_T rtb_LogicalOperator10;
  boolean_T rtb_LogicalOperator17;
  boolean_T rtb_LogicalOperator8;
  boolean_T rtb_RelationalOperator;
  boolean_T rtb_RelationalOperator1;
  boolean_T rtb_RelationalOperator2;
  boolean_T rtb_RelationalOperator4;

  /* S-Function (sfun_spssw_discc): '<S59>/State-Space' incorporates:
   *  Constant: '<S22>/DC'
   *  Constant: '<S23>/eee'
   *  Constant: '<S61>/SwitchCurrents'
   */

  /* S-Function block: <S59>/State-Space */
  {
    real_T accum;

    /* Circuit has switches */
    int_T *switch_status = (int_T*) untitled_DW.StateSpace_PWORK.SWITCH_STATUS;
    int_T *switch_status_init = (int_T*)
      untitled_DW.StateSpace_PWORK.SWITCH_STATUS_INIT;
    int_T *SwitchChange = (int_T*) untitled_DW.StateSpace_PWORK.SW_CHG;
    int_T *gState = (int_T*) untitled_DW.StateSpace_PWORK.G_STATE;
    real_T *yswitch = (real_T*)untitled_DW.StateSpace_PWORK.Y_SWITCH;
    int_T *switchTypes = (int_T*) untitled_DW.StateSpace_PWORK.SWITCH_TYPES;
    int_T *idxOutSw = (int_T*) untitled_DW.StateSpace_PWORK.IDX_OUT_SW;
    real_T *DxCol = (real_T*)untitled_DW.StateSpace_PWORK.DX_COL;
    real_T *tmp2 = (real_T*)untitled_DW.StateSpace_PWORK.TMP2;
    real_T *BDcol = (real_T*)untitled_DW.StateSpace_PWORK.BD_COL;
    real_T *tmp1 = (real_T*)untitled_DW.StateSpace_PWORK.TMP1;
    real_T *uswlast = (real_T*)untitled_DW.StateSpace_PWORK.USWLAST;
    int_T newState;
    int_T swChanged = 0;
    int loopsToDo = 20;
    real_T temp;

    /* keep an initial copy of switch_status*/
    memcpy(switch_status_init, switch_status, 13 * sizeof(int_T));
    memcpy(uswlast, &untitled_B.StateSpace_o1[0], 13*sizeof(real_T));
    do {
      if (loopsToDo == 1) {            /* Need to reset some variables: */
        swChanged = 0;

        /* return to the original switch status*/
        {
          int_T i1;
          for (i1=0; i1 < 13; i1++) {
            swChanged = ((SwitchChange[i1] = switch_status_init[i1] -
                          switch_status[i1]) != 0) ? 1 : swChanged;
            switch_status[i1] = switch_status_init[i1];
          }
        }
      } else {
        /*
         * Compute outputs:
         * ---------------
         */
        real_T *Cs = (real_T*)untitled_DW.StateSpace_PWORK.CS;
        real_T *Ds = (real_T*)untitled_DW.StateSpace_PWORK.DS;

        {
          int_T i1;
          real_T *y0 = &untitled_B.StateSpace_o1[0];
          for (i1=0; i1 < 17; i1++) {
            accum = 0.0;
            accum += *(Cs++) * untitled_DW.StateSpace_DSTATE[0];
            accum += *(Cs++) * untitled_DW.StateSpace_DSTATE[1];
            accum += *(Cs++) * untitled_DW.StateSpace_DSTATE[2];
            accum += *(Cs++) * untitled_DW.StateSpace_DSTATE[3];

            {
              int_T i2;
              const real_T *u0 = &untitled_P.SwitchCurrents_Value[0];
              for (i2=0; i2 < 13; i2++) {
                accum += *(Ds++) * u0[i2];
              }

              accum += *(Ds++) * untitled_P.DC1_Amplitude;
              accum += *(Ds++) * untitled_P.eee_Value;
            }

            y0[i1] = accum;
          }
        }

        swChanged = 0;

        {
          int_T i1;
          real_T *y0 = &untitled_B.StateSpace_o1[0];
          for (i1=0; i1 < 13; i1++) {
            switch (switchTypes[i1]) {
             case 3 :                  /* Diodes */
              newState = y0[i1] > 0.0 ? 1 : ((y0[i1] < 0.0) ? 0 :
                switch_status[i1]);
              break;

             case 7 :                  /* MOSFETs or IGBT/Diode pairs */
              newState = ((y0[i1] > 0.0) && (gState[i1] > 0)) || (y0[i1] < 0.0) ?
                1 : (((y0[i1] > 0.0) && gState[i1] == 0) ? 0 : switch_status[i1]);
              break;
            }

            swChanged = ((SwitchChange[i1] = newState - switch_status[i1]) != 0)
              ? 1 : swChanged;
            switch_status[i1] = newState;/* Keep new state */
          }
        }
      }

      /*
       * Compute new As, Bs, Cs and Ds matrixes:
       * --------------------------------------
       */
      if (swChanged) {
        real_T *As = (real_T*)untitled_DW.StateSpace_PWORK.AS;
        real_T *Cs = (real_T*)untitled_DW.StateSpace_PWORK.CS;
        real_T *Bs = (real_T*)untitled_DW.StateSpace_PWORK.BS;
        real_T *Ds = (real_T*)untitled_DW.StateSpace_PWORK.DS;
        real_T a1;

        {
          int_T i1;
          for (i1=0; i1 < 13; i1++) {
            if (SwitchChange[i1] != 0) {
              a1 = 1000.0*SwitchChange[i1];
              temp = 1/(1-Ds[i1*16]*a1);

              {
                int_T i2;
                for (i2=0; i2 < 17; i2++) {
                  DxCol[i2]= Ds[i2 * 15 + i1]*temp*a1;
                }
              }

              DxCol[i1] = temp;
              BDcol[0]= Bs[0 + i1]*a1;
              BDcol[1]= Bs[15 + i1]*a1;
              BDcol[2]= Bs[30 + i1]*a1;
              BDcol[3]= Bs[45 + i1]*a1;

              /* Copy row nSw of Cs into tmp1 and zero it out in Cs */
              memcpy(tmp1, &Cs[i1 * 4], 4 * sizeof(real_T));
              memset(&Cs[i1 * 4], '\0', 4 * sizeof(real_T));

              /* Copy row nSw of Ds into tmp2 and zero it out in Ds */
              memcpy(tmp2, &Ds[i1 * 15], 15 * sizeof(real_T));
              memset(&Ds[i1 * 15], '\0', 15 * sizeof(real_T));

              /* Cs = Cs + DxCol * tmp1, Ds = Ds + DxCol * tmp2 *******************/
              {
                int_T i2;
                for (i2=0; i2 < 17; i2++) {
                  a1 = DxCol[i2];
                  Cs[i2 * 4 + 0] += a1 * tmp1[0];
                  Cs[i2 * 4 + 1] += a1 * tmp1[1];
                  Cs[i2 * 4 + 2] += a1 * tmp1[2];
                  Cs[i2 * 4 + 3] += a1 * tmp1[3];

                  {
                    int_T i3;
                    for (i3=0; i3 < 15; i3++) {
                      Ds[i2 * 15 + i3] += a1 * tmp2[i3];
                    }
                  }
                }
              }

              /* As = As + BdCol*Cs(nSw,:), Bs = Bs + BdCol*Ds(nSw,:) *************/
              a1 = BDcol[0];
              As[0 + 0] += a1 * Cs[i1 * 4 + 0];
              As[0 + 1] += a1 * Cs[i1 * 4 + 1];
              As[0 + 2] += a1 * Cs[i1 * 4 + 2];
              As[0 + 3] += a1 * Cs[i1 * 4 + 3];

              {
                int_T i2;
                for (i2=0; i2 < 15; i2++) {
                  Bs[0 + i2] += a1 * Ds[i1 * 15 + i2];
                }
              }

              a1 = BDcol[1];
              As[4 + 0] += a1 * Cs[i1 * 4 + 0];
              As[4 + 1] += a1 * Cs[i1 * 4 + 1];
              As[4 + 2] += a1 * Cs[i1 * 4 + 2];
              As[4 + 3] += a1 * Cs[i1 * 4 + 3];

              {
                int_T i2;
                for (i2=0; i2 < 15; i2++) {
                  Bs[15 + i2] += a1 * Ds[i1 * 15 + i2];
                }
              }

              a1 = BDcol[2];
              As[8 + 0] += a1 * Cs[i1 * 4 + 0];
              As[8 + 1] += a1 * Cs[i1 * 4 + 1];
              As[8 + 2] += a1 * Cs[i1 * 4 + 2];
              As[8 + 3] += a1 * Cs[i1 * 4 + 3];

              {
                int_T i2;
                for (i2=0; i2 < 15; i2++) {
                  Bs[30 + i2] += a1 * Ds[i1 * 15 + i2];
                }
              }

              a1 = BDcol[3];
              As[12 + 0] += a1 * Cs[i1 * 4 + 0];
              As[12 + 1] += a1 * Cs[i1 * 4 + 1];
              As[12 + 2] += a1 * Cs[i1 * 4 + 2];
              As[12 + 3] += a1 * Cs[i1 * 4 + 3];

              {
                int_T i2;
                for (i2=0; i2 < 15; i2++) {
                  Bs[45 + i2] += a1 * Ds[i1 * 15 + i2];
                }
              }
            }
          }
        }
      }                                /* if (swChanged) */
    } while (swChanged > 0 && --loopsToDo > 0);

    if (loopsToDo == 0) {
      real_T *Cs = (real_T*)untitled_DW.StateSpace_PWORK.CS;
      real_T *Ds = (real_T*)untitled_DW.StateSpace_PWORK.DS;

      {
        int_T i1;
        real_T *y0 = &untitled_B.StateSpace_o1[0];
        for (i1=0; i1 < 17; i1++) {
          accum = 0.0;
          accum += *(Cs++) * untitled_DW.StateSpace_DSTATE[0];
          accum += *(Cs++) * untitled_DW.StateSpace_DSTATE[1];
          accum += *(Cs++) * untitled_DW.StateSpace_DSTATE[2];
          accum += *(Cs++) * untitled_DW.StateSpace_DSTATE[3];

          {
            int_T i2;
            const real_T *u0 = &untitled_P.SwitchCurrents_Value[0];
            for (i2=0; i2 < 13; i2++) {
              accum += *(Ds++) * u0[i2];
            }

            accum += *(Ds++) * untitled_P.DC1_Amplitude;
            accum += *(Ds++) * untitled_P.eee_Value;
          }

          y0[i1] = accum;
        }
      }
    }

    /* Output new switches states */
    {
      int_T i1;
      real_T *y1 = &untitled_B.StateSpace_o2[0];
      for (i1=0; i1 < 13; i1++) {
        y1[i1] = (real_T)switch_status[i1];
      }
    }
  }

  /* Gain: '<S17>/do not delete this gain' */
  rtb_donotdeletethisgain = untitled_P.donotdeletethisgain_Gain *
    untitled_B.StateSpace_o1[13];

  /* Gain: '<S1>/do not delete this gain' */
  rtb_donotdeletethisgain_p = untitled_P.donotdeletethisgain_Gain_i *
    untitled_B.StateSpace_o1[16];

  /* Gain: '<Root>/Gain' */
  rtb_donotdeletethisgain_p *= untitled_P.Gain_Gain;

  /* Scope: '<Root>/Scope' */
  {
    StructLogVar *svar = (StructLogVar *)untitled_DW.Scope_PWORK.LoggedData[0];
    LogVar *var = svar->signals.values;

    /* time */
    {
      double locTime = (((untitled_M->Timing.clockTick1+
                          untitled_M->Timing.clockTickH1* 4294967296.0)) *
                        5.0E-7)
        ;
      rt_UpdateLogVar((LogVar *)svar->time, &locTime, 0);
    }

    /* signals */
    {
      real_T up0[1];
      up0[0] = rtb_donotdeletethisgain;
      rt_UpdateLogVar((LogVar *)var, up0, 0);
      var = var->next;
    }

    {
      real_T up1[1];
      up1[0] = rtb_donotdeletethisgain_p;
      rt_UpdateLogVar((LogVar *)var, up1, 0);
    }
  }

  /* Scope: '<Root>/Scope5' */
  {
    StructLogVar *svar = (StructLogVar *)untitled_DW.Scope5_PWORK.LoggedData;
    LogVar *var = svar->signals.values;

    /* time */
    {
      double locTime = (((untitled_M->Timing.clockTick1+
                          untitled_M->Timing.clockTickH1* 4294967296.0)) *
                        5.0E-7)
        ;
      rt_UpdateLogVar((LogVar *)svar->time, &locTime, 0);
    }

    /* signals */
    {
      real_T up0[1];
      up0[0] = rtb_donotdeletethisgain_p;
      rt_UpdateLogVar((LogVar *)var, up0, 0);
    }
  }

  /* Sin: '<S12>/Sine Wave2' */
  rtb_donotdeletethisgain = sin(untitled_P.SineWave2_Freq * untitled_M->
    Timing.t[0] + untitled_P.SineWave2_Phase) * untitled_P.SineWave2_Amp +
    untitled_P.SineWave2_Bias;

  /* RelationalOperator: '<S12>/Relational Operator3' incorporates:
   *  Constant: '<S12>/Constant'
   */
  untitled_B.RelationalOperator3 = (rtb_donotdeletethisgain >=
    untitled_P.Constant_Value);

  /* DataTypeConversion: '<S33>/Data Type Conversion' */
  untitled_B.DataTypeConversion = untitled_B.RelationalOperator3;

  /* Abs: '<S12>/Abs' */
  untitled_B.Abs = fabs(rtb_donotdeletethisgain);

  /* RelationalOperator: '<S12>/Relational Operator1' incorporates:
   *  Constant: '<S12>/Constant7'
   */
  rtb_RelationalOperator1 = (untitled_P.Constant7_Value <= untitled_B.Abs);

  /* RelationalOperator: '<S12>/Relational Operator2' incorporates:
   *  Constant: '<S12>/Constant9'
   */
  rtb_RelationalOperator2 = (untitled_P.Constant9_Value <= untitled_B.Abs);

  /* Logic: '<S12>/Logical Operator8' */
  rtb_LogicalOperator8 = !rtb_RelationalOperator2;

  /* RelationalOperator: '<S12>/Relational Operator4' incorporates:
   *  Constant: '<S12>/Constant1'
   */
  rtb_RelationalOperator4 = (untitled_P.Constant1_Value <= untitled_B.Abs);

  /* Logic: '<S44>/AND4' incorporates:
   *  Logic: '<S41>/AND2'
   *  Logic: '<S42>/AND2'
   */
  AND6_tmp = (rtb_RelationalOperator1 && rtb_LogicalOperator8);

  /* Logic: '<S44>/AND6' incorporates:
   *  Logic: '<S44>/AND4'
   */
  untitled_B.AND6 = (AND6_tmp || rtb_RelationalOperator4);

  /* DataTypeConversion: '<S31>/Data Type Conversion' */
  untitled_B.DataTypeConversion_o = untitled_B.AND6;

  /* DataTypeConversion: '<S35>/Data Type Conversion' incorporates:
   *  Logic: '<S12>/Logical Operator1'
   */
  untitled_B.DataTypeConversion_f = !untitled_B.RelationalOperator3;

  /* RelationalOperator: '<S12>/Relational Operator' incorporates:
   *  Constant: '<S12>/Constant6'
   */
  rtb_RelationalOperator = (untitled_P.Constant6_Value <= untitled_B.Abs);

  /* Logic: '<S12>/Logical Operator17' */
  rtb_LogicalOperator17 = !untitled_B.RelationalOperator3;

  /* Logic: '<S12>/Logical Operator10' */
  rtb_LogicalOperator10 = !rtb_RelationalOperator;

  /* Logic: '<S45>/AND4' incorporates:
   *  Logic: '<S45>/AND1'
   *  Logic: '<S45>/AND2'
   *  Logic: '<S45>/AND7'
   */
  untitled_B.AND4 = (((rtb_RelationalOperator1 || rtb_RelationalOperator2 ||
                       rtb_RelationalOperator || rtb_RelationalOperator4) &&
                      rtb_LogicalOperator17) || (rtb_LogicalOperator10 &&
    untitled_B.RelationalOperator3));

  /* DataTypeConversion: '<S25>/Data Type Conversion' incorporates:
   *  Logic: '<S12>/Logical Operator2'
   */
  untitled_B.DataTypeConversion_c = !untitled_B.AND4;

  /* Logic: '<S12>/Logical Operator6' */
  rtb_RelationalOperator1 = !rtb_RelationalOperator1;

  /* Logic: '<S41>/AND1' incorporates:
   *  Logic: '<S42>/AND1'
   */
  rtb_LogicalOperator8 = (rtb_LogicalOperator8 || rtb_LogicalOperator10 ||
    rtb_RelationalOperator1);

  /* Logic: '<S41>/AND6' incorporates:
   *  Logic: '<S41>/AND1'
   *  Logic: '<S41>/AND3'
   *  Logic: '<S41>/AND5'
   */
  untitled_B.AND6_n = ((AND6_tmp && rtb_LogicalOperator17) ||
                       (rtb_LogicalOperator8 && untitled_B.RelationalOperator3));

  /* DataTypeConversion: '<S52>/Data Type Conversion' */
  untitled_B.DataTypeConversion_d = untitled_B.AND6_n;

  /* DataTypeConversion: '<S54>/Data Type Conversion' incorporates:
   *  DataTypeConversion: '<S52>/Data Type Conversion'
   */
  untitled_B.DataTypeConversion_h = untitled_B.AND6_n;

  /* Logic: '<S43>/AND6' incorporates:
   *  Logic: '<S12>/Logical Operator3'
   *  Logic: '<S43>/AND3'
   *  Logic: '<S43>/AND4'
   */
  untitled_B.AND6_m = ((rtb_RelationalOperator && rtb_RelationalOperator1) ||
                       (rtb_RelationalOperator2 && (!rtb_RelationalOperator4)));

  /* DataTypeConversion: '<S39>/Data Type Conversion' */
  untitled_B.DataTypeConversion_k = untitled_B.AND6_m;

  /* Logic: '<S42>/AND6' incorporates:
   *  Logic: '<S42>/AND3'
   *  Logic: '<S42>/AND5'
   */
  untitled_B.AND6_f = ((AND6_tmp && untitled_B.RelationalOperator3) ||
                       (rtb_LogicalOperator8 && rtb_LogicalOperator17));

  /* DataTypeConversion: '<S48>/Data Type Conversion' */
  untitled_B.DataTypeConversion_hc = untitled_B.AND6_f;

  /* DataTypeConversion: '<S50>/Data Type Conversion' incorporates:
   *  DataTypeConversion: '<S48>/Data Type Conversion'
   */
  untitled_B.DataTypeConversion_ow = untitled_B.AND6_f;

  /* Logic: '<S47>/AND3' incorporates:
   *  Logic: '<S46>/AND3'
   */
  rtb_RelationalOperator2 = (rtb_RelationalOperator4 || rtb_RelationalOperator2);

  /* Logic: '<S47>/AND4' incorporates:
   *  Logic: '<S47>/AND3'
   */
  untitled_B.AND4_m = (rtb_RelationalOperator2 && rtb_LogicalOperator17);

  /* DataTypeConversion: '<S27>/Data Type Conversion' */
  untitled_B.DataTypeConversion_e = untitled_B.AND4_m;

  /* Logic: '<S46>/AND4' */
  untitled_B.AND4_b = (rtb_RelationalOperator2 && untitled_B.RelationalOperator3);

  /* DataTypeConversion: '<S37>/Data Type Conversion' */
  untitled_B.DataTypeConversion_i = untitled_B.AND4_b;

  /* DataTypeConversion: '<S29>/Data Type Conversion' */
  untitled_B.DataTypeConversion_g = untitled_B.AND4;

  /* Gain: '<S18>/do not delete this gain' */
  rtb_donotdeletethisgain_p = untitled_P.donotdeletethisgain_Gain_m *
    untitled_B.StateSpace_o1[14];

  /* Gain: '<S19>/do not delete this gain' */
  rtb_donotdeletethisgain = untitled_P.donotdeletethisgain_Gain_b *
    untitled_B.StateSpace_o1[15];

  /* Scope: '<Root>/Scope1' */
  {
    StructLogVar *svar = (StructLogVar *)untitled_DW.Scope1_PWORK.LoggedData[0];
    LogVar *var = svar->signals.values;

    /* time */
    {
      double locTime = (((untitled_M->Timing.clockTick1+
                          untitled_M->Timing.clockTickH1* 4294967296.0)) *
                        5.0E-7)
        ;
      rt_UpdateLogVar((LogVar *)svar->time, &locTime, 0);
    }

    /* signals */
    {
      real_T up0[1];
      up0[0] = rtb_donotdeletethisgain_p;
      rt_UpdateLogVar((LogVar *)var, up0, 0);
      var = var->next;
    }

    {
      real_T up1[1];
      up1[0] = rtb_donotdeletethisgain;
      rt_UpdateLogVar((LogVar *)var, up1, 0);
    }
  }

  /* Matfile logging */
  rt_UpdateTXYLogVars(untitled_M->rtwLogInfo, (untitled_M->Timing.t));

  /* Update for S-Function (sfun_spssw_discc): '<S59>/State-Space' incorporates:
   *  Constant: '<S22>/DC'
   *  Constant: '<S23>/eee'
   *  Constant: '<S61>/SwitchCurrents'
   */

  /* S-Function block: <S59>/State-Space */
  {
    const real_T *As = (real_T*)untitled_DW.StateSpace_PWORK.AS;
    const real_T *Bs = (real_T*)untitled_DW.StateSpace_PWORK.BS;
    real_T *xtmp = (real_T*)untitled_DW.StateSpace_PWORK.XTMP;
    real_T accum;

    /* Calculate new states... */
    accum = 0.0;
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[0];
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[1];
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[2];
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[3];

    {
      int_T i1;
      const real_T *u0 = &untitled_P.SwitchCurrents_Value[0];
      for (i1=0; i1 < 13; i1++) {
        accum += *(Bs++) * u0[i1];
      }

      accum += *(Bs++) * untitled_P.DC1_Amplitude;
      accum += *(Bs++) * untitled_P.eee_Value;
    }

    xtmp[0] = accum;
    accum = 0.0;
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[0];
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[1];
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[2];
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[3];

    {
      int_T i1;
      const real_T *u0 = &untitled_P.SwitchCurrents_Value[0];
      for (i1=0; i1 < 13; i1++) {
        accum += *(Bs++) * u0[i1];
      }

      accum += *(Bs++) * untitled_P.DC1_Amplitude;
      accum += *(Bs++) * untitled_P.eee_Value;
    }

    xtmp[1] = accum;
    accum = 0.0;
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[0];
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[1];
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[2];
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[3];

    {
      int_T i1;
      const real_T *u0 = &untitled_P.SwitchCurrents_Value[0];
      for (i1=0; i1 < 13; i1++) {
        accum += *(Bs++) * u0[i1];
      }

      accum += *(Bs++) * untitled_P.DC1_Amplitude;
      accum += *(Bs++) * untitled_P.eee_Value;
    }

    xtmp[2] = accum;
    accum = 0.0;
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[0];
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[1];
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[2];
    accum += *(As++) * untitled_DW.StateSpace_DSTATE[3];

    {
      int_T i1;
      const real_T *u0 = &untitled_P.SwitchCurrents_Value[0];
      for (i1=0; i1 < 13; i1++) {
        accum += *(Bs++) * u0[i1];
      }

      accum += *(Bs++) * untitled_P.DC1_Amplitude;
      accum += *(Bs++) * untitled_P.eee_Value;
    }

    xtmp[3] = accum;
    untitled_DW.StateSpace_DSTATE[0] = xtmp[0];
    untitled_DW.StateSpace_DSTATE[1] = xtmp[1];
    untitled_DW.StateSpace_DSTATE[2] = xtmp[2];
    untitled_DW.StateSpace_DSTATE[3] = xtmp[3];

    {
      int_T *gState = (int_T*)untitled_DW.StateSpace_PWORK.G_STATE;

      /* Store switch gates values for next step */
      *(gState++) = (int_T) 0.0;
      *(gState++) = (int_T) untitled_B.DataTypeConversion_c;
      *(gState++) = (int_T) untitled_B.DataTypeConversion_e;
      *(gState++) = (int_T) untitled_B.DataTypeConversion_g;
      *(gState++) = (int_T) untitled_B.DataTypeConversion_o;
      *(gState++) = (int_T) untitled_B.DataTypeConversion;
      *(gState++) = (int_T) untitled_B.DataTypeConversion_f;
      *(gState++) = (int_T) untitled_B.DataTypeConversion_i;
      *(gState++) = (int_T) untitled_B.DataTypeConversion_k;
      *(gState++) = (int_T) untitled_B.DataTypeConversion_hc;
      *(gState++) = (int_T) untitled_B.DataTypeConversion_ow;
      *(gState++) = (int_T) untitled_B.DataTypeConversion_d;
      *(gState++) = (int_T) untitled_B.DataTypeConversion_h;
    }
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.0s, 0.0s] */
    if ((rtmGetTFinal(untitled_M)!=-1) &&
        !((rtmGetTFinal(untitled_M)-untitled_M->Timing.t[0]) >
          untitled_M->Timing.t[0] * (DBL_EPSILON))) {
      rtmSetErrorStatus(untitled_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++untitled_M->Timing.clockTick0)) {
    ++untitled_M->Timing.clockTickH0;
  }

  untitled_M->Timing.t[0] = untitled_M->Timing.clockTick0 *
    untitled_M->Timing.stepSize0 + untitled_M->Timing.clockTickH0 *
    untitled_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [5.0E-7s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 5.0E-7, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    untitled_M->Timing.clockTick1++;
    if (!untitled_M->Timing.clockTick1) {
      untitled_M->Timing.clockTickH1++;
    }
  }
}

/* Model initialize function */
void untitled_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)untitled_M, 0,
                sizeof(RT_MODEL_untitled_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&untitled_M->solverInfo,
                          &untitled_M->Timing.simTimeStep);
    rtsiSetTPtr(&untitled_M->solverInfo, &rtmGetTPtr(untitled_M));
    rtsiSetStepSizePtr(&untitled_M->solverInfo, &untitled_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&untitled_M->solverInfo, (&rtmGetErrorStatus
      (untitled_M)));
    rtsiSetRTModelPtr(&untitled_M->solverInfo, untitled_M);
  }

  rtsiSetSimTimeStep(&untitled_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&untitled_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(untitled_M, &untitled_M->Timing.tArray[0]);
  rtmSetTFinal(untitled_M, 10.0);
  untitled_M->Timing.stepSize0 = 5.0E-7;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    untitled_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(untitled_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(untitled_M->rtwLogInfo, (NULL));
    rtliSetLogT(untitled_M->rtwLogInfo, "tout");
    rtliSetLogX(untitled_M->rtwLogInfo, "");
    rtliSetLogXFinal(untitled_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(untitled_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(untitled_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(untitled_M->rtwLogInfo, 0);
    rtliSetLogDecimation(untitled_M->rtwLogInfo, 1);
    rtliSetLogY(untitled_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(untitled_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(untitled_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &untitled_B), 0,
                sizeof(B_untitled_T));

  /* states (dwork) */
  (void) memset((void *)&untitled_DW, 0,
                sizeof(DW_untitled_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(untitled_M->rtwLogInfo, 0.0, rtmGetTFinal
    (untitled_M), untitled_M->Timing.stepSize0, (&rtmGetErrorStatus(untitled_M)));

  /* SetupRuntimeResources for Scope: '<Root>/Scope' */
  {
    RTWLogSignalInfo rt_ScopeSignalInfo;
    static int_T rt_ScopeSignalWidths[] = { 1, 1 };

    static int_T rt_ScopeSignalNumDimensions[] = { 1, 1 };

    static int_T rt_ScopeSignalDimensions[] = { 1, 1 };

    static void *rt_ScopeCurrSigDims[] = { (NULL), (NULL) };

    static int_T rt_ScopeCurrSigDimsSize[] = { 4, 4 };

    static const char_T *rt_ScopeSignalLabels[] = { "",
      "" };

    static char_T rt_ScopeSignalTitles[] = "";
    static int_T rt_ScopeSignalTitleLengths[] = { 0, 0 };

    static boolean_T rt_ScopeSignalIsVarDims[] = { 0, 0 };

    static int_T rt_ScopeSignalPlotStyles[] = { 1, 1 };

    BuiltInDTypeId dTypes[2] = { SS_DOUBLE, SS_DOUBLE };

    static char_T rt_ScopeBlockName[] = "untitled/Scope";
    static int_T rt_ScopeFrameData[] = { 0, 0 };

    static RTWPreprocessingFcnPtr rt_ScopeSignalLoggingPreprocessingFcnPtrs[] =
      {
      (NULL), (NULL)
    };

    rt_ScopeSignalInfo.numSignals = 2;
    rt_ScopeSignalInfo.numCols = rt_ScopeSignalWidths;
    rt_ScopeSignalInfo.numDims = rt_ScopeSignalNumDimensions;
    rt_ScopeSignalInfo.dims = rt_ScopeSignalDimensions;
    rt_ScopeSignalInfo.isVarDims = rt_ScopeSignalIsVarDims;
    rt_ScopeSignalInfo.currSigDims = rt_ScopeCurrSigDims;
    rt_ScopeSignalInfo.currSigDimsSize = rt_ScopeCurrSigDimsSize;
    rt_ScopeSignalInfo.dataTypes = dTypes;
    rt_ScopeSignalInfo.complexSignals = (NULL);
    rt_ScopeSignalInfo.frameData = rt_ScopeFrameData;
    rt_ScopeSignalInfo.preprocessingPtrs =
      rt_ScopeSignalLoggingPreprocessingFcnPtrs;
    rt_ScopeSignalInfo.labels.cptr = rt_ScopeSignalLabels;
    rt_ScopeSignalInfo.titles = rt_ScopeSignalTitles;
    rt_ScopeSignalInfo.titleLengths = rt_ScopeSignalTitleLengths;
    rt_ScopeSignalInfo.plotStyles = rt_ScopeSignalPlotStyles;
    rt_ScopeSignalInfo.blockNames.cptr = (NULL);
    rt_ScopeSignalInfo.stateNames.cptr = (NULL);
    rt_ScopeSignalInfo.crossMdlRef = (NULL);
    rt_ScopeSignalInfo.dataTypeConvert = (NULL);
    untitled_DW.Scope_PWORK.LoggedData[0] = rt_CreateStructLogVar(
      untitled_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(untitled_M),
      untitled_M->Timing.stepSize0,
      (&rtmGetErrorStatus(untitled_M)),
      "ScopeData1",
      1,
      0,
      1,
      5.0E-7,
      &rt_ScopeSignalInfo,
      rt_ScopeBlockName);
    if (untitled_DW.Scope_PWORK.LoggedData[0] == (NULL))
      return;
  }

  /* SetupRuntimeResources for Scope: '<Root>/Scope5' */
  {
    RTWLogSignalInfo rt_ScopeSignalInfo;
    static int_T rt_ScopeSignalWidths[] = { 1 };

    static int_T rt_ScopeSignalNumDimensions[] = { 1 };

    static int_T rt_ScopeSignalDimensions[] = { 1 };

    static void *rt_ScopeCurrSigDims[] = { (NULL) };

    static int_T rt_ScopeCurrSigDimsSize[] = { 4 };

    static const char_T *rt_ScopeSignalLabels[] = { "" };

    static char_T rt_ScopeSignalTitles[] = "";
    static int_T rt_ScopeSignalTitleLengths[] = { 0 };

    static boolean_T rt_ScopeSignalIsVarDims[] = { 0 };

    static int_T rt_ScopeSignalPlotStyles[] = { 1 };

    BuiltInDTypeId dTypes[1] = { SS_DOUBLE };

    static char_T rt_ScopeBlockName[] = "untitled/Scope5";
    static int_T rt_ScopeFrameData[] = { 0 };

    static RTWPreprocessingFcnPtr rt_ScopeSignalLoggingPreprocessingFcnPtrs[] =
      {
      (NULL)
    };

    rt_ScopeSignalInfo.numSignals = 1;
    rt_ScopeSignalInfo.numCols = rt_ScopeSignalWidths;
    rt_ScopeSignalInfo.numDims = rt_ScopeSignalNumDimensions;
    rt_ScopeSignalInfo.dims = rt_ScopeSignalDimensions;
    rt_ScopeSignalInfo.isVarDims = rt_ScopeSignalIsVarDims;
    rt_ScopeSignalInfo.currSigDims = rt_ScopeCurrSigDims;
    rt_ScopeSignalInfo.currSigDimsSize = rt_ScopeCurrSigDimsSize;
    rt_ScopeSignalInfo.dataTypes = dTypes;
    rt_ScopeSignalInfo.complexSignals = (NULL);
    rt_ScopeSignalInfo.frameData = rt_ScopeFrameData;
    rt_ScopeSignalInfo.preprocessingPtrs =
      rt_ScopeSignalLoggingPreprocessingFcnPtrs;
    rt_ScopeSignalInfo.labels.cptr = rt_ScopeSignalLabels;
    rt_ScopeSignalInfo.titles = rt_ScopeSignalTitles;
    rt_ScopeSignalInfo.titleLengths = rt_ScopeSignalTitleLengths;
    rt_ScopeSignalInfo.plotStyles = rt_ScopeSignalPlotStyles;
    rt_ScopeSignalInfo.blockNames.cptr = (NULL);
    rt_ScopeSignalInfo.stateNames.cptr = (NULL);
    rt_ScopeSignalInfo.crossMdlRef = (NULL);
    rt_ScopeSignalInfo.dataTypeConvert = (NULL);
    untitled_DW.Scope5_PWORK.LoggedData = rt_CreateStructLogVar(
      untitled_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(untitled_M),
      untitled_M->Timing.stepSize0,
      (&rtmGetErrorStatus(untitled_M)),
      "ScopeData3",
      1,
      0,
      1,
      5.0E-7,
      &rt_ScopeSignalInfo,
      rt_ScopeBlockName);
    if (untitled_DW.Scope5_PWORK.LoggedData == (NULL))
      return;
  }

  /* SetupRuntimeResources for Scope: '<Root>/Scope1' */
  {
    RTWLogSignalInfo rt_ScopeSignalInfo;
    static int_T rt_ScopeSignalWidths[] = { 1, 1 };

    static int_T rt_ScopeSignalNumDimensions[] = { 1, 1 };

    static int_T rt_ScopeSignalDimensions[] = { 1, 1 };

    static void *rt_ScopeCurrSigDims[] = { (NULL), (NULL) };

    static int_T rt_ScopeCurrSigDimsSize[] = { 4, 4 };

    static const char_T *rt_ScopeSignalLabels[] = { "",
      "" };

    static char_T rt_ScopeSignalTitles[] = "";
    static int_T rt_ScopeSignalTitleLengths[] = { 0, 0 };

    static boolean_T rt_ScopeSignalIsVarDims[] = { 0, 0 };

    static int_T rt_ScopeSignalPlotStyles[] = { 1, 1 };

    BuiltInDTypeId dTypes[2] = { SS_DOUBLE, SS_DOUBLE };

    static char_T rt_ScopeBlockName[] = "untitled/Scope1";
    static int_T rt_ScopeFrameData[] = { 0, 0 };

    static RTWPreprocessingFcnPtr rt_ScopeSignalLoggingPreprocessingFcnPtrs[] =
      {
      (NULL), (NULL)
    };

    rt_ScopeSignalInfo.numSignals = 2;
    rt_ScopeSignalInfo.numCols = rt_ScopeSignalWidths;
    rt_ScopeSignalInfo.numDims = rt_ScopeSignalNumDimensions;
    rt_ScopeSignalInfo.dims = rt_ScopeSignalDimensions;
    rt_ScopeSignalInfo.isVarDims = rt_ScopeSignalIsVarDims;
    rt_ScopeSignalInfo.currSigDims = rt_ScopeCurrSigDims;
    rt_ScopeSignalInfo.currSigDimsSize = rt_ScopeCurrSigDimsSize;
    rt_ScopeSignalInfo.dataTypes = dTypes;
    rt_ScopeSignalInfo.complexSignals = (NULL);
    rt_ScopeSignalInfo.frameData = rt_ScopeFrameData;
    rt_ScopeSignalInfo.preprocessingPtrs =
      rt_ScopeSignalLoggingPreprocessingFcnPtrs;
    rt_ScopeSignalInfo.labels.cptr = rt_ScopeSignalLabels;
    rt_ScopeSignalInfo.titles = rt_ScopeSignalTitles;
    rt_ScopeSignalInfo.titleLengths = rt_ScopeSignalTitleLengths;
    rt_ScopeSignalInfo.plotStyles = rt_ScopeSignalPlotStyles;
    rt_ScopeSignalInfo.blockNames.cptr = (NULL);
    rt_ScopeSignalInfo.stateNames.cptr = (NULL);
    rt_ScopeSignalInfo.crossMdlRef = (NULL);
    rt_ScopeSignalInfo.dataTypeConvert = (NULL);
    untitled_DW.Scope1_PWORK.LoggedData[0] = rt_CreateStructLogVar(
      untitled_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(untitled_M),
      untitled_M->Timing.stepSize0,
      (&rtmGetErrorStatus(untitled_M)),
      "ScopeData2",
      1,
      0,
      1,
      5.0E-7,
      &rt_ScopeSignalInfo,
      rt_ScopeBlockName);
    if (untitled_DW.Scope1_PWORK.LoggedData[0] == (NULL))
      return;
  }

  /* Start for S-Function (sfun_spssw_discc): '<S59>/State-Space' incorporates:
   *  Constant: '<S22>/DC'
   *  Constant: '<S23>/eee'
   *  Constant: '<S61>/SwitchCurrents'
   */

  /* S-Function block: <S59>/State-Space */
  {
    untitled_DW.StateSpace_PWORK.AS = (real_T*)calloc(4 * 4, sizeof(real_T));
    untitled_DW.StateSpace_PWORK.BS = (real_T*)calloc(4 * 15, sizeof(real_T));
    untitled_DW.StateSpace_PWORK.CS = (real_T*)calloc(17 * 4, sizeof(real_T));
    untitled_DW.StateSpace_PWORK.DS = (real_T*)calloc(17 * 15, sizeof(real_T));
    untitled_DW.StateSpace_PWORK.DX_COL = (real_T*)calloc(17, sizeof(real_T));
    untitled_DW.StateSpace_PWORK.TMP2 = (real_T*)calloc(15, sizeof(real_T));
    untitled_DW.StateSpace_PWORK.BD_COL = (real_T*)calloc(4, sizeof(real_T));
    untitled_DW.StateSpace_PWORK.TMP1 = (real_T*)calloc(4, sizeof(real_T));
    untitled_DW.StateSpace_PWORK.XTMP = (real_T*)calloc(4, sizeof(real_T));
    untitled_DW.StateSpace_PWORK.SWITCH_STATUS = (int_T*)calloc(13, sizeof(int_T));
    untitled_DW.StateSpace_PWORK.SW_CHG = (int_T*)calloc(13, sizeof(int_T));
    untitled_DW.StateSpace_PWORK.G_STATE = (int_T*)calloc(13, sizeof(int_T));
    untitled_DW.StateSpace_PWORK.Y_SWITCH = (real_T*)calloc(13, sizeof(real_T));
    untitled_DW.StateSpace_PWORK.SWITCH_TYPES = (int_T*)calloc(13, sizeof(int_T));
    untitled_DW.StateSpace_PWORK.IDX_OUT_SW = (int_T*)calloc(13, sizeof(int_T));
    untitled_DW.StateSpace_PWORK.SWITCH_STATUS_INIT = (int_T*)calloc(13, sizeof
      (int_T));
    untitled_DW.StateSpace_PWORK.USWLAST = (real_T*)calloc(13, sizeof(real_T));
  }

  /* InitializeConditions for S-Function (sfun_spssw_discc): '<S59>/State-Space' incorporates:
   *  Constant: '<S22>/DC'
   *  Constant: '<S23>/eee'
   *  Constant: '<S61>/SwitchCurrents'
   */
  {
    int32_T i, j;
    real_T *As = (real_T*)untitled_DW.StateSpace_PWORK.AS;
    real_T *Bs = (real_T*)untitled_DW.StateSpace_PWORK.BS;
    real_T *Cs = (real_T*)untitled_DW.StateSpace_PWORK.CS;
    real_T *Ds = (real_T*)untitled_DW.StateSpace_PWORK.DS;
    real_T *X0 = (real_T*)&untitled_DW.StateSpace_DSTATE[0];
    for (i = 0; i < 4; i++) {
      X0[i] = (untitled_P.StateSpace_X0_param[i]);
    }

    /* Copy and transpose A and B */
    for (i=0; i<4; i++) {
      for (j=0; j<4; j++)
        As[i*4 + j] = (untitled_P.StateSpace_AS_param[i + j*4]);
      for (j=0; j<15; j++)
        Bs[i*15 + j] = (untitled_P.StateSpace_BS_param[i + j*4]);
    }

    /* Copy and transpose C */
    for (i=0; i<17; i++) {
      for (j=0; j<4; j++)
        Cs[i*4 + j] = (untitled_P.StateSpace_CS_param[i + j*17]);
    }

    /* Copy and transpose D */
    for (i=0; i<17; i++) {
      for (j=0; j<15; j++)
        Ds[i*15 + j] = (untitled_P.StateSpace_DS_param[i + j*17]);
    }

    {
      /* Switches work vectors */
      int_T *switch_status = (int_T*) untitled_DW.StateSpace_PWORK.SWITCH_STATUS;
      int_T *gState = (int_T*)untitled_DW.StateSpace_PWORK.G_STATE;
      real_T *yswitch = (real_T*)untitled_DW.StateSpace_PWORK.Y_SWITCH;
      int_T *switchTypes = (int_T*)untitled_DW.StateSpace_PWORK.SWITCH_TYPES;
      int_T *idxOutSw = (int_T*)untitled_DW.StateSpace_PWORK.IDX_OUT_SW;
      int_T *switch_status_init = (int_T*)
        untitled_DW.StateSpace_PWORK.SWITCH_STATUS_INIT;

      /* Initialize work vectors */
      switch_status[0] = 0;
      switch_status_init[0] = 0;
      gState[0] = (int_T) 0.0;
      yswitch[0] = 1/0.001;
      switchTypes[0] = (int_T)3.0;
      idxOutSw[0] = ((int_T)0.0) - 1;
      switch_status[1] = 0;
      switch_status_init[1] = 0;
      gState[1] = (int_T) 0.0;
      yswitch[1] = 1/0.001;
      switchTypes[1] = (int_T)7.0;
      idxOutSw[1] = ((int_T)0.0) - 1;
      switch_status[2] = 0;
      switch_status_init[2] = 0;
      gState[2] = (int_T) 0.0;
      yswitch[2] = 1/0.001;
      switchTypes[2] = (int_T)7.0;
      idxOutSw[2] = ((int_T)0.0) - 1;
      switch_status[3] = 0;
      switch_status_init[3] = 0;
      gState[3] = (int_T) 0.0;
      yswitch[3] = 1/0.001;
      switchTypes[3] = (int_T)7.0;
      idxOutSw[3] = ((int_T)0.0) - 1;
      switch_status[4] = 0;
      switch_status_init[4] = 0;
      gState[4] = (int_T) 0.0;
      yswitch[4] = 1/0.001;
      switchTypes[4] = (int_T)7.0;
      idxOutSw[4] = ((int_T)0.0) - 1;
      switch_status[5] = 0;
      switch_status_init[5] = 0;
      gState[5] = (int_T) 0.0;
      yswitch[5] = 1/0.001;
      switchTypes[5] = (int_T)7.0;
      idxOutSw[5] = ((int_T)0.0) - 1;
      switch_status[6] = 0;
      switch_status_init[6] = 0;
      gState[6] = (int_T) 0.0;
      yswitch[6] = 1/0.001;
      switchTypes[6] = (int_T)7.0;
      idxOutSw[6] = ((int_T)0.0) - 1;
      switch_status[7] = 0;
      switch_status_init[7] = 0;
      gState[7] = (int_T) 0.0;
      yswitch[7] = 1/0.001;
      switchTypes[7] = (int_T)7.0;
      idxOutSw[7] = ((int_T)0.0) - 1;
      switch_status[8] = 0;
      switch_status_init[8] = 0;
      gState[8] = (int_T) 0.0;
      yswitch[8] = 1/0.001;
      switchTypes[8] = (int_T)7.0;
      idxOutSw[8] = ((int_T)0.0) - 1;
      switch_status[9] = 0;
      switch_status_init[9] = 0;
      gState[9] = (int_T) 0.0;
      yswitch[9] = 1/0.001;
      switchTypes[9] = (int_T)7.0;
      idxOutSw[9] = ((int_T)0.0) - 1;
      switch_status[10] = 0;
      switch_status_init[10] = 0;
      gState[10] = (int_T) 0.0;
      yswitch[10] = 1/0.001;
      switchTypes[10] = (int_T)7.0;
      idxOutSw[10] = ((int_T)0.0) - 1;
      switch_status[11] = 0;
      switch_status_init[11] = 0;
      gState[11] = (int_T) 0.0;
      yswitch[11] = 1/0.001;
      switchTypes[11] = (int_T)7.0;
      idxOutSw[11] = ((int_T)0.0) - 1;
      switch_status[12] = 0;
      switch_status_init[12] = 0;
      gState[12] = (int_T) 0.0;
      yswitch[12] = 1/0.001;
      switchTypes[12] = (int_T)7.0;
      idxOutSw[12] = ((int_T)0.0) - 1;
    }
  }
}

/* Model terminate function */
void untitled_terminate(void)
{
  /* Terminate for S-Function (sfun_spssw_discc): '<S59>/State-Space' incorporates:
   *  Constant: '<S22>/DC'
   *  Constant: '<S23>/eee'
   *  Constant: '<S61>/SwitchCurrents'
   */

  /* S-Function block: <S59>/State-Space */
  {
    /* Free memory */
    free(untitled_DW.StateSpace_PWORK.AS);
    free(untitled_DW.StateSpace_PWORK.BS);
    free(untitled_DW.StateSpace_PWORK.CS);
    free(untitled_DW.StateSpace_PWORK.DS);
    free(untitled_DW.StateSpace_PWORK.DX_COL);
    free(untitled_DW.StateSpace_PWORK.TMP2);
    free(untitled_DW.StateSpace_PWORK.BD_COL);
    free(untitled_DW.StateSpace_PWORK.TMP1);
    free(untitled_DW.StateSpace_PWORK.XTMP);

    /*
     * Circuit has switches*/
    free(untitled_DW.StateSpace_PWORK.G_STATE);
    free(untitled_DW.StateSpace_PWORK.SWITCH_STATUS);
    free(untitled_DW.StateSpace_PWORK.SW_CHG);
    free(untitled_DW.StateSpace_PWORK.SWITCH_STATUS_INIT);
  }
}
