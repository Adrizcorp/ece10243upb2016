module chu_avalon_vga_de2
   (
    input wire clk, reset,
    // Avalon MM interface
    input wire [19:0] vga_address,
    input wire vga_chipselect, vga_write, vga_read,
    input wire [31:0] vga_writedata,
    output wire [31:0] vga_readdata,
    // conduit (to VGA monitor)
    output wire vsync, hsync,
    //***************** for DE2 board *******************
    output wire [29:0] rgb,
    output wire vdac_clk,
    output wire vdac_blank_n,
    output wire vdac_sync_n,
    //***************************************************
    // conduit (to/from SRAM)
    output wire [17:0] sram_addr,
    inout [15:0] sram_dq,
    output sram_ce_n, sram_oe_n, sram_we_n,
    output sram_lb_n, sram_ub_n
 );

   // signal declaration
   reg video_on_reg, vsync_reg, hsync_reg;
   wire vsync_i, hsync_i, video_on_i, p_tick;
   wire [9:0] pixel_x, pixel_y;
   wire wr_vram, rd_vram;
   wire [7:0] cpu_rd_data, vga_rd_data;
   wire [29:0] color;

   // body
   //==================================================================
   // instantiation  
   //==================================================================
   // instantiate VGA sync circuit
   vga_sync sync_unit
      (.clk(clk), .reset(reset), .hsync_i(hsync_i), .vsync_i(vsync_i), 
       .video_on_i(video_on_i), .p_tick(p_tick), 
       .pixel_x(pixel_x), .pixel_y(pixel_y));
   // instantiate video SRAM control
   vram_ctrl vram_unit
      (.clk(clk), .reset(reset), 
       // from video sync
       .pixel_x(pixel_x), .pixel_y(pixel_y), .p_tick(p_tick), 
       // avalon bus interface 
       .vga_rd_data(vga_rd_data), .cpu_rd_data(cpu_rd_data),
       .cpu_wr_data(vga_writedata[7:0]),      
       .cpu_addr(vga_address[18:0]),      
       .cpu_mem_wr(wr_vram), .cpu_mem_rd(rd_vram),
       // to/from SRAM chip
       .sram_addr(sram_addr), .sram_dq(sram_dq),
       .sram_we_n(sram_we_n), .sram_oe_n(sram_oe_n), .sram_ce_n(sram_ce_n),
       .sram_ub_n(sram_ub_n), .sram_lb_n(sram_lb_n)
      );
   // instantiate palette table (8-bit to 12-bit conversion)
   palette_de2 palet_unit
      (.color_in(vga_rd_data), .color_out(color));
   //==================================================================
   // registers, write decoding, and read multiplexing 
   //==================================================================
   // delay vga sync to accomodate memory access 
   always @(posedge clk)
      if (p_tick)
         begin
            vsync_reg <= vsync_i;
            hsync_reg <= hsync_i;
            video_on_reg <= video_on_i;
         end 
   assign vsync = vsync_reg;    
   assign hsync = hsync_reg;    
   // memory read/write decoding
   assign wr_vram = vga_write & vga_chipselect &  ~vga_address[19];             
   assign rd_vram = vga_read & vga_chipselect &  ~vga_address[19];             
   // read data mux
   assign vga_readdata = ~vga_address[19] ? {24'b0, cpu_rd_data} :
                                            {12'b0, pixel_y, pixel_x};                
   // video output
   assign rgb = video_on_reg ? color : 12'b0; 
   //***************   For DE2  ****************************************
   assign vdac_sync_n = 0;              // lower voltage in blank period 
   assign vdac_blank_n = video_on_reg; 
   assign vdac_clk = p_tick;            // clock for the video DAC 
   //*******************************************************************
 
endmodule