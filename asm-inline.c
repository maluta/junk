/* 
 * Tiago Maluta
 * gcc -ggdb asm-inline.c -o asm-inline
*/

#include <stdio.h>

int main(void)
{
int x = 15, y;

printf("x=%d, y=%d\n",x,y);

/* y == x */

asm ("movl %1, %%eax;"  
     "movl %%eax, %0;"
     :"=&r"(y)
     :"r"(x)
     :"%eax");

printf("x=%d, y=%d\n",x,y);
     
return 0;   
}
