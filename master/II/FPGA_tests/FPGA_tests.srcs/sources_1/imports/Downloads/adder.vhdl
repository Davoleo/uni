library ieee;
use ieee.std_logic_1164.all;

entity adder is
    generic ( Nb : integer ) ;
    port(cin  :in  std_logic; 
         a, b :in  std_logic_vector(Nb-1 downto 0);
         c    :out std_logic_vector(Nb-1 downto 0);
         cout :out std_logic);
    end adder;
    
architecture adder_behavior of adder is
		
	component full_adder is
         port(cin, x, y:in std_logic;
         z, cout  :out std_logic);
	end component;
		
	signal carry0: std_logic;
	signal carry: std_logic_vector(Nb downto 0);
	
	begin

         hdi : for k in Nb-1 downto 0 generate
         ni : full_adder port map(carry(k), a(k), b(k), c(k), carry(k+1));
         end generate;

	 carry(0) <= cin;
         cout <= carry(Nb);
  
end adder_behavior;