----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/18/2025 04:44:37 PM
-- Design Name: 
-- Module Name: tb_blinkerv3 - Behavioral
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

entity tb_blinkerv3 is
--  Port ( );
end tb_blinkerv3;

architecture Behavioral of tb_blinkerv3 is

component blinker_v3 is
     Port (btn : in STD_LOGIC_VECTOR(0 to 1);
           led0_r : out STD_LOGIC;
           led0_g : out STD_LOGIC;
           led0_b : out STD_LOGIC;
           led: out STD_LOGIC_VECTOR(0 to 3));
end component;

signal clk1, button0, button1:std_logic;
signal btn_internal: std_logic_vector(0 to 1);
signal output_leds_RGB: std_logic_vector(0 to 2);
signal output_leds: std_logic_vector(0 to 3);

begin
btn_internal <= button1 & button0;

button0_process: process
    begin
    button0<='0'; wait for 200 ns;
    button0<='1'; wait for 200 ns;
end process;

button1_process: process
    begin
    button1<='0'; wait for 400 ns;
    button1<='1'; wait for 400 ns;
end process;

dut: blinker_v3 port map (btn_internal, output_leds_RGB(0), output_leds_RGB(1), output_leds_RGB(2), output_leds);

end Behavioral;
