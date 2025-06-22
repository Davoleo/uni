----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/23/2025 08:14:40 PM
-- Design Name: 
-- Module Name: tb_filter_ma - Behavioral
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

entity tb_filter_ma is
--  Port ( );
end tb_filter_ma;

architecture Behavioral of tb_filter_ma is

constant numbNbf:integer:=8;
constant numblog2NFIFOf:integer:=6;
constant numb_of_samples_constant:integer:=4096;

component filter_ma is
generic (
  Nbf: integer:=8;
  log2NFIFOf: integer:=7);
port (en, rst, clk: in std_logic;
datain:in signed(Nbf-1 downto 0);
dataout: out signed(Nbf+log2NFIFOf-1 downto 0));
end component;

file file_to_be_read, file_to_be_written : text;
signal dfilter_output: signed(numbNbf+numblog2NFIFOf-1 downto 0);
signal dfilter_input: signed(numbNbf-1 downto 0);
signal ens, rsts, clks: std_logic;

begin

----------------------------------------------------------
-- clk, enable and reset generator -----------------------
----------------------------------------------------------
clk_process: process
begin
clks <= '1'; wait for 10 ns;
clks <= '0'; wait for 10 ns;
end process;

en_process: process
begin
ens <= '0'; wait for 50 ns;
ens <= '1'; wait for 1 ms;
end process;

rst_process: process
begin
rsts <= '0'; wait for 30ns;
rsts <= '1'; wait for 1ms;
end process;

----------------- THE FILTER -----------------------------
dut_filterma: filter_ma generic map (Nbf => numbNBf, log2NFIFOf => numblog2NFIFOf)
port map (en => ens, rst => rsts, clk => clks, 
datain => dfilter_input, dataout => dfilter_output);
----------------------------------------------------------

----------------------------------------------------------
-- READ from a file --------------------------------------
----------------------------------------------------------
process
    variable linevariable_in     : line;
    variable numb_of_sample :integer:=0; 
    variable datafile: std_logic_vector(7 downto 0);
  begin
 
    file_open(file_to_be_read, "mysignal.txt",  read_mode);
     
    while numb_of_sample < 4096  loop
      readline(file_to_be_read, linevariable_in);
      read(linevariable_in, datafile);
 
      dfilter_input <= signed(datafile);
  
      wait for 20 ns;
      numb_of_sample:=numb_of_sample+1;
      
    end loop;
 
    file_close(file_to_be_read);

     
    wait;

  end process;
  
----------------------------------------------------------
-- WRITE to a file ---------------------------------------
----------------------------------------------------------
process
    variable linevariable_out: line;
    variable spacevariable: character;
    variable items_count :integer:=0; 
  begin
 
    file_open(file_to_be_written, "output_results_filtered.txt", write_mode);
 
    while items_count < 4096  loop
 
      wait for 20 ns;
 
      write(linevariable_out, std_logic_vector(dfilter_output), right, 8);
      writeline(file_to_be_written, linevariable_out);
      items_count:=items_count+1;
      
    end loop;
 
    -- file_close(file_VECTORS);
    file_close(file_to_be_written);
     
    wait;

  end process;


end Behavioral;
