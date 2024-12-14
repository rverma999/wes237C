#include "cordiccart2pol.h"

data_t Kvalues[NO_ITER] = {1,	0.500000000000000,	0.250000000000000,	0.125000000000000,	0.0625000000000000,	0.0312500000000000,	0.0156250000000000,	0.00781250000000000,	0.00390625000000000,	0.00195312500000000,	0.000976562500000000,	0.000488281250000000,	0.000244140625000000,	0.000122070312500000,	6.10351562500000e-05,	3.05175781250000e-05};

data_t angles[NO_ITER] = {0.785398163397448,	0.463647609000806,	0.244978663126864,	0.124354994546761,	0.0624188099959574,	0.0312398334302683,	0.0156237286204768,	0.00781234106010111,	0.00390623013196697,	0.00195312251647882,	0.000976562189559320,	0.000488281211194898,	0.000244140620149362,	0.000122070311893670,	6.10351561742088e-05,	3.05175781155261e-05};


void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta)
//void cordiccart2pol(ap_fixed<16,2> x, ap_fixed<16,2> y, ap_fixed<16,2> * r,  ap_fixed<20,3> * theta)
{
	// Write your code here
    #pragma HLS INTERFACE ap_ctrl_none port=return
    #pragma HLS INTERFACE ap_none port=x
    #pragma HLS INTERFACE ap_none port=y
    #pragma HLS INTERFACE ap_none port=r
    #pragma HLS INTERFACE ap_none port=theta
    
    // Pipeline the function
    #pragma HLS PIPELINE II=1


 //ap_int<3>  direction;
 int  direction;
 //const data_t K = 0.607252935;
 const data_t K =0.6072788442269037 ;
 const data_t PI = 3.14159265358979323846;
 //data_t calc_K=1;
 // Store current values
 //data_t angle=0;
 //data_t x_temp;// = x;
 //data_t y_temp;//  = y;
 //data_t org_x = x;
 //data_t org_y = y;
 //data_t quadrant_angle = 0.0;
 ap_fixed<16,2> x_temp;// = x;
 ap_fixed<16,2> y_temp;//  = y;
 ap_fixed<16,2> org_x = x;
 ap_fixed<16,2> org_y = y;
 ap_fixed<16,2> quadrant_angle = 0.0;
 ap_fixed<20,3> angle=0;


        


        // Determine quadrant and pre-rotate if needed
        if (x < 0) {
            if (y < 0) {
                // Quadrant III
            	quadrant_angle = -PI;
                x = -x;
                y = -y;
            } else  {
                // Quadrant II
            	quadrant_angle = PI;
                x = -x;

            }
        } else if (y < 0 && x>= 0) {
            // Quadrant IV
        	quadrant_angle = 0;
            x=x;
            y=-y;
        }


      //for(int i =0;i<=NO_ITER;i++){
      //for(ap_int<5> i =0;i<=17;i++){
      for(ap_uint<5> i = 0; i < NO_ITER; i++) {
        #pragma HLS UNROLL factor=4
        #pragma HLS LOOP_TRIPCOUNT min=16 max=16

        direction = (y >= 0) ? -1 : 1;
        x_temp = x;
        y_temp = y;

        // Perform rotation using K-values 
        x = x_temp - direction*(y_temp*Kvalues[i]);
        y = y_temp + direction*(x_temp*Kvalues[i]);
        
        // Accumulate angle (radians)
        angle -= direction * angles[i];
        // Calculate final angle based on quadrant
        if (org_x < 0) {
            if (org_y < 0) {
                *theta = -PI +  angle;  // Quadrant III
            } else {
                *theta = PI - angle;  // Quadrant II
            }
        } else if (org_y < 0) {
            *theta =-angle;      // Quadrant IV
        } else {
            *theta = angle;                       // Quadrant I
        }
        //calc_K*= Kvalues[i];
        //printf("Step %2d: x=%.6f, y=%.6f, angle=%.6f calc_k=%.8f \n",i+1, x, y, angle,calc_K);
    }
    
    // Apply CORDIC scaling factor
    //doesnt work with ap_fixed *r = sqrt(org_x*org_x + org_y*org_y);
        // Convert to double before sqrt
    double temp = (double)(org_x*org_x + org_y*org_y);
    *r = (data_t)sqrt(temp);

    //theta = atan(y,x);
    //*r = x / K;    // x contains magnitude
    //*theta = angle; // angle in radians
    //printf("Step %2d: x=%.6f, y=%.6f, angle=%.6f\n",i+1, x, y, angle);
   


	
}
