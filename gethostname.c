#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

/* paddr: print the IP address in a standard decimal dotted format */
void paddr(unsigned char *a)
{
        printf("%d.%d.%d.%d\n", a[0], a[1], a[2], a[3]);
}

main(int argc, char **argv)
{
        struct hostent *hp;
        char *host = "google.com";
        if (argc >= 2)
                host = argv[1];

        int i;

        printf("getting host name of "
               "%s"
               "\n",
               host);
        hp = gethostbyname(host);
        if (!hp)
        {
                fprintf(stderr, "could not obtain address of %s\n", host);
                return 0;
        }
        for (i = 0; hp->h_addr_list[i] != 0; i++)
                paddr((unsigned char *)hp->h_addr_list[i]);
        exit(0);
}
