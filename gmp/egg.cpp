#include <gmp.h>
#include <gmpxx.h>
#include <stdio.h>
using namespace std;

int main() {
  int index = 0;
  mpz_t ans[10003], rec;
  mpf_t num1, num2, pi, sides, rec2;
  mpf_init2(num1, 40008);
  mpf_init2(num2, 40008);
  mpf_init2(pi, 40008);
  mpz_init(rec);
  mpf_init(sides);
  mpf_init(rec2);
  mpf_set_ui(sides, 3);
  mpf_sqrt_ui(num1, 3);
  mpf_sqrt_ui(num2, 1);
  while (1) {
    mpf_mul(pi, num1, sides);
    mpf_mul_ui(sides, sides, 2);
    mpf_mul(num1, num1, num1);
    mpf_neg(num1, num1);
    mpf_add_ui(num1, num1, 4);
    mpf_sqrt(num1, num1);
    mpf_neg(num1, num1);
    mpf_add_ui(num1, num1, 2);
    mpf_sqrt(num1, num1);
    if (mpf_cmp(pi, num2) == false)
      break;
    mpf_set(num2, pi);
  }
  while (index <= 10000) {
    mpz_set_f(ans[index], pi);
    mpf_mul_ui(pi, pi, 10);
    mpz_mul_ui(rec, ans[index], 10);
    mpf_set_z(rec2, rec);
    mpf_sub(pi, pi, rec2);
    index++;
  }
  int T, l, r;
  scanf("%d", &T);
  for (int i = 1; i <= T; i++) {
    scanf("%d %d", &l, &r);
    for (int j = l; j <= r; j++)
      gmp_printf("%Zd", ans[i]);
    printf("\n");
  }
}
