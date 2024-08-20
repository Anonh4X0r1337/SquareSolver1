#include "TXLib.h"

int main() {
  double a, b, c, eps = 0.000001;
  scanf("%lf %lf %lf", &a, &b, &c);

  if (fabs(a - 0) < eps) {
    printf("%lf", -c / b);
  } else if ((fabs(b - 0) < eps) && signbit(a) != signbit(c)) {
    printf("%lf", sqrt(-c / a));
  } else if (fabs(c - 0) < eps) {
    printf("%d, %lf", 0, -b / a);
  } else {
    double d = b * b - 4 * a * c;
    if (fabs(d - 0) < eps)
      printf("%lf", -b / (2 * a));
    else if (d < 0)
      printf("Нет корней");
    else
      printf("%lf, %lf", (-b - sqrt(d)) / (2 * a), (-b + sqrt(d)) / (2 * a));
  }

  return 0;
}
