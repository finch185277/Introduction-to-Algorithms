#include <gmp.h>
#include <iostream>
int main() {
  int idx = 0;
  mpz_t ans[11000];
  mpf_t n1, n2, pi, sds, tmp;
  mpf_init2(n1, 69000);
  mpf_init2(n2, 69000);
  mpf_init2(pi, 69000);
  mpf_init(sds);
  mpf_init(tmp);
  mpf_set_ui(n1, 1);
  mpf_set_ui(n2, 0);
  mpf_set_ui(sds, 3);
  while (1) {
    mpf_mul(pi, n1, sds);
    mpf_mul_ui(sds, sds, 2);
    mpf_mul(n1, n1, n1);
    mpf_neg(n1, n1);
    mpf_add_ui(n1, n1, 4);
    mpf_sqrt(n1, n1);
    mpf_neg(n1, n1);
    mpf_add_ui(n1, n1, 2);
    mpf_sqrt(n1, n1);
    if (mpf_cmp(pi, n2) == 0)
      break;
    mpf_set(n2, pi);
  }
  while (idx <= 10000) {
    mpz_set_f(ans[idx], pi);
    mpf_set_z(tmp, ans[idx]);
    mpf_sub(pi, pi, tmp);
    mpf_mul_ui(pi, pi, 10);
    idx++;
  }
  int C, l, r;
  scanf("%d", &C);
  for (int i = 1; i <= C; i++) {
    scanf("%d %d", &l, &r);
    for (int j = l; j <= r; j++)
      gmp_printf("%Zd", ans[j]);
    printf("\n");
  }
}
