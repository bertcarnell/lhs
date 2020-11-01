/*
 * NOTE: This file should be excluded from the Doxygen build
 ****** COMPUTER GENERATED etc/CreatePowerCylce.R ******
 *
 * file xtn.h
 * author Robert Carnell
 * copyright Copyright (c) 2020, Robert Carnell
 *
 * License:  MIT
 *
 * Reference:
 * <ul><li><a href="http://lib.stat.cmu.edu/designs/">Statlib Designs</a></li>
 * <li><a href="http://lib.stat.cmu.edu/designs/oa.c">Owen's Orthogonal Array Algorithms</a></li></ul>
 * 
 * This file is derived from the xtndispatch.h xtnset.h xtndeclare.h
 * See Table B.3 Power cycle II pg 316 in Block Designs:  A Randomization Approach
 */

#ifndef XTN_H
#define XTN_H

// GF(2^2) = GF(4)
// x^2 = 1 + x
if (q == primes::ipow(2,2)) xtn = {1, 1};
// GF(2^3) = GF(8)
// x^3 = 1 + x^2
else if (q == primes::ipow(2,3)) xtn = {1, 0, 1};
// GF(2^4) = GF(16)
// x^4 = 1 + x^3
else if (q == primes::ipow(2,4)) xtn = {1, 0, 0, 1};
// GF(2^5) = GF(32)
// x^5 = 1 + x^3
else if (q == primes::ipow(2,5)) xtn = {1, 0, 0, 1, 0};
// GF(2^6) = GF(64)
// x^6 = 1 + x^5
else if (q == primes::ipow(2,6)) xtn = {1, 0, 0, 0, 0, 1};
// GF(2^7) = GF(128)
// x^7 = 1 + x^6
else if (q == primes::ipow(2,7)) xtn = {1, 0, 0, 0, 0, 0, 1};
// GF(2^8) = GF(256)
// x^8 = 1 + x^4 + x^5 + x^6
else if (q == primes::ipow(2,8)) xtn = {1, 0, 0, 0, 1, 1, 1, 0};
// GF(2^9) = GF(512)
// x^9 = 1 + x^5
else if (q == primes::ipow(2,9)) xtn = {1, 0, 0, 0, 0, 1, 0, 0, 0};
// GF(2^10) = GF(1024)
// x^10 = 1 + x^7
else if (q == primes::ipow(2,10)) xtn = {1, 0, 0, 0, 0, 0, 0, 1, 0, 0};
// GF(2^11) = GF(2048)
// x^11 = 1 + x^9
else if (q == primes::ipow(2,11)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
// GF(2^12) = GF(4096)
// x^12 = 1 + x^4 + x^10 + x^11
else if (q == primes::ipow(2,12)) xtn = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1};
// GF(2^13) = GF(8192)
// x^13 = 1 + x^8 + x^11 + x^12
else if (q == primes::ipow(2,13)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1};
// GF(2^14) = GF(16384)
// x^14 = 1 + x^2 + x^12 + x^13
else if (q == primes::ipow(2,14)) xtn = {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
// GF(2^15) = GF(32768)
// x^15 = 1 + x^14
else if (q == primes::ipow(2,15)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
// GF(2^16) = GF(65536)
// x^16 = 1 + x^4 + x^13 + x^15
else if (q == primes::ipow(2,16)) xtn = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1};
// GF(2^17) = GF(131072)
// x^17 = 1 + x^14
else if (q == primes::ipow(2,17)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
// GF(2^18) = GF(262144)
// x^18 = 1 + x^11
else if (q == primes::ipow(2,18)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
// GF(2^19) = GF(524288)
// x^19 = 1 + x^14 + x^17 + x^18
else if (q == primes::ipow(2,19)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1};
// GF(2^20) = GF(1048576)
// x^20 = 1 + x^17
else if (q == primes::ipow(2,20)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
// GF(2^21) = GF(2097152)
// x^21 = 1 + x^19
else if (q == primes::ipow(2,21)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
// GF(2^22) = GF(4194304)
// x^22 = 1 + x^21
else if (q == primes::ipow(2,22)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
// GF(2^23) = GF(8388608)
// x^23 = 1 + x^18
else if (q == primes::ipow(2,23)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
// GF(2^24) = GF(16777216)
// x^24 = 1 + x^17 + x^22 + x^23
else if (q == primes::ipow(2,24)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1};
// GF(2^25) = GF(33554432)
// x^25 = 1 + x^22
else if (q == primes::ipow(2,25)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
// GF(2^26) = GF(67108864)
// x^26 = 1 + x^20 + x^24 + x^25
else if (q == primes::ipow(2,26)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1};
// GF(2^27) = GF(134217728)
// x^27 = 1 + x^22 + x^25 + x^26
else if (q == primes::ipow(2,27)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1};
// GF(2^28) = GF(268435456)
// x^28 = 1 + x^25
else if (q == primes::ipow(2,28)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
// GF(2^29) = GF(536870912)
// x^29 = 1 + x^27
else if (q == primes::ipow(2,29)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
// GF(3^2) = GF(9)
// x^2 = 1 + 2x
else if (q == primes::ipow(3,2)) xtn = {1, 2};
// GF(3^3) = GF(27)
// x^3 = 2 + x^2
else if (q == primes::ipow(3,3)) xtn = {2, 0, 1};
// GF(3^4) = GF(81)
// x^4 = 1 + 2x^3
else if (q == primes::ipow(3,4)) xtn = {1, 0, 0, 2};
// GF(3^5) = GF(243)
// x^5 = 2 + 2x^2 + 2x^4
else if (q == primes::ipow(3,5)) xtn = {2, 0, 2, 0, 2};
// GF(3^6) = GF(729)
// x^6 = 1 + 2x^5
else if (q == primes::ipow(3,6)) xtn = {1, 0, 0, 0, 0, 2};
// GF(3^7) = GF(2187)
// x^7 = 2 + 2x^4 + 2x^6
else if (q == primes::ipow(3,7)) xtn = {2, 0, 0, 0, 2, 0, 2};
// GF(3^8) = GF(6561)
// x^8 = 1 + 2x^5
else if (q == primes::ipow(3,8)) xtn = {1, 0, 0, 0, 0, 2, 0, 0};
// GF(3^9) = GF(19683)
// x^9 = 2 + 2x^5 + 2x^7
else if (q == primes::ipow(3,9)) xtn = {2, 0, 0, 0, 0, 2, 0, 2, 0};
// GF(3^10) = GF(59049)
// x^10 = 1 + 2x^7 + 2x^9
else if (q == primes::ipow(3,10)) xtn = {1, 0, 0, 0, 0, 0, 0, 2, 0, 2};
// GF(3^11) = GF(177147)
// x^11 = 2 + 2x^4 + 2x^10
else if (q == primes::ipow(3,11)) xtn = {2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2};
// GF(3^12) = GF(531441)
// x^12 = 1 + 2x^7 + 2x^11
else if (q == primes::ipow(3,12)) xtn = {1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2};
// GF(3^13) = GF(1594323)
// x^13 = 2 + 2x^6 + 2x^12
else if (q == primes::ipow(3,13)) xtn = {2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2};
// GF(3^14) = GF(4782969)
// x^14 = 1 + 2x^13
else if (q == primes::ipow(3,14)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2};
// GF(3^15) = GF(14348907)
// x^15 = 2 + 2x^4 + 2x^14
else if (q == primes::ipow(3,15)) xtn = {2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2};
// GF(3^16) = GF(43046721)
// x^16 = 1 + 2x^9
else if (q == primes::ipow(3,16)) xtn = {1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0};
// GF(3^17) = GF(129140163)
// x^17 = 2 + 2x^8 + 2x^16
else if (q == primes::ipow(3,17)) xtn = {2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2};
// GF(3^18) = GF(387420489)
// x^18 = 1 + 2x^5 + 2x^17
else if (q == primes::ipow(3,18)) xtn = {1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2};
// GF(5^2) = GF(25)
// x^2 = 3 + 4x
else if (q == primes::ipow(5,2)) xtn = {3, 4};
// GF(5^3) = GF(125)
// x^3 = 3 + 4x^2
else if (q == primes::ipow(5,3)) xtn = {3, 0, 4};
// GF(5^4) = GF(625)
// x^4 = 2 + 4x + 4x^3
else if (q == primes::ipow(5,4)) xtn = {2, 4, 0, 4};
// GF(5^5) = GF(3125)
// x^5 = 3 + 4x^2
else if (q == primes::ipow(5,5)) xtn = {3, 0, 4, 0, 0};
// GF(5^6) = GF(15625)
// x^6 = 3 + 4x^5
else if (q == primes::ipow(5,6)) xtn = {3, 0, 0, 0, 0, 4};
// GF(5^7) = GF(78125)
// x^7 = 3 + 4x^6
else if (q == primes::ipow(5,7)) xtn = {3, 0, 0, 0, 0, 0, 4};
// GF(5^8) = GF(390625)
// x^8 = 2 + 4x^3 + 4x^5
else if (q == primes::ipow(5,8)) xtn = {2, 0, 0, 4, 0, 4, 0, 0};
// GF(5^9) = GF(1953125)
// x^9 = 2 + 4x^6 + 4x^7
else if (q == primes::ipow(5,9)) xtn = {2, 0, 0, 0, 0, 0, 4, 4, 0};
// GF(5^10) = GF(9765625)
// x^10 = 2 + 4x^7 + 4x^9
else if (q == primes::ipow(5,10)) xtn = {2, 0, 0, 0, 0, 0, 0, 4, 0, 4};
// GF(5^11) = GF(48828125)
// x^11 = 3 + 4x^10
else if (q == primes::ipow(5,11)) xtn = {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4};
// GF(5^12) = GF(244140625)
// x^12 = 2 + 4x^4 + 4x^7
else if (q == primes::ipow(5,12)) xtn = {2, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 0};
// GF(7^2) = GF(49)
// x^2 = 4 + 6x
else if (q == primes::ipow(7,2)) xtn = {4, 6};
// GF(7^3) = GF(343)
// x^3 = 5 + 6x + 6x^2
else if (q == primes::ipow(7,3)) xtn = {5, 6, 6};
// GF(7^4) = GF(2401)
// x^4 = 4 + 6x^2 + 6x^3
else if (q == primes::ipow(7,4)) xtn = {4, 0, 6, 6};
// GF(7^5) = GF(16807)
// x^5 = 3 + 6x^4
else if (q == primes::ipow(7,5)) xtn = {3, 0, 0, 0, 6};
// GF(7^6) = GF(117649)
// x^6 = 4 + 6x^4 + 6x^5
else if (q == primes::ipow(7,6)) xtn = {4, 0, 0, 0, 6, 6};
// GF(7^7) = GF(823543)
// x^7 = 3 + 6x^5
else if (q == primes::ipow(7,7)) xtn = {3, 0, 0, 0, 0, 6, 0};
// GF(7^8) = GF(5764801)
// x^8 = 4 + 6x^7
else if (q == primes::ipow(7,8)) xtn = {4, 0, 0, 0, 0, 0, 0, 6};
// GF(7^9) = GF(40353607)
// x^9 = 5 + 6x^3 + 6x^8
else if (q == primes::ipow(7,9)) xtn = {5, 0, 0, 6, 0, 0, 0, 0, 6};
// GF(7^10) = GF(282475249)
// x^10 = 4 + 6x^8 + 6x^9
else if (q == primes::ipow(7,10)) xtn = {4, 0, 0, 0, 0, 0, 0, 0, 6, 6};
// GF(11^2) = GF(121)
// x^2 = 4 + 10x
else if (q == primes::ipow(11,2)) xtn = {4, 10};
// GF(11^3) = GF(1331)
// x^3 = 6 + 10x^2
else if (q == primes::ipow(11,3)) xtn = {6, 0, 10};
// GF(11^4) = GF(14641)
// x^4 = 9 + 10x
else if (q == primes::ipow(11,4)) xtn = {9, 10, 0, 0};
// GF(11^5) = GF(161051)
// x^5 = 2 + 10x^2 + 10x^3
else if (q == primes::ipow(11,5)) xtn = {2, 0, 10, 10, 0};
// GF(11^6) = GF(1771561)
// x^6 = 4 + 10x + 10x^5
else if (q == primes::ipow(11,6)) xtn = {4, 10, 0, 0, 0, 10};
// GF(11^7) = GF(19487171)
// x^7 = 6 + 10x^6
else if (q == primes::ipow(11,7)) xtn = {6, 0, 0, 0, 0, 0, 10};
// GF(11^8) = GF(214358881)
// x^8 = 9 + 10x + 10x^4
else if (q == primes::ipow(11,8)) xtn = {9, 10, 0, 0, 10, 0, 0, 0};
// GF(13^2) = GF(169)
// x^2 = 11 + 12x
else if (q == primes::ipow(13,2)) xtn = {11, 12};
// GF(13^3) = GF(2197)
// x^3 = 6 + 12x^2
else if (q == primes::ipow(13,3)) xtn = {6, 0, 12};
// GF(13^4) = GF(28561)
// x^4 = 11 + 12x + 12x^3
else if (q == primes::ipow(13,4)) xtn = {11, 12, 0, 12};
// GF(13^5) = GF(371293)
// x^5 = 2 + 12x + 12x^3
else if (q == primes::ipow(13,5)) xtn = {2, 12, 0, 12, 0};
// GF(13^6) = GF(4826809)
// x^6 = 7 + 12x^3 + 12x^5
else if (q == primes::ipow(13,6)) xtn = {7, 0, 0, 12, 0, 12};
// GF(13^7) = GF(62748517)
// x^7 = 7 + 12x^4
else if (q == primes::ipow(13,7)) xtn = {7, 0, 0, 0, 12, 0, 0};
// GF(13^8) = GF(815730721)
// x^8 = 11 + 12x^5 + 12x^6
else if (q == primes::ipow(13,8)) xtn = {11, 0, 0, 0, 0, 12, 12, 0};
// GF(17^2) = GF(289)
// x^2 = 14 + 16x
else if (q == primes::ipow(17,2)) xtn = {14, 16};
// GF(17^3) = GF(4913)
// x^3 = 3 + 16x
else if (q == primes::ipow(17,3)) xtn = {3, 16, 0};
// GF(17^4) = GF(83521)
// x^4 = 12 + 16x^3
else if (q == primes::ipow(17,4)) xtn = {12, 0, 0, 16};
// GF(17^5) = GF(1419857)
// x^5 = 3 + 16x^4
else if (q == primes::ipow(17,5)) xtn = {3, 0, 0, 0, 16};
// GF(17^6) = GF(24137569)
// x^6 = 14 + 16x^5
else if (q == primes::ipow(17,6)) xtn = {14, 0, 0, 0, 0, 16};
// GF(17^7) = GF(410338673)
// x^7 = 3 + 16x^3
else if (q == primes::ipow(17,7)) xtn = {3, 0, 0, 16, 0, 0, 0};
// GF(19^2) = GF(361)
// x^2 = 17 + 18x
else if (q == primes::ipow(19,2)) xtn = {17, 18};
// GF(19^3) = GF(6859)
// x^3 = 3 + 18x^2
else if (q == primes::ipow(19,3)) xtn = {3, 0, 18};
// GF(19^4) = GF(130321)
// x^4 = 17 + 18x^3
else if (q == primes::ipow(19,4)) xtn = {17, 0, 0, 18};
// GF(19^5) = GF(2476099)
// x^5 = 3 + 18x
else if (q == primes::ipow(19,5)) xtn = {3, 18, 0, 0, 0};
// GF(19^6) = GF(47045881)
// x^6 = 16 + 18x
else if (q == primes::ipow(19,6)) xtn = {16, 18, 0, 0, 0, 0};
// GF(19^7) = GF(893871739)
// x^7 = 10 + 18x^5
else if (q == primes::ipow(19,7)) xtn = {10, 0, 0, 0, 0, 18, 0};
// GF(23^2) = GF(529)
// x^2 = 16 + 22x
else if (q == primes::ipow(23,2)) xtn = {16, 22};
// GF(23^3) = GF(12167)
// x^3 = 7 + 22x^2
else if (q == primes::ipow(23,3)) xtn = {7, 0, 22};
// GF(23^4) = GF(279841)
// x^4 = 12 + 22x
else if (q == primes::ipow(23,4)) xtn = {12, 22, 0, 0};
// GF(23^5) = GF(6436343)
// x^5 = 5 + 22x^4
else if (q == primes::ipow(23,5)) xtn = {5, 0, 0, 0, 22};
// GF(23^6) = GF(148035889)
// x^6 = 16 + 22x^5
else if (q == primes::ipow(23,6)) xtn = {16, 0, 0, 0, 0, 22};
// GF(29^2) = GF(841)
// x^2 = 26 + 28x
else if (q == primes::ipow(29,2)) xtn = {26, 28};
// GF(29^3) = GF(24389)
// x^3 = 11 + 28x
else if (q == primes::ipow(29,3)) xtn = {11, 28, 0};
// GF(29^4) = GF(707281)
// x^4 = 27 + 28x^3
else if (q == primes::ipow(29,4)) xtn = {27, 0, 0, 28};
// GF(29^5) = GF(20511149)
// x^5 = 3 + 28x^3
else if (q == primes::ipow(29,5)) xtn = {3, 0, 0, 28, 0};
// GF(29^6) = GF(594823321)
// x^6 = 26 + 28x
else if (q == primes::ipow(29,6)) xtn = {26, 28, 0, 0, 0, 0};
// GF(31^2) = GF(961)
// x^2 = 19 + 30x
else if (q == primes::ipow(31,2)) xtn = {19, 30};
// GF(31^3) = GF(29791)
// x^3 = 3 + 30x
else if (q == primes::ipow(31,3)) xtn = {3, 30, 0};
// GF(31^4) = GF(923521)
// x^4 = 18 + 30x^3
else if (q == primes::ipow(31,4)) xtn = {18, 0, 0, 30};
// GF(31^5) = GF(28629151)
// x^5 = 11 + 30x^3
else if (q == primes::ipow(31,5)) xtn = {11, 0, 0, 30, 0};
// GF(31^6) = GF(887503681)
// x^6 = 19 + 30x^5
else if (q == primes::ipow(31,6)) xtn = {19, 0, 0, 0, 0, 30};
// GF(37^2) = GF(1369)
// x^2 = 32 + 36x
else if (q == primes::ipow(37,2)) xtn = {32, 36};
// GF(37^3) = GF(50653)
// x^3 = 13 + 36x^2
else if (q == primes::ipow(37,3)) xtn = {13, 0, 36};
// GF(37^4) = GF(1874161)
// x^4 = 35 + 36x
else if (q == primes::ipow(37,4)) xtn = {35, 36, 0, 0};
// GF(37^5) = GF(69343957)
// x^5 = 5 + 36x
else if (q == primes::ipow(37,5)) xtn = {5, 36, 0, 0, 0};
// GF(41^2) = GF(1681)
// x^2 = 29 + 40x
else if (q == primes::ipow(41,2)) xtn = {29, 40};
// GF(41^3) = GF(68921)
// x^3 = 6 + 40x
else if (q == primes::ipow(41,3)) xtn = {6, 40, 0};
// GF(41^4) = GF(2825761)
// x^4 = 24 + 40x
else if (q == primes::ipow(41,4)) xtn = {24, 40, 0, 0};
// GF(41^5) = GF(115856201)
// x^5 = 6 + 40x^4
else if (q == primes::ipow(41,5)) xtn = {6, 0, 0, 0, 40};
// GF(43^2) = GF(1849)
// x^2 = 40 + 42x
else if (q == primes::ipow(43,2)) xtn = {40, 42};
// GF(43^3) = GF(79507)
// x^3 = 3 + 42x
else if (q == primes::ipow(43,3)) xtn = {3, 42, 0};
// GF(43^4) = GF(3418801)
// x^4 = 23 + 42x
else if (q == primes::ipow(43,4)) xtn = {23, 42, 0, 0};
// GF(43^5) = GF(147008443)
// x^5 = 3 + 42x^4
else if (q == primes::ipow(43,5)) xtn = {3, 0, 0, 0, 42};
// GF(47^2) = GF(2209)
// x^2 = 34 + 46x
else if (q == primes::ipow(47,2)) xtn = {34, 46};
// GF(47^3) = GF(103823)
// x^3 = 5 + 46x^2
else if (q == primes::ipow(47,3)) xtn = {5, 0, 46};
// GF(47^4) = GF(4879681)
// x^4 = 42 + 46x^3
else if (q == primes::ipow(47,4)) xtn = {42, 0, 0, 46};
// GF(47^5) = GF(229345007)
// x^5 = 5 + 46x
else if (q == primes::ipow(47,5)) xtn = {5, 46, 0, 0, 0};
#endif
