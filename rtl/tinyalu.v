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
reg [15:0] result_next;
wire [15:0] result_aax;
wire [15:0] result_mul;
wire done_aax;
wire done_mul;
assign result = result_aax | result_mul;
assign done = done_aax | done_mul;
delay_aax aax(
    .clk(clk),
    .reset_n(reset_n),
    .start(start),
    .result_i(result_next),
    .result_o(result_aax),
    .done(done_aax)
);
delay_mul mul(
    .clk(clk),
    .reset_n(reset_n),
    .start(start),
    .result_i(result_next),
    .result_o(result_mul),
    .done(done_mul)
);
always @(*)
    case(op)
        add_op: result_next[7:0] = A + B;
        and_op: result_next[7:0] = A & B;
        xor_op: result_next[7:0] = A ^ B;
        mul_op: result_next = A * B;
    endcase
endmodule

module delay_aax(
    input clk, reset_n, start,
    input [15:0] result_i,
    output done,
    output [15:0] result_o
);
reg [15:0] result_reg1;
reg done_reg1;
assign done = done_reg1;
assign result_o = result_reg1;
always @(posedge clk)
    if(!reset_n) begin
        result_reg1 <= 0;
        done_reg1 <= 0;
    end else begin
        result_reg1 <= result_i;
        done_reg1 <= start;
    end
endmodule

module delay_mul(
    input clk, reset_n, start,
    input [15:0] result_i,
    output done,
    output [15:0] result_o
);
reg [15:0] result_reg1;
reg [15:0] result_reg2;
reg [15:0] result_reg3;
reg done_reg1;
reg done_reg2;
reg done_reg3;
assign done = done_reg3;
assign result_o = result_reg3;
always @(posedge clk)
    if(!reset_n) begin
        result_reg1 <= 0;
        result_reg2 <= 0;
        result_reg3 <= 0;
        done_reg1 <= 0;
        done_reg2 <= 0;
        done_reg3 <= 0;
    end else begin
        result_reg1 <= result_i;
        result_reg2 <= result_reg1;
        result_reg3 <= result_reg2;
        done_reg1 <= start;
        done_reg2 <= done_reg1;
        done_reg3 <= done_reg2;
    end
endmodule
