#include "progress.h"
#include <stdio.h>

int main() {
    ascii_progressbar_t* one_line = ascii_progressbar_new( "One line", 5, 0);
    ascii_progressbar( one_line );
    printf("---------------------------------------\n");

    ascii_progressbar_t* one_line_dotted = ascii_progressbar_new( "One line dotted", 5, 0);
    one_line_dotted->type = APB_TYPE_DOTTED;
    ascii_progressbar( one_line_dotted );
    printf("---------------------------------------\n");

    ascii_progressbar_t* one_line_eta = ascii_progressbar_new( "One line ETA", 5, APB_OPT_ETA_LABEL );
    ascii_progressbar( one_line_eta );
    printf("---------------------------------------\n");

    ascii_progressbar_t* one_line_dot_eta = ascii_progressbar_new( "One line dot ETA", 5, APB_OPT_ETA_LABEL );
    one_line_dot_eta->type = APB_TYPE_DOTTED;
    ascii_progressbar( one_line_dot_eta );
    printf("---------------------------------------\n");

    ascii_progressbar_t* two_line = ascii_progressbar_new( "Two line", 5, APB_OPT_LABEL_NL );
    ascii_progressbar( two_line );
    printf("---------------------------------------\n");

    ascii_progressbar_t* two_line_dot = ascii_progressbar_new( "Two line dot", 5, APB_OPT_LABEL_NL );
    two_line_dot->type = APB_TYPE_DOTTED;
    ascii_progressbar( two_line_dot );
    printf("---------------------------------------\n");

    ascii_progressbar_t* two_line_eta = ascii_progressbar_new( "Two line eta", 5, APB_OPT_LABEL_NL | APB_OPT_ETA_LABEL );
    ascii_progressbar( two_line_eta );
    printf("---------------------------------------\n");

    ascii_progressbar_t* two_line_dot_eta = ascii_progressbar_new( "Two line dot eta", 5, APB_OPT_LABEL_NL | APB_OPT_ETA_LABEL );
    two_line_dot_eta->type = APB_TYPE_DOTTED;
    ascii_progressbar( two_line_dot_eta );
    printf("---------------------------------------\n");

    return 0;
}
