#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINE 256

int main()
{
  int fd;
  int index = 0;
  char line[1];
  char line2[MAX_LINE];

  char *student_number;
  int average;
  char * grade1;
  char * grade2;
  char *grade3;

  printf("%s\t", "Student number");
  printf("%s\n", "Avergae score");

  //initialize line2
  for(int i=0; i<MAX_LINE; i++)
  {
    line2[i] = '\0';
  }

  if ( fd = open("data", O_RDONLY) == -1)
  {     printf("cannot open \"data\" file.");
      return 1;
  }

  fd = open("data", O_RDONLY);


 while(read(fd, line, 1)!=0) //because function 'read' return 0 when it meets EOF
  {
    if(line2[0] =='\0' && line[0] == '\n')
    {
      index =0;
    }

    else if(line[0] == '\n')
    {
      student_number = strtok(line2, " ");
      grade1 = strtok(NULL, " ");
      grade2 = strtok(NULL, " ");
      grade3 = strtok(NULL, " ");
      average = (atoi(grade1) + atoi(grade2) + atoi(grade3))/3;

      printf("-%s\t    ", student_number);
      printf("%d\n", average);

      //initialize line2 and index
      for(int i=0; i<MAX_LINE; i++)
      {
        line2[i] = '\0';
      }
      index =0;
    }
    else
    {
      line2[index] = line[0]; //duplicate character one by one
      index++;
    }
  }
  return 0;
}
