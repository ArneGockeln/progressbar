/*
 * Author: 2023 Arne Gockeln, <https://0xArne.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef OREBIT_ASCII_H
#define OREBIT_ASCII_H

#include <time.h>

#define ASCII_RAND_DURATION_MIN 1 // duration_seconds
#define ASCII_RAND_DURATION_MAX 5 // duration_seconds
#define ASCII_ESC 0x1B
#define ASCII_INVISIBLE_CUR "[?25l"
#define ASCII_VISIBLE_CUR "[?25h"

typedef enum {
    APB_TYPE_SHEBANG,
    APB_TYPE_DOTTED
} ascii_progressbar_type_e;

typedef enum {
    // no options, default value.
    APB_OPT_DEFAULT = 1 << 0,
    // label on new line, default single line
    APB_OPT_LABEL_NL = 1 << 1,          // 00000001
    // time based, use value as duration_seconds. Default value = fixed %.
    APB_OPT_VALUE_DURATION = 1 << 2,    // 00000010
    // show ETA time label
    APB_OPT_ETA_LABEL = 1 << 3,         // 00000100
    // use random duration_seconds
    APB_OPT_RAND_DURATION = 1 << 4,     // 00001000
} ascii_progressbar_opt_e;

typedef struct {
    ascii_progressbar_type_e type;
    unsigned int options;
    double duration_seconds;
    int eta_hours;
    int eta_minutes;
    int eta_seconds;
    char* label;
    time_t start_time;
} ascii_progressbar_t;

void ascii_hide_cursor();
void ascii_show_cursor();
ascii_progressbar_t* ascii_progressbar_new(const char* label, double duration, int opt);
void ascii_progressbar_free(ascii_progressbar_t* ptr);
void ascii_progressbar_dotted(ascii_progressbar_t* ptr);
void ascii_progressbar_set_opt(ascii_progressbar_t* ptr, ascii_progressbar_opt_e opt);
void ascii_progressbar_eta(ascii_progressbar_t* ptr);
void ascii_progressbar_set_label(ascii_progressbar_t* ptr, const char* label);

//void ascii_progressbar_draw(const char *label, double percentage, const char *eta_label);
//void ascii_progressbar_draw_nl(const char *label, double percentage, const char *eta_label);
//void ascii_progressbar(const char* label, double value, unsigned int options);
void ascii_progressbar(ascii_progressbar_t* ptr);
#endif //OREBIT_ASCII_H
