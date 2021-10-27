
--
-- Definition of a single port ROM for KCPSM3 program defined by OpenBlaze8_ROM.psm
--
-- Generated by KCPSM3 Assembler . 
--
-- Standard IEEE libraries
--
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity OpenBlaze8_ROM is
  Port (
    clk_i           : in  std_logic;
    cke_i           : in  std_logic;
    address_i       : in  std_logic_vector(10-1 downto 0);
    instruction_o   : out std_logic_vector(18-1 downto 0)
    );
end OpenBlaze8_ROM;
--
architecture rtl of OpenBlaze8_ROM is

begin

  process (clk_i) is
  begin  -- process
    if clk_i'event and clk_i = '1'
    then
      if (cke_i = '1')
      then
        case conv_integer(address_i) is
          when    0 => instruction_o <= "00"&x"00A5";
          when    1 => instruction_o <= "00"&x"0100";
          when    2 => instruction_o <= "00"&x"1900";
          when    3 => instruction_o <= "10"&x"0907";
          when    4 => instruction_o <= "11"&x"5C34";
          when    5 => instruction_o <= "11"&x"5034";
          when    6 => instruction_o <= "01"&x"494B";
          when    7 => instruction_o <= "11"&x"5834";
          when    8 => instruction_o <= "11"&x"5434";
          when    9 => instruction_o <= "10"&x"0907";
          when   10 => instruction_o <= "11"&x"5834";
          when   11 => instruction_o <= "11"&x"5034";
          when   12 => instruction_o <= "01"&x"4997";
          when   13 => instruction_o <= "11"&x"5834";
          when   14 => instruction_o <= "11"&x"5434";
          when   15 => instruction_o <= "10"&x"0907";
          when   16 => instruction_o <= "11"&x"5C34";
          when   17 => instruction_o <= "11"&x"5034";
          when   18 => instruction_o <= "01"&x"492F";
          when   19 => instruction_o <= "11"&x"5834";
          when   20 => instruction_o <= "11"&x"5434";
          when   21 => instruction_o <= "10"&x"0907";
          when   22 => instruction_o <= "11"&x"5834";
          when   23 => instruction_o <= "11"&x"5034";
          when   24 => instruction_o <= "01"&x"495F";
          when   25 => instruction_o <= "11"&x"5834";
          when   26 => instruction_o <= "11"&x"5434";
          when   27 => instruction_o <= "10"&x"0907";
          when   28 => instruction_o <= "11"&x"5834";
          when   29 => instruction_o <= "11"&x"5034";
          when   30 => instruction_o <= "01"&x"49BF";
          when   31 => instruction_o <= "11"&x"5834";
          when   32 => instruction_o <= "11"&x"5434";
          when   33 => instruction_o <= "10"&x"0907";
          when   34 => instruction_o <= "11"&x"5C34";
          when   35 => instruction_o <= "11"&x"5034";
          when   36 => instruction_o <= "01"&x"497F";
          when   37 => instruction_o <= "11"&x"5834";
          when   38 => instruction_o <= "11"&x"5434";
          when   39 => instruction_o <= "10"&x"0907";
          when   40 => instruction_o <= "11"&x"5834";
          when   41 => instruction_o <= "11"&x"5034";
          when   42 => instruction_o <= "01"&x"49FF";
          when   43 => instruction_o <= "11"&x"5834";
          when   44 => instruction_o <= "11"&x"5434";
          when   45 => instruction_o <= "10"&x"0907";
          when   46 => instruction_o <= "11"&x"5C34";
          when   47 => instruction_o <= "11"&x"5034";
          when   48 => instruction_o <= "01"&x"49FF";
          when   49 => instruction_o <= "11"&x"5834";
          when   50 => instruction_o <= "11"&x"5434";
          when   51 => instruction_o <= "11"&x"43FC";
          when   52 => instruction_o <= "00"&x"0EED";
          when   53 => instruction_o <= "10"&x"CEE0";
          when   54 => instruction_o <= "11"&x"4034";
          when 1020 => instruction_o <= "00"&x"0EFA";
          when 1021 => instruction_o <= "10"&x"CEE0";
          when 1022 => instruction_o <= "11"&x"43FC";
          when 1023 => instruction_o <= "11"&x"8001";

          when others => instruction_o <= (others => '0');
        end case;
      end if;
    end if;
  end process;
  
--
end rtl;
--
------------------------------------------------------------------------------------
--
-- END OF FILE OpenBlaze8_ROM.vhd
--
------------------------------------------------------------------------------------
