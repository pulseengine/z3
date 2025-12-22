// Stubs for libc++ iostream and exception functions missing in WASI
// These are no-ops since Z3's iostream usage is primarily for debug output
//
// The symbols are provided with their mangled names because the class
// definitions already exist in libc++ headers - we just need implementations.
//
// IMPORTANT: Return types must match C++ ABI expectations:
// - Destructors and many methods return `this` for chaining
// - getloc() uses an out-parameter pattern

#ifdef __wasi__

#include <cstddef>
#include <cstdlib>

extern "C" {

// ============================================================================
// iostream stubs
// ============================================================================

// std::basic_ostream<char, std::char_traits<char>>::flush()
// Returns this for chaining
void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEE5flushEv(void* self) {
    return self;
}

// std::basic_ostream<char, std::char_traits<char>>::sentry::sentry(basic_ostream&)
// Returns this
void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_(void* self, void* stream) {
    return self;
}

// std::basic_ostream<char, std::char_traits<char>>::sentry::~sentry()
// Returns this
void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev(void* self) {
    return self;
}

// std::basic_ostream<char, std::char_traits<char>>::operator<<(unsigned int)
void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEElsEj(void* self, unsigned int val) {
    return self;
}

// std::locale::use_facet(std::locale::id const&)
void* _ZNKSt3__26locale9use_facetERNS0_2idE(void* self, void* id) {
    return nullptr;
}

// std::ios_base::getloc() const
// Uses out-parameter: (this, result_ptr) -> void
void _ZNKSt3__28ios_base6getlocEv(void* self, void* result) {
    // Zero-initialize the result locale
    for (int i = 0; i < 64; i++) {
        ((char*)result)[i] = 0;
    }
}

// std::locale::~locale()
// Returns this
void* _ZNSt3__26localeD1Ev(void* self) {
    return self;
}

// std::ios_base::clear(unsigned int)
void _ZNSt3__28ios_base5clearEj(void* self, unsigned int state) {
    // no-op
}

// std::ctype<char>::id - static member variable
char _ZNSt3__25ctypeIcE2idE = 0;

// ============================================================================
// C++ exception handling stubs (libcxxabi)
// Z3 uses exceptions but in WASI single-threaded mode, we abort on throw
// ============================================================================

// Allocate memory for exception object
void* __cxa_allocate_exception(size_t thrown_size) {
    // Allocate space for exception object
    void* ptr = malloc(thrown_size);
    if (!ptr) {
        abort();
    }
    return ptr;
}

// Free exception memory
void __cxa_free_exception(void* thrown_exception) {
    free(thrown_exception);
}

// Throw an exception - in WASI we abort
[[noreturn]]
void __cxa_throw(void* thrown_exception, void* tinfo, void (*dest)(void*)) {
    // In single-threaded WASI, we can't propagate exceptions
    // Just abort - this matches Z3_SINGLE_THREADED behavior
    abort();
}

// Begin catch - should never be called if we abort on throw
void* __cxa_begin_catch(void* exception_object) {
    abort();
    return nullptr;
}

// End catch
void __cxa_end_catch() {
    // no-op
}

// Rethrow exception
[[noreturn]]
void __cxa_rethrow() {
    abort();
}

// Get exception pointer
void* __cxa_current_primary_exception() {
    return nullptr;
}

// Exception type info comparison
int __cxa_type_match(void* thrown_type, void* catch_type, void** thrown_ptr) {
    return 0; // No match
}

// Guard for thread-safe initialization (single-threaded, no-op)
int __cxa_guard_acquire(long long* guard_object) {
    if (*guard_object) return 0;
    return 1;
}

void __cxa_guard_release(long long* guard_object) {
    *guard_object = 1;
}

void __cxa_guard_abort(long long* guard_object) {
    // no-op
}

// Pure virtual call handler
[[noreturn]]
void __cxa_pure_virtual() {
    abort();
}

// Deleted virtual call handler
[[noreturn]]
void __cxa_deleted_virtual() {
    abort();
}

// ============================================================================
// C++ new/delete operators
// These are normally provided by libc++abi but may be missing in WASI
// ============================================================================

// operator new(size_t) - _Znwm
void* _Znwm(size_t size) {
    void* ptr = malloc(size ? size : 1);
    if (!ptr) {
        abort(); // In WASI, we abort on allocation failure
    }
    return ptr;
}

// operator new[](size_t) - _Znam
void* _Znam(size_t size) {
    return _Znwm(size);
}

// operator delete(void*) - _ZdlPv
void _ZdlPv(void* ptr) {
    free(ptr);
}

// operator delete[](void*) - _ZdaPv
void _ZdaPv(void* ptr) {
    free(ptr);
}

// operator delete(void*, size_t) - _ZdlPvm (sized delete)
void _ZdlPvm(void* ptr, size_t) {
    free(ptr);
}

// operator delete[](void*, size_t) - _ZdaPvm (sized delete)
void _ZdaPvm(void* ptr, size_t) {
    free(ptr);
}

// operator new(size_t, std::nothrow_t const&) - _ZnwmRKSt9nothrow_t
void* _ZnwmRKSt9nothrow_t(size_t size, void*) {
    return malloc(size ? size : 1);
}

// operator new[](size_t, std::nothrow_t const&) - _ZnamRKSt9nothrow_t
void* _ZnamRKSt9nothrow_t(size_t size, void*) {
    return malloc(size ? size : 1);
}

// operator delete(void*, std::nothrow_t const&) - _ZdlPvRKSt9nothrow_t
void _ZdlPvRKSt9nothrow_t(void* ptr, void*) {
    free(ptr);
}

// operator delete[](void*, std::nothrow_t const&) - _ZdaPvRKSt9nothrow_t
void _ZdaPvRKSt9nothrow_t(void* ptr, void*) {
    free(ptr);
}

}

#endif // __wasi__
