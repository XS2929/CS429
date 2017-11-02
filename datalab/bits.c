/*
 * CS:APP Data Lab 
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
/* basic application of De Morgan's Law*/
  return ~(~x|~y); 
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
/*Calculate how many bits x needs to shift according to n value, then shift.
  Only keep the last byte(8 bits) as output */
  return (x>>(n<<3))&0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
/* To get logical shift, the 1s resulting from arithmetical shift should be
changed to 0s. And at the same time,the valued bits on the right should        
be saved*/
   int temp;
   temp=~((0x1<<31>>n)<<1);
   return (x>>n)&temp;

}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
/*use a mask 0x01010101 scan 4 bits per time
 bits from 0,8,16,24 to 1,9,17,25 and util 7,15,23,31
value record the amount of 1s by every bit position
at the end adding up the 4 bits total value which equals to 1 amount */ 
int mask=(((0x1<<8)|(0x1))|(0x1<<16))|(0x1<<24);
int result=0;
result+=x&mask;
result+=(x>>1)&mask;
result+=(x>>2)&mask;
result+=(x>>3)&mask;
result+=(x>>4)&mask;
result+=(x>>5)&mask;
result+=(x>>6)&mask;
result+=(x>>7)&mask;
result+=result>>16;
result+=result>>8;
return result&0xFF;
}
   
   
    
     
/*
 * bang - Compute !x without using )!
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
/*when x is 0, the sign bit of ~x+1 is 0, so signs are same
  when x is not 0, the signs of x and ~x=1 are different 
  so the difference in x sign and ~x+1 sign can be used for judging
*/
return (~((x>>31)|((~x+1)>>31)))&0x1;}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
/*
  Tmin+TMin=0
  but 0+0 is also 0
  so also need to check !!x=1;   
  */
  return (!(x+x))&(!!x);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
/*first left shift 32-n bits then right shift 32-n bits
  if the value is still the same as beginning, then it fit  */
  return !(x^((x<<(~n+1+32))>>(~n+1+32)));
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
/*get the sign of x and value of (2^n)-1
  if x is postive, bias=0, it can be shifted directly
  if x is negative, the bias should be added     
*/

int xSign,mask,bias;
xSign=x>>31;
mask=(~0)+(1<<n);
bias=xSign&mask;
return (x+bias)>>n;
 
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
/*
check the result sign
check x and y signs's difference

*/
 int result=x+(~y+1);
 int resultSign=result>>31;
 int signDifference=(x>>31)^(y>>31);
return !((signDifference)&(!((y>>31)^resultSign)));
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
/*int x is 0 when its most left bit is 0(sign)
  also, 0 is not positive. needs to be excluded*/
 return !(x>>31)&!!x;
 }
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
/*x<=y means y-x>=0
if x and y have same signs
result won't be out of range only need to check result sign

if they have different signs, result might be  out of range
in that case result sign and y sign equal
*/ 
int xSign=!!(x>>31);
 int ySign=!!(y>>31); 
 int reSign=!((y+1+~x)>>31);
 return ((!(xSign^ySign))&reSign)|((xSign^ySign)&xSign);
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
/*get positive of x first
  get a mask 0xFFFFFFFF
  if the left 16 bits not 0, then need at least 16 bits
  right shift
  at last add the sign bit
*/
 int ope=x^(x>>31);
 int negOpe=!ope;
 int bit16,bit8,bit4,bit2,bit1;
 int mask=(!(!ope)<<31)>>31;
 
 bit16=!(!(ope>>16))<<4;
 ope=ope>>bit16;
 bit8=!(!(ope>>8))<<3;
 ope=ope>>bit8;
 bit4=!(!(ope>>4))<<2;
 ope=ope>>bit4;
 bit2=!(!(ope>>2))<<1;
 ope=ope>>bit2;
 bit1=!(!(ope>>1));
 ope=bit16+bit8+bit4+bit2+bit1+2;
 return (negOpe|(ope&mask));
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
/*change sign of uf first
  judage store the value of uf with sign bit as 0
  then check whether judge is NaN
*/
 
 unsigned result=uf^(1<<31);
 unsigned judge=uf&(~(1<<31));
 if(judge>(0xFF<<23)){
return uf;}
return result;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
/*considering sign exponent and fraction
  get their initial value
  sign=x&(1<<31);
  exponent value depends on sign value
  for precision,x&0xFF  */
unsigned sign=x&(1<<31);
int count=30;
int exponent=0;
int fraction=0;
int de;
int mask=(1<<23)-1;
if(x>>31){
exponent=158;
}
if(x<<1){
if(x<0){
x=-x;
}
while(!((x>>count)&0x1)){
count--;}
exponent=count+127;
x=x<<(31-count);
fraction=mask&(x>>8);
x=x&0xFF;
de=x>128||((x==128)&&(fraction&0x1));
fraction+=de;
if(fraction>>23){
fraction&=mask;
exponent+=1;
 }
}
return sign|(exponent<<23)|fraction;
}


	


/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
/*get 2uf and check whether it is NaN                  
  return the value uf
*/
unsigned exponent =uf&(0xFF<<23);
unsigned sign=uf&(0x1<<31);
if(exponent!=0) {
if((uf&(0xFF<<23))!=(0XFF<<23)){
uf=uf+(0x1<<23);
}}else{
uf=(uf<<1)|sign;
}
return uf;
}
