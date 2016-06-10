module syncro( input async,
					input clock,
					output sync);
					

					
reg [2:0]q=3'd0;

wire reset=~async & q[2];
assign sync=q[2];

always@(posedge async, posedge reset)
begin
	if(reset==1'b1)
		begin
			q[0]<=1'b0;
		end
	else
		begin
			q[0]<=1'b1;
		end
end


always@(posedge clock)
begin
	q[1]<=q[0];
	q[2]<=q[1];
end



endmodule


