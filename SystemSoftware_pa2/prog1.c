#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
  char target, mode;
  struct stat buf;

  if(argc != 3) {
      fprintf(stderr, "error! usage : (%s) (access mode) (file name)\n", argv[0]);
      return -1;
  }

  target = *argv[1];
  mode = *(argv[1] + 2);

  int a = stat(argv[2], &buf);

  if(a == -1){
    fprintf(stderr, "error! (wrong file name)\n");
    return -1;
  }

  if(target == 'u'){
    if(mode == 'r'){
      if((buf.st_mode & S_IRUSR) != 0){
        buf.st_mode &= ~(S_IRUSR);
        chmod(argv[2], buf.st_mode);
      }
      else{
        buf.st_mode |= S_IRUSR;
        chmod(argv[2], buf.st_mode);
      }
    }
    else if (mode == 'w'){
      if((buf.st_mode & S_IWUSR) != 0) {
        buf.st_mode &= ~(S_IWUSR);
        chmod(argv[2], buf.st_mode);
      }
      else {
        buf.st_mode |= S_IWUSR;
        chmod(argv[2], buf.st_mode);
      }
    }
    else if (mode == 'x') {
      if((buf.st_mode & S_IXUSR) !=0) {
        buf.st_mode &= ~(S_IXUSR);
        chmod(argv[2], buf.st_mode);
      }
      else {
        buf.st_mode |= S_IXUSR;
        chmod(argv[2], buf.st_mode);
      }
    }
  }

  if(target == 'g'){
    if(mode == 'r'){
      if((buf.st_mode & S_IRGRP) != 0){
        buf.st_mode &= ~(S_IRGRP);
        chmod(argv[2], buf.st_mode);
      }
      else{
        buf.st_mode |= S_IRGRP;
        chmod(argv[2], buf.st_mode);
      }
    }
    else if (mode == 'w'){
      if((buf.st_mode & S_IWGRP) != 0) {
        buf.st_mode &= ~(S_IWGRP);
        chmod(argv[2], buf.st_mode);
      }
      else {
        buf.st_mode |= S_IWGRP;
        chmod(argv[2], buf.st_mode);
      }
    }
    else if (mode == 'x') {
      if((buf.st_mode & S_IXGRP) !=0) {
        buf.st_mode &= ~(S_IXGRP);
        chmod(argv[2], buf.st_mode);
      }
      else {
        buf.st_mode |= S_IXGRP;
        chmod(argv[2], buf.st_mode);
      }
    }
  }

  if(target == 'o'){
    if(mode == 'r'){
      if((buf.st_mode & S_IROTH) != 0){
        buf.st_mode &= ~(S_IROTH);
        chmod(argv[2], buf.st_mode);
      }
     else{
        buf.st_mode |= S_IROTH;
        chmod(argv[2], buf.st_mode);
      }
    }
    else if (mode == 'w'){
      if((buf.st_mode & S_IWOTH) != 0) {
        buf.st_mode &= ~(S_IWOTH);
        chmod(argv[2], buf.st_mode);
      }
      else {
        buf.st_mode |= S_IWOTH;
        chmod(argv[2], buf.st_mode);
      }
    }
    else if (mode == 'x') {
      if((buf.st_mode & S_IXOTH) !=0) {
        buf.st_mode &= ~(S_IXOTH);
        chmod(argv[2], buf.st_mode);
      }
      else {
        buf.st_mode |= S_IXOTH;
        chmod(argv[2], buf.st_mode);
      }
    }
  }
  return 0;
}
