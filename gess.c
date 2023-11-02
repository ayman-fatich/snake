#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


int main(){
    printf("Welcome to your first game in C language!\n");
    srand(time(0));
    int correctAnswer=rand()%100+1;
    /*sprintf(correctAnswer, "%d", rand()%100+1);*/
    char a[]="000";
    int noa=0;
    while (correctAnswer!=atoi(a))
    {

        fgets(a, sizeof(a), stdin);
        a[strcspn(a, "\n")] = '\0';
        fflush(stdin);

        if (correctAnswer==atoi(a))
        {
            printf("you win!!, you did it in %d attempts\n", noa);
        }
        else if (correctAnswer>atoi(a))
        {
            printf("naah wrong!!, it's bigger\n");
        }
        else if (correctAnswer<atoi(a))
        {
            printf("naah wrong!!, it's smaller\n");
        }
        noa++;
    }
    
    return 0;
}