# ANSI Progress Bar
These progress bars are build with ansi escape sequences. No need to use ncurses. Some variations are included and can be set by options.

Tested on macOS iTerm and Terminal. Should be working on any vt100 compatible terminal.

## Features
- compatible with C99
- no dependencies
- label and progress bar on one line
- label and progress bar on next line
- \# as progress indicator
- . as progress indicator
- ETA label at the end of the progress line
- Duration in seconds
- Use as drop in

## Usage
```c
// Copy the progress.h/.c file to your project.
#include "progress.h"
// Look at the examples.
```

## Examples

### One line, default options.
```c
ascii_progressbar_t* one_line = ascii_progressbar_new("One line", 5.0f, 0);
ascii_progressbar(one_line); 
// this frees the memory!
// Don't use `one_line` after you printed it with ascii_progressbar();
 
// output
// One line ###################################################  done
```

### One line, dotted indicator
```c
ascii_progressbar_t* one_line_dotted = ascii_progressbar_new("One line dotted", 5.0f, 0);
one_line_dotted->type = APB_TYPE_DOTTED;
ascii_progressbar(one_line_dotted);

// output
// One line dotted ...................................................  done
```

### One line, ETA label
```c
ascii_progressbar_t* one_line_eta = ascii_progressbar_new("One line ETA", 5.0f, APB_OPT_ETA_LABEL);
ascii_progressbar(one_line_eta);

// output
// One line ETA ################################################### 100.00% | ETA 0s
```

### Two line
```c
ascii_progressbar_t* two_line = ascii_progressbar_new("Two line", 5.0f, APB_OPT_LABEL_NL);
ascii_progressbar(two_line);

// output
// Two line
// ##################################################  done
```

### Two line, ETA label
```c
ascii_progressbar_t* two_line_eta = ascii_progressbar_new("Two line eta", 5.0f, APB_OPT_LABEL_NL | APB_OPT_ETA_LABEL);
ascii_progressbar(two_line_eta);

// output
// Two line eta
// ################################################## 100.00% | ETA 0s
```

### Set option to existing progress bar
```c
ascii_progressbar_t* somewhere_initialized = ascii_progressbar_new(...);
ascii_progressbar_set_opt(somewhere_initialized, APB_OPT_ETA_LABEL);
```

## License
This software is distributed under MIT license, so feel free to integrate it in your commercial products. 