module counter #(
     parameter WIDTH = 8 //witdth is the "bandwidth" of this compoent, 位数
)
(
    //interface signals 
    input logic clk, //clock - 单bit信号，不需要位序声明
    input logic rst, //reset - 单bit信号，不需要位序声明
    input logic en, //counter enable - 单bit信号，不需要位序声明
    output logic [WIDTH-1:0] count //count output - 多位信号需要声明位序[MSB:LSB]
    // [WIDTH-1:0] 定义大端序：MSB在左边，LSB在右边
    // logic类型支持4种状态：0(低电平), 1(高电平), X(无关), Z(高阻态, 输出阻抗高，即断路，该信号pin不驱动其他pin), 
);

always_ff @ (posedge clk)  // always后面跟_ff是指flip flop的sequential logic, 在时钟的上升沿触发(就是clock的positive edge,这是sensitivity list的其中一个)
    if (rst) count <= {WIDTH{1'b0}}; //'<='的意思是get(被赋值), 注意这个是non-blocking. {WIDTH{1'b0}}: 重复操作符，创建 WIDTH=8 个 0, 所以当rst为1的时候,count值为00000000
    else     count <= count + {{WIDTH-1{1'b0}},en}; //注意,{}构建的是一整个数字, ,en相当于concatenate(连接)，相当于count + 00000001 (en的值)

endmodule
