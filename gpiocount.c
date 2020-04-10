void gpioOutput(int currentValue){
        FILE *fptr = NULL;
        int gpioNo[] = {6,6,6,7,6,9,6,8,4,5,4,4};
        char fpath[] = "/sys/class/gpio/gpioXX/value";
        int binaryNum[]={0,0,0,0,0,0};
        int index=0;
        while(currentValue>0){
                        binaryNum[index] = currentValue%2;
                        currentValue = currentValue/2;
                        index++;
        }
        index = 0;
        for(int i=0;i<6;i++){
                fpath[20] = (char)(gpioNo[index]+'0');
                index++;
                fpath[21] = (char)(gpioNo[index]+'0');
                index++;
                printf("%s ",fpath);
                fptr = fopen(fpath,"w");
                fprintf(fptr,"%d",binaryNum[i]);
                printf("%d\n",binaryNum[i]);
                fclose(fptr);
        }
}

int main(int argc, char** argv){
        int i;
        i = atoi(argv[1]);
        printf("%d\n",i);
        gpioOutput(i);
}
