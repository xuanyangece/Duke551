#include <stdio.h>
#include <stdlib.h>

struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct retire_info_tag retire_info_t;

double calAndPrt(int, double, retire_info_t);

void retirement(int startAge, double initial, retire_info_t working, retire_info_t retired) {
  double newBalance = calAndPrt(startAge, initial, working);
  startAge = startAge + working.months;
  calAndPrt(startAge, newBalance, retired);
  // startAge = startAge + retired.months;
  // printf("Age %3d month %2d you have $%.2lf\n", (startAge / 12), (startAge % 12), endBalance);
}

double calAndPrt(int age, double balance, retire_info_t parameter) {
  for (int i = 0; i < parameter.months; i++) {
    int years = (age + i) / 12;
    int months = (age + i) % 12;
    printf("Age %3d month %2d you have $%.2lf\n", years, months, balance);
    balance = balance + (balance * parameter.rate_of_return) + parameter.contribution;
  }
  return balance;
}

int main(void) {
  retire_info_t atWork;
  atWork.months = 489;
  atWork.contribution = 1000;
  atWork.rate_of_return = 0.045 / 12;

  retire_info_t atRetire;
  atRetire.months = 384;
  atRetire.contribution = -4000;
  atRetire.rate_of_return = 0.01 / 12;

  retirement(327, 21345, atWork, atRetire);

  return EXIT_SUCCESS;
}
