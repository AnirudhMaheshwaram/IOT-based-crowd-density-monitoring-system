#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int current = 0;
int total = 0;
void *pir_func(void *arg)
{
        int* pir = (int *)arg;                                     
        FILE *fptr = NULL;
        char char_value;
        int int_value;
        char fpath[] = "/sys/class/gpio/gpio47/value";                 // path to gpio
//        printf("%d\n",*pir);
        if(*pir == 1)                                                  // if statement to work with pir 1 or pir 2
                fpath[21] = '6';	//pir 1 at gpio46
        else if(*pir == 2)
                fpath[21] = '7';	//pir 2 at gpio47
        else{
                printf("error invalid pir thread number");
//                exit(0);
        }
        printf("%s\n",fpath);
        while(1){

                fptr = fopen(fpath,"r");
                char_value = fgetc(fptr);                             // getting the value
                //printf("char_value=%c\n",char_value);
                int_value =(int)char_value-48;
                if(int_value==1)                                      //value for gpio input
                {
                                                                     
                         if(*pir == 1)                                // if pir 1 is active
                         {
                                if(current<10)
                                {
                                    current++;
                                     in++;
                                    openservo1();                     // open the servo motor at entry
                                        printf("in:%d\ncurrent:%d\n\n",in,current);
                                }
                        }
                         if(*pir == 2)                                // if pir 2 is active
                         {
                                if(current>0)
                                {
                                        out++;
                                        current--;
                                        openservo2();                // open the servo motor at exit
                                        printf("out:%d\ncurrent:%d\n\n",out,current);
                                }
                                     }
                     
                //usleep(5000000);
                }
                fclose(fptr);
                usleep(100000);
        }
}
