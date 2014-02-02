/* 
 * File:   simpleAssert.h
 * Author: carnellr
 *
 * Created on December 6, 2013, 6:14 PM
 */

#ifndef SIMPLEASSERT_H
#define	SIMPLEASSERT_H

#include <math.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include <limits>

#define ASSERT_NOTHROW(exp) \
    try \
    { \
        exp; \
    } \
    catch (std::exception e) \
    { \
        throw bclib::assertion_error("Failed: an exception was thrown in assert_nothrow"); \
    }

#define ASSERT_THROW(exp) \
    try \
    { \
        exp; /*if error is thrown, won't make it to the assertion_error*/ \
        /*assertion_error will not be caught by the runtime_error or logic_error*/ \
        throw bclib::assertion_error("Failed: no exception was thrown in assert_throw"); \
    } \
    catch (std::runtime_error re) \
    { \
    } \
    catch (std::logic_error le) \
    { \
    }

#define ASSERT_ASSERTIONERROR(exp) \
    try \
    { \
        exp; \
        throw std::runtime_error("Failed: no exception was thrown in assert_noassertionerror"); \
    } \
    catch (bclib::assertion_error ae) \
    { \
        /* expected */ \
    }

namespace bclib
{
    class assertion_error : public std::exception 
    {
    private:
        std::string m_msg;

    public:
        /** Takes a character string describing the error.  */
        explicit 
        assertion_error(const std::string & arg) : m_msg(arg)
        {
        };
        
        explicit assertion_error(const char * arg) : m_msg(arg)
        {
        };

        ~assertion_error() throw(){};

        const char * what() const throw()
        {
            return m_msg.c_str();
        };
    };
    
    /**
     * Assert true
     * @param test a test expected to return true
     * @param msg a message
     */
    inline
    void Assert(bool test, std::string msg)
	{
		if (!test)
        {
            std::string message = "Assertion Error: ";
            message.append(msg);
            message.append("\n\n");
			throw assertion_error(message.c_str());
        }
	}
    
    /**
     * Assert true
     * @param test a test expected to return true
     */
    inline
    void Assert(bool test)
    {
        Assert(test, "Error in test - no message");
    }
    
    /**
     * Assert equals
     * @param expected the expected value
     * @param actual the actual value
     * @param msg the message
     */
    inline
    void Assert(int expected, int actual, std::string msg)
    {
        std::ostringstream ss;
        ss << "Expected:" << expected << "  Actual:" << actual << "  " << msg.c_str();
        Assert(expected == actual, ss.str());
    }
    
    /**
     * Assert equals
     * @param expected the expected value
     * @param actual the actual value
     */
    inline
    void Assert(int expected, int actual)
    {
        Assert(expected, actual, "Error in integer comparison - no message");
    }
    
    /**
     * Assert that expected and actual are equal to within a certain log relative error.
     * Log relative error measures the number of significant digits of agreement.
     * @param message message if the test fails
     * @param expected
     * @param actual
     * @param lre log relative error desired
     */
    inline
    void AssertEqualsLRE(double expected, double actual, int lre, std::string message)
    {
        double testlre;
        if (expected == actual)
        {
            return;
        }
        if (expected == 0.0)
        {
            testlre = -1.0 * log10(abs(actual));
        }
        else
        {
            testlre = -1.0 * log10(abs(actual-expected)) + log10(abs(expected));
        }
        
        if (isinf(testlre)) // C99 only
        {
            return;
        }
        if (testlre >= (double) std::numeric_limits<int>::max())
        {
            return;
        }
        if ((int) floor(testlre) < lre)
        {
            std::ostringstream mess;
            mess << "LRE is " << testlre << ", expected LRE is " << lre << " for " << actual << " vs " << expected;
            if (!message.empty())
            {
                mess << "\n" << message.c_str();
            }
            throw assertion_error(mess.str().c_str());
        }
    }

    inline
    void AssertEqualsLRE(double expected, double actual, int lre)
    {
        AssertEqualsLRE(expected, actual, lre, "Error in lre comparison - no message");
    }
    
    inline
    void Assert(double expected, double actual, double tol)
    {
        Assert(abs(expected-actual) < tol, "Failure:  message not provided");
    }
    
    inline
    void Assert(double expected, double actual, double tol, std::string msg)
    {
        Assert(abs(expected-actual) < tol, msg);
    }
} //  end namespace


#endif	/* SIMPLEASSERT_H */

