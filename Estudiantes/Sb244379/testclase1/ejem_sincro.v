module sincro(
	input async,
	input clock,
	output sync
); // This synchronizer is used to detect a signal that be in the middle of the clock and it's not  detected

//Assign register

reg[2:0]q=3'd0; //initialize value of "d"

//Wire is used to conect two parts

wire reset=~async & q[2];

//Assign the values for the output for the last register

assign sync=q[2];

//assign each process for each one
always@(posedge async, posedge reset)
begin
	if (reset==1'b1)
		begin
			q[0]<=1'b0;
		end
	else
		begin
			q[0]<=01'b1;
		end
end

always@(posedge clock)
begin
	q[1]<=q[0];
	q[2]<=q[1];
end



endmodule
