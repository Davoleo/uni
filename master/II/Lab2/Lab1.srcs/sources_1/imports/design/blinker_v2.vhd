library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity blinker_v2 is
     Port (clk : in STD_LOGIC;
           btn : in STD_LOGIC_VECTOR(0 to 1);
           led0_r : out STD_LOGIC;
           led0_g : out STD_LOGIC;
           led0_b : out STD_LOGIC);
end blinker_v2;

architecture blincker_v2_behavioral of blinker_v2 is
  
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

signal pulse, ylight: std_logic;
signal led0_rgb: std_logic_vector(1 to 3);
begin

dut_pulsegen: blinker_v2_pulsegen port map (btn(0), clk, pulse);
dut_fsm: blinker_v2_fsm port map (pulse, ylight, btn(1), clk);

led0_rgb <= (others => not(ylight));
led0_r <= led0_rgb(1);
led0_g <= led0_rgb(2);
led0_b <= led0_rgb(3);


end blincker_v2_behavioral;



