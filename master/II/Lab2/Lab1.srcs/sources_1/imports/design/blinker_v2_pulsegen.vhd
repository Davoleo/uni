----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/16/2025 06:05:43 PM
-- Design Name: 
-- Module Name: blinker_v2_pulsegen - Behavioral
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

entity blinker_v2_pulsegen is
    Port ( btn0 : in STD_LOGIC;
           clk : in STD_LOGIC;
           pulseout : out STD_LOGIC);
end blinker_v2_pulsegen;

architecture Behavioral of blinker_v2_pulsegen is

component blinker_v2_FFRE is
    Port ( clk, D : in STD_LOGIC;
           E : in STD_LOGIC;
           RESET : in STD_LOGIC;
           Q : out STD_LOGIC);
end component;

signal Q0, Q1: std_logic;

begin

ff0: blinker_v2_FFRE port map (clk, btn0, '1','1', Q0);
ff1: blinker_v2_FFRE port map (clk, Q0, '1','1', Q1);

pulseout <= Q0 and not(Q1);

end Behavioral;
