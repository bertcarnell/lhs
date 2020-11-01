/**
 * @file RWarningException.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2020, Robert Carnell
 *
 * @license <a href="http://www.gnu.org/licenses/lgpl.html">GNU Lesser General Public License (LGPL v3)</a>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RWARNINGEXCEPTION_H
#define	RWARNINGEXCEPTION_H

#include <stdexcept>
#include <string>

 /**
  * @namespace bclib The bertcarnell template library namespace
  */
namespace bclib {

    class RWarningException : public std::runtime_error
    {
    public:
        explicit RWarningException(const std::string & _Message)
            : std::runtime_error(_Message.c_str())
        {
        }

        explicit RWarningException(const char *_Message)
            : std::runtime_error(_Message)
        {
        }
    };
} // end namespace

#endif	/* RWARNINGEXCEPTION_H */
