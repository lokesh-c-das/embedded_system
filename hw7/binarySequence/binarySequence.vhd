-- A VHDL program for detecting binary sequence "11010"
-- Develop By: Lokesh
-- Date: 04/10/2021
-- Load necessary libraries
library ieee;
use ieee.std_logic_1164.all;

-- Entity
entity binarySequence is
	port(clk, reset, sequenc_in : in std_logic;
		 F 				: out std_logic
		 );
end entity;
-- Architecture
architecture seq_arch of binarySequence is
	type states is (s0, s1, s2, s3, s4, s5);
	signal state : states;
	
	begin
	process(clk, reset)
		begin
		if reset = '1' then
			state <= s0;
		elsif rising_edge(clk) then
			case state is
				when s0 =>
					if sequenc_in = '1' then
						state <= s1;
					else
						state <= s0;
					end if;
				when s1 =>
					if sequenc_in = '1' then
						state <= s2;
					else
						state <= s0;
					end if;
				when s2 =>
					if sequenc_in = '0' then
						state <= s3;
					else
						state <= s1;
					end if;
				when s3 =>
					if sequenc_in = '1' then
						state <= s4;
					else
						state <= s0;
					end if;
				when s4 =>
					if sequenc_in = '0' then 
						state <= s5;
					else
						state <= s1;
					end if;
				when s5 =>
					if sequenc_in = '1' then
						state <= s1;
					else 
						state <= s0;
					end if;
			end case;
		end if;
	end process;
	-- output process
	process(state)
	begin
		case state is
			when s0 =>
				F <= '0';
			when s1 =>
				F <= '0';
			when s2 =>
				F <= '0';
			when s3 =>
				F <= '0';
			when s4 =>
				F <= '0';
			when s5 =>
				F <= '1'; -- output '1' if binary sequence '11010' succesfully gets detected
		end case;
	end process;
end architecture;