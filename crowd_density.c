#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <pthread.h>
int current = 0;
int in = 0;
int out = 0;

void *aws_func(void *args){
        int prev_current=0, prev_in=0, prev_out=0;
        if(prev_current!=current&&
                prev_in!=in&&
                prev_out!=out){
                char sys_cmd[50];
                sprintf(sys_cmd,"python dynamoput.py %d %d %d",current,in,out);
                system(sys_cmd);
                prev_current = current;
                prev_in = in;
                prev_out = out;
                usleep(30000000);
        }
}

void *pir_thread(void *arg){
        int* pir = (int *)arg;
        FILE *fptr = NULL;
        char char_value;
        int int_value;
        char fpath[] = "/sys/class/gpio/gpio47/value";
       // printf("%d\n",*pir);
        if(*pir == 1)
                fpath[21] = '7';
        else if(*pir == 2)
                fpath[21] = '6';
        else{
                printf("error invalid pir thread number");
                exit(0);
        }
        //printf("%s\n",fpath);
        while(1){
                fptr = fopen(fpath,"r");
                char_value = fgetc(fptr);
                //printf("char_value=%c\n",char_value);
                int_value =(int)char_value-48;
                if(int_value==1){
                         if(*pir == 1){
                            current++;
                             in++;
                            openservo1();
                        printf("in:%d\ncurrent:%d\n\n",in,current);
                        }
                         if(*pir == 2){
                                out++;
                                current--;
                                openservo2();
                        printf("out:%d\ncurrent:%d\n\n",out,current);
                        }
                usleep(5000000);
                }
                fclose(fptr);
                usleep(100000);
        }
}
int main(){
        int pir_number1 =1;
        pthread_t pir_thread1;         //this is our handle to the pthread
        pthread_create(&pir_thread1, NULL, &pir_thread, &pir_number1);

        int pir_number2 =2;
        pthread_t pir_thread2;         //this is our handle to the pthread
        pthread_create(&pir_thread2, NULL, &pir_thread, &pir_number2);

        pthread_t aws_thread;         //this is our handle to the pthread
        pthread_create(&aws_func, NULL, &pir_thread, NULL);

        return 0;
}


void openservo1(){
         system("./openservo1.py 0");
        usleep(5000000);
        system("./openservo1.py 1");

}
void openservo2(){
         system("./openservo2.py 0");
        usleep(5000000);
        system("./openservo2.py 1");

