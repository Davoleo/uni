----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/16/2025 04:04:06 PM
-- Design Name: 
-- Module Name: tb_blinker_v2 - tb_blinker_v2_behavioral
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

entity tb_blinker_v2 is
--  Port ( );
end tb_blinker_v2;

architecture behavioral of tb_blinker_v2 is


component blinker_v2 is
     Port (clk : in STD_LOGIC;
           btn : in STD_LOGIC_VECTOR(0 to 1);
           led0_r : out STD_LOGIC;
           led0_g : out STD_LOGIC;
           led0_b : out STD_LOGIC);
end component;

signal clk1, button0, button1, ledout0, ledout1, ledout2: std_logic;
signal buttons:std_logic_vector(0 to 1);

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

reset_process: process
    begin
    button1<='0'; wait for 1500 ns;
    button1<='1'; wait for 133 ns;
end process;

buttons <= button0 & button1;

dut_blinker_v2: blinker_v2 port map (clk1, buttons, ledout0, ledout1, ledout2);

end behavioral;
