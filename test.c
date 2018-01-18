#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  unsigned char c = (unsigned char)-1;
  unsigned short s = (unsigned short)-1;
  unsigned int u = (unsigned int)-1;
  unsigned long l = (unsigned long)-1;
//  unsigned double d = (unsigned double)-1;

  printf ( "size of unsigned char is %d\n",sizeof(c));
  printf ( "max unsigned char is %u\n\n",c);

  printf ( "size of unsigned short is %d\n",sizeof(s));
  printf ( "max unsigned short is %u\n\n",s);

  printf ( "size of unsigned int is %d\n",sizeof(u));
  printf ( "max unsigned int is %u\n\n",u);

  printf ( "size of unsigned long is %d\n",sizeof(l));
  printf ( "max unsigned long is %lu\n",l);

//  printf ( "size of unsigned double is %d\n",sizeof(d));
//  printf ( "max unsigned double is %lu\n",d);

  return 0;
}
