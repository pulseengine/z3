// Stubs for C++ runtime functions missing in WASI libc++
//
// libc++ provides iostream, chrono, locale - those are NOT stubbed here.
// What's missing and stubbed here:
// - Exception handling (__cxa_*) - libc++abi is built without exceptions
// - new/delete operators - need explicit linking
// - std::exception class hierarchy - for exception types
// - RTTI (__dynamic_cast) - for polymorphic casts

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
    return src_ptr;
}

// type_info comparison
int __cxa_can_catch(void* thrown_type, void* catch_type, void** thrown_ptr) {
    return 0; // Can't catch anything
}

// typeid support - pointers to type_info objects
void* _ZTIPKc = nullptr;
void* _ZTIPc = nullptr;
void* _ZTIi = nullptr;
void* _ZTIl = nullptr;
void* _ZTIv = nullptr;

}

#endif // __wasi__
