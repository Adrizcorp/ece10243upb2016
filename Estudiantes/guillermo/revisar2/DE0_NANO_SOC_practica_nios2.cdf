/* Quartus II 64-Bit Version 15.0.0 Build 145 04/22/2015 SJ Web Edition */
JedecChain;
	FileRevision(JESD32A);
	DefaultMfr(6E);

	P ActionCode(Ign)
		Device PartName(SOCVHPS) MfrSpec(OpMask(0));
	P ActionCode(Cfg)
		Device PartName(5CSEMA4U23) Path("D:/Material_FPGAs/nios2/karplus_strong_nios2_custom_hardware/") File("DE0_NANO_SOC_practica_nios2.sof") MfrSpec(OpMask(1));

ChainEnd;

AlteraBegin;
	ChainType(JTAG);
AlteraEnd;