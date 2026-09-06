#include <stdio.h>
#include <math.h>

#define delta_t 1          //Sampling time: Depends on ADC of the STM32 board
#define C       16400      //Capacity of the cell
#define R0      1.2        //Internal Resistance

float SOC_to_OCV(float SoC_k_pred);
float OCV_to_SOC(float Voc);
float dOCV_dSOC_slope(float SoC_k_pred);

float Kalman_Filter(float Vt_meas, float I_meas){
    
    //Step 1: Delcaring & Initializating variables
    static float SOC_k_est = 0.5;           //Use pointer and OCV_to_SOC function to initialize 
    static float SOC_k_pred;

//    int   A = 1;
//    float B = delta_t/C;
//    float D = -R0;
    float H; 
    
//    float u = I_meas;
    static float uk_minus1 = 0;
//    float y_meas = Vt_meas;
    static float y_pred;            //Yk_minus

    static float P_k_est = 10;      //Initialized P0 = 10(as of right now; can be changed) 
    static float P_k_pred;          //Pk_minus
    static float K;                 //kalman Gain
    float w, v, Q, R;
    
    //Step 2: Prediction 
    //SoC_minus(k) = SoC_(k-1) + delta(t)*I(k-1)/C + w
    //P_minus(k) =  A*P(k-1)*A_transpose + Q
    SOC_k_pred = SOC_k_est + (delta_t/C)*uk_minus1 + w;
    P_k_pred = P_k_est + Q;

    //Step 3: Output Equation
    //Vt_pred = H*SoC_minus(k) + (-R0)*I(k)
    H = dOCV_dSOC_slope(SOC_k_pred);
    y_pred = H*SOC_k_pred + (-R0)*I_meas + v;
    uk_minus1 = I_meas;

    //Step 4: Kalman Gain
    //k = P_minus(k)*H_transpose*(H*P_minus(k)*H_transpose + R)_inverse
    K = P_k_pred*H/(H*P_k_pred*H + R);
    
    //Step 5: SoC Estimation
    SOC_k_est =  SOC_k_pred + K*(Vt_meas - y_pred);

    //Step 6: Update error Covariance
    P_k_est = P_k_pred - K*H*P_k_pred;

    return SOC_k_est;
}

//Get the open circuit voltage Voc from SoC
float SOC_to_OCV(float SoC_k_pred){


}

//Get SoC from open circuit voltage Voc 
float OCV_to_SOC(float Voc){


}

//Get local dOCV/dSOC slope 
float dOCV_dSOC_slope(float SoC_k_pred){

    return SoC_k_pred*0.1 + 3.0; //Example slope function, replace with actual model
}
