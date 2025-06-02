----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/16/2025 09:36:20 PM
-- Design Name: 
-- Module Name: tb_blinker_v2_fsm - Behavioral
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

entity tb_blinker_v2_fsm is
--  Port ( );
end tb_blinker_v2_fsm;

architecture Behavioral of tb_blinker_v2_fsm is

component blinker_v2_fsm is
    Port ( i_X : in STD_LOGIC;
           o_OUT : out STD_LOGIC;
           reset : in STD_LOGIC;
           ck : in STD_LOGIC);
end component;

component blinker_v2_pulsegen is
    Port ( btn0 : in STD_LOGIC;
           clk : in STD_LOGIC;
           pulseout : out STD_LOGIC);
end component;

signal pulse, clk1, button0, reset1, ylight: std_logic;

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
    reset1<='0'; wait for 1500 ns;
    reset1<='1'; wait for 133 ns;
end process;

dut_pulsegen: blinker_v2_pulsegen port map (button0, clk1, pulse);
dut_fsm: blinker_v2_fsm port map (pulse, ylight, reset1, clk1);


end Behavioral;
