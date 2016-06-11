module ejem_mux (
	input [1:0]sel,
	output [7:0]out
	);

	//assign the output0 using condition that will can to pin up the value that we wanted
assign out[7:0]=sel[1:0]==(2'b00)? 8'b10101010:
					 sel[1:0]==(2'b01)? 8'b11110000:
					 sel[1:0]==(2'b10)? 8'b11111100:
					 8'b00001111;
endmodule
