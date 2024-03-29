#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
   int opt = 0;
   char *in_fname = NULL;
   char *out_fname = NULL;

   while ((opt = getopt(argc, argv, "hi:o:")) != -1)
   {
      switch (opt)
      {
      case 'h':
         printf("show usage message");
         break;
      case 'i':
         in_fname = optarg;
         printf("\nInput option value=%s", in_fname);
         break;
      case 'o':
         out_fname = optarg;
         printf("\nOutput option value=%s", out_fname);
         break;

      case '?':
         /* Case when user enters the command as
          * $ ./cmd_exe -i
          */
         if (optopt == 'i')
         {
            printf("\nMissing mandatory input option");
            /* Case when user enters the command as
             * # ./cmd_exe -o
             */
         }
         else if (optopt == 'o')
         {
            printf("\nMissing mandatory output option");
         }
         else
         {
            printf("\nInvalid option received");
         }
         break;
      }
   }

   printf("\n");
   return 0;
}
