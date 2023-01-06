#include <stdlib.h>
#include <stdio.h>
/*
    dynamic memory allocate test
    input: memory block to allocate in KB
*/
int main(int argc, char **argv)
{
    int *nPtr;
    int block = 1024 * 128;
    double isize = 0;
    long i;

    if (argc >= 2)
        block = 1024 * atoi(argv[1]);
    else
    {
        printf("input block size:");
        scanf("%d", &block);
        block = block * 1024;
    }
    while (1)
    {
        nPtr = malloc(sizeof(int) * block);

        if (nPtr == NULL)
        {
            printf("建立記憶體空間失敗\n");
            break;
        }
        else
        {
            isize += sizeof(int) * block;
            for (i = 0; i < block; i++)
                *(nPtr + i) = i;
            printf("建立記憶體空間成功: %.3f MB \n", isize / 1024.0 / 1024.0);
            // system("free -h");
        }
    } // emd while
    block = getchar();
    return 0;
}
