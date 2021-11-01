#ifndef kode_debug_stack_trace
#define kode_debug_stack_trace
//----------------------------------------------------------------------

// https://gist.github.com/heapwolf/26ff79b82e5f310e2d53

#include <iostream>
#include <signal.h>
#include <string>
#include <dlfcn.h>
#include <cxxabi.h>
#include <regex>
#include <execinfo.h>

class KODE_DebugStackTrace {

//------------------------------
public:
//------------------------------

  struct sigaction sa;

//------------------------------
public:
//------------------------------

  KODE_DebugStackTrace() {
    using namespace std;

    auto backtrace_handler = [](int sig) {
      string white = "";//"\033[1;37m";
      string blue = "";//"\033[1;34m";
      cout << white << "Error: ";
      switch (sig) {
        case SIGSEGV:
          cout << "Segmentation fault" << endl;
          break;
        case SIGFPE:
          cout << "Floating point exception" << endl;
          break;
        case SIGBUS:
          cout << "An invalid pointer was dereferenced" << endl;
          break;
      }
      void* callstack[128];
      size_t size = backtrace(callstack, 128);
      char** symbols = backtrace_symbols(callstack, size);
      for (size_t i = 0; i < size; i++) {
        Dl_info info;
        //int res =
        dladdr(callstack[i], &info);
        string s = symbols[i];
        int f = s.find_last_of(" + ");
        s = s.substr(0, f - 2);
        f = s.find_last_of(" ");
        s = s.substr(f + 1, s.size());
        int status = 0;
        char* name = abi::__cxa_demangle(s.c_str(), NULL, NULL, &status);
        if (status == 0 && string(name).find("Trace::Trace()") == string::npos) {
          cout << white << "  at " << blue << name
               << white << " in " << info.dli_fname << endl;
        }
      }
      abort();
    };

    sa.sa_handler = backtrace_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGFPE, &sa, NULL);
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGBUS, &sa, NULL);

  }

};

KODE_DebugStackTrace KODE_DEBUG_STACK_TRACE;

//----------------------------------------------------------------------
#endif
