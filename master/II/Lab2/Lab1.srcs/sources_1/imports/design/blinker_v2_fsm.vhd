----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/16/2025 06:05:43 PM
-- Design Name: 
-- Module Name: blinker_v2_fsm - Behavioral
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

entity blinker_v2_fsm is
    Port ( i_X : in STD_LOGIC;
           o_OUT : out STD_LOGIC;
           reset : in STD_LOGIC;
           ck : in STD_LOGIC);
end blinker_v2_fsm;

ARCHITECTURE behavioral OF blinker_v2_fsm IS       -- (Behavioral Description)
  TYPE states is ( state_s0,
                   state_s1,
                   state_s2,
                   state_s3 );
  SIGNAL State,
         Next_State: states;
BEGIN

  -- Next State Combinational Logic ----------------------------------
  FSM: process( State, i_X )
  begin
    CASE State IS
      when state_s0 =>
                 if (i_X = '1') then
                   Next_State <= state_s1;
                 else
                   Next_State <= state_s2;
                 end if;
      when state_s1 =>
                 if (i_X = '1') then
                   Next_State <= state_s3;
                 else
                   Next_State <= state_s1;
                 end if;
      when state_s3 =>
                 if (i_X = '1') then
                   Next_State <= state_s1; --  Previously S2
                 else
                   Next_State <= state_s3;
                 end if;
      when state_s2 =>
                 if (i_X = '1') then
                   Next_State <= state_s1;
                 else
                   Next_State <= state_s2;
                 end if;
    END case;
  end process;

  -- State Register --------------------------------------------------
  REG: process( Ck, Reset )
  begin
    if (Reset = '1') then
              State <= state_s2;
    elsif rising_edge(Ck) then
              State <= Next_State;
       end if;
  end process;

  -- Outputs Combinational Logic -----------------------------------
  OUTPUTS: process( State, i_X )
  begin
    -- Set output defaults:
    o_OUT <= '0';

    -- Set output as function of current state and input:
    CASE State IS
      when state_s3 =>
                 o_OUT <= '1';
      when OTHERS =>
                 o_OUT <= '0';
    END case;
  end process;

END behavioral;

