/* 
 * Tiago Maluta
 * gcc -ggdb asm-inline.c -o asm-inline
*/

#include <stdio.h>
#include <stdlib.h> // malloc()

void _strncpy(char *src, char *dst, int *count) {

    asm("cld;"
        "rep movsb;"
        :
        : "S"(src), "D"(dst), "c"(*count));

}


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

 int x = 15, y = 88;

 int count=5;
 char s[]="tiago";
 char *s1;

 s1 = malloc(sizeof(char)*5);

 printf("-------- Copy and Increment an variable --------\n");
 /* Test #1: copying an Increment an variable (int)  */
 printf("Begin: x=%d, y=%d\n",x,y);
 copy(&x,&y);
 printf("After copy([from]x,[to]y): x=%d, y=%d\n",x,y);
 inc(&x);
 printf("After inc(x): x=%d, y=%d\n",x,y);

 printf("-------- String copy (fake strncpy)  --------\n");
 /* Test #2: string copy */
 printf("s=\"%s\" s1=\"%s\"\n",s,s1);
 _strncpy(s,s1,&count);
 printf("s=\"%s\" s1=\"%s\"\n",s,s1);



 return 0;
}
