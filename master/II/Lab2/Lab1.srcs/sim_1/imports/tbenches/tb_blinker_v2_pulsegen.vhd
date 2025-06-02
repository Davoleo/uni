----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/16/2025 08:10:38 PM
-- Design Name: 
-- Module Name: tb_blinker_v2_pulsegen - Behavioral
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

entity tb_blinker_v2_pulsegen is
--  Port ( );
end tb_blinker_v2_pulsegen;

architecture Behavioral of tb_blinker_v2_pulsegen is

component blinker_v2_pulsegen is
    Port ( btn0 : in STD_LOGIC;
           clk : in STD_LOGIC;
           pulseout : out STD_LOGIC);
end component;

signal clk1, button0, pulseoutput:std_logic;

begin

clk_process: process
    begin
    clk1<='1'; wait for 10 ns;
    clk1<='0'; wait for 10 ns;
end process;

button0_process: process
    begin
    button0<='0'; wait for 150 ns;
    button0<='1'; wait for 133 ns;
end process;

dut_pulsegen: blinker_v2_pulsegen port map (button0, clk1, pulseoutput);

end Behavioral;
