#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void gpioOutput(int currentValue)
{
        FILE *fptr = NULL;	                           //file pointer
        int gpioNo[] = {6,6,6,7,6,8,4,5,4,4};          //gpio pin number 66,67,68,45,44
        char fpath[] = "/sys/class/gpio/gpioXX/value"; //file path for gpio value
        int binaryNum[]={0,0,0,0,0,0};	               //empty array
        int index=0;
        while(currentValue>0)
        {	                                            //converting decimal integer to binary array
                        binaryNum[index] = currentValue%2;
                        currentValue = currentValue/2;
                        index++;
        }
        index = 0;
        for(int i=0;i<5;i++)
        {	                                            //updating the value with binary array
                fpath[20] = (char)(gpioNo[index]+'0');
                index++;
                fpath[21] = (char)(gpioNo[index]+'0');
                index++;
//              printf("%s ",fpath);
                fptr = fopen(fpath,"w");
                fprintf(fptr,"%d",binaryNum[i]);
//              printf("%d\n",binaryNum[i]);
                fclose(fptr);
        }
}

int main(int argc, char** argv)
{
        int i;
        i = atoi(argv[1]);	                         //input from command line
//        printf("%d\n",i);
        if(i<31)
        {
                                                     //check for maximum input
                gpioOutput(i);
        }
}
