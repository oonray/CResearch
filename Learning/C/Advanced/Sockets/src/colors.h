//
// Created by oonray on 18.10.2019.
//

#ifndef CHECKLISTS_COLORS_H
#define CHECKLISTS_COLORS_H
#include <ncurses.h>

#define COLOR_REGULAR 1
#define COLOR_SELECTED 2

int loc_init_color() {
    start_color();
    use_default_colors();
    init_pair(COLOR_REGULAR, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_SELECTED, COLOR_BLACK, COLOR_WHITE);
}

#endif //CHECKLISTS_COLORS_H
