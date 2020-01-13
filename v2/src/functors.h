#include <math.h>

namespace oort {
    class UnaryFunction {
    public:
        virtual ~UnaryFunction() {};
        virtual double operator() (const double value) = 0;
    };

    class Sigmoid : public UnaryFunction {
    public:
        Sigmoid() {};
        ~Sigmoid() {};
        double operator() (const double value);
    };

    class FastSigmoid : public UnaryFunction {
    public:
        FastSigmoid() {};
        ~FastSigmoid() {};
        double operator() (const double value);
    };

    double der(const double value, UnaryFunction* function);
    double prim(const double value, UnaryFunction* function);
}
