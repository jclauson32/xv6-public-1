#include "types.h"
#include "user.h"

int main(int argc, char* argv[]){
int pid = getpid();
printf(1,"hello %s\n", argv[1]);
int calls = getnumsyscallsgood(pid);
printf(1,"%d\n", calls);
exit();
}
