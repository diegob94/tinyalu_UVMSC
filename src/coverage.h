#ifndef COVERAGE_H
#define COVERAGE_H

#include "fc4sc.hpp"

class output_coverage : public covergroup {
public:
    CG_CONS(output_coverage) {}

    void sample(int value, bool valid) {
        this->value = value;
        this->valid = valid;
        covergroup::sample();
    }

    COVERPOINT(int, data_ready_cvp, value){
        bin<int>("zero", 0),
        illegal_bin<int>("illegal_zero", 0),
        bin<int>("positive", interval(1,INT_MAX - 1)),
        bin<int>("negative", interval(-1,INT_MIN + 1))
    };

    COVERPOINT(int, output_valid_cvp, valid) {
        bin<int>("valid", 1),
        bin<int>("invalid", 0)
    };

private:
    int value = 0;
    int valid = 0;
};


#endif // COVERAGE_H
