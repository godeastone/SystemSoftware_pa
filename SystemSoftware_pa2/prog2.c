#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>

#define MAX_USRNAME 32
#define MAX_LINE 256

int main()
{
  char *username = malloc(sizeof(char) * MAX_USRNAME);

  struct group *grp;
  struct passwd *pw;
  int m, gid;

  printf("Input user name : ");
  scanf("%s",username);

  if((pw = getpwnam(username)) == NULL) {
    fprintf(stderr, "error! No user matches the input information\n");
    return -1;
  }

  gid = pw->pw_gid;
  grp = getgrgid(gid);

  printf("User : %s\n", username);
  printf("Primary Group : %s\n", grp->gr_name);
  printf("Secondary Group : ");

  while((grp = getgrent()) != NULL){
    m=0;
    while (grp->gr_mem[m] != NULL){
      if(!strcmp(grp->gr_mem[m], username)){
        printf("%s ",grp->gr_name);
        break;
      }
      m++;
    }
  }
  printf("\n");
  return 0;
}
