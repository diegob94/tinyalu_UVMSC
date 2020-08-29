
`define VL_PUBLIC_GETTER(signal) \
function get_``signal``;         \
    /* verilator public */       \
    get_``signal`` = ``signal``; \
endfunction // VL_PUBLIC_GETTER



