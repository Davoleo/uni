----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/23/2025 03:36:52 PM
-- Design Name: 
-- Module Name: tb_accumulator - Behavioral
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

entity tb_accumulator is
--  Port ( );
end tb_accumulator;

architecture Behavioral of tb_accumulator is

constant numbNb:integer:=8;
constant numblog2NFIFO:integer:=6;

component accumulator is
generic(
  Nb: integer;
  log2NFIFO: integer);
  port 
(en, rst, clk: in std_logic;
datain: in signed(Nb+log2NFIFO-1 downto 0);
dataout: out signed(Nb+log2NFIFO-1 downto 0));
end component;

component counter is
    generic ( Nb : integer:=numbNb+numblog2NFIFO) ;
    port( T           :in std_logic;
          clk         :in std_logic; 
          OUT_COUNT   :out std_logic_vector(Nb-1 downto 0)
    );
    end component;

signal clks, rsts, ens: std_logic;
signal datains, dataouts: signed(numbNb+numblog2NFIFO-1 downto 0);
signal datains2: std_logic_vector(numbNb+numblog2NFIFO-1 downto 0);
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

rsts <= '0';

datains <= "00110011001100";

dut_accumulator: accumulator generic map (Nb => numbNb, log2NFIFO => numblog2NFIFO)
port map (ens, rsts, clks, datains, dataouts);

end Behavioral;
