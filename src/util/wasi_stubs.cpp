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

// std::basic_ostream<char, std::char_traits<char>>::flush()
void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEE5flushEv(void* self) {
    return self;
}

// std::basic_ostream sentry constructor/destructor
void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_(void* self, void* stream) {
    return self;
}

void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev(void* self) {
    return self;
}

// std::basic_ostream::operator<<(unsigned int)
void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEElsEj(void* self, unsigned int val) {
    return self;
}

// std::locale functions
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
    // In WASI, we can't propagate exceptions - abort
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
// ============================================================================

void _ZNSt9exceptionD2Ev(void* self) {}
void _ZNSt9exceptionD1Ev(void* self) {}
void _ZNSt9exceptionD0Ev(void* self) { free(self); }
const char* _ZNKSt9exception4whatEv(void* self) { return "std::exception"; }

void _ZNSt9bad_allocD2Ev(void* self) {}
void _ZNSt9bad_allocD1Ev(void* self) {}
void _ZNSt9bad_allocD0Ev(void* self) { free(self); }
const char* _ZNKSt9bad_alloc4whatEv(void* self) { return "std::bad_alloc"; }

void _ZNSt12length_errorD2Ev(void* self) {}
void _ZNSt12length_errorD1Ev(void* self) {}
void _ZNSt12length_errorD0Ev(void* self) { free(self); }

void _ZNSt12out_of_rangeD2Ev(void* self) {}
void _ZNSt12out_of_rangeD1Ev(void* self) {}
void _ZNSt12out_of_rangeD0Ev(void* self) { free(self); }

void _ZNSt11logic_errorD2Ev(void* self) {}
void _ZNSt11logic_errorD1Ev(void* self) {}
void _ZNSt11logic_errorD0Ev(void* self) { free(self); }

void _ZNSt13runtime_errorD2Ev(void* self) {}
void _ZNSt13runtime_errorD1Ev(void* self) {}
void _ZNSt13runtime_errorD0Ev(void* self) { free(self); }

}

#endif // __wasi__
