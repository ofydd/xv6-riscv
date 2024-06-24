#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    if(argc == 0){
        printf("Specify number of ticks! Process will be terminated");
    }
    else{
        sleep(atoi(argv[1]));
    }
    exit(0);
}