/* comput Golden ratio ~= 1.618*/

#include <gmp.h>
#include <gmpxx.h> // for c++
#include <stdio.h>

int main(){
	mpf_t a, b;

	mpf_init2(a,1000);  // set precision 1000 bits
	mpf_init2(b,1000);  // 1 digit ~= 4bit

	mpf_sqrt_ui(b,5);   // b := sqrt(5)
	mpf_add_ui(a,b,1);  // a = b+1
	mpf_div_ui(a,a,2);  // a := a/2

	gmp_printf("%.100Ff", a);
}
