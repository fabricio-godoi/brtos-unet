/***********************************************************************************
@file   math_utils.c
@brief  math functions
@authors: Gustavo Weber Denardin
          Carlos Henrique Barriquello

Copyright (c) <2009-2013> <Universidade Federal de Santa Maria>

  * Software License Agreement
  *
  * The Software is owned by the authors, and is protected under 
  * applicable copyright laws. All rights are reserved.
  *
  * The above copyright notice shall be included in
  * all copies or substantial portions of the Software.
  *  
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  * THE SOFTWARE.
  
**********************************************************************************/

#include "math_utils.h"


//static INT32U        A = 0;
volatile INT16U        Acc = 0;
volatile INT32U        Acc_temp = 0;

//--------------------------------------------
//   return absolute value of a number
//
//   Input parameter: unsigned 32-bits 
//   Output parameter: unsigned 32-bits
//--------------------------------------------
INT32U Absolute(INT32S x) {
  
  if (x<0) return -x;
  else return x;
}

//--------------------------------------------
//   return positive value of a number
//   and zero if negative
//
//   Input parameter: unsigned 32-bits 
//   Output parameter: unsigned 32-bits
//--------------------------------------------
INT32U Positive(INT32S x) {
  
  if (x<0) return 0;
  else return x;
}


//--------------------------------------------
//   Guess the initial root square seed
//
//   Input parameter: unsigned 32-bits 
//   Output parameter: unsigned 16-bits
//--------------------------------------------
/* Root Square Initial Seed */
INT32U ASM_FF1(INT32U A)
{
	uint32_t v = A;

  __asm__ volatile("ff1.l %0 \n\t" \
		  	  	   "move.l %0,%1 \n\t" \
		  	  	   : "=r" (A) \
				   : "r" (v)); // find the first one

  A = (32-A)>>1;               // first one index divided by 2
  if(A < 16)
	  A = ((INT32U)(1)<<A);       // multiplies by two
  else
	  A = ((INT32U)(1)<<A)-1;       // multiplies by two
  return(A);                   // Return parameter
}

      
//--------------------------------------------
//   Square root
//
//   Input parameter: unsigned 32-bits 
//   Output parameter: unsigned 16-bits
//--------------------------------------------
/* Square root */
#define MAX_INT 5                                       // maximum number of interactions for square root calculation
                                                        //
INT16U  SquareRoot(INT32U A)                            //
{                                                       //
  INT16U j;                                             // local variable 
  Acc = ASM_FF1(A);                            			// initial seed
  if (Acc == 0)  return 0;                              // skip 0
  for(j=0;j<MAX_INT;j++){                               // execute maximum of MAX_INT interactions
    Acc_temp = (A/Acc + Acc) >> 1;                         // Calculate interaction
    if((Absolute(Acc - Acc_temp) <= 0x0001)||(Acc_temp == 0)) // Test if precision is good enough
      break;                                            // break if a good precision was reached
    Acc = (INT16U)Acc_temp;                             // Save previous interaction
  }                                                     //
  //Number_of_interactions[i] = (unsigned short) (j+1); // For debugging purposes
  return((INT16U)Acc_temp);                             // Return parameter 
}

int square_root_test(void)
{
	uint16_t k = 1;
	static uint32_t sq = 1;
	static uint16_t root = 0;
	for(k=2;k<((1<<16)-2);k++)
	{
		sq = k*k;
		root=SquareRoot(sq);
		if(Absolute(root - k) > 1)
		{
			return k;
		}
	}
	return 0;
}
