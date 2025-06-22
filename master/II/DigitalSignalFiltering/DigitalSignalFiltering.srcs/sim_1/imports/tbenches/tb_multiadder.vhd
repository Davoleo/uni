----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/23/2025 03:20:50 PM
-- Design Name: 
-- Module Name: tb_multiadder - Behavioral
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

entity tb_multiadder is
--  Port ( );
end tb_multiadder;

architecture Behavioral of tb_multiadder is

constant numbNb:integer:=8;
constant numblog2NFIFO:integer:=6;

component multiadder is 
generic (
  Nb: integer;
  log2NFIFO: integer);
port 
(datain_fifo, dataout_fifo: in signed(Nb-1 downto 0);
dataout_accumulator: in signed(Nb+log2NFIFO-1 downto 0);
dataout: out signed(Nb+log2NFIFO-1 downto 0));
end component;

signal dataouts:signed(numbNb+numblog2NFIFO-1 downto 0);

begin

dut_multiadder: multiadder generic map (Nb => numbNb, log2NFIFO => numblog2NFIFO)
port map (datain_fifo => "00000001", dataout_fifo => "00001111", dataout_accumulator => "11111111111111", 
dataout => dataouts);

end Behavioral;
