----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/23/2025 01:49:05 PM
-- Design Name: 
-- Module Name: tf_fifo - Behavioral
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

entity tf_fifo is
--  Port ( );
end tf_fifo;

architecture Behavioral of tf_fifo is

constant numb:integer:=8;

component fifo is 
generic (
  Nb: integer:=numb;
  log2NFIFO: integer:=6);
port (en, rst, clk: in std_logic;
din: in signed(Nb-1 downto 0);
dout: out signed(Nb-1 downto 0) );
end component;

component counter is
    generic ( Nb : integer:=numb);
    port( T           :in std_logic;
          clk         :in std_logic; 
          OUT_COUNT   :out std_logic_vector(Nb-1 downto 0)
    );
    end component;

signal clks, rsts, ens: std_logic;
signal dinfifo: std_logic_vector(numb-1 downto 0);
signal doutfifo: signed(numb-1 downto 0);
--file file_to_be_read : text;
begin

clk_process: process
begin
clks <= '1'; wait for 10 ns;
clks <= '0'; wait for 10 ns;
end process;

en_process: process
begin
ens <= '0'; wait for 30 ns;
ens <= '1'; wait for 1 ms;
end process;

rst_process: process
begin
rsts <= '0'; wait for 10 ns;
rsts <= '1'; wait for 10000 ns;
end process;

--.
dut_counter: counter port map ('1', clks, dinfifo);
dut_fifo: fifo port map (ens, rsts, clks, signed(dinfifo), doutfifo);

--process(clks)
--begin
--if rising_edge(clks) then
--    dinfifo1 <= dinfifo;
--end if;
--
--end process;


-- READ into a file
--process
--    variable linevariable_in     : line;
--    variable numb_of_sample :integer:=0; 
--    variable datafile: std_logic_vector(7 downto 0);
--  begin
 
--    file_open(file_to_be_read, "mysignal.txt",  read_mode);
     
--    while numb_of_sample < 4096  loop
--      readline(file_to_be_read, linevariable_in);
--      read(linevariable_in, datafile);
 
--      dinfifo1 <= datafile;
  
--      wait for 20 ns;
--      numb_of_sample:=numb_of_sample+1;
      
--    end loop;
 
--    file_close(file_to_be_read);

     
--    wait;

--  end process;

end Behavioral;
