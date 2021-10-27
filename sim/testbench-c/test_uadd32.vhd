
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
          when    0 => instruction_o <= "00"&x"0F3F";
          when    1 => instruction_o <= "11"&x"4002";
          when    2 => instruction_o <= "11"&x"0019";
          when    3 => instruction_o <= "11"&x"4003";
          when    4 => instruction_o <= "00"&x"10B0";
          when    5 => instruction_o <= "00"&x"11C0";
          when    6 => instruction_o <= "00"&x"12D0";
          when    7 => instruction_o <= "00"&x"13E0";
          when    8 => instruction_o <= "01"&x"8F01";
          when    9 => instruction_o <= "00"&x"74F0";
          when   10 => instruction_o <= "01"&x"8F01";
          when   11 => instruction_o <= "00"&x"75F0";
          when   12 => instruction_o <= "01"&x"8F01";
          when   13 => instruction_o <= "00"&x"76F0";
          when   14 => instruction_o <= "01"&x"8F01";
          when   15 => instruction_o <= "00"&x"77F0";
          when   16 => instruction_o <= "01"&x"9070";
          when   17 => instruction_o <= "01"&x"B160";
          when   18 => instruction_o <= "01"&x"B250";
          when   19 => instruction_o <= "01"&x"B340";
          when   20 => instruction_o <= "00"&x"1E30";
          when   21 => instruction_o <= "00"&x"1D20";
          when   22 => instruction_o <= "00"&x"1C10";
          when   23 => instruction_o <= "00"&x"1B00";
          when   24 => instruction_o <= "10"&x"A000";
          when   25 => instruction_o <= "00"&x"00CA";
          when   26 => instruction_o <= "10"&x"F0F0";
          when   27 => instruction_o <= "01"&x"CF01";
          when   28 => instruction_o <= "00"&x"00DE";
          when   29 => instruction_o <= "10"&x"F0F0";
          when   30 => instruction_o <= "01"&x"CF01";
          when   31 => instruction_o <= "00"&x"00FE";
          when   32 => instruction_o <= "10"&x"F0F0";
          when   33 => instruction_o <= "01"&x"CF01";
          when   34 => instruction_o <= "00"&x"00CA";
          when   35 => instruction_o <= "10"&x"F0F0";
          when   36 => instruction_o <= "01"&x"CF01";
          when   37 => instruction_o <= "00"&x"0BEF";
          when   38 => instruction_o <= "00"&x"0CBE";
          when   39 => instruction_o <= "00"&x"0DAD";
          when   40 => instruction_o <= "00"&x"0EDE";
          when   41 => instruction_o <= "11"&x"0004";
          when   42 => instruction_o <= "00"&x"10B0";
          when   43 => instruction_o <= "00"&x"11C0";
          when   44 => instruction_o <= "00"&x"12D0";
          when   45 => instruction_o <= "00"&x"13E0";
          when   46 => instruction_o <= "01"&x"40B9";
          when   47 => instruction_o <= "11"&x"5438";
          when   48 => instruction_o <= "01"&x"419D";
          when   49 => instruction_o <= "11"&x"5438";
          when   50 => instruction_o <= "01"&x"42AC";
          when   51 => instruction_o <= "11"&x"5438";
          when   52 => instruction_o <= "01"&x"43A9";
          when   53 => instruction_o <= "11"&x"5438";
          when   54 => instruction_o <= "00"&x"00FA";
          when   55 => instruction_o <= "10"&x"C0E0";
          when   56 => instruction_o <= "00"&x"00ED";
          when   57 => instruction_o <= "10"&x"C0E0";
          when   58 => instruction_o <= "10"&x"A000";

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

