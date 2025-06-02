----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/23/2025 03:08:49 PM
-- Design Name: 
-- Module Name: multiadder - Behavioral
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

entity multiadder is 
generic (
  Nb: integer;
  log2NFIFO: integer);
port 
(datain_fifo, dataout_fifo: in signed(Nb-1 downto 0);
dataout_accumulator: in signed(Nb+log2NFIFO-1 downto 0);
dataout: out signed(Nb+log2NFIFO-1 downto 0));
end multiadder;

architecture Behavioral of multiadder is
signal datain_fifo_large, dataout_fifo_large: signed(Nb+log2NFIFO-1 downto 0);
signal mask0: signed(log2NFIFO-1 downto 0):=(others => '0');
begin

datain_fifo_large <= mask0 & datain_fifo;
dataout_fifo_large <= mask0 & dataout_fifo;

dataout <= datain_fifo_large - dataout_fifo_large + dataout_accumulator;

end Behavioral;
