`include "vl_utils_h.v"

module tinyalu (
    input [7:0] A, B,
    input [2:0] op,
    input clk, reset_n, start,
    output done,
    output [15:0] result
);
parameter no_op = 0;
parameter add_op = 1;
parameter and_op = 2;
parameter xor_op = 3;
parameter mul_op = 4;
reg [15:0] result_reg1;
reg [15:0] result_reg2;
reg [15:0] result_reg3;
reg done_reg1;
reg done_reg2;
reg done_reg3;
reg [15:0] result_next;
assign result = op == mul_op ? result_reg3 : result_reg1;
assign done = op == mul_op ? done_reg3 : done_reg1;
always @(posedge clk)
    if(!reset_n) begin
        result_reg1 <= 0;
        result_reg2 <= 0;
        result_reg3 <= 0;
    end else if(start && op == mul_op) begin
        result_reg1 <= result_next;
        result_reg2 <= result_reg1;
        result_reg3 <= result_reg2;
        done_reg1 <= start;
        done_reg2 <= done_reg1;
        done_reg3 <= done_reg2;
    end else if(start) begin
        result_reg1 <= result_next;
        done_reg1 <= start;
    end
always @(*)
    case(op)
        add_op: result_next[7:0] = A + B;
        and_op: result_next[7:0] = A & B;
        xor_op: result_next[7:0] = A ^ B;
        mul_op: result_next = A * B;
    endcase
`ifdef verilator
    `VL_PUBLIC_GETTER(done_reg1);
`endif
endmodule

