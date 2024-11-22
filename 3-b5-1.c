/*2351127 李烨 信11*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main() 
{
    printf("请输入年，月，日\n");
    int a, b, c, ey, day, d = 0;
    int run = 0, bb = 0;
   
    scanf("%d %d %d", &a, &b, &c);

    if (a % 4 == 0) {
        if (a % 100 == 0) {
            if (a % 400 == 0)
                run = 1;
        }
        else {
            run = 1;
        }
    }

    ey = 28 + run;

    bb = ((b == 1 || b == 3 || b == 5 || b == 7 || b == 8 || b == 10 || b == 12) && (c <= 31 && c >= 1)) || ((b == 4 || b == 6 || b == 9 || b == 11) && (c <= 30 && c >= 1)) ||((b == 2) && (c <= ey && c >= 1));

    if (b >= 1 && b <= 12) {
        if (bb==1) {
            if (b <= 7) {
                if (b % 2 == 0) {
                    if (b == 2)
                        d = 31;
                    else
                        d = b / 2 * 31 + ((b - 2) / 2 - 1) * 30 + ey;
                }
                else {
                    if (b == 1)
                        d = 0;
                    else
                        d = (b - 1) / 2 * 31 + ((b - 1) / 2 - 1) * 30 + ey;
                }
            }
            else {
                if (b % 2 == 0)
                    d = (b - 8) / 2 * (31 + 30) + 184 + ey;
                else
                    d = (b + 1 - 8) / 2 * 31 + (b - 1 - 8) / 2 * 30 + 184 + ey;
            }
            day = d + c;
            printf("%d-%d-%d是%d年的第%d天\n", a, b, c, a, day);
        }
        else {
            printf("输入错误-日与月的关系非法\n");
        }
    }
    else {
        printf("输入错误-月份不正确\n");
    }

    return 0;
}