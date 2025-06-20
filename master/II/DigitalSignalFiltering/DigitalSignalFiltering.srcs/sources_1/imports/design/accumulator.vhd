----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/23/2025 03:30:56 PM
-- Design Name: 
-- Module Name: accumulator - Behavioral
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

entity accumulator is
generic(
  Nb: integer;
  log2NFIFO: integer);
  port 
(en, rst, clk: in std_logic;
datain: in signed(Nb+log2NFIFO-1 downto 0);
dataout: out signed(Nb+log2NFIFO-1 downto 0));
end accumulator;

architecture Behavioral of accumulator is
  signal reg: signed(Nb + log2NFIFO - 1 downto 0);
begin

  process(clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        reg <= (others => '0');
      elsif en = '1' then
        reg <= datain;         
      end if;
    end if;
  end process;

  dataout <= reg; 

end Behavioral;