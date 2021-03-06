#include "../include/mitchell.h"

void Mitchell::initConst (double CONSTANTS[], double RATES[], double STATES[])
{
    CONSTANTS[0] = 0;
    CONSTANTS[1] = 50000;
    CONSTANTS[2] = 0.2;
    CONSTANTS[3] = 500;
    CONSTANTS[4] = 1;
    CONSTANTS[5] = 0.3;
    CONSTANTS[6] = 120.0;
    CONSTANTS[7] = 150.0;
    CONSTANTS[8] = 0.13;
    CONSTANTS[9] = 6.0;
    STATES[0] = 0.00000820413566106744;
    STATES[1] = 0.8789655121804799;
}

void Mitchell::compVariables (double t, double CONSTANTS[], double RATES[], double STATES[], double ALGEBRAIC[])
{
    ALGEBRAIC[0] = (t>=CONSTANTS[0]&&t<=CONSTANTS[1]&&(t - CONSTANTS[0]) -  floor((t - CONSTANTS[0])/CONSTANTS[3])*CONSTANTS[3]<=CONSTANTS[4] ? CONSTANTS[2] : 0.00000);
    ALGEBRAIC[1] = ( STATES[1]*( pow(STATES[0], 2.00000)*(1.00000 - STATES[0])))/CONSTANTS[5];
    ALGEBRAIC[2] = - (STATES[0]/CONSTANTS[9]);
}

void Mitchell::compRates (double t, double CONSTANTS[], double RATES[], double STATES[], double ALGEBRAIC[])
{
    RATES[0] = ALGEBRAIC[1]+ALGEBRAIC[2]+ALGEBRAIC[0];
    RATES[1] = (STATES[0]<CONSTANTS[8] ? (1.00000 - STATES[1])/CONSTANTS[6] : - STATES[1]/CONSTANTS[7]);
}

void Mitchell::compRates_FE (double t, double CONSTANTS[], double RATES[], double STATES[], double ALGEBRAIC[])
{

}

void Mitchell::RL (double DT, double CONSTANTS[], double RATES[], double STATES[], double ALGEBRAIC[])
{

}

/*
   There are a total of 3 entries in the algebraic variable array.
   There are a total of 2 entries in each of the rate and state variable arrays.
   There are a total of 10 entries in the constant variable array.
 */
 
/*
 * VOI is time in component environment (ms).
 * ALGEBRAIC[0] is J_stim in component J_stim (per_ms).
 * CONSTANTS[0] is IstimStart in component J_stim (ms).
 * CONSTANTS[1] is IstimEnd in component J_stim (ms).
 * CONSTANTS[2] is IstimAmplitude in component J_stim (per_ms).
 * CONSTANTS[3] is IstimPeriod in component J_stim (ms).
 * CONSTANTS[4] is IstimPulseDuration in component J_stim (ms).
 * STATES[0] is Vm in component membrane (dimensionless).
 * ALGEBRAIC[1] is J_in in component J_in (per_ms).
 * ALGEBRAIC[2] is J_out in component J_out (per_ms).
 * CONSTANTS[5] is tau_in in component J_in (ms).
 * STATES[1] is h in component J_in_h_gate (dimensionless).
 * CONSTANTS[6] is tau_open in component J_in_h_gate (ms).
 * CONSTANTS[7] is tau_close in component J_in_h_gate (ms).
 * CONSTANTS[8] is V_gate in component J_in_h_gate (dimensionless).
 * CONSTANTS[9] is tau_out in component J_out (ms).
 * RATES[0] is d/dt Vm in component membrane (dimensionless).
 * RATES[1] is d/dt h in component J_in_h_gate (dimensionless).
 */

