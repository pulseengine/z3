// Minimal stubs for C++ runtime functions missing in WASI
//
// libc++ provides: iostream, chrono, locale, exception class constructors
// libc++abi provides: exception destructors, RTTI (__dynamic_cast), guard functions
//
// What's still missing and stubbed here:
// - Exception handling (__cxa_throw, etc.) - libc++abi built without exceptions
// - new/delete operators - libc++abi references but doesn't define them

#ifdef __wasi__

#include <cstddef>
#include <cstdlib>

extern "C" {

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
// libc++abi references these but doesn't define them
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

}

#endif // __wasi__
