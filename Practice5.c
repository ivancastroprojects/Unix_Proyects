#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   int i;
   pid_t p;
   int children[5];
   for (i=0; i<5; i++) { 
      p=fork();
      if (p==-1) perror("Error en la llamada a fork()");
      else if (p==0) {       
         switch(i) {
            case 0:
               execl("/usr/bin/xeyes", "xeyes", (char *)0);
               break;
            case 1:
               execl("/usr/bin/xload", "xload", (char *)0);
               break;
            case 2:
               execl("/usr/bin/xlogo", "xlogo", (char *)0);
               break;
            case 3:
               execl("/usr/bin/xcalc", "xcalc", (char *)0);
               break;
            case 4:
               execl("/usr/bin/xclock", "xclock", "-update", "1", (char *)0);
               break;
         }
      } else children[i]=p;
   }

   int status;

   p=wait(&status);
   while (p!=-1) {
      pid_t newp;
      newp=fork();
      if (newp==-1) perror("Error en la llamada a fork()");
      else if (newp==0) {       
         if (p==children[0]) execl("/usr/bin/xeyes", "xeyes", (char *)0);
         if (p==children[1]) execl("/usr/bin/xload", "xload", (char *)0);
         if (p==children[2]) execl("/usr/bin/xlogo", "xlogo", (char *)0);
         if (p==children[3]) execl("/usr/bin/xcalc", "xcalc", (char *)0);
         if (p==children[4]) execl("/usr/bin/xclock", "xclock", "-update", "1", (char *)0);
      } else {
         if (p==children[0]) children[0]=newp;
         if (p==children[1]) children[1]=newp;
         if (p==children[2]) children[2]=newp;
         if (p==children[3]) children[3]=newp;
         if (p==children[4]) children[4]=newp;
      }
      p=wait(&status);
   }

   return 0;
}
