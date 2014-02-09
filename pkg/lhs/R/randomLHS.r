################################################################################
#
# Copyright (c) 2013, Robert Carnell
# 
# GNU General Public License (GPL v3)
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#  
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# 

#' Construct a random Latin hypercube design
#'
#' \code{randomLHS(4,3)} returns a 4x3 matrix with each column 
#' constructed as follows: A random permutation of (1,2,3,4) is 
#' generated, say (3,1,2,4) for each of K columns.  Then a uniform 
#' random number is picked from each indicated quartile.  In this 
#' example a random number between .5 and .75 is chosen, then one between
#' 0 and .25, then one between .25 and .5, finally one between
#' .75 and 1.
#'
#' @param n the number of rows or samples
#' @param k the number of columns or parameters/variables
#' @param preserveDraw should the draw be constructed so that it is the same for variable numbers of columns?
#' @return a Latin hypercube sample
#' @export
randomLHS <- function(n, k, preserveDraw=FALSE)
{
  .Call("randomLHS_cpp", as.integer(n), as.integer(k), as.logical(preserveDraw))
}
