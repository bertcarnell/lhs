
test.bush <- function()
{
  test.oa_type1.standard("createBush", 3, 3, 3^3, 3)
  test.oa_type1.standard("createBush", 4, 3, 4^3, 3)
  test.oa_type1.standard("createBush", 4, 5, 4^3, 5)
}

test.bose <- function()
{
  test.oa_type1.standard("createBose", 3, 3, 3^2, 3)
  test.oa_type1.standard("createBose", 3, 4, 3^2, 4)
  test.oa_type1.standard("createBose", 5, 4, 5^2, 4)
}

test.bosebush <- function()
{
  test.oa_type1.standard("createBoseBush", 4, 4, 2*(4^2), 4)
  test.oa_type1.standard("createBoseBush", 4, 5, 2*(4^2), 5)
  test.oa_type1.standard("createBoseBush", 4, 3, 2*(4^2), 3)
}

test.addelkemp <- function()
{
  test.oa_type1.standard("createAddelKemp", 3, 3, 2*(3^2), 3)
  test.oa_type1.standard("createAddelKemp", 3, 6, 2*(3^2), 6)
  test.oa_type1.standard("createAddelKemp", 4, 3, 2*(4^2), 3)
}

test.addelkemp3 <- function()
{
  test.oa_type1.standard("createAddelKemp3", 3, 3, 2*(3^3), 3)
  test.oa_type1.standard("createAddelKemp3", 3, 6, 2*(3^3), 6)
  test.oa_type1.standard("createAddelKemp3", 4, 3, 2*(4^3), 3)
}
