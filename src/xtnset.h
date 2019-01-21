/*
 * NOTE: This file should be excluded from the Doxygen build
 * 
 * file xtnset.h
 * author Robert Carnell
 * copyright Copyright (c) 2013, Robert Carnell
 * 
 * License:  This file may be freely used and shared according to the original license.
 * 
 * Reference:
 * <ul><li><a href="http://lib.stat.cmu.edu/designs/">Statlib Designs</a></li>
 * <li><a href="http://lib.stat.cmu.edu/designs/oa.c">Owen's Orthogonal Array Algorithms</a></li></ul>
 * 
 * Original Header:
 * <blockquote>
 * These programs construct and manipulate orthogonal arrays.  They were prepared by
 * 
 * - Art Owen
 * - Department of Statistics
 * - Sequoia Hall
 * - Stanford CA 94305
 * 
 * They may be freely used and shared.  This code comes 
 * with no warranty of any kind.  Use it at your own
 * risk.
 * 
 * I thank the Semiconductor Research Corporation and
 * the National Science Foundation for supporting this
 * work.
 * </blockquote>
 */

#ifndef XTNSET_H
#define XTNSET_H

/*  This code was computer generated */

/*  GF( 2 ^ 2 ) = GF( 4 ) */
xtn2t2 = std::vector<int>(1+1);
xtn2t2[0] = 1;
xtn2t2[1] = 1;

/*  GF( 2 ^ 3 ) = GF( 8 ) */
xtn2t3 = std::vector<int>(1+2);
xtn2t3[0] = 1;
xtn2t3[1] = 0;
xtn2t3[2] = 1;

/*  GF( 2 ^ 4 ) = GF( 16 ) */
xtn2t4 = std::vector<int>(1+3);
xtn2t4[0] = 1;
xtn2t4[1] = 0;
xtn2t4[2] = 0;
xtn2t4[3] = 1;

/*  GF( 2 ^ 5 ) = GF( 32 ) */
xtn2t5 = std::vector<int>(1+4);
xtn2t5[0] = 1;
xtn2t5[1] = 0;
xtn2t5[2] = 0;
xtn2t5[3] = 1;
xtn2t5[4] = 0;

/*  GF( 2 ^ 6 ) = GF( 64 ) */
xtn2t6 = std::vector<int>(1+5);
xtn2t6[0] = 1;
xtn2t6[1] = 0;
xtn2t6[2] = 0;
xtn2t6[3] = 0;
xtn2t6[4] = 0;
xtn2t6[5] = 1;

/*  GF( 2 ^ 7 ) = GF( 128 ) */
xtn2t7 = std::vector<int>(1+6);
xtn2t7[0] = 1;
xtn2t7[1] = 0;
xtn2t7[2] = 0;
xtn2t7[3] = 0;
xtn2t7[4] = 0;
xtn2t7[5] = 0;
xtn2t7[6] = 1;

/*  GF( 2 ^ 8 ) = GF( 256 ) */
xtn2t8 = std::vector<int>(1+7);
xtn2t8[0] = 1;
xtn2t8[1] = 0;
xtn2t8[2] = 0;
xtn2t8[3] = 0;
xtn2t8[4] = 1;
xtn2t8[5] = 1;
xtn2t8[6] = 1;
xtn2t8[7] = 0;

/*  GF( 2 ^ 9 ) = GF( 512 ) */
xtn2t9 = std::vector<int>(1+8);
xtn2t9[0] = 1;
xtn2t9[1] = 0;
xtn2t9[2] = 0;
xtn2t9[3] = 0;
xtn2t9[4] = 0;
xtn2t9[5] = 1;
xtn2t9[6] = 0;
xtn2t9[7] = 0;
xtn2t9[8] = 0;

/*  GF( 2 ^ 10 ) = GF( 1024 ) */
xtn2t10 = std::vector<int>(1+9);
xtn2t10[0] = 1;
xtn2t10[1] = 0;
xtn2t10[2] = 0;
xtn2t10[3] = 0;
xtn2t10[4] = 0;
xtn2t10[5] = 0;
xtn2t10[6] = 0;
xtn2t10[7] = 1;
xtn2t10[8] = 0;
xtn2t10[9] = 0;

/*  GF( 2 ^ 11 ) = GF( 2048 ) */
xtn2t11 = std::vector<int>(1+10);
xtn2t11[0] = 1;
xtn2t11[1] = 0;
xtn2t11[2] = 0;
xtn2t11[3] = 0;
xtn2t11[4] = 0;
xtn2t11[5] = 0;
xtn2t11[6] = 0;
xtn2t11[7] = 0;
xtn2t11[8] = 0;
xtn2t11[9] = 1;
xtn2t11[10] = 0;

/*  GF( 2 ^ 12 ) = GF( 4096 ) */
xtn2t12 = std::vector<int>(1+11);
xtn2t12[0] = 1;
xtn2t12[1] = 0;
xtn2t12[2] = 0;
xtn2t12[3] = 0;
xtn2t12[4] = 1;
xtn2t12[5] = 0;
xtn2t12[6] = 0;
xtn2t12[7] = 0;
xtn2t12[8] = 0;
xtn2t12[9] = 0;
xtn2t12[10] = 1;
xtn2t12[11] = 1;

/*  GF( 2 ^ 13 ) = GF( 8192 ) */
xtn2t13 = std::vector<int>(1+12);
xtn2t13[0] = 1;
xtn2t13[1] = 0;
xtn2t13[2] = 0;
xtn2t13[3] = 0;
xtn2t13[4] = 0;
xtn2t13[5] = 0;
xtn2t13[6] = 0;
xtn2t13[7] = 0;
xtn2t13[8] = 1;
xtn2t13[9] = 0;
xtn2t13[10] = 0;
xtn2t13[11] = 1;
xtn2t13[12] = 1;

/*  GF( 2 ^ 14 ) = GF( 16384 ) */
xtn2t14 = std::vector<int>(1+13);
xtn2t14[0] = 1;
xtn2t14[1] = 0;
xtn2t14[2] = 1;
xtn2t14[3] = 0;
xtn2t14[4] = 0;
xtn2t14[5] = 0;
xtn2t14[6] = 0;
xtn2t14[7] = 0;
xtn2t14[8] = 0;
xtn2t14[9] = 0;
xtn2t14[10] = 0;
xtn2t14[11] = 0;
xtn2t14[12] = 1;
xtn2t14[13] = 1;

/*  GF( 2 ^ 15 ) = GF( 32768 ) */
xtn2t15 = std::vector<int>(1+14);
xtn2t15[0] = 1;
xtn2t15[1] = 0;
xtn2t15[2] = 0;
xtn2t15[3] = 0;
xtn2t15[4] = 0;
xtn2t15[5] = 0;
xtn2t15[6] = 0;
xtn2t15[7] = 0;
xtn2t15[8] = 0;
xtn2t15[9] = 0;
xtn2t15[10] = 0;
xtn2t15[11] = 0;
xtn2t15[12] = 0;
xtn2t15[13] = 0;
xtn2t15[14] = 1;

/*  GF( 2 ^ 16 ) = GF( 65536 ) */
xtn2t16 = std::vector<int>(1+15);
xtn2t16[0] = 1;
xtn2t16[1] = 0;
xtn2t16[2] = 0;
xtn2t16[3] = 0;
xtn2t16[4] = 1;
xtn2t16[5] = 0;
xtn2t16[6] = 0;
xtn2t16[7] = 0;
xtn2t16[8] = 0;
xtn2t16[9] = 0;
xtn2t16[10] = 0;
xtn2t16[11] = 0;
xtn2t16[12] = 0;
xtn2t16[13] = 1;
xtn2t16[14] = 0;
xtn2t16[15] = 1;

/*  GF( 2 ^ 17 ) = GF( 131072 ) */
xtn2t17 = std::vector<int>(1+16);
xtn2t17[0] = 1;
xtn2t17[1] = 0;
xtn2t17[2] = 0;
xtn2t17[3] = 0;
xtn2t17[4] = 0;
xtn2t17[5] = 0;
xtn2t17[6] = 0;
xtn2t17[7] = 0;
xtn2t17[8] = 0;
xtn2t17[9] = 0;
xtn2t17[10] = 0;
xtn2t17[11] = 0;
xtn2t17[12] = 0;
xtn2t17[13] = 0;
xtn2t17[14] = 1;
xtn2t17[15] = 0;
xtn2t17[16] = 0;

/*  GF( 2 ^ 18 ) = GF( 262144 ) */
xtn2t18 = std::vector<int>(1+17);
xtn2t18[0] = 1;
xtn2t18[1] = 0;
xtn2t18[2] = 0;
xtn2t18[3] = 0;
xtn2t18[4] = 0;
xtn2t18[5] = 0;
xtn2t18[6] = 0;
xtn2t18[7] = 0;
xtn2t18[8] = 0;
xtn2t18[9] = 0;
xtn2t18[10] = 0;
xtn2t18[11] = 1;
xtn2t18[12] = 0;
xtn2t18[13] = 0;
xtn2t18[14] = 0;
xtn2t18[15] = 0;
xtn2t18[16] = 0;
xtn2t18[17] = 0;

/*  GF( 2 ^ 19 ) = GF( 524288 ) */
xtn2t19 = std::vector<int>(1+18);
xtn2t19[0] = 1;
xtn2t19[1] = 0;
xtn2t19[2] = 0;
xtn2t19[3] = 0;
xtn2t19[4] = 0;
xtn2t19[5] = 0;
xtn2t19[6] = 0;
xtn2t19[7] = 0;
xtn2t19[8] = 0;
xtn2t19[9] = 0;
xtn2t19[10] = 0;
xtn2t19[11] = 0;
xtn2t19[12] = 0;
xtn2t19[13] = 0;
xtn2t19[14] = 1;
xtn2t19[15] = 0;
xtn2t19[16] = 0;
xtn2t19[17] = 1;
xtn2t19[18] = 1;

/*  GF( 2 ^ 20 ) = GF( 1048576 ) */
xtn2t20 = std::vector<int>(1+19);
xtn2t20[0] = 1;
xtn2t20[1] = 0;
xtn2t20[2] = 0;
xtn2t20[3] = 0;
xtn2t20[4] = 0;
xtn2t20[5] = 0;
xtn2t20[6] = 0;
xtn2t20[7] = 0;
xtn2t20[8] = 0;
xtn2t20[9] = 0;
xtn2t20[10] = 0;
xtn2t20[11] = 0;
xtn2t20[12] = 0;
xtn2t20[13] = 0;
xtn2t20[14] = 0;
xtn2t20[15] = 0;
xtn2t20[16] = 0;
xtn2t20[17] = 1;
xtn2t20[18] = 0;
xtn2t20[19] = 0;

/*  GF( 2 ^ 21 ) = GF( 2097152 ) */
xtn2t21 = std::vector<int>(1+20);
xtn2t21[0] = 1;
xtn2t21[1] = 0;
xtn2t21[2] = 0;
xtn2t21[3] = 0;
xtn2t21[4] = 0;
xtn2t21[5] = 0;
xtn2t21[6] = 0;
xtn2t21[7] = 0;
xtn2t21[8] = 0;
xtn2t21[9] = 0;
xtn2t21[10] = 0;
xtn2t21[11] = 0;
xtn2t21[12] = 0;
xtn2t21[13] = 0;
xtn2t21[14] = 0;
xtn2t21[15] = 0;
xtn2t21[16] = 0;
xtn2t21[17] = 0;
xtn2t21[18] = 0;
xtn2t21[19] = 1;
xtn2t21[20] = 0;

/*  GF( 2 ^ 22 ) = GF( 4194304 ) */
xtn2t22 = std::vector<int>(1+21);
xtn2t22[0] = 1;
xtn2t22[1] = 0;
xtn2t22[2] = 0;
xtn2t22[3] = 0;
xtn2t22[4] = 0;
xtn2t22[5] = 0;
xtn2t22[6] = 0;
xtn2t22[7] = 0;
xtn2t22[8] = 0;
xtn2t22[9] = 0;
xtn2t22[10] = 0;
xtn2t22[11] = 0;
xtn2t22[12] = 0;
xtn2t22[13] = 0;
xtn2t22[14] = 0;
xtn2t22[15] = 0;
xtn2t22[16] = 0;
xtn2t22[17] = 0;
xtn2t22[18] = 0;
xtn2t22[19] = 0;
xtn2t22[20] = 0;
xtn2t22[21] = 1;

/*  GF( 2 ^ 23 ) = GF( 8388608 ) */
xtn2t23 = std::vector<int>(1+22);
xtn2t23[0] = 1;
xtn2t23[1] = 0;
xtn2t23[2] = 0;
xtn2t23[3] = 0;
xtn2t23[4] = 0;
xtn2t23[5] = 0;
xtn2t23[6] = 0;
xtn2t23[7] = 0;
xtn2t23[8] = 0;
xtn2t23[9] = 0;
xtn2t23[10] = 0;
xtn2t23[11] = 0;
xtn2t23[12] = 0;
xtn2t23[13] = 0;
xtn2t23[14] = 0;
xtn2t23[15] = 0;
xtn2t23[16] = 0;
xtn2t23[17] = 0;
xtn2t23[18] = 1;
xtn2t23[19] = 0;
xtn2t23[20] = 0;
xtn2t23[21] = 0;
xtn2t23[22] = 0;

/*  GF( 2 ^ 24 ) = GF( 16777216 ) */
xtn2t24 = std::vector<int>(1+23);
xtn2t24[0] = 1;
xtn2t24[1] = 0;
xtn2t24[2] = 0;
xtn2t24[3] = 0;
xtn2t24[4] = 0;
xtn2t24[5] = 0;
xtn2t24[6] = 0;
xtn2t24[7] = 0;
xtn2t24[8] = 0;
xtn2t24[9] = 0;
xtn2t24[10] = 0;
xtn2t24[11] = 0;
xtn2t24[12] = 0;
xtn2t24[13] = 0;
xtn2t24[14] = 0;
xtn2t24[15] = 0;
xtn2t24[16] = 0;
xtn2t24[17] = 1;
xtn2t24[18] = 0;
xtn2t24[19] = 0;
xtn2t24[20] = 0;
xtn2t24[21] = 0;
xtn2t24[22] = 1;
xtn2t24[23] = 1;

/*  GF( 2 ^ 25 ) = GF( 33554432 ) */
xtn2t25 = std::vector<int>(1+24);
xtn2t25[0] = 1;
xtn2t25[1] = 0;
xtn2t25[2] = 0;
xtn2t25[3] = 0;
xtn2t25[4] = 0;
xtn2t25[5] = 0;
xtn2t25[6] = 0;
xtn2t25[7] = 0;
xtn2t25[8] = 0;
xtn2t25[9] = 0;
xtn2t25[10] = 0;
xtn2t25[11] = 0;
xtn2t25[12] = 0;
xtn2t25[13] = 0;
xtn2t25[14] = 0;
xtn2t25[15] = 0;
xtn2t25[16] = 0;
xtn2t25[17] = 0;
xtn2t25[18] = 0;
xtn2t25[19] = 0;
xtn2t25[20] = 0;
xtn2t25[21] = 0;
xtn2t25[22] = 1;
xtn2t25[23] = 0;
xtn2t25[24] = 0;

/*  GF( 2 ^ 26 ) = GF( 67108864 ) */
xtn2t26 = std::vector<int>(1+25);
xtn2t26[0] = 1;
xtn2t26[1] = 0;
xtn2t26[2] = 0;
xtn2t26[3] = 0;
xtn2t26[4] = 0;
xtn2t26[5] = 0;
xtn2t26[6] = 0;
xtn2t26[7] = 0;
xtn2t26[8] = 0;
xtn2t26[9] = 0;
xtn2t26[10] = 0;
xtn2t26[11] = 0;
xtn2t26[12] = 0;
xtn2t26[13] = 0;
xtn2t26[14] = 0;
xtn2t26[15] = 0;
xtn2t26[16] = 0;
xtn2t26[17] = 0;
xtn2t26[18] = 0;
xtn2t26[19] = 0;
xtn2t26[20] = 1;
xtn2t26[21] = 0;
xtn2t26[22] = 0;
xtn2t26[23] = 0;
xtn2t26[24] = 1;
xtn2t26[25] = 1;

/*  GF( 2 ^ 27 ) = GF( 134217728 ) */
xtn2t27 = std::vector<int>(1+26);
xtn2t27[0] = 1;
xtn2t27[1] = 0;
xtn2t27[2] = 0;
xtn2t27[3] = 0;
xtn2t27[4] = 0;
xtn2t27[5] = 0;
xtn2t27[6] = 0;
xtn2t27[7] = 0;
xtn2t27[8] = 0;
xtn2t27[9] = 0;
xtn2t27[10] = 0;
xtn2t27[11] = 0;
xtn2t27[12] = 0;
xtn2t27[13] = 0;
xtn2t27[14] = 0;
xtn2t27[15] = 0;
xtn2t27[16] = 0;
xtn2t27[17] = 0;
xtn2t27[18] = 0;
xtn2t27[19] = 0;
xtn2t27[20] = 0;
xtn2t27[21] = 0;
xtn2t27[22] = 1;
xtn2t27[23] = 0;
xtn2t27[24] = 0;
xtn2t27[25] = 1;
xtn2t27[26] = 1;

/*  GF( 2 ^ 28 ) = GF( 268435456 ) */
xtn2t28 = std::vector<int>(1+27);
xtn2t28[0] = 1;
xtn2t28[1] = 0;
xtn2t28[2] = 0;
xtn2t28[3] = 0;
xtn2t28[4] = 0;
xtn2t28[5] = 0;
xtn2t28[6] = 0;
xtn2t28[7] = 0;
xtn2t28[8] = 0;
xtn2t28[9] = 0;
xtn2t28[10] = 0;
xtn2t28[11] = 0;
xtn2t28[12] = 0;
xtn2t28[13] = 0;
xtn2t28[14] = 0;
xtn2t28[15] = 0;
xtn2t28[16] = 0;
xtn2t28[17] = 0;
xtn2t28[18] = 0;
xtn2t28[19] = 0;
xtn2t28[20] = 0;
xtn2t28[21] = 0;
xtn2t28[22] = 0;
xtn2t28[23] = 0;
xtn2t28[24] = 0;
xtn2t28[25] = 1;
xtn2t28[26] = 0;
xtn2t28[27] = 0;

/*  GF( 2 ^ 29 ) = GF( 536870912 ) */
xtn2t29 = std::vector<int>(1+28);
xtn2t29[0] = 1;
xtn2t29[1] = 0;
xtn2t29[2] = 0;
xtn2t29[3] = 0;
xtn2t29[4] = 0;
xtn2t29[5] = 0;
xtn2t29[6] = 0;
xtn2t29[7] = 0;
xtn2t29[8] = 0;
xtn2t29[9] = 0;
xtn2t29[10] = 0;
xtn2t29[11] = 0;
xtn2t29[12] = 0;
xtn2t29[13] = 0;
xtn2t29[14] = 0;
xtn2t29[15] = 0;
xtn2t29[16] = 0;
xtn2t29[17] = 0;
xtn2t29[18] = 0;
xtn2t29[19] = 0;
xtn2t29[20] = 0;
xtn2t29[21] = 0;
xtn2t29[22] = 0;
xtn2t29[23] = 0;
xtn2t29[24] = 0;
xtn2t29[25] = 0;
xtn2t29[26] = 0;
xtn2t29[27] = 1;
xtn2t29[28] = 0;

/*  GF( 3 ^ 2 ) = GF( 9 ) */
xtn3t2 = std::vector<int>(1+1);
xtn3t2[0] = 1;
xtn3t2[1] = 2;

/*  GF( 3 ^ 3 ) = GF( 27 ) */
xtn3t3 = std::vector<int>(1+2);
xtn3t3[0] = 2;
xtn3t3[1] = 0;
xtn3t3[2] = 1;

/*  GF( 3 ^ 4 ) = GF( 81 ) */
xtn3t4 = std::vector<int>(1+3);
xtn3t4[0] = 1;
xtn3t4[1] = 0;
xtn3t4[2] = 0;
xtn3t4[3] = 2;

/*  GF( 3 ^ 5 ) = GF( 243 ) */
xtn3t5 = std::vector<int>(1+4);
xtn3t5[0] = 2;
xtn3t5[1] = 0;
xtn3t5[2] = 2;
xtn3t5[3] = 0;
xtn3t5[4] = 2;

/*  GF( 3 ^ 6 ) = GF( 729 ) */
xtn3t6 = std::vector<int>(1+5);
xtn3t6[0] = 1;
xtn3t6[1] = 0;
xtn3t6[2] = 0;
xtn3t6[3] = 0;
xtn3t6[4] = 0;
xtn3t6[5] = 2;

/*  GF( 3 ^ 7 ) = GF( 2187 ) */
xtn3t7 = std::vector<int>(1+6);
xtn3t7[0] = 2;
xtn3t7[1] = 0;
xtn3t7[2] = 0;
xtn3t7[3] = 0;
xtn3t7[4] = 2;
xtn3t7[5] = 0;
xtn3t7[6] = 2;

/*  GF( 3 ^ 8 ) = GF( 6561 ) */
xtn3t8 = std::vector<int>(1+7);
xtn3t8[0] = 1;
xtn3t8[1] = 0;
xtn3t8[2] = 0;
xtn3t8[3] = 0;
xtn3t8[4] = 0;
xtn3t8[5] = 2;
xtn3t8[6] = 0;
xtn3t8[7] = 0;

/*  GF( 3 ^ 9 ) = GF( 19683 ) */
xtn3t9 = std::vector<int>(1+8);
xtn3t9[0] = 2;
xtn3t9[1] = 0;
xtn3t9[2] = 0;
xtn3t9[3] = 0;
xtn3t9[4] = 0;
xtn3t9[5] = 2;
xtn3t9[6] = 0;
xtn3t9[7] = 2;
xtn3t9[8] = 0;

/*  GF( 3 ^ 10 ) = GF( 59049 ) */
xtn3t10 = std::vector<int>(1+9);
xtn3t10[0] = 1;
xtn3t10[1] = 0;
xtn3t10[2] = 0;
xtn3t10[3] = 0;
xtn3t10[4] = 0;
xtn3t10[5] = 0;
xtn3t10[6] = 0;
xtn3t10[7] = 2;
xtn3t10[8] = 0;
xtn3t10[9] = 2;

/*  GF( 3 ^ 11 ) = GF( 177147 ) */
xtn3t11 = std::vector<int>(1+10);
xtn3t11[0] = 2;
xtn3t11[1] = 0;
xtn3t11[2] = 0;
xtn3t11[3] = 0;
xtn3t11[4] = 2;
xtn3t11[5] = 0;
xtn3t11[6] = 0;
xtn3t11[7] = 0;
xtn3t11[8] = 0;
xtn3t11[9] = 0;
xtn3t11[10] = 2;

/*  GF( 3 ^ 12 ) = GF( 531441 ) */
xtn3t12 = std::vector<int>(1+11);
xtn3t12[0] = 1;
xtn3t12[1] = 0;
xtn3t12[2] = 0;
xtn3t12[3] = 0;
xtn3t12[4] = 0;
xtn3t12[5] = 0;
xtn3t12[6] = 0;
xtn3t12[7] = 2;
xtn3t12[8] = 0;
xtn3t12[9] = 0;
xtn3t12[10] = 0;
xtn3t12[11] = 2;

/*  GF( 3 ^ 13 ) = GF( 1594323 ) */
xtn3t13 = std::vector<int>(1+12);
xtn3t13[0] = 2;
xtn3t13[1] = 0;
xtn3t13[2] = 0;
xtn3t13[3] = 0;
xtn3t13[4] = 0;
xtn3t13[5] = 0;
xtn3t13[6] = 2;
xtn3t13[7] = 0;
xtn3t13[8] = 0;
xtn3t13[9] = 0;
xtn3t13[10] = 0;
xtn3t13[11] = 0;
xtn3t13[12] = 2;

/*  GF( 3 ^ 14 ) = GF( 4782969 ) */
xtn3t14 = std::vector<int>(1+13);
xtn3t14[0] = 1;
xtn3t14[1] = 0;
xtn3t14[2] = 0;
xtn3t14[3] = 0;
xtn3t14[4] = 0;
xtn3t14[5] = 0;
xtn3t14[6] = 0;
xtn3t14[7] = 0;
xtn3t14[8] = 0;
xtn3t14[9] = 0;
xtn3t14[10] = 0;
xtn3t14[11] = 0;
xtn3t14[12] = 0;
xtn3t14[13] = 2;

/*  GF( 3 ^ 15 ) = GF( 14348907 ) */
xtn3t15 = std::vector<int>(1+14);
xtn3t15[0] = 2;
xtn3t15[1] = 0;
xtn3t15[2] = 0;
xtn3t15[3] = 0;
xtn3t15[4] = 2;
xtn3t15[5] = 0;
xtn3t15[6] = 0;
xtn3t15[7] = 0;
xtn3t15[8] = 0;
xtn3t15[9] = 0;
xtn3t15[10] = 0;
xtn3t15[11] = 0;
xtn3t15[12] = 0;
xtn3t15[13] = 0;
xtn3t15[14] = 2;

/*  GF( 3 ^ 16 ) = GF( 43046721 ) */
xtn3t16 = std::vector<int>(1+15);
xtn3t16[0] = 1;
xtn3t16[1] = 0;
xtn3t16[2] = 0;
xtn3t16[3] = 0;
xtn3t16[4] = 0;
xtn3t16[5] = 0;
xtn3t16[6] = 0;
xtn3t16[7] = 0;
xtn3t16[8] = 0;
xtn3t16[9] = 2;
xtn3t16[10] = 0;
xtn3t16[11] = 0;
xtn3t16[12] = 0;
xtn3t16[13] = 0;
xtn3t16[14] = 0;
xtn3t16[15] = 0;

/*  GF( 3 ^ 17 ) = GF( 129140163 ) */
xtn3t17 = std::vector<int>(1+16);
xtn3t17[0] = 2;
xtn3t17[1] = 0;
xtn3t17[2] = 0;
xtn3t17[3] = 0;
xtn3t17[4] = 0;
xtn3t17[5] = 0;
xtn3t17[6] = 0;
xtn3t17[7] = 0;
xtn3t17[8] = 2;
xtn3t17[9] = 0;
xtn3t17[10] = 0;
xtn3t17[11] = 0;
xtn3t17[12] = 0;
xtn3t17[13] = 0;
xtn3t17[14] = 0;
xtn3t17[15] = 0;
xtn3t17[16] = 2;

/*  GF( 3 ^ 18 ) = GF( 387420489 ) */
xtn3t18 = std::vector<int>(1+17);
xtn3t18[0] = 1;
xtn3t18[1] = 0;
xtn3t18[2] = 0;
xtn3t18[3] = 0;
xtn3t18[4] = 0;
xtn3t18[5] = 2;
xtn3t18[6] = 0;
xtn3t18[7] = 0;
xtn3t18[8] = 0;
xtn3t18[9] = 0;
xtn3t18[10] = 0;
xtn3t18[11] = 0;
xtn3t18[12] = 0;
xtn3t18[13] = 0;
xtn3t18[14] = 0;
xtn3t18[15] = 0;
xtn3t18[16] = 0;
xtn3t18[17] = 2;

/*  GF( 5 ^ 2 ) = GF( 25 ) */
xtn5t2 = std::vector<int>(1+1);
xtn5t2[0] = 3;
xtn5t2[1] = 4;

/*  GF( 5 ^ 3 ) = GF( 125 ) */
xtn5t3 = std::vector<int>(1+2);
xtn5t3[0] = 3;
xtn5t3[1] = 0;
xtn5t3[2] = 4;

/*  GF( 5 ^ 4 ) = GF( 625 ) */
xtn5t4 = std::vector<int>(1+3);
xtn5t4[0] = 2;
xtn5t4[1] = 4;
xtn5t4[2] = 0;
xtn5t4[3] = 4;

/*  GF( 5 ^ 5 ) = GF( 3125 ) */
xtn5t5 = std::vector<int>(1+4);
xtn5t5[0] = 3;
xtn5t5[1] = 0;
xtn5t5[2] = 4;
xtn5t5[3] = 0;
xtn5t5[4] = 0;

/*  GF( 5 ^ 6 ) = GF( 15625 ) */
xtn5t6 = std::vector<int>(1+5);
xtn5t6[0] = 3;
xtn5t6[1] = 0;
xtn5t6[2] = 0;
xtn5t6[3] = 0;
xtn5t6[4] = 0;
xtn5t6[5] = 4;

/*  GF( 5 ^ 7 ) = GF( 78125 ) */
xtn5t7 = std::vector<int>(1+6);
xtn5t7[0] = 3;
xtn5t7[1] = 0;
xtn5t7[2] = 0;
xtn5t7[3] = 0;
xtn5t7[4] = 0;
xtn5t7[5] = 0;
xtn5t7[6] = 4;

/*  GF( 5 ^ 8 ) = GF( 390625 ) */
xtn5t8 = std::vector<int>(1+7);
xtn5t8[0] = 2;
xtn5t8[1] = 0;
xtn5t8[2] = 0;
xtn5t8[3] = 4;
xtn5t8[4] = 0;
xtn5t8[5] = 4;
xtn5t8[6] = 0;
xtn5t8[7] = 0;

/*  GF( 5 ^ 9 ) = GF( 1953125 ) */
xtn5t9 = std::vector<int>(1+8);
xtn5t9[0] = 2;
xtn5t9[1] = 0;
xtn5t9[2] = 0;
xtn5t9[3] = 0;
xtn5t9[4] = 0;
xtn5t9[5] = 0;
xtn5t9[6] = 4;
xtn5t9[7] = 4;
xtn5t9[8] = 0;

/*  GF( 5 ^ 10 ) = GF( 9765625 ) */
xtn5t10 = std::vector<int>(1+9);
xtn5t10[0] = 2;
xtn5t10[1] = 0;
xtn5t10[2] = 0;
xtn5t10[3] = 0;
xtn5t10[4] = 0;
xtn5t10[5] = 0;
xtn5t10[6] = 0;
xtn5t10[7] = 4;
xtn5t10[8] = 0;
xtn5t10[9] = 4;

/*  GF( 5 ^ 11 ) = GF( 48828125 ) */
xtn5t11 = std::vector<int>(1+10);
xtn5t11[0] = 3;
xtn5t11[1] = 0;
xtn5t11[2] = 0;
xtn5t11[3] = 0;
xtn5t11[4] = 0;
xtn5t11[5] = 0;
xtn5t11[6] = 0;
xtn5t11[7] = 0;
xtn5t11[8] = 0;
xtn5t11[9] = 0;
xtn5t11[10] = 4;

/*  GF( 5 ^ 12 ) = GF( 244140625 ) */
xtn5t12 = std::vector<int>(1+11);
xtn5t12[0] = 2;
xtn5t12[1] = 0;
xtn5t12[2] = 0;
xtn5t12[3] = 0;
xtn5t12[4] = 4;
xtn5t12[5] = 0;
xtn5t12[6] = 0;
xtn5t12[7] = 4;
xtn5t12[8] = 0;
xtn5t12[9] = 0;
xtn5t12[10] = 0;
xtn5t12[11] = 0;

/*  GF( 7 ^ 2 ) = GF( 49 ) */
xtn7t2 = std::vector<int>(1+1);
xtn7t2[0] = 4;
xtn7t2[1] = 6;

/*  GF( 7 ^ 3 ) = GF( 343 ) */
xtn7t3 = std::vector<int>(1+2);
xtn7t3[0] = 5;
xtn7t3[1] = 6;
xtn7t3[2] = 6;

/*  GF( 7 ^ 4 ) = GF( 2401 ) */
xtn7t4 = std::vector<int>(1+3);
xtn7t4[0] = 4;
xtn7t4[1] = 0;
xtn7t4[2] = 6;
xtn7t4[3] = 6;

/*  GF( 7 ^ 5 ) = GF( 16807 ) */
xtn7t5 = std::vector<int>(1+4);
xtn7t5[0] = 3;
xtn7t5[1] = 0;
xtn7t5[2] = 0;
xtn7t5[3] = 0;
xtn7t5[4] = 6;

/*  GF( 7 ^ 6 ) = GF( 117649 ) */
xtn7t6 = std::vector<int>(1+5);
xtn7t6[0] = 4;
xtn7t6[1] = 0;
xtn7t6[2] = 0;
xtn7t6[3] = 0;
xtn7t6[4] = 6;
xtn7t6[5] = 6;

/*  GF( 7 ^ 7 ) = GF( 823543 ) */
xtn7t7 = std::vector<int>(1+6);
xtn7t7[0] = 3;
xtn7t7[1] = 0;
xtn7t7[2] = 0;
xtn7t7[3] = 0;
xtn7t7[4] = 0;
xtn7t7[5] = 6;
xtn7t7[6] = 0;

/*  GF( 7 ^ 8 ) = GF( 5764801 ) */
xtn7t8 = std::vector<int>(1+7);
xtn7t8[0] = 4;
xtn7t8[1] = 0;
xtn7t8[2] = 0;
xtn7t8[3] = 0;
xtn7t8[4] = 0;
xtn7t8[5] = 0;
xtn7t8[6] = 0;
xtn7t8[7] = 6;

/*  GF( 7 ^ 9 ) = GF( 40353607 ) */
xtn7t9 = std::vector<int>(1+8);
xtn7t9[0] = 5;
xtn7t9[1] = 0;
xtn7t9[2] = 0;
xtn7t9[3] = 6;
xtn7t9[4] = 0;
xtn7t9[5] = 0;
xtn7t9[6] = 0;
xtn7t9[7] = 0;
xtn7t9[8] = 6;

/*  GF( 7 ^ 10 ) = GF( 282475249 ) */
xtn7t10 = std::vector<int>(1+9);
xtn7t10[0] = 4;
xtn7t10[1] = 0;
xtn7t10[2] = 0;
xtn7t10[3] = 0;
xtn7t10[4] = 0;
xtn7t10[5] = 0;
xtn7t10[6] = 0;
xtn7t10[7] = 0;
xtn7t10[8] = 6;
xtn7t10[9] = 6;

/*  GF( 11 ^ 2 ) = GF( 121 ) */
xtn11t2 = std::vector<int>(1+1);
xtn11t2[0] = 4;
xtn11t2[1] = 10;

/*  GF( 11 ^ 3 ) = GF( 1331 ) */
xtn11t3 = std::vector<int>(1+2);
xtn11t3[0] = 6;
xtn11t3[1] = 0;
xtn11t3[2] = 10;

/*  GF( 11 ^ 4 ) = GF( 14641 ) */
xtn11t4 = std::vector<int>(1+3);
xtn11t4[0] = 9;
xtn11t4[1] = 10;
xtn11t4[2] = 0;
xtn11t4[3] = 0;

/*  GF( 11 ^ 5 ) = GF( 161051 ) */
xtn11t5 = std::vector<int>(1+4);
xtn11t5[0] = 2;
xtn11t5[1] = 0;
xtn11t5[2] = 10;
xtn11t5[3] = 10;
xtn11t5[4] = 0;

/*  GF( 11 ^ 6 ) = GF( 1771561 ) */
xtn11t6 = std::vector<int>(1+5);
xtn11t6[0] = 4;
xtn11t6[1] = 10;
xtn11t6[2] = 0;
xtn11t6[3] = 0;
xtn11t6[4] = 0;
xtn11t6[5] = 10;

/*  GF( 11 ^ 7 ) = GF( 19487171 ) */
xtn11t7 = std::vector<int>(1+6);
xtn11t7[0] = 6;
xtn11t7[1] = 0;
xtn11t7[2] = 0;
xtn11t7[3] = 0;
xtn11t7[4] = 0;
xtn11t7[5] = 0;
xtn11t7[6] = 10;

/*  GF( 11 ^ 8 ) = GF( 214358881 ) */
xtn11t8 = std::vector<int>(1+7);
xtn11t8[0] = 9;
xtn11t8[1] = 10;
xtn11t8[2] = 0;
xtn11t8[3] = 0;
xtn11t8[4] = 10;
xtn11t8[5] = 0;
xtn11t8[6] = 0;
xtn11t8[7] = 0;

/*  GF( 13 ^ 2 ) = GF( 169 ) */
xtn13t2 = std::vector<int>(1+1);
xtn13t2[0] = 11;
xtn13t2[1] = 12;

/*  GF( 13 ^ 3 ) = GF( 2197 ) */
xtn13t3 = std::vector<int>(1+2);
xtn13t3[0] = 6;
xtn13t3[1] = 0;
xtn13t3[2] = 12;

/*  GF( 13 ^ 4 ) = GF( 28561 ) */
xtn13t4 = std::vector<int>(1+3);
xtn13t4[0] = 11;
xtn13t4[1] = 12;
xtn13t4[2] = 0;
xtn13t4[3] = 12;

/*  GF( 13 ^ 5 ) = GF( 371293 ) */
xtn13t5 = std::vector<int>(1+4);
xtn13t5[0] = 2;
xtn13t5[1] = 12;
xtn13t5[2] = 0;
xtn13t5[3] = 12;
xtn13t5[4] = 0;

/*  GF( 13 ^ 6 ) = GF( 4826809 ) */
xtn13t6 = std::vector<int>(1+5);
xtn13t6[0] = 7;
xtn13t6[1] = 0;
xtn13t6[2] = 0;
xtn13t6[3] = 12;
xtn13t6[4] = 0;
xtn13t6[5] = 12;

/*  GF( 13 ^ 7 ) = GF( 62748517 ) */
xtn13t7 = std::vector<int>(1+6);
xtn13t7[0] = 7;
xtn13t7[1] = 0;
xtn13t7[2] = 0;
xtn13t7[3] = 0;
xtn13t7[4] = 12;
xtn13t7[5] = 0;
xtn13t7[6] = 0;

/*  GF( 13 ^ 8 ) = GF( 815730721 ) */
xtn13t8 = std::vector<int>(1+7);
xtn13t8[0] = 11;
xtn13t8[1] = 0;
xtn13t8[2] = 0;
xtn13t8[3] = 0;
xtn13t8[4] = 0;
xtn13t8[5] = 12;
xtn13t8[6] = 12;
xtn13t8[7] = 0;

/*  GF( 17 ^ 2 ) = GF( 289 ) */
xtn17t2 = std::vector<int>(1+1);
xtn17t2[0] = 14;
xtn17t2[1] = 16;

/*  GF( 17 ^ 3 ) = GF( 4913 ) */
xtn17t3 = std::vector<int>(1+2);
xtn17t3[0] = 3;
xtn17t3[1] = 16;
xtn17t3[2] = 0;

/*  GF( 17 ^ 4 ) = GF( 83521 ) */
xtn17t4 = std::vector<int>(1+3);
xtn17t4[0] = 12;
xtn17t4[1] = 0;
xtn17t4[2] = 0;
xtn17t4[3] = 16;

/*  GF( 17 ^ 5 ) = GF( 1419857 ) */
xtn17t5 = std::vector<int>(1+4);
xtn17t5[0] = 3;
xtn17t5[1] = 0;
xtn17t5[2] = 0;
xtn17t5[3] = 0;
xtn17t5[4] = 16;

/*  GF( 17 ^ 6 ) = GF( 24137569 ) */
xtn17t6 = std::vector<int>(1+5);
xtn17t6[0] = 14;
xtn17t6[1] = 0;
xtn17t6[2] = 0;
xtn17t6[3] = 0;
xtn17t6[4] = 0;
xtn17t6[5] = 16;

/*  GF( 17 ^ 7 ) = GF( 410338673 ) */
xtn17t7 = std::vector<int>(1+6);
xtn17t7[0] = 3;
xtn17t7[1] = 0;
xtn17t7[2] = 0;
xtn17t7[3] = 16;
xtn17t7[4] = 0;
xtn17t7[5] = 0;
xtn17t7[6] = 0;

/*  GF( 19 ^ 2 ) = GF( 361 ) */
xtn19t2 = std::vector<int>(1+1);
xtn19t2[0] = 17;
xtn19t2[1] = 18;

/*  GF( 19 ^ 3 ) = GF( 6859 ) */
xtn19t3 = std::vector<int>(1+2);
xtn19t3[0] = 3;
xtn19t3[1] = 0;
xtn19t3[2] = 18;

/*  GF( 19 ^ 4 ) = GF( 130321 ) */
xtn19t4 = std::vector<int>(1+3);
xtn19t4[0] = 17;
xtn19t4[1] = 0;
xtn19t4[2] = 0;
xtn19t4[3] = 18;

/*  GF( 19 ^ 5 ) = GF( 2476099 ) */
xtn19t5 = std::vector<int>(1+4);
xtn19t5[0] = 3;
xtn19t5[1] = 18;
xtn19t5[2] = 0;
xtn19t5[3] = 0;
xtn19t5[4] = 0;

/*  GF( 19 ^ 6 ) = GF( 47045881 ) */
xtn19t6 = std::vector<int>(1+5);
xtn19t6[0] = 16;
xtn19t6[1] = 18;
xtn19t6[2] = 0;
xtn19t6[3] = 0;
xtn19t6[4] = 0;
xtn19t6[5] = 0;

/*  GF( 19 ^ 7 ) = GF( 893871739 ) */
xtn19t7 = std::vector<int>(1+6);
xtn19t7[0] = 10;
xtn19t7[1] = 0;
xtn19t7[2] = 0;
xtn19t7[3] = 0;
xtn19t7[4] = 0;
xtn19t7[5] = 18;
xtn19t7[6] = 0;

/*  GF( 23 ^ 2 ) = GF( 529 ) */
xtn23t2 = std::vector<int>(1+1);
xtn23t2[0] = 16;
xtn23t2[1] = 22;

/*  GF( 23 ^ 3 ) = GF( 12167 ) */
xtn23t3 = std::vector<int>(1+2);
xtn23t3[0] = 7;
xtn23t3[1] = 0;
xtn23t3[2] = 22;

/*  GF( 23 ^ 4 ) = GF( 279841 ) */
xtn23t4 = std::vector<int>(1+3);
xtn23t4[0] = 12;
xtn23t4[1] = 22;
xtn23t4[2] = 0;
xtn23t4[3] = 0;

/*  GF( 23 ^ 5 ) = GF( 6436343 ) */
xtn23t5 = std::vector<int>(1+4);
xtn23t5[0] = 5;
xtn23t5[1] = 0;
xtn23t5[2] = 0;
xtn23t5[3] = 0;
xtn23t5[4] = 22;

/*  GF( 23 ^ 6 ) = GF( 148035889 ) */
xtn23t6 = std::vector<int>(1+5);
xtn23t6[0] = 16;
xtn23t6[1] = 0;
xtn23t6[2] = 0;
xtn23t6[3] = 0;
xtn23t6[4] = 0;
xtn23t6[5] = 22;

/*  GF( 29 ^ 2 ) = GF( 841 ) */
xtn29t2 = std::vector<int>(1+1);
xtn29t2[0] = 26;
xtn29t2[1] = 28;

/*  GF( 29 ^ 3 ) = GF( 24389 ) */
xtn29t3 = std::vector<int>(1+2);
xtn29t3[0] = 11;
xtn29t3[1] = 28;
xtn29t3[2] = 0;

/*  GF( 29 ^ 4 ) = GF( 707281 ) */
xtn29t4 = std::vector<int>(1+3);
xtn29t4[0] = 27;
xtn29t4[1] = 0;
xtn29t4[2] = 0;
xtn29t4[3] = 28;

/*  GF( 29 ^ 5 ) = GF( 20511149 ) */
xtn29t5 = std::vector<int>(1+4);
xtn29t5[0] = 3;
xtn29t5[1] = 0;
xtn29t5[2] = 0;
xtn29t5[3] = 28;
xtn29t5[4] = 0;

/*  GF( 29 ^ 6 ) = GF( 594823321 ) */
xtn29t6 = std::vector<int>(1+5);
xtn29t6[0] = 26;
xtn29t6[1] = 28;
xtn29t6[2] = 0;
xtn29t6[3] = 0;
xtn29t6[4] = 0;
xtn29t6[5] = 0;

/*  GF( 31 ^ 2 ) = GF( 961 ) */
xtn31t2 = std::vector<int>(1+1);
xtn31t2[0] = 19;
xtn31t2[1] = 30;

/*  GF( 31 ^ 3 ) = GF( 29791 ) */
xtn31t3 = std::vector<int>(1+2);
xtn31t3[0] = 3;
xtn31t3[1] = 30;
xtn31t3[2] = 0;

/*  GF( 31 ^ 4 ) = GF( 923521 ) */
xtn31t4 = std::vector<int>(1+3);
xtn31t4[0] = 18;
xtn31t4[1] = 0;
xtn31t4[2] = 0;
xtn31t4[3] = 30;

/*  GF( 31 ^ 5 ) = GF( 28629151 ) */
xtn31t5 = std::vector<int>(1+4);
xtn31t5[0] = 11;
xtn31t5[1] = 0;
xtn31t5[2] = 0;
xtn31t5[3] = 30;
xtn31t5[4] = 0;

/*  GF( 31 ^ 6 ) = GF( 887503681 ) */
xtn31t6 = std::vector<int>(1+5);
xtn31t6[0] = 19;
xtn31t6[1] = 0;
xtn31t6[2] = 0;
xtn31t6[3] = 0;
xtn31t6[4] = 0;
xtn31t6[5] = 30;

/*  GF( 37 ^ 2 ) = GF( 1369 ) */
xtn37t2 = std::vector<int>(1+1);
xtn37t2[0] = 32;
xtn37t2[1] = 36;

/*  GF( 37 ^ 3 ) = GF( 50653 ) */
xtn37t3 = std::vector<int>(1+2);
xtn37t3[0] = 13;
xtn37t3[1] = 0;
xtn37t3[2] = 36;

/*  GF( 37 ^ 4 ) = GF( 1874161 ) */
xtn37t4 = std::vector<int>(1+3);
xtn37t4[0] = 35;
xtn37t4[1] = 36;
xtn37t4[2] = 0;
xtn37t4[3] = 0;

/*  GF( 37 ^ 5 ) = GF( 69343957 ) */
xtn37t5 = std::vector<int>(1+4);
xtn37t5[0] = 5;
xtn37t5[1] = 36;
xtn37t5[2] = 0;
xtn37t5[3] = 0;
xtn37t5[4] = 0;

/*  GF( 41 ^ 2 ) = GF( 1681 ) */
xtn41t2 = std::vector<int>(1+1);
xtn41t2[0] = 29;
xtn41t2[1] = 40;

/*  GF( 41 ^ 3 ) = GF( 68921 ) */
xtn41t3 = std::vector<int>(1+2);
xtn41t3[0] = 6;
xtn41t3[1] = 40;
xtn41t3[2] = 0;

/*  GF( 41 ^ 4 ) = GF( 2825761 ) */
xtn41t4 = std::vector<int>(1+3);
xtn41t4[0] = 24;
xtn41t4[1] = 40;
xtn41t4[2] = 0;
xtn41t4[3] = 0;

/*  GF( 41 ^ 5 ) = GF( 115856201 ) */
xtn41t5 = std::vector<int>(1+4);
xtn41t5[0] = 6;
xtn41t5[1] = 0;
xtn41t5[2] = 0;
xtn41t5[3] = 0;
xtn41t5[4] = 40;

/*  GF( 43 ^ 2 ) = GF( 1849 ) */
xtn43t2 = std::vector<int>(1+1);
xtn43t2[0] = 40;
xtn43t2[1] = 42;

/*  GF( 43 ^ 3 ) = GF( 79507 ) */
xtn43t3 = std::vector<int>(1+2);
xtn43t3[0] = 3;
xtn43t3[1] = 42;
xtn43t3[2] = 0;

/*  GF( 43 ^ 4 ) = GF( 3418801 ) */
xtn43t4 = std::vector<int>(1+3);
xtn43t4[0] = 23;
xtn43t4[1] = 42;
xtn43t4[2] = 0;
xtn43t4[3] = 0;

/*  GF( 43 ^ 5 ) = GF( 147008443 ) */
xtn43t5 = std::vector<int>(1+4);
xtn43t5[0] = 3;
xtn43t5[1] = 0;
xtn43t5[2] = 0;
xtn43t5[3] = 0;
xtn43t5[4] = 42;

/*  GF( 47 ^ 2 ) = GF( 2209 ) */
xtn47t2 = std::vector<int>(1+1);
xtn47t2[0] = 34;
xtn47t2[1] = 46;

/*  GF( 47 ^ 3 ) = GF( 103823 ) */
xtn47t3 = std::vector<int>(1+2);
xtn47t3[0] = 5;
xtn47t3[1] = 0;
xtn47t3[2] = 46;

/*  GF( 47 ^ 4 ) = GF( 4879681 ) */
xtn47t4 = std::vector<int>(1+3);
xtn47t4[0] = 42;
xtn47t4[1] = 0;
xtn47t4[2] = 0;
xtn47t4[3] = 46;

/*  GF( 47 ^ 5 ) = GF( 229345007 ) */
xtn47t5 = std::vector<int>(1+4);
xtn47t5[0] = 5;
xtn47t5[1] = 46;
xtn47t5[2] = 0;
xtn47t5[3] = 0;
xtn47t5[4] = 0;

#endif
