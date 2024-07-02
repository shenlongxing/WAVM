#include <signal.h>

void f10() {
    raise(SIGABRT);
    return;
}

void f9() { f10(); }

void f8() { f9(); }

void f7() { f8(); }

void f6() { f7(); }

void f5() { f6(); }

void f4() { f5(); }

void f3() { f4(); }

void f2() { f3(); }

void f1() { f2(); }

void f0() { f1(); }

int main() {
    f0();
    return 0;
}
