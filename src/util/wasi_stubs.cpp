// Stubs for libc++ iostream functions missing in WASI
// These are no-ops since Z3's iostream usage is primarily for debug output
//
// The symbols are provided with their mangled names because the class
// definitions already exist in libc++ headers - we just need implementations.

#ifdef __wasi__

#include <cstddef>

extern "C" {

// std::basic_ostream<char, std::char_traits<char>>::flush()
void _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEE5flushEv(void* self) {
    // no-op flush - WASI handles buffering automatically
}

// std::basic_ostream<char, std::char_traits<char>>::sentry::sentry(basic_ostream&)
void _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_(void* self, void* stream) {
    // no-op sentry constructor
}

// std::basic_ostream<char, std::char_traits<char>>::sentry::~sentry()
void _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev(void* self) {
    // no-op sentry destructor
}

// std::basic_ostream<char, std::char_traits<char>>::operator<<(unsigned int)
void* _ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEElsEj(void* self, unsigned int val) {
    return self; // return self for chaining
}

// std::locale::use_facet(std::locale::id const&)
void* _ZNKSt3__26locale9use_facetERNS0_2idE(void* self, void* id) {
    return nullptr;
}

// std::ios_base::getloc() const
void* _ZNKSt3__28ios_base6getlocEv(void* self) {
    static char dummy_locale[64] = {0};
    return dummy_locale;
}

// std::locale::~locale()
void _ZNSt3__26localeD1Ev(void* self) {
    // no-op destructor
}

// std::ios_base::clear(unsigned int)
void _ZNSt3__28ios_base5clearEj(void* self, unsigned int state) {
    // no-op
}

// std::ctype<char>::id - static member variable
char _ZNSt3__25ctypeIcE2idE = 0;

}

#endif // __wasi__
