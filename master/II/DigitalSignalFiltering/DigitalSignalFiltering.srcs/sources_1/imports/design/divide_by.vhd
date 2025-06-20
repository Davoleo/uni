----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/23/2025 05:09:57 PM
-- Design Name: 
-- Module Name: divide_by - Behavioral
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

entity divide_by is 
  generic (
    Nb: integer;
    log2NFIFO: integer
  );
  port (
    en, rst, clk: in std_logic;
    datain: in signed(Nb + log2NFIFO - 1 downto 0);
    dataout: out signed(Nb + log2NFIFO - 1 downto 0)
  );
end divide_by;

architecture Behavioral of divide_by is
  constant Nacc: integer := Nb + log2NFIFO;
  signal reg: signed(Nacc - 1 downto 0);
begin

  process(clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        reg <= (others => '0');
      elsif en = '1' then
        reg(Nacc - log2NFIFO-1 downto 0) <= datain(Nacc - 1 downto log2NFIFO);
        reg(Nacc-1 downto Nacc-log2NFIFO) <= (others => '0');
      end if;
    end if;
  end process;

  dataout <= reg;

end Behavioral;
