module div_freq(
			input clk,
			input [31:0]in,
			output div
	);

reg [31:0]contadorcito=32'd0;

reg toggle=1'b0;
assign div=toggle;

always@(posedge clk)
begin
	toggle<=toggle;
	contadorcito[31:0]<=contadorcito[31:0]+1'b1;
	if(contadorcito[31:0]>=in[31:0])
		begin
			toggle<=~toggle;
			contadorcito[31:0]<=32'd0;
		end
end


	
endmodule
