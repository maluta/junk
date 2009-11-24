/* 
   Tiago Maluta
   gcc -Wall -ggdb asm-inline.c -o asm-inline

   The basic idea is that every asm() entry follow the skeleton:

     asm("assembly code"
        : output operand
	: input operand
	: clobbered register
	);
*/

#include <stdio.h>
#include <stdlib.h> // malloc()

void swap(int *x, int *y) {

    asm(""
        : "=a"(*y),"=b"(*x)
        : "a"(*x),"b"(*y)
       );

}

void vector_copy(int *v_src, int *v_dst, int *count) {

    asm("up: lodsl;"
	"    stosl;"
	"loop up;  "
	:
	: "S"(v_src), "D"(v_dst), "c"(*count)
	: "%eax"
	);

}

void _strncpy(char *src, char *dst, int *count) {

    asm("cld;"
        "rep movsb;"
        :
        : "S"(src), // 'S' -> %esi
	  "D"(dst), // 'D' -> %edi
	  "c"(*count)); // 'c' -> %ecx
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

 int i;
 int count=5;


 char s[]="tiago";
 char *s1;

 int *v1;
 int *v2;

 v1 = malloc(sizeof(int)*5);
 v2 = malloc(sizeof(int)*5);

 /* fill v1 with some value */
 for (i=0;i<5;i++)
     v1[i]=i+5;

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

 printf("-------- Vector copy  --------\n");
 for (i=0;i<5;i++) printf("v1[%d]=%d v2[%d]=%d\n",i,v1[i],i,v2[i]);
 vector_copy(v1,v2,&count);
 printf("** v1 = v2 **\n");
 for (i=0;i<5;i++) printf("v1[%d]=%d v2[%d]=%d\n",i,v1[i],i,v2[i]);

 printf("-------- Swap  --------\n");
 printf("Before swap: x=%d, y=%d\n",x,y);
 swap(&x,&y);
 printf("After swap:  x=%d, y=%d\n",x,y);
 return 0;
}
