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

entity read_signal_from_file is port(
dout: out std_logic_vector(7 downto 0));
end read_signal_from_file;

architecture Behavioral of read_signal_from_file is
file file_to_be_read : text;

begin

-- READ from a file
process
    variable linevariable_in     : line;
    variable numb_of_sample :integer:=0; 
    variable datafile: std_logic_vector(7 downto 0);
  begin
 
    file_open(file_to_be_read, "mysignal.txt",  read_mode);
     
    while numb_of_sample < 4096  loop
      readline(file_to_be_read, linevariable_in);
      read(linevariable_in, datafile);
 
      dout <= datafile;
  
      wait for 20 ns;
      numb_of_sample:=numb_of_sample+1;
      
    end loop;
 
    file_close(file_to_be_read);

     
    wait;

  end process;

end Behavioral;
















