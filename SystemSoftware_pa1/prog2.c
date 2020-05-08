#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_LINE 256


int main()
{
  FILE *input;

   input = fopen("data", "r");

   if(input == NULL)
  {
      perror("ERROR");
     exit(EXIT_FAILURE);
   }

   printf("%s\t", "Student number");
   printf("%s\n", "Avergae score");



   char line[MAX_LINE];
   char *student_number;
   int average;
   char * grade1;
   char * grade2;
   char *grade3;

   while (fgets(line, sizeof(line), input))
    {
    if(line[0] != '\n')
 	   {
      student_number = strtok(line, " ");
      grade1 = strtok(NULL, " ");
      grade2 = strtok(NULL, " ");
      grade3 = strtok(NULL, " ");
      average = (atoi(grade1) + atoi(grade2) + atoi(grade3))/3;

      printf("-%s\t    ", student_number);
      printf("%d\n", average);
     }
   }


   fclose(input);
   exit(EXIT_SUCCESS);
}


