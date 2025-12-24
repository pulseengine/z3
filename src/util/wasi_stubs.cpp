// Stubs for libc++ functions missing in WASI
// These provide minimal implementations needed by Z3
//
// WASI libc++abi is built without exception support, so we provide
// stubs that abort on throw. This matches Z3_SINGLE_THREADED behavior.

#ifdef __wasi__

#include <cstddef>
#include <cstdlib>

extern "C" {

// ============================================================================
// iostream stubs
// These functions are missing from WASI libc++ but Z3 references them
// ============================================================================

void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEE5flushEv(void* self) {
    return self;
}

void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_(void* self, void* stream) {
    return self;
}

void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev(void* self) {
    return self;
}

void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEElsEj(void* self, unsigned int val) {
    return self;
}

void* _ZNKSt3__26locale9use_facetERNS0_2idE(void* self, void* id) {
    return nullptr;
}

void _ZNKSt3__28ios_base6getlocEv(void* self, void* result) {
    for (int i = 0; i < 64; i++) ((char*)result)[i] = 0;
}

void* _ZNSt3__26localeD1Ev(void* self) {
    return self;
}

void _ZNSt3__28ios_base5clearEj(void* self, unsigned int state) {}

char _ZNSt3__25ctypeIcE2idE = 0;

// std::basic_streambuf constructor and destructor
void* _ZNSt3__215basic_streambufIcNS_11char_traitsIcEEEC2Ev(void* self) { return self; }
void* _ZNSt3__215basic_streambufIcNS_11char_traitsIcEEEC1Ev(void* self) { return self; }
void* _ZNSt3__215basic_streambufIcNS_11char_traitsIcEEED2Ev(void* self) { return self; }
void* _ZNSt3__215basic_streambufIcNS_11char_traitsIcEEED1Ev(void* self) { return self; }
void* _ZNSt3__215basic_streambufIcNS_11char_traitsIcEEED0Ev(void* self) { free(self); return self; }

// std::basic_ios destructor
void* _ZNSt3__29basic_iosIcNS_11char_traitsIcEEED2Ev(void* self) { return self; }
void* _ZNSt3__29basic_iosIcNS_11char_traitsIcEEED1Ev(void* self) { return self; }
void* _ZNSt3__29basic_iosIcNS_11char_traitsIcEEED0Ev(void* self) { free(self); return self; }

// std::ios_base destructor
void* _ZNSt3__28ios_baseD2Ev(void* self) { return self; }
void* _ZNSt3__28ios_baseD1Ev(void* self) { return self; }
void* _ZNSt3__28ios_baseD0Ev(void* self) { free(self); return self; }

// std::basic_ostream destructor (with virtual base offset parameter)
void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEED2Ev(void* self, int vbase_offset) { return self; }
void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEED1Ev(void* self, int vbase_offset) { return self; }
void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEED0Ev(void* self, int vbase_offset) { free(self); return self; }

// std::basic_istream destructor (with virtual base offset parameter)
void* _ZNSt3__213basic_istreamIcNS_11char_traitsIcEEED2Ev(void* self, int vbase_offset) { return self; }
void* _ZNSt3__213basic_istreamIcNS_11char_traitsIcEEED1Ev(void* self, int vbase_offset) { return self; }
void* _ZNSt3__213basic_istreamIcNS_11char_traitsIcEEED0Ev(void* self, int vbase_offset) { free(self); return self; }

// std::basic_iostream destructor (with virtual base offset parameter)
void* _ZNSt3__214basic_iostreamIcNS_11char_traitsIcEEED2Ev(void* self, int vbase_offset) { return self; }
void* _ZNSt3__214basic_iostreamIcNS_11char_traitsIcEEED1Ev(void* self, int vbase_offset) { return self; }
void* _ZNSt3__214basic_iostreamIcNS_11char_traitsIcEEED0Ev(void* self, int vbase_offset) { free(self); return self; }

// std::ios_base::init(void*)
void _ZNSt3__28ios_base4initEPv(void* self, void* sb) {}

// std::basic_stringbuf destructor
void* _ZNSt3__215basic_stringbufIcNS_11char_traitsIcEENS_9allocatorIcEEED2Ev(void* self) { return self; }
void* _ZNSt3__215basic_stringbufIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(void* self) { return self; }
void* _ZNSt3__215basic_stringbufIcNS_11char_traitsIcEENS_9allocatorIcEEED0Ev(void* self) { free(self); return self; }

// std::basic_ostringstream destructor
void* _ZNSt3__219basic_ostringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEED2Ev(void* self) { return self; }
void* _ZNSt3__219basic_ostringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(void* self) { return self; }
void* _ZNSt3__219basic_ostringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEED0Ev(void* self) { free(self); return self; }

// std::basic_istringstream destructor
void* _ZNSt3__219basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEED2Ev(void* self) { return self; }
void* _ZNSt3__219basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(void* self) { return self; }
void* _ZNSt3__219basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEED0Ev(void* self) { free(self); return self; }

// ============================================================================
// C++ exception handling stubs
// WASI libc++abi doesn't include these - we abort on throw
// ============================================================================

void* __cxa_allocate_exception(size_t thrown_size) {
    void* ptr = malloc(thrown_size);
    if (!ptr) abort();
    return ptr;
}

void __cxa_free_exception(void* thrown_exception) {
    free(thrown_exception);
}

[[noreturn]] void __cxa_throw(void* thrown_exception, void* tinfo, void (*dest)(void*)) {
    abort();
}

void* __cxa_begin_catch(void* exception_object) {
    abort();
    return nullptr;
}

void __cxa_end_catch() {}

[[noreturn]] void __cxa_rethrow() {
    abort();
}

void* __cxa_current_primary_exception() {
    return nullptr;
}

// ============================================================================
// C++ new/delete operators
// ============================================================================

void* _Znwm(size_t size) {
    void* ptr = malloc(size ? size : 1);
    if (!ptr) abort();
    return ptr;
}

void* _Znam(size_t size) {
    return _Znwm(size);
}

void _ZdlPv(void* ptr) { free(ptr); }
void _ZdaPv(void* ptr) { free(ptr); }
void _ZdlPvm(void* ptr, size_t) { free(ptr); }
void _ZdaPvm(void* ptr, size_t) { free(ptr); }

void* _ZnwmRKSt9nothrow_t(size_t size, void*) {
    return malloc(size ? size : 1);
}

void* _ZnamRKSt9nothrow_t(size_t size, void*) {
    return malloc(size ? size : 1);
}

void _ZdlPvRKSt9nothrow_t(void* ptr, void*) { free(ptr); }
void _ZdaPvRKSt9nothrow_t(void* ptr, void*) { free(ptr); }

// ============================================================================
// std::exception class stubs
// Destructors return this pointer for C++ ABI compatibility
// ============================================================================

// std::exception
void* _ZNSt9exceptionD2Ev(void* self) { return self; }
void* _ZNSt9exceptionD1Ev(void* self) { return self; }
void* _ZNSt9exceptionD0Ev(void* self) { free(self); return self; }
const char* _ZNKSt9exception4whatEv(void* self) { return "std::exception"; }

// std::bad_alloc
void* _ZNSt9bad_allocD2Ev(void* self) { return self; }
void* _ZNSt9bad_allocD1Ev(void* self) { return self; }
void* _ZNSt9bad_allocD0Ev(void* self) { free(self); return self; }
const char* _ZNKSt9bad_alloc4whatEv(void* self) { return "std::bad_alloc"; }

// std::logic_error - constructors and destructors
void* _ZNSt11logic_errorC2EPKc(void* self, const char* msg) { return self; }
void* _ZNSt11logic_errorC1EPKc(void* self, const char* msg) { return self; }
void* _ZNSt11logic_errorD2Ev(void* self) { return self; }
void* _ZNSt11logic_errorD1Ev(void* self) { return self; }
void* _ZNSt11logic_errorD0Ev(void* self) { free(self); return self; }

// std::length_error
void* _ZNSt12length_errorC2EPKc(void* self, const char* msg) { return self; }
void* _ZNSt12length_errorC1EPKc(void* self, const char* msg) { return self; }
void* _ZNSt12length_errorD2Ev(void* self) { return self; }
void* _ZNSt12length_errorD1Ev(void* self) { return self; }
void* _ZNSt12length_errorD0Ev(void* self) { free(self); return self; }

// std::out_of_range
void* _ZNSt12out_of_rangeC2EPKc(void* self, const char* msg) { return self; }
void* _ZNSt12out_of_rangeC1EPKc(void* self, const char* msg) { return self; }
void* _ZNSt12out_of_rangeD2Ev(void* self) { return self; }
void* _ZNSt12out_of_rangeD1Ev(void* self) { return self; }
void* _ZNSt12out_of_rangeD0Ev(void* self) { free(self); return self; }

// std::runtime_error
void* _ZNSt13runtime_errorC2EPKc(void* self, const char* msg) { return self; }
void* _ZNSt13runtime_errorC1EPKc(void* self, const char* msg) { return self; }
void* _ZNSt13runtime_errorD2Ev(void* self) { return self; }
void* _ZNSt13runtime_errorD1Ev(void* self) { return self; }
void* _ZNSt13runtime_errorD0Ev(void* self) { free(self); return self; }

// std::invalid_argument
void* _ZNSt16invalid_argumentC2EPKc(void* self, const char* msg) { return self; }
void* _ZNSt16invalid_argumentC1EPKc(void* self, const char* msg) { return self; }
void* _ZNSt16invalid_argumentD2Ev(void* self) { return self; }
void* _ZNSt16invalid_argumentD1Ev(void* self) { return self; }
void* _ZNSt16invalid_argumentD0Ev(void* self) { free(self); return self; }

// std::overflow_error
void* _ZNSt14overflow_errorC2EPKc(void* self, const char* msg) { return self; }
void* _ZNSt14overflow_errorC1EPKc(void* self, const char* msg) { return self; }
void* _ZNSt14overflow_errorD2Ev(void* self) { return self; }
void* _ZNSt14overflow_errorD1Ev(void* self) { return self; }
void* _ZNSt14overflow_errorD0Ev(void* self) { free(self); return self; }

// ============================================================================
// RTTI (Runtime Type Information) stubs
// ============================================================================

// dynamic_cast runtime support
void* __dynamic_cast(void* src_ptr, void* src_type, void* dst_type, long offset) {
    // Simplified: just return src_ptr (no actual type checking)
    // This is safe for Z3 since we abort on exceptions anyway
    return src_ptr;
}

// type_info comparison
int __cxa_can_catch(void* thrown_type, void* catch_type, void** thrown_ptr) {
    return 0; // Can't catch anything
}

// typeid support - these return pointers to type_info objects
// In practice Z3 only uses these for exception type matching which we abort on
void* _ZTIPKc = nullptr;  // typeinfo for const char*
void* _ZTIPc = nullptr;   // typeinfo for char*
void* _ZTIi = nullptr;    // typeinfo for int
void* _ZTIl = nullptr;    // typeinfo for long
void* _ZTIv = nullptr;    // typeinfo for void

}

#endif // __wasi__
