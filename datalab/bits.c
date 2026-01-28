/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /* Make use of the fact that ~(x & y) is equivalent to (~x | ~y) */
  return ~(~(~x & y) & ~(~y & x));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /* The minimum integer (signed 32-bit) is 1000...0000 (31 zeros) */
  return 0x1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* 
   * If I can use >>, an easier way is to return (!(x >> 31)) & ((x + 1) >> 31);
   * Alternatively, if x + x + 2 is 0, x should be Tmax (0111...1111) or -1 (1111...1111) 
   */
  return !((x + x + 2) | !(x + 1));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /* 
   * Method 1: generate a mask 0xAAAAAAAA 
   * Method 2: fold
   */
  // ----------------- Method 1 -----------------
  // int small_mask = 0xAA;
  // int middle_mask = (small_mask << 8) | small_mask;
  // int mask = (middle_mask << 16) | middle_mask;
  // return !((x & mask) ^ mask);

  // ----------------- Method 2 -----------------
  x = x & (x >> 16);
  x = x & (x >> 8);
  x = x & (x >> 4);
  x = x & (x >> 2);
  return (x >> 1) & 0x1; 
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /* 
   * 1. x >= 0x30 (x - 0x30 >> 31 is 0)
   * 2. x <= 0x39 (0x39 - x >> 31 is 0)
   * 3. I cannot use -, use ~ and + instead
   */
  return !(((x + ~0x30 + 1) >> 31) | ((0x39 + ~x + 1) >> 31));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /* 
   * if x is 0, y's mask should be 0000...0000, z's mask should be 1111...1111
   * if x is not 0, y's mask should be 1111...1111, z's mask should be 0000...0000 
   */
  int mask = (!x) + ~0x0; // Or: int mask = (!!x << 31) >> 31; 
  return (y & mask) | (z & ~mask);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /* 
   * ----------------- Method 1 -----------------
   * No overflow: if (y - x)'s is non-negative, then x <= y 
   * case 1: if x < 0, y-x <= y     => positive overflow, true
   * case 2: if x < 0, y-x > y      => no overflow
   * case 3: if x >= 0, y-x > y     => negative overflow, false
   * case 4: if x >= 0, y-x <= y    => no overflow
   * if x is Tmin: ~x + 1 = x. Result must be true (NOT included in case 1)
   * blah blah...
   * 
   * ----------------- Method 2 -----------------
   * 1. convert to monotonically increasing bit patterns: int ux = x ^ (0x1 << 31)
   * 2. regard them as unsigned numbers, let's call them uy and ux
   *    - if uy >= ux, uy - ux should have no negative overflow
   * Method 2 is not practical. Because, in order to tell if overflow occurs,
   * we have to realize isLessOrEqual() first.
   */

  int sx = (x >> 31) & 0x1;
  int sy = (y >> 31) & 0x1;
  int different_sign = sx ^ sy;
  int neg_x = ~x + 1;
  int diff_starts_with_0 = !((y + neg_x) >> 31);
  return (different_sign & sx) | ((!different_sign) & diff_starts_with_0);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /* 
   * To distinglish 0 from other numbers
   * Method 1: 
   *   1. if x and x - 1 (= x + ~0x0) have different highest bit, x must be 0 or (10...xx) or (01...xx)
   *   2. 0's highest two bits are the same
   * Method 2:
   *   If x starts with 00, and x - 1 (= x + ~0x0) starts with 11, then x should be 0
   * Method 3:
   *   FOLD: let 32 -> 16 -> 8 -> 4 -> 2 -> 1
   */
  x = x | (x >> 16);
  x = x | (x >> 8);
  x = x | (x >> 4);
  x = x | (x >> 2);
  x = x | (x >> 1); // possible values: 00...00; 00...01; 11...11
  return ~x & 0x1; // Get the last bit 
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
  /* 
   * if x starts with 0, remove first n-1 zeros
   *    eg. for a byte: 0001 1111 => 01 1111 (remove 2 zeros, 6 bits are needed)
   * if x starts with 1, remove first n-1 ones
   *    eg. for a byte: 1111 1000 => 1000 (remove 4 ones, 4 bits are needed)
   * to combine 2 cases: convert negative x to ~x (or convert non-negative x to ~x)
   *    eg. convert 1111 1000 to 0000 0111 => 0111 (remove 4 zeros, 4 bits are needed)
   */
  int sx = (x >> 31) & 0x1; // x's sign
  int cnt, shift, seg, flag, mask; // To eliminate warnings raised by dlc
  // Convert all numbers to negative case (remove first n ones)
  /* ----------------- Method 1 -----------------
   * ----------(more than 90 operations)----------
   * x = x ^ (sx + ~0x0); // sx = 0: x = x ^ 11...11 = ~x; sx = 1, x = x ^ 00...00 = x
   * int bit = 0x1, cnt = 0;
   * // The [n] below is from 31 to 0 (32 steps in total)
   * bit = (x >> [n]) & bit;
   * cnt = cnt + bit;
   * return 33 - cnt; 
   */

   /* ----------------- Method 2: Divide and Conquer ----------------- 
    * 1. divide into 2 segments: seg highest 16 bits, seg_0 lowest 16 bits
    * 2. check if it is 0 
    *    Method 1: int flag = seg | (seg >> 8);
                   flag = flag | (flag >> 4);
                   flag = flag | (flag >> 2);
                   flag = flag | (flag >> 1);
                   flag = flag & 0x1;
         Method 2: int flag = !!seg;
    */
  x = x ^ (~sx + 1); // sx = 0: x = x ^ 0..0 = x; sx = 1, x = x ^ 1...1 = ~x
  cnt = 0;
  shift = 16;
  seg = x >> shift; // I don't need mask ((0x10 << shift) - 1), because I've convert x to be non-negative
  // assign new x. if if flag == 1: x = seg; else: x = x;
  flag = !!seg;
  mask = ~flag + 1;  // Or int mask = (flag << 31) >> 31;
  x = (seg & mask) | (x & (~mask));
  // add cnt. if flag == 1: cnt += 8; else: cnt += 0;
  cnt = cnt + (shift & mask);

  shift = 8;
  seg = x >> shift;
  flag = !!seg;
  mask = ~flag + 1; 
  x = (seg & mask) | (x & (~mask));
  cnt = cnt + (shift & mask);

  shift = 4;
  seg = x >> shift;
  flag = !!seg;
  mask = ~flag + 1; 
  x = (seg & mask) | (x & (~mask));
  cnt = cnt + (shift & mask);

  shift = 2;
  seg = x >> shift;
  flag = !!seg;
  mask = ~flag + 1; 
  x = (seg & mask) | (x & (~mask));
  cnt = cnt + (shift & mask);;

  // -...- + xx + -...-(n bits), xx could be 11, 10, 01 (usually it's not 00)
  //  if it's -...- + 01 + n bits, we should return n + 2
  //  if it's -...- + 11 / 10 + n bits, we should return n + 3
  // special case: x = 0000...0000: --...-- + 00 + 0 bits, we should return 1 (n + 1)
  shift = 1;
  seg = x >> shift;
  flag = !!seg;
  mask = ~flag + 1; 
  x = (seg & mask) | (x & (~mask));
  cnt = cnt + (shift & mask);

  return cnt + x + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  /* 
   * single-precision floating point values: 
   * s - 1 bit; e - 8 bits; f - 23 bits 
   *   V = pow(-1, s) * pow(2, E) * M    (e != 255)
   *   E = e - Bias (e != 0 && e != 255) | 1 - Bias (e == 0)
   *      where Bias = 127
   *   M = 1 + f (e != 0 && e != 255) | f (e == 0)
   * 
   *   =>
   *   V = pow(-1, s) * pow(2, 1 - 127) * f    (e == 0)
   *   V = pow(-1, s) * pow(2, e - 127) * (1 + f)    (e! = 0, e != 255)
   *   V = +/- Inf (e == 255 && f == 0) | NaN (e == 255 && f != 0)
   */
  unsigned bits_f = 23;
  unsigned bits_e = 8;
  unsigned mask_f = (0x1 << bits_f) - 1;
  unsigned mask_e = (0x1 << bits_e) - 1;
  unsigned f = uf & mask_f;
  unsigned e = (uf >> bits_f) & mask_e;
  unsigned s = (uf >> (bits_f + bits_e)) & 0x1;
  if ((e + 1) >> bits_e ) // if (e == 255). It seems that I cannot use `==`
    return uf;
  if (!e) {
    f = f << 1;
    e = e + (f >> bits_f);
  }
  else {
    e = e + 1;
  }
  if (e >> 8)  // if (e == 256): Inf
    f = 0;
  return (s << 31) | ((e & mask_e) << 23) | (f & mask_f);
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  /* 
   * According to test, it should return ceil(float)
   * eg. floatFloat2Int(0x007fffff) returns 0
   *          0x007fffff is +0.9999998808 X 2^(-126) = 1.175494211e-38
   *     floatFloat2Int(0x407fffff) returns 3
   *          0x407fffff is +1.9999998808 X 2^(1) = 3.999999762
   * 1. convert to non-negative int 
   * 2. convert based on s
   */
  int bits_f = 23;
  int bits_e = 8;
  unsigned mask_f = (0x1 << bits_f) - 1;
  unsigned mask_e = (0x1 << bits_e) - 1;
  unsigned f = uf & mask_f;
  unsigned e = (uf >> bits_f) & mask_e;
  unsigned s = (uf >> (bits_f + bits_e)) & 0x1;
  int value;
  int bias = (0x1 << (bits_e - 1)) - 1;
  int out_of_range = 0x80000000u;

  // if (e == 0), a more precise expression is 
  //      f << (1 - bias - bits_f)
  // rather than the general expression: 
  //      (f + (0x1 << bits_f)) << (e - bias - bits_f)
  // but in both cases, we will get 0.
  // so, I will the general expression
  int shift = e - bias - bits_f;
  if (shift >= 32 - bits_f) // make sure this expression has no unsigned 
    return out_of_range;
  // We cannot << or >> a negative number
  if (shift < 0) {
    if (-shift > bits_f)
      return 0;
    value = (f + (0x1 << bits_f)) >> (-shift); 
  }
  else 
    value = (f + (0x1 << bits_f)) << shift; 
  if (s)
    value = ~value + 1;
  return value;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  /* 
   * 2.0^x is 
   *     (1 + 0.0000) * 2^x  
   *           --- Normalized, e-127 = x (1<=e<=254) => -126<=x<=127
   *     (0.1000) * 2^(x+1) = (0.0100) * 2^(x+2) = ... = (0.0...1) * 2^(x+23)
   *           --- Denormalized, 1-127 = x+1/2/.../23 => -149<=x<=-127
   * eg. floatPower2(-2) returns: 0x3e800000
   *    (float) 0x3e800000 is +1.0000000000 X 2^(-2) = 0.25
   */
  unsigned f, e;
  unsigned s = 0;
  int out_of_range = 0x7f800000;

  if (x > 127) {
    return out_of_range;
  } else if (x < -149) {
    return 0;
  }
  else if (x >= -126) {  // Normalized
    f = 0;
    e = x + 127;
  } else {
    e = 0;
    f = 0x1 << (149 + x);
  }
  
  return (s << 31) | (e << 23) | f;
}
