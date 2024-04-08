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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int revX = ~x;
  int revY = ~y;

  int res1 = x & revY;
  int res2 = y & revX;

  int res = ~res1 & ~res2; // ~A & ~B  <=> A | B

  return ~res;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x) {
  int x_minux_1 = x + 1; // if x == Tmax, x + 1 = Tmin

  int res = !(~x_minux_1 ^ x); // ^ can be used to determine whether the two are equal

  res &= !!(~x ^ 0);

  return res;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // Set all odd bits in word to 1
  int hexA_2 = 0xAA;
  int hexA_8 = hexA_2 << 8;
  int res;
  hexA_8 |= hexA_2;
  hexA_8 <<= 8;
  hexA_8 |= hexA_2;
  hexA_8 <<= 8;
  hexA_8 |= hexA_2;

  // Keep only the odd bits in x
  x &= hexA_8;

  res = x ^ hexA_8;

  return !res;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  // ~x + 1 = -x
  // ~(x - 1) = -x
  x += ~0;
  return ~x;
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
  int judge_pre, judge_post, Tmin, res;

  // The pre bits must be the same as 0x30
  judge_pre = x & ~0xF;
  judge_pre ^= 0x30;

  // Post needs to be less than 10, which means post minus 10 will result in a negative value
  judge_post = x & 0xF;
  judge_post += ~10 + 1;

  // Determine whether the calculation result is a negative number
  Tmin = 1 << 31;
  judge_post &= Tmin;
  judge_post ^= Tmin;
  
  // The pre and post conditions need to be met at the same time
  res = judge_pre | judge_post;

  return !res;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // If x is 0, take the latter, otherwise take the former
  int post = !x;
  int pre = !post;

  // all 0 or all 1(0 or -1)
  pre = ~pre + 1;
  post = ~post + 1;

  return (y & pre) | (z & post);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // y - x
  int revX = ~x + 1;
  int y_minus_x = y + revX;

  int res = !(y_minus_x >> 31); // y - x > 0
  res |= (x >> 31) & !(y >> 31); // or (x < 0 and y > 0)
  res &= !(!(x >> 31) & (y >> 31));// and !(x > 0 and y < 0)

  return res;
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
  // Returns 1 only when x=0, otherwise returns 0
  // So determine whether x is equal to 0
  // When x=0, x - 1 < 0 && x + 1 >= 0 && x >= 0
  int plus1 = x + 1;
  int minus1 = x + (~1 + 1);

  int Tmin = 1 << 31;

  // Note the difference between logical right shift and arithmetic right shift
  int res = ((minus1 & Tmin) & (plus1 ^ Tmin) & (x ^ Tmin)) >> 31;
  res &= 1;

  return res;
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
  return 0;
}
//float
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
  unsigned exp = (uf & 0x7F800000) >> 23; // get specific exp
  unsigned frac = uf & 0x007FFFFF; // get specific frac

  unsigned res = uf; // if argument is NaN or infinity, return argument

  if(exp ^ 0xFF) { // else if exp is not all 1
    // If exp is not all 0, it means that frac has an implicit 1 before the decimal point
    if(exp ^ 0x00) {
      frac |= 0x800000;
    }
    
    frac = 2 * frac; // calculate 2*f

    if(frac & 0x01000000) { // if 2*f is not in the range 1~2
      frac >>= 1;
      exp += 1;
      if(!(exp ^ 0xFF)) { // if exp is all 1 it means res needs to be infinite
        frac = 0;
      }
    }
    
    if(!(exp ^ 0x00) && frac & 0x800000) { // if exp is all 0 and frac is between 1~2
      exp += 1;
    }

    frac &= 0x7FFFFF;

    res &= 0x80000000;
    res |= exp << 23;
    res |= frac;
  }

  return res;
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
  // values will be used
  int step;
  unsigned indicator;
  
  // printf("x: %x\n", x);
  unsigned s = x & 0x80000000; // s: plus or minus
  unsigned exp = 150; // exp: init exp, 150 = 127 + 23
  unsigned frac = x & 0x7FFFFFFF; // frac: get absolute value
  if (s) {
    frac = s - frac;
  }
  // printf("frac: %x\n", frac);

  // trim left
  step = 8;
  indicator = 0x80000000;
  while (indicator && !(frac & indicator)) {
    --step;
    indicator >>= 1;
  }
  // printf("step: %d\n", step);
  // printf("indicator: %x\n", indicator);

  // trim right
  if (step > 0) {
    unsigned right = frac & ~(0xFFFFFFFF << step);
    unsigned half_val = 1 << (step - 1);

    frac >>= step;

    // take an approximation
    if (right > half_val) {
      frac += 1;
    } else if (right == half_val) {
      if(frac & 1) {
        frac += 1;
      }
    }

    // special case: ux == 0xFFFFFF + 1
    if (frac & 0x1000000) {
      frac = 0x800000;
      ++exp;
    }

    // printf("frac: %x\n", frac);
    // printf("exp: %d\n", exp);
  } else {
    frac <<= -step;
  }

  if (!indicator) { // special case: ux == 0
    exp = 0;
  } else {
    exp += step;
  }
  // printf("exp: %d\n", exp);

  frac &= 0xFF7FFFFF;
  
  // printf("frac: %x\n", frac);

  // printf("ux: %x\n", ux);
  // printf("exp: %d\n", exp);
  // printf("step: %d\n", step);
  
  s |= exp << 23;
  s |= frac;
  
  // printf("res: %x\n", res);
  return s;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
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
int float_f2i(unsigned uf) {
  // values will be used
  int res, E;
  unsigned indicator;

  // printf("uf: %x\n", uf);
  unsigned exp = (uf & 0x7F800000) >> 23;
  // printf("exp: %d\n", exp);
  unsigned frac = uf & 0x007FFFFF;

  // NaN or infinity
  if (!(exp ^ 0xFF)) {
    // printf("uf is NaN or infinity\n");
    return 0x80000000;
  }

  // if exp != 0
  if (exp) {
    frac |= 0x800000;
  } else {
    exp += 1; // E = 1 - bias when exp == 0
  }

  // calculate absolute value
  res = frac;
  E = exp - 150; // 150 = 127 + 23
  indicator = 0x80;
  if (E < 0) {
    E = -E;
    while (E) {
      // printf("E: %d\n", E);
      // printf("indicator: %d\n", indicator);
      if (E & indicator) {
        unsigned off_set = indicator;
        if (off_set > 31) {
          off_set = 31;
        }
        res >>= off_set;
        // printf("res: %x\n", res);
      }
      E &= ~indicator;
      indicator >>= 1;
    }
  } else if (E > 0) {
    if (E > 7) { // out of range
      return 0x80000000;
    }
    while (E) {
      if (E & indicator) {
        unsigned off_set = indicator;
        res <<= off_set;
      }
      E &= ~indicator;
      indicator >>= 1;
    }
  }
  
  // get the real value
  if (uf & 0x80000000) {
      res = -res;
  }
  
  // printf("res: %x\n", res);
  return res;
}
