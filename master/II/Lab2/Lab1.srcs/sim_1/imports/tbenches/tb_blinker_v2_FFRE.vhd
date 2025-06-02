----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/16/2025 06:15:57 PM
-- Design Name: 
-- Module Name: tb_blinker_v2_FFRE - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity tb_blinker_v2_FFRE is
--  Port ( );
end tb_blinker_v2_FFRE;

architecture Behavioral of tb_blinker_v2_FFRE is

component blinker_v2_FFRE is
    Port ( clk, D : in STD_LOGIC;
           E : in STD_LOGIC;
           RESET : in STD_LOGIC;
           Q : out STD_LOGIC);
end component;

signal clk1, D1, E1, RESET1, Q1: std_logic;
begin


clk_process: process
    begin
    clk1<='1'; wait for 10 ns;
    clk1<='0'; wait for 10 ns;
end process;

enable_process: process
    begin
    E1<='0'; wait for 40 ns;
    E1<='1'; wait for 100 ns;
end process;

reset_process: process
    begin
    RESET1<='1'; wait for 100 ns;
    RESET1<='1'; wait for 100 ns;
end process;

D_process: process
    begin
    D1<='1'; wait for 72 ns;
    D1<='0'; wait for 132 ns;
end process;

dut_ff: blinker_v2_FFRE port map (clk1, D1, E1, RESET1, Q1);


end Behavioral;
