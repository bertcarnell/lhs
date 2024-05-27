# Copyright 2024 Robert Carnell

context("test-correlatedLHS")

test_that("Normal Operations", {
  temp <- correlatedLHS(randomLHS(10, 3),
                        marginal_transform_function = function(x, ...) {
                          x[,1] <- qunif(x[,1], 3, 6)
                          return(x)
                        },
                        cost_function = function(x, ...) {
                          (cor(x[,1], x[,2]) - 0.8)^2
                        })
  expect_true(is.numeric(temp$cost))
  expect_true(is.matrix(temp$lhs))
  expect_true(is.matrix(temp$transformed_lhs))

  # debug
  expect_output(temp <- correlatedLHS(randomLHS(10, 3),
                        marginal_transform_function = function(x, ...) {
                          x[,1] <- qunif(x[,1], 3, 6)
                          return(x)
                        },
                        cost_function = function(x, ...) {
                          (cor(x[,1], x[,2]) - 0.8)^2
                        }, debug = TRUE))
})

test_that("problems", {
  # bad marginal_transform_function return
  #   not a data.frame or matrix
  expect_error({
    correlatedLHS(randomLHS(10, 3),
                  marginal_transform_function = function(x, ...) {
                    return(NA)
                  },
                  cost_function = function(x, ...) {
                    return(1)
                  })
  })

  #   wrong dimensions
  expect_error({
    correlatedLHS(randomLHS(10, 3),
                  marginal_transform_function = function(x, ...) {
                    return(matrix(1, nrow = 2, ncol = 2))
                  },
                  cost_function = function(x, ...) {
                    return(1)
                  })
  })

  # bad cost_function return
  expect_error({
    correlatedLHS(randomLHS(10, 3),
                  marginal_transform_function = function(x, ...) {
                    return(x)
                  },
                  cost_function = function(x, ...) {
                    return("eight")
                  })
  })

  # bad marginal_transform_function without ... with a passed in var
  expect_error({
    correlatedLHS(randomLHS(10, 3),
                  marginal_transform_function = function(x) {
                    return(x)
                  },
                  cost_function = function(x, ...) {
                    return(1)
                  },
                  test_var = "A")
  })

  # bad cost_function without ... with a passed in var
  expect_error({
    correlatedLHS(randomLHS(10, 3),
                  marginal_transform_function = function(x, ...) {
                    return(x)
                  },
                  cost_function = function(x) {
                    return(1)
                  },
                  test_var = "A")
  })

  # bad lhs
  expect_output(
    expect_error(
      temp <- correlatedLHS(matrix(-1, nrow = 2, ncol = 2),
                                      marginal_transform_function = function(x, ...) {
                                        return(x)
                                      },
                                      cost_function = function(x, ...) {
                                        return(sum(x))
                                      }, debug = TRUE)
    )
  )

})
