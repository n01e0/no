#include <stdio.h>
#include <string.h>
void help(void);
int main(int argc, char *argv[]){
    if(argc ==1){
        while(1){
            printf("n\n");
        }
    }else if(argc == 3){
        if(strcmp(argv[1],"-s") == 0){
            while(1){
                printf("%s\n",argv[2]);
            }
        }else if(strcmp(argv[1],"-h") == 0){
            help();
        }
    }else{
        help();
    }
    return 0;
}

void help(void){
    printf("usage no -h             :print this help\n");
    printf("      no -s [strings]   :print [strings] instead of 'no'\n");
}
