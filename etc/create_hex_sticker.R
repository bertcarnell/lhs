require(ggplot2)
require(hexSticker)
require(svglite)

lhs_xdots <- 1:6 - 0.5
lhs_ydots <- c(1.5, 3.5, 0.5, 5.5, 4.5, 2.5)
lhs_lines <- 0:6
xdata <- data.frame(x=lhs_xdots, y=lhs_ydots)
segment_data <- data.frame(x =    c(1,    2,    3, 4,    5,    0.50, 0, 0, 0, 0.55, 2.2,  2.3),
                           xend = c(1,    2,    3, 4,    5,    5.45, 6, 6, 6, 5.45, 3.75, 3.75),
                           y =    c(0.70, 0.15, 0, 0.15, 0.75, 1,    2, 3, 4, 5,    0,    6),
                           yend = c(5.25, 5.85, 6, 5.85, 5.25, 1,    2, 3, 4, 5,    0,    6))
#segment_data <- data.frame(x = c(lhs_lines, rep(0, length(lhs_lines))),
#                           xend = c(lhs_lines, rep(6, length(lhs_lines))),
#                           y = c(rep(0, length(lhs_lines)), lhs_lines),
#                           yend = c(rep(6, length(lhs_lines)), lhs_lines))

R_blue <- rgb(22, 92, 170, maxColorValue = 255)
R_blue2 <- rgb(39, 109, 195, maxColorValue = 255)
R_grey <- rgb(203, 206, 208, maxColorValue = 255)
R_grey2 <- rgb(132, 131, 139, maxColorValue = 255)

hex_back <- R_grey
hex_border <- R_blue
grid_line_width <- 1
lhs_point_size <- 3
lhs_text_size <- 12
hex_border_size <- 3

g1 <- ggplot(xdata, aes(x = x, y = y)) +
  xlim(0,6) + ylim(0,6) +
  geom_point(size = lhs_point_size, col = "red") +
  geom_segment(aes(x = x, xend = xend, y = y, yend = yend), data = segment_data,
               col = R_blue, lwd = grid_line_width) +
  theme(axis.text = element_blank(),
        axis.line = element_blank(),
        axis.title = element_blank(),
        panel.background = element_blank(), #element_rect(fill = "transparent"),
        plot.background = element_blank(), #element_rect(fill = "transparent"),
        panel.grid = element_blank(),
        panel.border = element_blank(),
        axis.ticks = element_blank())

g2 <- ggplot() +
  geom_hexagon(size = hex_border_size, fill = hex_back, color = hex_border) +
  theme_sticker(hex_border_size) +
  geom_subview(subview = g1, x = 1, y = 1, width = 2, height = 2) +
  geom_pkgname("lhs", x = 1, y = 1, size = lhs_text_size, color = "black", family = "sans")

plot(g2)

ggsave(g2, width = 48.9, height = 50.8, filename = file.path("lhs_hex.svg"),
       bg = "transparent", units = "mm")

# adjust the image and lines using inkscape
#  save as /etc/logo.svg
