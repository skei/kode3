
#include "kode.h"

//#define __cplusplus >= 201103L

//#include "../../clap/include/clap/clap.h"

#include <stdio.h>

int main() {
  return 0;
}

//----------

/*

1) c++11

  if i compile with -std=c++11
  i get this error:
    clap/version.h, 34, ‘constexpr bool clap_version_is_compatible(const clap_version&)’
    body of ‘constexpr’ function ‘constexpr bool clap_version_is_compatible(const clap_version&)’ not a return-statement
  without -std=c++11, it compiles ok

*/
