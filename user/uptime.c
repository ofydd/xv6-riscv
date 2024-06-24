#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    printf("Uptime: %d ticks\n", uptime());
    exit(0);
}