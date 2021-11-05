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

//----------

const char* KODE_SignalNames[] = {
  "0",          // 0    kill(pid, 0)
  "SIGHUP",     // 1    Hangup.
  "SIGINT",     // 2    Interactive attention signal.
  "SIGQUIT",    // 3    Quit.
  "SIGILL",     // 4    Illegal instruction.
  "SIGTRAP",    // 5    Trace/breakpoint trap.
  "SIGABRT",    // 6    Abnormal termination.
  "7",
  "SIGFPE",     // 8    Erroneous arithmetic operation.
  "SIGKILL",    // 9    Killed.
  "SIGBUS",     // 10   Bus error.
  "SIGSEGV",    // 11   Invalid access to storage.
  "SIGSYS",     // 12   Bad system call.
  "SIGPIPE",    // 13   Broken pipe.
  "SIGALRM",    // 14   Alarm clock.
  "SIGTERM",    // 15   Termination request.
  "SIGURG",     // 16   Urgent data is available at a socket.
  "SIGSTOP",    // 17   Stop, unblockable.
  "SIGTSTP",    // 18   Keyboard stop.
  "SIGCONT",    // 19   Continue.
  "SIGCHLD",    // 20   Child terminated or stopped.
  "SIGTTIN",    // 21   Background read from control terminal.
  "SIGTTOU",    // 22   Background write to control terminal.
  "SIGPOLL",    // 23   Pollable event occurred (System V).
  "SIGXCPU",    // 24   CPU time limit exceeded.
  "SIGXFSZ",    // 25   File size limit exceeded.
  "SIGVTALRM",  // 26   Virtual timer expired.
  "SIGPROF",    // 27   Profiling timer expired.
  "SIGWINCH",   // 28   Window size change (4.3 BSD, Sun).
  "29",
  "SIGUSR1",    // 30   User-defined signal 1.
  "SIGUSR2"     // 31   User-defined signal 2.
};

const char* KODE_SignalDescriptions[] = {
  "kill(pid,0)",                            // 0
  "Hangup",                                 // 1
  "Interactive attention signal",           // 2
  "Quit",                                   // 3
  "Illegal instruction",                    // 4
  "Trace/breakpoint trap",                  // 5
  "Abnormal termination",                   // 6
  "7",                                      // 7
  "Erroneous arithmetic operation",         // 8
  "Killed",                                 // 9
  "Bus error",                              // 10
  "Invalid access to storage",              // 11
  "Bad system call",                        // 12
  "Broken pipe",                            // 13
  "Alarm clock",                            // 14
  "Termination request",                    // 15
  "Urgent data is available at a socket",   // 16
  "Stop, unblockable",                      // 17
  "Keyboard stop",                          // 18
  "Continue",                               // 19
  "Child terminated or stopped",            // 20
  "Background read from control terminal",  // 21
  "Background write to control terminal",   // 22
  "Pollable event occurred (System V)",     // 23
  "CPU time limit exceeded",                // 24
  "File size limit exceeded",               // 25
  "Virtual timer expired",                  // 26
  "Profiling timer expired",                // 27
  "Window size change (4.3 BSD, Sun)",      // 28
  "29",                                     // 29
  "User-defined signal 1",                  // 30
  "User-defined signal 2"                   // 31
};

//----------------------------------------------------------------------

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
      //string white = "";//"\033[1;37m";
      //string blue = "";//"\033[1;34m";
      //cout << white << "Error: ";
      //switch (sig) {
      //  case SIGSEGV:
      //    cout << "Segmentation fault" << endl;
      //    break;
      //  case SIGFPE:
      //    cout << "Floating point exception" << endl;
      //    break;
      //  case SIGBUS:
      //    cout << "An invalid pointer was dereferenced" << endl;
      //    break;
      //}

      KODE_DPrint("Error: %s (%i) %s\n", KODE_SignalNames[sig], sig, KODE_SignalDescriptions[sig]);

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
        //if (status == 0 && string(name).find("Trace::Trace()") == string::npos) {
        //  cout << white << "  at " << blue << name
        //       << white << " in " << info.dli_fname << endl;
        //}
        //if (status == 0 ) {g
          if ((name[0] != 0) && (info.dli_fname[0] != 0)) {
            KODE_DPrint(" at %s in %s\n",name,_kode_debug_strip_path(info.dli_fname));
          }
        //}
      }
      //abort();
      exit(1);
    };

    sa.sa_handler = backtrace_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;//SA_RESTART;

    //sigaction(SIGFPE, &sa, NULL);
    //sigaction(SIGSEGV, &sa, NULL);
    //sigaction(SIGBUS, &sa, NULL);

  //sigaction( 0,         &sa, NULL);   // 0    kill(pid, 0)
  //sigaction( SIGHUP,    &sa, NULL);   // 1    Hangup.
  //sigaction( SIGINT,    &sa, NULL);   // 2    Interactive attention signal.
  //sigaction( SIGQUIT,   &sa, NULL);   // 3    Quit.
    sigaction( SIGILL,    &sa, NULL);   // 4    Illegal instruction.
  //sigaction( SIGTRAP,   &sa, NULL);   // 5    Trace/breakpoint trap.
    sigaction( SIGABRT,   &sa, NULL);   // 6    Abnormal termination.
  //sigaction( 7,         &sa, NULL);
    sigaction( SIGFPE,    &sa, NULL);   // 8    Erroneous arithmetic operation.
  //sigaction( SIGKILL,   &sa, NULL);   // 9    Killed.
  //sigaction( SIGBUS,    &sa, NULL);   // 10   Bus error.
    sigaction( SIGSEGV,   &sa, NULL);   // 11   Invalid access to storage.
  //sigaction( SIGSYS,    &sa, NULL);   // 12   Bad system call.
  //sigaction( SIGPIPE,   &sa, NULL);   // 13   Broken pipe.
  //sigaction( SIGALRM,   &sa, NULL);   // 14   Alarm clock.
  //sigaction( SIGTERM,   &sa, NULL);   // 15   Termination request.
  //sigaction( SIGURG,    &sa, NULL);   // 16   Urgent data is available at a socket.
  //sigaction( SIGSTOP,   &sa, NULL);   // 17   Stop, unblockable.
  //sigaction( SIGTSTP,   &sa, NULL);   // 18   Keyboard stop.
  //sigaction( SIGCONT,   &sa, NULL);   // 19   Continue.
  //sigaction( SIGCHLD,   &sa, NULL);   // 20   Child terminated or stopped.
  //sigaction( SIGTTIN,   &sa, NULL);   // 21   Background read from control terminal.
  //sigaction( SIGTTOU,   &sa, NULL);   // 22   Background write to control terminal.
  //sigaction( SIGPOLL,   &sa, NULL);   // 23   Pollable event occurred (System V).
  //sigaction( SIGXCPU,   &sa, NULL);   // 24   CPU time limit exceeded.
  //sigaction( SIGXFSZ,   &sa, NULL);   // 25   File size limit exceeded.
  //sigaction( SIGVTALRM, &sa, NULL);   // 26   Virtual timer expired.
  //sigaction( SIGPROF,   &sa, NULL);   // 27   Profiling timer expired.
  //sigaction( SIGWINCH , &sa, NULL);   // 28   Window size change (4.3 BSD, Sun).
  //sigaction( 29,        &sa, NULL);
  //sigaction( SIGUSR1,   &sa, NULL);   // 30   User-defined signal 1.
  //sigaction( SIGUSR2,   &sa, NULL);   // 31   User-defined signal 2.


  }

};

//----------

KODE_DebugStackTrace KODE_DEBUG_STACK_TRACE;

//----------------------------------------------------------------------
#endif
