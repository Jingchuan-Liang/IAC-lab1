module counter #(
     parameter WIDTH = 8 //witdth is the "bandwidth" of this compoent, 位数
)
(
    //interface signals 
    input logic clk, //clock - 单bit信号，不需要位序声明
    input logic rst, //reset - 单bit信号，不需要位序声明 (asynchronous)
    input logic en, //counter enable - 单bit信号，不需要位序声明 (asynchronous)
    output logic [WIDTH-1:0] count //count output - 多位信号需要声明位序[MSB:LSB]
    // [WIDTH-1:0] 定义大端序：MSB在左边，LSB在右边
    // logic类型支持4种状态：0(低电平), 1(高电平), X(无关), Z(高阻态, 输出阻抗高，即断路，该信号pin不驱动其他pin), 
);

// Asynchronous Reset and Enable with Rising Edge Clock
// Features:
// 1. Count updates ONLY on rising edge of clk (sequential)
// 2. Reset is asynchronous - takes effect immediately regardless of clock
// 3. Enable is asynchronous - enables/disables counter immediately
// 4. Counter increments when enabled and on clock edge
always_ff @(posedge clk or posedge rst) begin
    // Asynchronous reset: Priority 1 - takes effect immediately
    if (rst)
        count <= {WIDTH{1'b0}};  // Reset to all zeros
    // Asynchronous enable: Priority 2 - counter increments when enabled
    else if (en)
        count <= count + {{WIDTH-1{1'b0}}, en};  // count + 1
    // When disabled: count holds its value
end 

endmodule 
