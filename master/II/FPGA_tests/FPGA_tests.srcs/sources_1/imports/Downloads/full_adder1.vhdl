library ieee;
use ieee.std_logic_1164.all;

entity full_adder is
    port(cin, x, y:in std_logic;
         z, cout  :out std_logic);
    end full_adder;
    
architecture full_adder_behavior of full_adder is
	
	begin
   
   cout <= (x and y) or (y and cin) or (x and cin);
   z    <= ( not(cin) and not(x) and y) or ( not(cin) and x and not(y) ) or ( cin and not(x) and not(y) ) or ( cin and x and y);

end full_adder_behavior;