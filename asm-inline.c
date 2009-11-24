/* 
 * Tiago Maluta
 * gcc -ggdb asm-inline.c -o asm-inline
*/

#include <stdio.h>

//void swap(int x, int y);
void copy(int *from, int *to) {

     asm ("movl %1, %%eax;"
          "movl %%eax, %0;"
          :"=&r"(*to)
          :"r"(*from));

}

void inc(int *value) {

    asm ( "incl %0"
         :"=a"(*value)
         :"0"(*value)
        );

}

int main(void)
{

 /* some test cases to functions */
 int x = 15, y = 0;

 printf("Begin: x=%d, y=%d\n",x,y);
 copy(&x,&y);
 printf("After copy([from]x,[to]y): x=%d, y=%d\n",x,y);
 inc(&x);
 printf("After inc(x): x=%d, y=%d\n",x,y);
 return 0;
}
