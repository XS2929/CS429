#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char*argv[] ){
int i;
int countStack=0;
printf("  .globl compute\n");
printf("compute:\n");
for(i=1;argv[i];i++){

if(isdigit(*argv[i])){
printf("  movq $%s,%%rax\n",argv[i]);
printf("  pushq %%rax\n");
countStack++;
}else if(*argv[i]=='x'||*argv[i]=='y'||*argv[i]=='z'){ 
switch (*argv[i]){
  case 'x': printf("  pushq %%rdi\n"); break;
  case 'y': printf("  pushq %%rsi\n"); break;
  case 'z': printf("  pushq %%rdx\n"); break;
}
countStack++;
}else if(*argv[i]=='+'||*argv[i]=='-'||*argv[i]=='t'||*argv[i]=='n'){
switch (*argv[i]){
  case '+': if(countStack-2<0){
            fprintf(stderr,"Error: The + operator requires two arguments\n");
            return -1;
            }
            printf("  popq %%r10\n"); 
            countStack--;
            printf("  popq %%r11\n");
            countStack--;
            printf("  addq %%r10, %%r11\n");
            printf("  pushq %%r11\n"); 
            countStack++;
            break;
  case '-': if(countStack-2<0){
            fprintf(stderr,"Error: The - operator requires two arguments\n");
            return -1;
            }
            printf("  popq %%r10\n"); 
            countStack--;
            printf("  popq %%r11\n");
            countStack--;
            printf("  subq %%r10, %%r11\n");
            printf("  pushq %%r11\n"); 
            countStack++;
            break;
  case 't': if(countStack-2<0){
            fprintf(stderr,"Error: The t operator requires two arguments\n");
            return -1;
            }
            printf("  popq %%r10\n"); 
            countStack--;
            printf("  popq %%r11\n");
            countStack--;
            printf("  imulq %%r10, %%r11\n");
            printf("  pushq %%r11\n"); 
            countStack++;
            break;
  case 'n': if(countStack-1<0){
            fprintf(stderr,"Error: The n operator requires one argument\n");
            return -1;
            }
            printf("  popq %%r10\n"); 
            countStack--;
            printf("  negq %%r10\n");
            printf("  pushq %%r10\n"); 
            countStack++;
            break;
}
}
else{
fprintf(stderr,"Error: %s is invalid\n",argv[i]);
return -1;
}
}
if(countStack!=1){
fprintf(stderr,"Error: More than one augument left on stack\n");
return -1;}
printf("  popq %%rax\n");
printf("  retq\n");
return 0;
}

