//
// Created by Arne on 29.01.23.
//

#include "ascii.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

/**
 * Send escape sequence to stdout to hide cursor. (no fflush).
 */
void ascii_hide_cursor() {
    printf( "%c%s", ASCII_ESC, ASCII_INVISIBLE_CUR );
}

/**
 * Send escape sequence to stdout to show cursor. (no fflush).
 */
void ascii_show_cursor() {
    printf( "%c%s", ASCII_ESC, ASCII_VISIBLE_CUR );
}

/**
 * Print ASCII Progress Bar
 * <label> #########------------------- 100 % ([ETA 00h00m00s])
 *
 * Defaults:
 *      APB_OPT_LABEL_NL = Off
 *      APB_OPT_ETA_LABEL = Off
 *      APB_OPT_RAND_DURATION = Off
 * Options:
 *      APB_OPT_LABEL_NL = Print progress bar on next line
 *      <label>
 *      #########------------------- 100 %
 *
 *      APB_OPT_ETA_LABEL = Shows ETA indicator at the end of the progress bar. Works only if APB_OPT_VALUE_DURATION is set.
 *      #########------------------- 100 % [ETA [23h] 59m 59s]
 *
 *      APB_OPT_RAND_DURATION = Use random duration_seconds. Min 10s, max 5min.
 *      Progress bar runs over time with random duration_seconds.
 *
 * @param const char* label The label to show.
 * @param double value Progress bar percentage value or duration_seconds in duration_seconds with option APB_OPT_VALUE_DURATION.
 * @param unsigned int options Optional.
 */
void ascii_progressbar(ascii_progressbar_t* ptr) {
    assert( ptr != NULL );
    assert( ptr->label != NULL );
    ascii_hide_cursor();

    if ( ptr->options & APB_OPT_RAND_DURATION ) {
        int max = ASCII_RAND_DURATION_MAX, min = ASCII_RAND_DURATION_MIN;
        srand( time( 0 ) );
        ptr->duration_seconds = ( rand() % ( max - min + 1 ) ) + min;
    }

    int dots = 50;
    int sleep_time_per_dot_ms = (int) ( ptr->duration_seconds * 1000000 / dots );
    int i_start = (int) strlen( ptr->label ) + 2;
    time( &ptr->start_time );

    char bar[dots + 1];
    memset( bar, 0, dots * sizeof(char));
    if ( ptr->type == APB_TYPE_SHEBANG ) {
        memset( bar, '-', dots );
    }
    bar[dots] = '\0';

    char pbchar = (char)( ptr->type == APB_TYPE_SHEBANG ? '#' : '.' );

    if ( ptr->options & APB_OPT_LABEL_NL ) {
        printf( "\n%c[2K%c[1F%s%c[1E", /* erase line */ ASCII_ESC, /* mv cur 1 up to begin */ ASCII_ESC, ptr->label, /* mv cur 1 down */ ASCII_ESC );
        i_start = 0;
    } else {
        printf( "%c[2K%c[1G%s", /* erase line */ ASCII_ESC, /* mv cur to col 1 */ ASCII_ESC, ptr->label );
    }

    printf( " %c[%dG %s", ASCII_ESC, i_start, bar );

    int i_end = i_start + dots;
    for( int i = i_start; i <= i_end; i++ ) {
        printf( "%c[%dG%c", ASCII_ESC, i, pbchar );

        if ( ptr->options & APB_OPT_ETA_LABEL ) {
            printf( "%c[%dG ", ASCII_ESC, i_end + 1 );
            ascii_progressbar_eta( ptr );
        }

        usleep( sleep_time_per_dot_ms );
        fflush( stdout );
    }

    if ( ! ( ptr->options & APB_OPT_ETA_LABEL ) ) {
        printf( " %c[1C%c[32mdone%c[0m", ASCII_ESC, ASCII_ESC, ASCII_ESC );
    }

    ascii_show_cursor();
    printf("\n");
    fflush( stdout );
    ascii_progressbar_free( ptr );
}

/**
 * malloc new progressbar struct.
 *
 * @param const char* label The label.
 * @param double duration The duration in seconds.
 * @param int opt Optional. Options.
 * @return ascii_progressbar_t*
 */
ascii_progressbar_t* ascii_progressbar_new(const char* label, double duration, int opt) {
    ascii_progressbar_t* pb = malloc(sizeof(ascii_progressbar_t));
    pb->options |= APB_OPT_DEFAULT;
    if ( opt != 0 ) {
        pb->options = opt;
    }

    pb->type = APB_TYPE_SHEBANG;
    pb->duration_seconds = duration;
    pb->eta_hours = 0;
    pb->eta_minutes = 0;
    pb->eta_seconds = 0;
    pb->label = malloc(sizeof(char) );
    pb->start_time = 0;
    ascii_progressbar_set_label( pb, label );
    return pb;
}

/**
 * Free progressbar struct.
 *
 * @param progressbar_t* ptr The progress bar pointer.
 */
void ascii_progressbar_free(ascii_progressbar_t* ptr) {
    assert( ptr != NULL );
    free( ptr->label );
    free( ptr );
}

/**
 * Enable option in progress bar.
 *
 * @param progressbar_t* ptr The progress bar.
 * @param ascii_progressbar_opt_e opt The option to enable.
 */
void ascii_progressbar_set_opt(ascii_progressbar_t* ptr, ascii_progressbar_opt_e opt) {
    assert( ptr != NULL );
    ptr->options |= opt;
}

/**
 * Print eta and percent label escape sequence.
 *
 * @param progressbar_t* ptr The progress bar pointer.
 */
void ascii_progressbar_eta(ascii_progressbar_t* ptr) {
    assert( ptr != NULL );

    double diff_seconds = difftime( time( NULL ), ptr->start_time );
    double percent = diff_seconds / ptr->duration_seconds * 100;

    int rseconds = (int) ( ( diff_seconds / percent ) * ( 100 - percent ) );
    int hours = rseconds / 3600;
    rseconds -= hours * 3600;

    int minutes = rseconds / 60;
    rseconds -= minutes * 60;

    if ( hours > 0 ) {
        printf( "%.2f%% | ETA %dh %dm %ds", percent, (int) hours, (int) minutes, (int) rseconds );
    } else if ( minutes > 0 ) {
        printf( "%.2f%% | ETA %dm %ds%c[0K", percent, (int) minutes, (int) rseconds, ASCII_ESC );
    } else if ( rseconds >= 0 ) {
        printf( "%.2f%% | ETA %ds%c[0K", percent, (int) rseconds, ASCII_ESC );
    } else {
        printf( "%.2f%%%c[0K", percent, ASCII_ESC );
    }
}

/**
 * Set progressbar label.
 *
 * @param ascii_progressbar_t* ptr The progress bar pointer.
 * @param const char* label The label string.
 */
void ascii_progressbar_set_label(ascii_progressbar_t* ptr, const char* label) {
    assert( ptr != NULL );
    assert( label != NULL );
    ptr->label = realloc( ptr->label, sizeof(label) );
    assert( ptr->label != NULL );
    strcpy( ptr->label, label );
}