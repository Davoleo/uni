----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/23/2025 01:01:09 PM
-- Design Name: 
-- Module Name: fifo - Behavioral
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


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity fifo is 
generic (
  Nb: integer;
  log2NFIFO: integer);
port (en, rst, clk: in std_logic;
din: in signed(Nb-1 downto 0);
dout: out signed(Nb-1 downto 0) );
end fifo;

architecture Behavioral of fifo is 

constant NFIFO: integer:=2**log2NFIFO;
type fifo_output_ALL is array (NFIFO-1 downto 0) of signed(Nb-1 downto 0);

signal fifo_output_ALLs: fifo_output_ALL;

begin

process(clk)
begin
if rst='0' then
    fifo_output_ALLs(NFIFO-1 downto 0) <= (others=>(others=>'0'));
    else if rising_edge(clk) then
    
        if en='1' then
            fifo_output_ALLs <= din&fifo_output_ALLs(NFIFO-1 downto 1);
        end if;   
                 
    end if;
    
end if;

end process;

dout <= fifo_output_ALLs(0);

end Behavioral;
