#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_string(char *);

int main()
{
   char string[100];

   printf("Enter some text\n");
   gets(string);

   sort_string(string);
   printf("%s\n", string);

   return 0;
}

void sort_string(char *s)
{
   int c, d = 0, length;
   char *pointer, *result, ch;

   length = strlen(s);

   result = (char *)malloc(length + 1);

   pointer = s;

   for (ch = 'a'; ch <= 'z'; ch++)
   {
      for (c = 0; c < length; c++)
      {
         if (*pointer == ch)
         {
            *(result + d) = *pointer;
            d++;
         }
         pointer++;
      }
      pointer = s;
   }
   *(result + d) = '\0';

   strcpy(s, result);
   free(result);
}
