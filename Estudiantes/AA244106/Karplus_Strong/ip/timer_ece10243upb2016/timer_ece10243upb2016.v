module timer_ece10243upb2016(
		input clk, //avalon clk
		input reset, //avaln reset
		input [2:0]timer_address, //avalon direccionamiento io_address
		input timer_chipselect, //avalon io_chipselect
		input timer_write, //avalon io_wr
		input [31:0]timer_writedata, //avalon writedata io_write data
		output [31:0]timer_readdata, //avalon read_data io_read_data
		output timer_irq, //avalon interrupcion del sistema
		//salida externa para el nios II
		output toggle
);

reg [31:0]timer_in=32'd0;

reg interrupt=1'b0;
assign timer_irq=interrupt;

wire request_irq;
wire wr_en=timer_chipselect & timer_write;
wire timer_in_wr=(timer_address[2:0]==3'd0)? wr_en: 1'b0;
wire timer_interrupt_wr=(timer_address[2:0]==3'd1)? wr_en: 1'b0;

assign timer_readdata[31:0]=(timer_address[2:0]==3'd0)? timer_in[31:0]:
									 ({31'd0, interrupt});

always@(posedge clk)
begin
	if(reset)
	begin
		timer_in[31:0]<=32'd0;
		interrupt<=1'b0;
	end
	else
	begin
		timer_in[31:0]<=timer_in[31:0];
		interrupt<=interrupt;
		if(timer_in_wr)
		begin
			timer_in[31:0]<=timer_writedata[31:0];
		end
		if(timer_interrupt_wr)
		begin
			interrupt<=timer_writedata[0];
		end
		else if(request_irq)
		begin
			interrupt<=1'b1;
		end
	end
end

 div_freq div_freq_inst
(
	.clk(clk) ,	// input  clk_sig
	.in(timer_in[31:0]) ,	// input [31:0] in_sig
	.div(toggle) 	// output  div_sig
);

syncro syncro_inst
(
	.async(toggle) ,	// input  async_sig
	.clock(clk) ,	// input  clock_sig
	.sync(request_irq) 	// output  sync_sig
);
	
endmodule
