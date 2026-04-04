// RUN: %clang_cc1 -std=c++98 -fexceptions -fcxx-exceptions -pedantic-errors %s -verify-directives -verify=expected,cxx98,cxx98-17
// RUN: %clang_cc1 -std=c++11 -fexceptions -fcxx-exceptions -pedantic-errors %s -verify-directives -verify=expected,cxx98-17
// RUN: %clang_cc1 -std=c++14 -fexceptions -fcxx-exceptions -pedantic-errors %s -verify-directives -verify=expected,cxx98-17
// RUN: %clang_cc1 -std=c++17 -fexceptions -fcxx-exceptions -pedantic-errors %s -verify-directives -verify=expected,cxx98-17
// RUN: %clang_cc1 -std=c++20 -fexceptions -fcxx-exceptions -pedantic-errors %s -verify-directives -verify=expected,since-cxx20
// RUN: %clang_cc1 -std=c++23 -fexceptions -fcxx-exceptions -pedantic-errors %s -verify-directives -verify=expected,since-cxx20
// RUN: %clang_cc1 -std=c++2c -fexceptions -fcxx-exceptions -pedantic-errors %s -verify-directives -verify=expected,since-cxx20

// cxx98-no-diagnostics

namespace cwg3106 { // cwg3106: 2.7
#if __cplusplus >= 201103L
const char str[9] = R"(\u{1234})";
#endif
} // namespace cwg3106

namespace cwg3128 { // cwg3128: 2.7
#if __cplusplus >= 201103L
void f();
static_assert(noexcept(noexcept(f())), "");
#endif
} // namespace cwg3128

namespace cwg3151 { // cwg3151: 2.7
#if __cplusplus >= 201402L
auto lambda = []{};
struct S : decltype(lambda) {};
static_assert(!__is_final(decltype(lambda)), "");
#endif
} // namespace cwg3151

namespace cwg3156 { // cwg3156: 3.5
#if __cplusplus >= 202002L
struct C { // #cwg3156-C
  C(int) = delete; // #cwg3156-C-int
  C(){};
};

decltype([b = C(3)](){ return 4; }()) x;
// since-cxx20-error@-1 {{functional-style cast from 'int' to 'C' uses deleted function}}
//   since-cxx20-note@#cwg3156-C-int {{candidate constructor has been explicitly deleted}}
//   since-cxx20-note@#cwg3156-C {{candidate constructor (the implicit copy constructor)}}
//   since-cxx20-note@#cwg3156-C {{candidate constructor (the implicit move constructor)}}
#endif
} // namespace cwg3156

// cwg3172: na

namespace cwg3179 { // cwg3179: 23 tentatively ready 2026-04-30
#if __cplusplus >= 201103L
  template<class> using void_t = void;
  template<class T> struct S {
    void f(void_t<T*>);
    // expected-error@-1 {{'void' as parameter must not involve template parameters}}

    using X = int(void_t<T*>);
    // expected-error@-1 {{'void' as parameter must not involve template parameters}}
  };
  template<class T> void g(decltype((void)(T*)0));
  // expected-error@-1 {{'void' as parameter must not involve template parameters}}
#endif
#if __cplusplus >= 202002L
  template<class T> bool v = requires(void_t<T>) { true; };
  // expected-error@-1 {{'void' as parameter must not involve template parameters}}
#endif
} // namespace cwg3179
