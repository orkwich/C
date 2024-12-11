#include <stdio.h>

int main (void)
{
    printf("Input number of seconds: ");
    int seconds = 0;
    scanf("%d",&seconds);
    int hours = seconds/3600;
    seconds -= 3600*hours;
    int minuts = seconds/60;
    seconds -= 60*minuts;
    printf("%02d:%02d:%02d",hours,minuts,seconds);
    return 0;
}