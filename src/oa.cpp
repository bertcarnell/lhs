/**
 * @file oa.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
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

#include "oa.h"
#include "matrix.h"

namespace oacpp
{
    namespace oastrength
    {
        void OA_strworkcheck(double work, int str)
        {
            if (work > BIGWORK) // LCOV_EXCL_START
            {
                PRINT_OUTPUT << "If the array has strength " << str << ", " << work << " comparisons will\n";
                PRINT_OUTPUT << "be required to prove it.  This might take a long time.\n";
                PRINT_OUTPUT << "This warning is triggered when more than " << BIGWORK << " comparisons\n";
                PRINT_OUTPUT << "are required.  To avoid this warning increase BIGWORK in\n";
                PRINT_OUTPUT << "oa.h.  Intermediate results will be printed.\n\n";
            }
            else if (work > MEDWORK)
            {
                PRINT_OUTPUT << "Since more than " << MEDWORK << " comparisons may be required to\n";
                PRINT_OUTPUT << "to check whether the array has strength " << str << ", intermediate\n";
                PRINT_OUTPUT << "results will be printed.  To avoid this warning increase\n";
                PRINT_OUTPUT << "MEDWORK in oa.h\n\n";
            } // LCOV_EXCL_STOP
        }

        void OA_strength(int q, const bclib::matrix<int> & A, int* str, int verbose)
        {
            *str = -1;

            int test = OA_str0(q, A, verbose);
            if (test == SUCCESS_CHECK)
            {
                *str = 0;
            }
            else
            {
                return;
            }

            test = OA_str1(q, A, verbose);
            if (test == SUCCESS_CHECK)
            {
                *str = 1;
            }
            else
            {
                return;
            }

            test = OA_strt(q, A, *str + 1, verbose);
            while (test == SUCCESS_CHECK)
            {
                (*str)++;
                test = OA_strt(q, A, *str + 1, verbose);
            }
        }

        int OA_str0(int q, const bclib::matrix<int> & A, int verbose)
        {
            size_t nrow = A.rowsize();
            size_t ncol = A.colsize();
            for (size_t j1 = 0; j1 < ncol; j1++)
            {
                for (size_t i = 0; i < nrow; i++)
                {
                    if (A(i,j1) < 0 || A(i,j1) >= q)
                    {
                        if (verbose >= 2) // LCOV_EXCL_START
                        {
                            PRINT_OUTPUT << "Array is not even of strength 0, that is there are elements\n";
                            PRINT_OUTPUT << "other than integers 0 through " << q << " inclusive in it.\n";
                            PRINT_OUTPUT << "The first exception is A[" << i << "," << j1 << "] = " << A(i, j1) << ".\n";
                        } // LCOV_EXCL_STOP
                        return 0;
                    }
                }
            }
            if (verbose >= 2)
            {
                PRINT_OUTPUT << "The array has strength (at least) 0.\n"; // LCOV_EXCL_LINE
            }
            return SUCCESS_CHECK;
        }

        int OA_str1(int q, const bclib::matrix<int> & A, int verbose)
        {
            size_t nrow = A.rowsize();
            size_t ncol = A.colsize();
            int lambda, count;
            double work;

            if (static_cast<int>(nrow) % q != 0)
            {
                if (verbose >= 2) // LCOV_EXCL_START
                {
                    PRINT_OUTPUT << "The array cannot have strength 1, because the number\n";
                    PRINT_OUTPUT << "of rows " << nrow << " is not a multiple of q = " << q << ".\n";
                } // LCOV_EXCL_STOP
                return FAILURE_CHECK;
            }

            lambda = static_cast<int>(nrow) / q;
            work = static_cast<double>(nrow) * static_cast<double>(ncol) * static_cast<double>(q);
            OA_strworkcheck(work, 1);
            for (size_t j1 = 0; j1 < ncol; j1++)
            {
                for (int q1 = 0; q1 < q; q1++)
                {
                    count = 0;
                    for (size_t i = 0; i < nrow; i++)
                    {
                        count += static_cast<int>(A(i,j1) == q1);
                    }
                    if (count != lambda)
                    {
                        if (verbose >= 2) // LCOV_EXCL_START
                        {
                            PRINT_OUTPUT << "Array is not of strength 1.  The first violation arises for\n";
                            PRINT_OUTPUT << "the number of times A[," << j1 << "] = " << q1 << ".\n";
                            PRINT_OUTPUT << "This happened in " << count << " rows, it should have happened in " << lambda << " rows.\n";
                        } // LCOV_EXCL_STOP
                        return FAILURE_CHECK;
                    }
                }
                if (work > MEDWORK && verbose > 0)
                {
                    PRINT_OUTPUT << "No violation of strength 1 involves column " << j1 << ".\n"; // LCOV_EXCL_LINE
                }
            }
            if (verbose >= 2)
            {
                PRINT_OUTPUT << "The array has strength (at least) 1.\n"; // LCOV_EXCL_LINE
            }
            return SUCCESS_CHECK;
        }

        int OA_str2(int q, const bclib::matrix<int> & A, int verbose)
        {
            size_t nrow = A.rowsize();
            size_t ncol = A.colsize();
            int q1, q2;
            int lambda, count;
            double work;

            if (ncol < 2)
            {
                if (verbose > 0) // LCOV_EXCL_START
                {
                    PRINT_OUTPUT << "Array has only " << ncol << " column(s).  At least two\n";
                    PRINT_OUTPUT << "columns are necessary for strength 2 to make sense.\n";
                } // LCOV_EXCL_STOP
                return FAILURE_CHECK;
            }
            if ((static_cast<int>(nrow) % (q * q)) != 0)
            {
                if (verbose > 0) // LCOV_EXCL_START
                {
                    PRINT_OUTPUT << "The array cannot have strength 2, because the number\n";
                    PRINT_OUTPUT << "of rows " << nrow << " is not a multiple of q^2 = " << q << "^2 = " << q*q << ".\n";
                } // LCOV_EXCL_STOP
                return FAILURE_CHECK;
            }

            lambda = static_cast<int>(nrow) / (q * q);
            work = static_cast<double>(nrow * ncol) * static_cast<double>((ncol - 1.0) * q * q) / 2.0;
            OA_strworkcheck(work, 2);

            for (size_t j1 = 0; j1 < ncol; j1++)
            {
                for (size_t j2 = j1 + 1; j2 < ncol; j2++)
                {
                    for (q1 = 0; q1 < q; q1++)
                    {
                        for (q2 = 0; q2 < q; q2++)
                        {
                            count = 0;
                            for (size_t i = 0; i < nrow; i++)
                            {
                                count += static_cast<int>((A(i,j1) == q1) && (A(i,j2) == q2));
                            }
                            if (count != lambda)
                            {
                                if (verbose >= 2) // LCOV_EXCL_START
                                {
                                    PRINT_OUTPUT << "Array is not of strength 2.  The first violation arises for\n";
                                    PRINT_OUTPUT << "the number of times (A[," << j1 << "],A[," << j2 << "]) = (" << q1 << "," << q2 << ").\n";
                                    PRINT_OUTPUT << "This happened in " << count << " rows, it should have happened in " << lambda << " rows.\n";
                                } // LCOV_EXCL_STOP
                                return FAILURE_CHECK;
                            }
                        }
                    }
                }
                if (work > MEDWORK && verbose > 0)
                {
                    PRINT_OUTPUT << "No violation of strength 2 involves column " << j1 << ".\n"; // LCOV_EXCL_LINE
                }
            }

            if (verbose >= 2)
            {
                PRINT_OUTPUT << "The array has strength (at least) 2.\n"; // LCOV_EXCL_LINE
            }
            return SUCCESS_CHECK;
        }

        int OA_str3(int q, const bclib::matrix<int> & A, int verbose)
        {
            size_t nrow = A.rowsize();
            size_t ncol = A.colsize();
            int q1, q2, q3;
            int lambda, count;
            double work;

            if (ncol < 3)
            {
                if (verbose > 0) // LCOV_EXCL_START
                {
                    PRINT_OUTPUT << "Array has only " << ncol << " column(s).  At least three\n";
                    PRINT_OUTPUT << "columns are necessary for strength 3 to make sense.\n";
                } // LCOV_EXCL_STOP
                return FAILURE_CHECK;
            }
            if (static_cast<int>(nrow) % (q * q * q) != 0)
            {
                if (verbose > 0) // LCOV_EXCL_START
                {
                    PRINT_OUTPUT << "The array cannot have strength 3, because the number\n";
                    PRINT_OUTPUT << "of rows " << nrow << " is not a multiple of q^3 = " << q << "^3 = " << q*q*q << ".\n";
                } // LCOV_EXCL_STOP
                return FAILURE_CHECK;
            }

            lambda = static_cast<int>(nrow) / (q * q * q);
            work = static_cast<double>(nrow * ncol) * static_cast<double>((ncol - 1.0)*(ncol - 2.0) * q * q * q) / 6.0;
            OA_strworkcheck(work, 3);

            for (size_t j1 = 0; j1 < ncol; j1++)
            {
                for (size_t j2 = j1 + 1; j2 < ncol; j2++)
                {
                    for (size_t j3 = j2 + 1; j3 < ncol; j3++)
                    {
                        for (q1 = 0; q1 < q; q1++)
                        {
                            for (q2 = 0; q2 < q; q2++)
                            {
                                for (q3 = 0; q3 < q; q3++)
                                {
                                    count = 0;
                                    for (size_t i = 0; i < nrow; i++)
                                    {
                                        count += static_cast<int>((A(i,j1) == q1) && (A(i,j2) == q2) && (A(i,j3) == q3));
                                    }
                                    if (count != lambda)
                                    {
                                        if (verbose >= 2) // LCOV_EXCL_START
                                        {
                                            PRINT_OUTPUT << "Array is not of strength 3.  The first violation arises for\n";
                                            PRINT_OUTPUT << "the number of times (A[," << j1 << "],A[," << j2 << "],A[," << j3 << "]) = (" << q1 << "," << q2 << "," << q3 << ").\n";
                                            PRINT_OUTPUT << "This happened in " << count << " rows, it should have happened in " << lambda << " rows.\n";
                                        } // LCOV_EXCL_STOP
                                        return FAILURE_CHECK;
                                    }
                                }
                            }
                        }
                    }
                }
                if (work > MEDWORK && verbose > 0)
                {
                    PRINT_OUTPUT << "No violation of strength 3 involves column " << j1 << ".\n"; // LCOV_EXCL_LINE
                }
            }
            if (verbose >= 2)
            {
                PRINT_OUTPUT << "The array has strength (at least) 3.\n"; // LCOV_EXCL_LINE
            }
            return SUCCESS_CHECK;
        }

        int OA_str4(int q, const bclib::matrix<int> & A, int verbose)
        {
            size_t nrow = A.rowsize();
            size_t ncol = A.colsize();
            int q1, q2, q3, q4;
            int lambda, count;
            double work;

            if (ncol < 4)
            {
                if (verbose > 0) // LCOV_EXCL_START
                {
                    PRINT_OUTPUT << "Array has only " << ncol << " column(s).  At least four\n";
                    PRINT_OUTPUT << "columns are necessary for strength 4 to make sense.\n";
                } // LCOV_EXCL_STOP
                return FAILURE_CHECK;
            }
            if (static_cast<int>(nrow) % (q * q * q * q) != 0)
            {
                if (verbose > 0) // LCOV_EXCL_START
                {
                    PRINT_OUTPUT << "The array cannot have strength 4, because the number\n";
                    PRINT_OUTPUT << "of rows " << nrow << " is not a multiple of q^4 = " << q << "^4 = " << q*q*q*q << ".\n";
                } // LCOV_EXCL_STOP
                return FAILURE_CHECK;
            }

            lambda = static_cast<int>(nrow) / (q * q * q * q);
			// cast to doubles to prevent overflow
			double dnrow = static_cast<double>(nrow);
			double dncol = static_cast<double>(ncol);
			double dq = static_cast<double>(q);
            work = dnrow * dncol * (dncol - 1.0) * (dncol - 2.0) * (dncol - 3.0) * dq * dq * dq * dq / 24.0;
            OA_strworkcheck(work, 4);

            for (size_t j1 = 0; j1 < ncol; j1++)
            {
                for (size_t j2 = j1 + 1; j2 < ncol; j2++)
                {
                    for (size_t j3 = j2 + 1; j3 < ncol; j3++)
                    {
                        for (size_t j4 = j3 + 1; j4 < ncol; j4++)
                        {
                            for (q1 = 0; q1 < q; q1++)
                            {
                                for (q2 = 0; q2 < q; q2++)
                                {
                                    for (q3 = 0; q3 < q; q3++)
                                    {
                                        for (q4 = 0; q4 < q; q4++)
                                        {
                                            count = 0;
                                            for (size_t i = 0; i < nrow; i++)
                                            {
                                                count += static_cast<int>((A(i,j1) == q1) && (A(i,j2) == q2) && (A(i,j3) == q3) && (A(i,j4) == q4));
                                            }
                                            if (count != lambda)
                                            {
                                                if (verbose >= 2) // LCOV_EXCL_START
                                                {
                                                    PRINT_OUTPUT << "Array is not of strength 4.  The first violation arises for\n";
                                                    PRINT_OUTPUT << "the number of times (A[," << j1 << "],A[," << j2 << "],A[," << j3 << "],A[," << j4 << "]) = (" << q1 << "," << q2 << "," << q3 << "," << q4 << ").\n";
                                                    PRINT_OUTPUT << "This happened in " << count << " rows, it should have happened in " << lambda << " rows.\n";
                                                } // LCOV_EXCL_STOP
                                                return FAILURE_CHECK;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (work > MEDWORK && verbose > 0)
                {
                    PRINT_OUTPUT << "No violation of strength 4 involves column " << j1 << ".\n"; // LCOV_EXCL_LINE
                }
            }

            if (verbose >= 2)
            {
                PRINT_OUTPUT << "The array has strength (at least) 4.\n"; // LCOV_EXCL_LINE
            }
            return SUCCESS_CHECK;
        }

        int OA_strt(int q, const bclib::matrix<int> & A, int t, int verbose)
        {
            size_t nrow = A.rowsize();
            size_t ncol = A.colsize();
            int ctuples, qtuples;
            int lambda, count, match;
            double work;
            std::vector<int> clist, qlist;

            if (t < 0)
            {
                if (verbose > 0) // LCOV_EXCL_START
                {
                    PRINT_OUTPUT << "Don't know how to verify strength " << t << ".  It doesn't\n";
                    PRINT_OUTPUT << "make sense.\n";
                } // LCOV_EXCL_STOP
                return FAILURE_CHECK;
            }
            if (ncol < static_cast<size_t>(t))
            {
                if (verbose > 0) // LCOV_EXCL_START
                {
                    PRINT_OUTPUT << "Array has only " << ncol << " column(s).  At least " << t << "\n";
                    PRINT_OUTPUT << "columns are necessary for strength " << t << " to make sense.\n";
                } // LCOV_EXCL_STOP
                return FAILURE_CHECK;
            }
            if (t == 0)
            {
                return OA_str0(q, A, verbose);
            }
            if (nrow % primes::ipow(q, t) != 0)
            {
                if (verbose > 0) // LCOV_EXCL_START
                {
                    PRINT_OUTPUT << "The array cannot have strength " << t << ", because the number\n";
                    PRINT_OUTPUT << "of rows " << nrow << " is not a multiple of q^" << t << " = " << q << "^" << t << " = " << primes::ipow(q, t) << ".\n";
                } // LCOV_EXCL_STOP
                return FAILURE_CHECK;
            }

            lambda = static_cast<int>(nrow) / primes::ipow(q, t);
            work = static_cast<double>(nrow * primes::ipow(q, t));
            ctuples = 1;

            clist = std::vector<int>(t);
            qlist = std::vector<int>(t);

            for (int i = 0; i < t; i++)
            {
                work *= static_cast<double>((ncol - i)) / static_cast<double>((i + 1.0));
                ctuples *= static_cast<int>(ncol) - i;
                qlist[i] = 0;
                clist[i] = i;
            }
            for (int i = 0; i < t; i++)
            {
                ctuples /= (i + 1);
            }
            qtuples = primes::ipow(q, t);

            OA_strworkcheck(work, t);

            for (int ic = 0; ic < ctuples; ic++) /* Loop over ordered tuples of columns */
            {
                for (int iq = 0; iq < qtuples; iq++) /* Loop over unordered tuples of symbols */
                {
                    count = 0;
                    for (size_t row = 0; row < nrow; row++)
                    {
                        match = 1;
                        for (int i = 0; i < t && match != 0; i++)
                        {
                            match *= static_cast<int>(A(row,clist[i]) == qlist[i]);
                        }
                        count += match;
                    }
                    if (count != lambda)
                    {
                        if (verbose >= 2) // LCOV_EXCL_START
                        {
                            PRINT_OUTPUT << "Array is not of strength " << t << ".  The first violation arises for\n";
                            PRINT_OUTPUT << "the number of times (";
                            for (int i = 0; i < t; i++)
                            {
                                std::string temp = (i == t - 1) ? ")" : ","; // warning about decaying a pointer when used on next line
                                PRINT_OUTPUT << "A(," << clist[i] << ")" << temp.c_str();
                            }
                            PRINT_OUTPUT << " = (";
                            for (int i = 0; i < t; i++)
                            {
                                PRINT_OUTPUT << qlist[i] << ((i == t - 1) ? ").\n" : ",");
                            }
                            PRINT_OUTPUT << "This happened in " << count << " rows, it should have happened in " << lambda << " rows.\n";
                        } // LCOV_EXCL_STOP
                        return FAILURE_CHECK;
                    }
                    for (int i = t - 1; i >= 0; i--) // has to be int
                    {
                        qlist[i] = (qlist[i] + 1) % q;
                        if (qlist[i] != 0)
                        {
                            break;
                        }
                    }
                }

                for (int i = t - 1; i >= 0; i--) // has to be int
                {
                    clist[i] = (clist[i] + 1) % (static_cast<int>(ncol) + i - t + 1);
                    if (clist[i] != 0)
                    {
                        break;
                    }
                }

                if (work > MEDWORK && verbose > 0 &&
                      ((t == 1 || t > 1) && (clist[1] == 0)))
                {
                    PRINT_OUTPUT << "No violation of strength " << t << " involves column " << (clist[0] + static_cast<int>(ncol) - 1) % static_cast<int>(ncol) << ".\n"; // LCOV_EXCL_LINE
                }

                for (size_t i = 1; i < static_cast<size_t>(t); i++)
                {
                    if (clist[i] <= clist[i - 1])
                    {
                        clist[i] = clist[i - 1] + 1;
                    }
                }
            }

            if (verbose >= 2)
            {
                PRINT_OUTPUT << "The array has strength (at least) " << t << ".\n"; // LCOV_EXCL_LINE
            }
            return SUCCESS_CHECK;
        }
    } // end namespace
}// end namespace
