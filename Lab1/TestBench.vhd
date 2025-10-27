library ieee;
use ieee.std_logic_1164.all;

entity TestBench is
end entity;

architecture Structural of TestBench is
	
	component AND2_1 is
		port(
			A, B: IN std_logic;
			Y : OUT std_logic
		);
	end component;
	
	signal a_s, b_s, y_s: std_logic := '0';
	
	signal clk: std_logic := '0';
	signal clk_period: time := 5 ns;
	
	begin
	
	DUT: AND2_1 port map(A => a_s, B => b_s, Y => y_s);
		
	myclk: process is
		begin
			clk <= '0';
			wait for clk_period/2;
			clk <= '1';
			wait for clk_period/2;
	end process myclk;
	
	andGate: process is
		begin
			a_s <= '1';
			b_s <= '1';
			wait for 10 ns;
			a_s <= '0';
			wait for 10 ns;
			a_s <= '1';
			b_s <= '0';
			wait for 10 ns;
			a_s <= '0';
			wait;
			
	end process andGate;

end architecture Structural;
