#ifndef COVERAGE_H
#define COVERAGE_H

#include <uvm>
#include "fc4sc.hpp"
#include "tinyalu.h"
#include "sequence_item.h"

class coverage : public uvm::uvm_subscriber<sequence_item> {
  private:
    uint8_t A;
    uint8_t B;
    op_t op_set;
    class op_cov : public covergroup {
      private:
        coverage* cov;
      public:
        CG_CONS(op_cov, coverage* cov=NULL) {};
        COVERPOINT(uint32_t, op_set_cvp, cov->op_set._to_integral()){
            bin<uint32_t>("single_cycle", interval(op_t::add_op,op_t::mul_op), op_t::no_op),
            bin<uint32_t>("multi_cycle", op_t::mul_op)
        };
            //! \todo implement transition coverage in fc4sc
            //bins opn_rst[] = ([add_op:mul_op] => rst_op);
            //bins rst_opn[] = (rst_op => [add_op:mul_op]);

            //bins sngl_mul[] = ([add_op:xor_op],no_op => mul_op);
            //bins mul_sngl[] = (mul_op => [add_op:xor_op], no_op);

            //bins twoops[] = ([add_op:mul_op] [* 2]);
            //bins manymult = (mul_op [* 3:5]);

            //bins rstmulrst   = (rst_op => mul_op [=  2] => rst_op);
            //bins rstmulrstim = (rst_op => mul_op [-> 2] => rst_op);
    };
    class zeros_or_ones_on_ops : public covergroup {
      private:
        coverage* cov;
      public:
        CG_CONS(zeros_or_ones_on_ops, coverage* cov=NULL) {};
        COVERPOINT(uint32_t, all_ops, cov->op_set._to_integral()){
            ignore_bin<uint32_t>("null_ops", op_t::rst_op, op_t::no_op)
        };
        COVERPOINT(uint8_t, a_leg, cov->A){
            bin<uint8_t>("zeros", 0x00),
            bin<uint8_t>("others", interval(1,0xFE)),
            bin<uint8_t>("ones", 0xFF)
        };
        COVERPOINT(uint8_t, b_leg, cov->B){
            bin<uint8_t>("zeros", 0x00),
            bin<uint8_t>("others", interval(1,0xFE)),
            bin<uint8_t>("ones", 0xFF)
        };
        cross<uint8_t,uint8_t,uint32_t> op_00_FF = cross<uint8_t,uint8_t,uint32_t>(this, &a_leg, &b_leg, &all_ops);
        //! \todo implement filtering
        //{
        //    bins add_00 = binsof (all_ops) intersect {add_op} &&
        //               (binsof (a_leg.zeros) || binsof (b_leg.zeros));
        //    bins add_FF = binsof (all_ops) intersect {add_op} &&
        //               (binsof (a_leg.ones) || binsof (b_leg.ones));
        //    bins and_00 = binsof (all_ops) intersect {and_op} &&
        //               (binsof (a_leg.zeros) || binsof (b_leg.zeros));
        //    bins and_FF = binsof (all_ops) intersect {and_op} &&
        //               (binsof (a_leg.ones) || binsof (b_leg.ones));
        //    bins xor_00 = binsof (all_ops) intersect {xor_op} &&
        //               (binsof (a_leg.zeros) || binsof (b_leg.zeros));
        //    bins xor_FF = binsof (all_ops) intersect {xor_op} &&
        //               (binsof (a_leg.ones) || binsof (b_leg.ones));
        //    bins mul_00 = binsof (all_ops) intersect {mul_op} &&
        //               (binsof (a_leg.zeros) || binsof (b_leg.zeros));
        //    bins mul_FF = binsof (all_ops) intersect {mul_op} &&
        //               (binsof (a_leg.ones) || binsof (b_leg.ones));
        //    bins mul_max = binsof (all_ops) intersect {mul_op} &&
        //                (binsof (a_leg.ones) && binsof (b_leg.ones));
        //    ignore_bins others_only =
        //                          binsof(a_leg.others) && binsof(b_leg.others);
        //}
    };
    op_cov op_cov_inst;
    zeros_or_ones_on_ops zeros_or_ones_on_ops_inst;
public:
    coverage(uvm::uvm_component_name);
    void write(const sequence_item&);
};

#endif // COVERAGE_H
