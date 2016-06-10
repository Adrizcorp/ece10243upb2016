module ejem_mux(
			input [1:0]sel,
			output [7:0]out
	);

assign out[7:0]= (sel[1:0]==2'b00)? 8'b10101010:
					  (sel[1:0]==2'b01)? 8'b11110000:
					  (sel[1:0]==2'd2)?  8'b10110001:
					  8'b00001111;
					  
	
endmodule

