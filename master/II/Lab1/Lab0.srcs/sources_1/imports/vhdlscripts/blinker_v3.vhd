----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/18/2025 04:25:03 PM
-- Design Name: 
-- Module Name: blinker_v3 - Behavioral
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

entity blinker_v3 is
     Port (btn : in STD_LOGIC_VECTOR(0 to 1);
           led0_r : out STD_LOGIC;
           led0_g : out STD_LOGIC;
           led0_b : out STD_LOGIC;
           led: out STD_LOGIC_VECTOR(0 to 3));
end blinker_v3;

architecture Behavioral of blinker_v3 is
signal btn01:std_logic_vector(0 to 1);
signal ylight: std_logic;

begin

btn01<=btn;
ylight <= not (btn(0) xor btn(1));

-- with btn select
--       ylight <= '0' when "00",
--       ylight <= '1' when "01",
--       ylight <= '1' when "10",
--       ylight <= '0' when "11";
			
led(0)<=btn(0);
led(1)<=btn(1);
led(2)<=btn(0);
led(3)<=btn(1);

led0_r <= ylight;
led0_g <= ylight;
led0_b <= ylight;

end Behavioral;
