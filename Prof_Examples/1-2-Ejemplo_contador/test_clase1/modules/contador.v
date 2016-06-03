module contador(
		input clk,
		input reset,
		output [7:0]conteo
	);

reg [7:0]conteito=8'd0;
assign conteo[7:0]= conteito[7:0];
always@(posedge clk, negedge reset)
begin	
	if(reset==0)
		begin
			conteito[7:0]<=8'd0;
		end
	else
		begin
			conteito[7:0]<=conteito[7:0]+1'b1;
		end
end
	
	
	
endmodule
