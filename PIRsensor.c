#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int current = 0;
int total = 0;
void pir_thread(int *pir){
        FILE *fptr = NULL;
        char char_value;
        int int_value;
        char fpath[] = "/sys/class/gpio/gpio60/value";
        printf("%d\n",*pir);
        if(*pir == 1)
                fpath[21] = '6';
        else if(*pir == 2)
                fpath[21] = '2';
        else{
                printf("error invalid pir thread number");
                exit(0);
        }
        printf("%s\n",fpath);
        while(1){
                fptr = fopen(fpath,"r");
                char_value = fgetc(fptr);
                //printf("char_value=%c\n",char_value);
                int_value =(int)char_value-48;
                if(int_value==1){
                        if(current == 1){
                                if(*pir == 1)
                                        total++;
                                if(*pir == 2)
                                        total--;
                        current = 0;
                        }
                        if(current == 0)
                                current=1;
                        printf("number of people in the library = %d\n",total);
                usleep(5000000);
                }
                fclose(fptr);
                usleep(100000);
        }
}
int main(){
        int pir_number =1;
        pir_thread(&pir_number);
        return 0;
}
