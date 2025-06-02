----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/16/2025 06:09:10 PM
-- Design Name: 
-- Module Name: blinker_v2_FFRE - Behavioral
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

entity blinker_v2_FFRE is
    Port ( clk, D : in STD_LOGIC;
           E : in STD_LOGIC;
           RESET : in STD_LOGIC;
           Q : out STD_LOGIC);
end blinker_v2_FFRE;

architecture Behavioral_FFRE of blinker_v2_FFRE is

begin
   process(clk)
   variable qvar: std_logic;
   begin
      if rising_edge(clk) then  
         if (RESET='0') then   
            q <= '0';
         elsif (E='1') then
            if (d ='1') then
            qvar:= '1';
         elsif (d ='0') then 
             qvar:= '0';
         end if;
      end if;
      end if;
      Q<=qvar;
   end process;

end Behavioral_FFRE;
