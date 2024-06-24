#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    int parentChild[2]; //parent-child pipe, parentChild[0] = read, parentChild[1] = write;
    int childParent[2];

    char message = '1';

    pipe(parentChild);
    pipe(childParent);

    if(fork() == 0){
        close(parentChild[0]);
        close(childParent[1]);

        read(parentChild[1], &message, sizeof(message));
        printf("%d: received ping\n", getpid());

        write(parentChild[1], &message, sizeof(message));
        exit(0);
    }
    else{
        close(parentChild[0]);
        close(childParent[1]);

        write(parentChild[1], &message, sizeof(message));

        wait(0);

        read(childParent[0], &message, sizeof(message));

        printf("%d: received pong\n", getpid());
        exit(0);
    }
}