----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/23/2025 06:15:50 PM
-- Design Name: 
-- Module Name: filter_ma - Behavioral
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

entity filter_ma is
generic (
  Nbf: integer;
  log2NFIFOf: integer);
port (en, rst, clk: in std_logic;
datain:in signed(Nbf-1 downto 0);
dataout: out signed(Nbf+log2NFIFOf-1 downto 0)); 
end filter_ma;

architecture Behavioral of filter_ma is

component fifo is 
generic (
  Nb: integer;
  log2NFIFO: integer);
port (en, rst, clk: in std_logic;
din: in signed(Nb-1 downto 0);
dout: out signed(Nb-1 downto 0) );
end component;

component multiadder is 
generic (
  Nb: integer;
  log2NFIFO: integer);
port 
(datain_fifo, dataout_fifo: in signed(Nb-1 downto 0);
dataout_accumulator: in signed(Nb+log2NFIFO-1 downto 0);
dataout: out signed(Nb+log2NFIFO-1 downto 0));
end component;

component accumulator is
generic(
  Nb: integer;
  log2NFIFO: integer);
  port 
(en, rst, clk: in std_logic;
datain: in signed(Nb+log2NFIFO-1 downto 0);
dataout: out signed(Nb+log2NFIFO-1 downto 0));
end component;

component divide_by is 
generic (
  Nb: integer;
  log2NFIFO: integer);
port (en, rst, clk: in std_logic;
datain:in signed(Nb+log2NFIFO-1 downto 0);
dataout: out signed(Nb+log2NFIFO-1 downto 0));
end component;

signal dataout_fifo_fma: signed(Nbf-1 downto 0);
signal dataout_accumulator_fma, dataout_multiadder_fma: signed(Nbf+log2NFIFOf-1 downto 0);

begin

fifo_impl: fifo generic map (Nb => Nbf, log2NFIFO => log2NFIFOf)
port map (en => en, rst => rst, clk => clk, din => datain, dout => dataout_fifo_fma);

multiadder_impl: multiadder generic map (Nb => Nbf, log2NFIFO => log2NFIFOf)
port map (datain_fifo => datain, dataout_fifo => dataout_fifo_fma, 
dataout_accumulator => dataout_accumulator_fma, dataout => dataout_multiadder_fma);

accumulator_impl: accumulator generic map(Nb => Nbf, log2NFIFO => log2NFIFOf)
port map (en => en, rst => rst, clk => clk, datain => dataout_multiadder_fma, 
dataout => dataout_accumulator_fma);

divideby_impl: divide_by generic map(Nb => Nbf, log2NFIFO => log2NFIFOf)
port map (en => en, rst => rst, clk => clk, datain => dataout_accumulator_fma, dataout => dataout);

end Behavioral;
