%{
#include "identifier.tab.h"  // Include Bison's header for token definitions
#include <stdio.h>
%}

%%

[a-zA-Z][a-zA-Z0-9]*    { return IDENTIFIER; }
[0-9]+                  { return DIGIT; }
\n                      { return EOL; }
.                       { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}

