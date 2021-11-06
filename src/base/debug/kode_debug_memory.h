#ifndef kode_debug_memory_included
#define kode_debug_memory_included
//----------------------------------------------------------------------

//#include <iostream>
//#include <signal.h>
//#include <string>
//#include <dlfcn.h>
//#include <cxxabi.h>
#include <regex> // gets rid of "error: ‘nothrow_t’ in namespace ‘std’ does not name a type"
//#include <execinfo.h>



//class KODE_DebugMemory {
//};

//----------------------------------------------------------------------

// /home/skei/test -> test

//----------

// not thread-safe..

const char* _kode_debug_prefix_file = "";
int         _kode_debug_prefix_line = 0;
const char* _kode_debug_prefix_func = "";

void _kode_debug_prefix(const char* file, int line, const char* func) {
  _kode_debug_prefix_file = file;
  _kode_debug_prefix_line = line;
  _kode_debug_prefix_func = func;
}

#define CLEAR_PREFIX  _kode_debug_prefix("?",0,"?")
#define DELETE_PREFIX _kode_debug_prefix(__FILE__,__LINE__,__FUNCTION__)

//----------

void* _kode_malloc(size_t sz, const char* file, int line, const char* func) {
  //printf("_kode_malloc\n");
  return std::malloc(sz);
}

void _kode_free(void *p, const char* file, int line, const char* func) {
  //printf("_kode_free\n");
  std::free(p);
}

void* _kode_new(size_t sz, const char* file, int line, const char* func) {
  //printf("_kode_new\n");
  return std::malloc(sz);
}

void _kode_delete(void *p) {
  //printf("_kode_delete\n");
  std::free(p);
}

void _kode_delete(void *p, int32_t sz) {
  //printf("_kode_delete sz\n");
  std::free(p);
}

//----------------------------------------------------------------------

void* operator new(std::size_t sz, const char* file, int line, const char* func) {
  printf("%s:%i:%s | new %zi\n",_kode_debug_strip_path(file),line,func,sz);
  return _kode_new(sz,file,line,func);
}


void* operator new[](std::size_t count, const char* file, int line, const char* func) {
  printf("%s:%i:%s | new[] %zi\n",_kode_debug_strip_path(file),line,func,count);
  return _kode_new(count,file,line,func);
}

void* operator new(std::size_t count, const std::nothrow_t& tag, const char* file, int line, const char* func) {
  printf("%s:%i:%s | new %zi tag\n",_kode_debug_strip_path(file),line,func,count);
  return _kode_new(count,file,line,func);
}

void* operator new[](std::size_t count, const std::nothrow_t& tag, const char* file, int line, const char* func) {
  printf("%s:%i:%s | new[] %zi tag\n",_kode_debug_strip_path(file),line,func,count);
  return _kode_new(count,file,line,func);
}

//----------

void operator delete(void* ptr) noexcept {
  printf("%s:%i:%s | delete %p\n",_kode_debug_strip_path(_kode_debug_prefix_file),_kode_debug_prefix_line,_kode_debug_prefix_func,ptr);
  CLEAR_PREFIX;
  _kode_delete(ptr);
}

void operator delete[](void* ptr) noexcept {
  printf("%s:%i:%s | delete[] %p\n",_kode_debug_strip_path(_kode_debug_prefix_file),_kode_debug_prefix_line,_kode_debug_prefix_func,ptr);
  CLEAR_PREFIX;
  _kode_delete(ptr);
}

void operator delete(void* ptr, const std::nothrow_t& tag) noexcept {
  printf("%s:%i:%s | delete %p tag\n",_kode_debug_strip_path(_kode_debug_prefix_file),_kode_debug_prefix_line,_kode_debug_prefix_func,ptr);
  CLEAR_PREFIX;
  _kode_delete(ptr);
}

void operator delete[](void* ptr, const std::nothrow_t& tag) noexcept {
  printf("%s:%i:%s | delete %p tag\n",_kode_debug_strip_path(_kode_debug_prefix_file),_kode_debug_prefix_line,_kode_debug_prefix_func,ptr);
  CLEAR_PREFIX;
  _kode_delete(ptr);
}

void operator delete(void* ptr, std::size_t sz) noexcept {
  printf("%s:%i:%s | delete %p size %zi\n",_kode_debug_strip_path(_kode_debug_prefix_file),_kode_debug_prefix_line,_kode_debug_prefix_func,ptr,sz);
  CLEAR_PREFIX;
  _kode_delete(ptr);
}

void operator delete[](void* ptr, std::size_t sz) noexcept {
  printf("%s:%i:%s | delete[] %p size %zi\n",_kode_debug_strip_path(_kode_debug_prefix_file),_kode_debug_prefix_line,_kode_debug_prefix_func,ptr,sz);
  CLEAR_PREFIX;
  _kode_delete(ptr);
}

//----------

#define malloc(size)      _kode_malloc(size,__FILE__,__LINE__,__FUNCTION__)
//#define calloc(num,size)  _calloc(num,size,__FILE__,__LINE__,__FUNCTION__)
//#define realloc(ptr,size) _realloc(ptr,size,__FILE__,__LINE__,__FUNCTION__)
#define free(ptr)         _kode_free(ptr,__FILE__,__LINE__,__FUNCTION__)
#define new               new(__FILE__,__LINE__,__FUNCTION__)
#define delete            DELETE_PREFIX; delete


//----------------------------------------------------------------------
#endif

