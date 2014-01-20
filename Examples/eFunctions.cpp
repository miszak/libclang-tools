#include <iostream>
#include <string>

void f1();

namespace A
{
    void f2();

    namespace X
    {
        void f3();
        void f4();
    }

    class Y
    {
    public:
        void f5();
        void f6();
    };

    void Y::f6() {}
    void f1() {}

    void f7() {}
    void X::f4() {}

    template<typename T> T f8() { return T(); }
}

void f1() {}
