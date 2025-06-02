library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
	 	 
entity counter is
    generic ( Nb : integer) ;
    port( T           :in std_logic;
          clk         :in std_logic; 
          OUT_COUNT   :out std_logic_vector(Nb-1 downto 0)
    );
    end counter;  
architecture counter_behavior of counter is
		

   constant ovf1: std_logic_vector(Nb-1 downto 0):=(others => '1');
   

	begin
    
      process(clk)
        variable count: std_logic_vector(Nb-1 downto 0):=(others => '0');
      begin
         
         if clk'event and clk='1' then
             
            if T='1' then
             
             if count=ovf1 then 
                 count := (others => '0');
                else 
                 count := count + '1';
                 end if;
                 
             else count := count;
                 
             end if; -- T='1'
 
         end if; --'clk'event
       
       out_count<=count;        
      
      end process;
    
	 
     
	   
end counter_behavior;
