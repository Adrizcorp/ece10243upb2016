module div_freq(
	input clk,
	input [31:0]in,
	output div
);

//Assign register

reg[31:0]contadorcito=32'd0; //initialize value of "contadorcito"
reg toggle=1'b0;

//Wire is used to conect some parts



//Assign the values for the outputs

assign div=toggle;

//assign each process for each one
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
