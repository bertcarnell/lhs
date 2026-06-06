# Copyright 2026 Robert Carnell
#
# Generator for src/xtn.h
#
# src/xtn.h contains the "power cycle" representation of the Galois fields
# GF(p^n) that are used by GaloisField.cpp.  For each prime power p^n the file
# records a vector `xtn` of length n that defines a primitive (and therefore
# irreducible) polynomial
#
#     x^n = xtn[1] + xtn[2] x + ... + xtn[n] x^(n-1)   (mod p)
#
# Because x is a primitive element, its powers cycle through every non-zero
# element of the field (see Table B.3, "Power cycle II", p. 316 of Bailey,
# "Design of Comparative Experiments").  GaloisField.cpp only requires the
# polynomial to be irreducible, but primitive polynomials are used to stay
# faithful to the original tables.
#
# Exponents n >= 2 are emitted while p^n < 1e9 (the same threshold used to
# generate the original table).  The historical entries for p <= 47 are kept
# as-is in src/xtn.h; this script was used to generate the appended entries for
# 53 <= p <= 127 (issue #61).  Re-run with a larger `max_base` to extend the
# table further, e.g. for applications such as covering arrays.
#
# Usage (from the package root):
#   source("etc/CreatePowerCycle.R")
#   writeLines(make_power_cycle_block(min_base = 53, max_base = 127))

is_prime <- function(m) {
  if (m < 2) return(FALSE)
  if (m %% 2 == 0) return(m == 2)
  i <- 3
  while (i * i <= m) {
    if (m %% i == 0) return(FALSE)
    i <- i + 2
  }
  TRUE
}

prime_factors <- function(m) {
  f <- numeric(0)
  d <- 2
  while (d * d <= m) {
    while (m %% d == 0) {
      f <- c(f, d)
      m <- m / d
    }
    d <- d + 1
  }
  if (m > 1) f <- c(f, m)
  unique(f)
}

primitive_roots <- function(p) {
  if (p == 2) return(1)
  order <- p - 1
  fs <- prime_factors(order)
  res <- integer(0)
  for (g in 2:(p - 1)) {
    # use modular exponentiation to avoid overflow for larger p
    is_pr <- all(vapply(fs, function(q) powmod_int(g, order / q, p) != 1, logical(1)))
    if (is_pr) res <- c(res, g)
  }
  res
}

# modular exponentiation of an integer base (avoids overflow)
powmod_int <- function(base, e, mod) {
  result <- 1
  base <- base %% mod
  while (e > 0) {
    if (e %% 2 == 1) result <- (result * base) %% mod
    e <- e %/% 2
    if (e > 0) base <- (base * base) %% mod
  }
  result
}

# multiply two polynomials (length n, index 1 == coefficient on x^0) modulo the
# field relation x^n = sum(cmod[j] x^(j-1))
poly_mul <- function(a, b, p, n, cmod) {
  long <- numeric(2 * n - 1)
  for (i in 1:n) {
    if (a[i] == 0) next
    for (j in 1:n) {
      if (b[j] != 0) long[i + j - 1] <- long[i + j - 1] + a[i] * b[j]
    }
  }
  if (n > 1) {
    for (i in (2 * n - 1):(n + 1)) {
      v <- long[i] %% p
      if (v != 0) {
        for (j in 1:n) {
          if (cmod[j] != 0) long[i - n + j] <- long[i - n + j] + v * cmod[j]
        }
      }
      long[i] <- 0
    }
  }
  long[1:n] %% p
}

poly_pow <- function(base, e, p, n, cmod) {
  result <- c(1, numeric(n - 1))
  b <- base
  while (e > 0) {
    if (e %% 2 == 1) result <- poly_mul(result, b, p, n, cmod)
    e <- e %/% 2
    if (e > 0) b <- poly_mul(b, b, p, n, cmod)
  }
  result
}

is_primitive <- function(cmod, p, n, order, fs) {
  x <- c(0, 1, numeric(n - 2))
  one <- c(1, numeric(n - 1))
  if (!all(poly_pow(x, order, p, n, cmod) == one)) return(FALSE)
  for (d in fs) {
    if (all(poly_pow(x, order / d, p, n, cmod) == one)) return(FALSE)
  }
  TRUE
}

# the smallest primitive polynomial for GF(p^n); the constant term of a
# primitive polynomial must be (-1)^(n+1) times a primitive root of GF(p), so we
# only search those constant terms
find_primitive <- function(p, n) {
  order <- p^n - 1
  fs <- prime_factors(order)
  sign <- if (n %% 2 == 1) 1 else -1
  c0set <- sort(unique((sign * primitive_roots(p)) %% p))
  c0set <- c0set[c0set != 0]
  rest_grid <- if (n == 1) NULL else as.matrix(expand.grid(rep(list(0:(p - 1)), n - 1)))
  for (c0 in c0set) {
    if (n == 1) {
      if (is_primitive(c0, p, n, order, fs)) return(c0)
    } else {
      for (r in seq_len(nrow(rest_grid))) {
        # rev() so the highest-order coefficient varies fastest, matching the
        # search order used to generate the committed entries
        cmod <- c(c0, rev(rest_grid[r, ]))
        if (is_primitive(cmod, p, n, order, fs)) return(as.numeric(cmod))
      }
    }
  }
  stop(sprintf("no primitive polynomial found for GF(%d^%d)", p, n))
}

# build the C++ else-if blocks for all prime bases in [min_base, max_base]
make_power_cycle_block <- function(min_base, max_base, limit = 1e9) {
  primes <- Filter(is_prime, min_base:max_base)
  out <- character(0)
  for (p in primes) {
    n <- 2
    while (p^n < limit) {
      cmod <- find_primitive(p, n)
      q <- p^n
      terms <- character(0)
      for (j in seq_len(n)) {
        cj <- cmod[j]
        if (cj == 0) next
        if (j == 1) terms <- c(terms, as.character(cj))
        else if (j == 2) terms <- c(terms, paste0(if (cj == 1) "" else cj, "x"))
        else terms <- c(terms, paste0(if (cj == 1) "" else cj, "x^", j - 1))
      }
      rhs <- if (length(terms)) paste(terms, collapse = " + ") else "0"
      out <- c(out,
               sprintf("// GF(%d^%d) = GF(%d)", p, n, q),
               sprintf("// x^%d = %s", n, rhs),
               sprintf("else if (q == primes::ipow(%d,%d)) xtn = {%s};",
                       p, n, paste(cmod, collapse = ", ")))
      n <- n + 1
    }
  }
  out
}
