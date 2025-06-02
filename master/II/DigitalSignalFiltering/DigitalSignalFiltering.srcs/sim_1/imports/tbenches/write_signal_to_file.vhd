----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/22/2025 12:02:04 AM
-- Design Name: 
-- Module Name: read_signal_from_file - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use STD.textio.all;
use ieee.std_logic_textio.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity write_signal_to_file is 
end write_signal_to_file;

architecture Behavioral of write_signal_to_file is

component counter is
    generic ( Nb : integer:=8) ;
    port( T           :in std_logic;
          clk         :in std_logic; 
          OUT_COUNT   :out std_logic_vector(Nb-1 downto 0)
    );
end component;


file file_to_be_written : text;
signal clks: std_logic;
signal outcount: std_logic_vector(7 downto 0); -- outcount is the variable thta will be written in "output_results_mdm_TEST.txt"

begin

clk_process: process
begin
clks <= '1'; wait for 10 ns;
clks <= '0'; wait for 10 ns;
end process;

dut_counter: counter port map ('1', clks, outcount);

-- WRITE to file
process
    variable linevariable_out: line;
    variable spacevariable: character;
    variable items_count :integer:=0; 
  begin
 
    file_open(file_to_be_written, "output_results_mdm_TEST.txt", write_mode);
 
    while items_count < 4096  loop
 
      wait for 20 ns;
 
      write(linevariable_out, outcount, right, 8);
      writeline(file_to_be_written, linevariable_out);
      items_count:=items_count+1;
      
    end loop;
 
    -- file_close(file_VECTORS);
    file_close(file_to_be_written);
     
    wait;

  end process;

end Behavioral;
















