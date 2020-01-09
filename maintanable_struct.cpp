#include <iostream>
#include <ostream>

// interesting alternative to array 
// if new data members are added, alter only both appl() implementations
// should be easy for compiler inline apply() calls
struct Traffic {
    double flows;
    double packets;
    double bytes;

    // return reference because of chaining
    template<typename F>
    Traffic& apply(F f) {
        f(flows);
        f(packets);
        f(bytes);
        return *this;
    }

        template<typename F>
    Traffic& apply(F f, const Traffic& t) {
        f(flows, t.flows);
        f(packets, t.packets);
        f(bytes, t.bytes);
        return *this;
    }

    Traffic& operator+=(double d) {
        apply([d](double& dd){ dd += d; });
        return *this;
    }

    Traffic& operator+=(const Traffic& r) {
        apply([](double& dd, double d){ dd += d; }, r);
        return *this;
    }

};

inline Traffic operator+(const Traffic& l, const Traffic& r) {
    Traffic res {l};
    return res += r;
}

inline std::ostream& operator<<(std::ostream& os, Traffic& t) {
    t.apply([&os](double d){ os << d << ' '; });
    return os;
}

int main() {
    Traffic t1 {10.0, 20.0, 30.0};
    Traffic t2 {1.0, 2.0, 3.0};

    Traffic t3 {t1+t2};

    std::cout << t3 << '\n';
}
