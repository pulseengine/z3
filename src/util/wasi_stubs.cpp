// Stubs for libc++ iostream functions missing in WASI
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

extern "C" {

// ============================================================================
// iostream stubs
// These functions are missing from WASI libc++ but Z3 references them
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

}

#endif // __wasi__
