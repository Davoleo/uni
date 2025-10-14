library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity tb_adder is
    end tb_adder;
    
architecture tb_adder_behavior of tb_adder is
		
component adder is
generic ( Nb : integer ) ;
port(cin  :in  std_logic; 
a, b :in  std_logic_vector(Nb-1 downto 0);
c    :out std_logic_vector(Nb-1 downto 0);
cout :out std_logic);
end component;
	
component counter is
generic ( Nb : integer) ;
port( T           :in std_logic;
clk         :in std_logic; 
OUT_COUNT   :out std_logic_vector(Nb-1 downto 0)
);
end component;

    
        constant numb1: integer := 2;    
        constant numbtot: integer := 4;
	signal data1, data2: std_logic_vector(numb1-1 downto 0);
	signal out_adder: std_logic_vector(numb1-1 downto 0);
	signal datatot: std_logic_vector(numbtot-1 downto 0);
	signal clock_internal, overflow: std_logic;
	
begin


data1 <= datatot(numb1-1 downto 0);
data2 <= datatot(numbtot-1 downto numb1);
cmpt_siggen1: counter generic map (Nb => numbtot)
port map('1', clock_internal, datatot);


cmpt2: adder generic map (Nb => numb1)
port map('0', data1, data2, out_adder, overflow);   

    process
        begin
            clock_internal <= '0'; wait for 10 ns;
	    clock_internal <= '1'; wait for 10 ns;
    end process;

end tb_adder_behavior;