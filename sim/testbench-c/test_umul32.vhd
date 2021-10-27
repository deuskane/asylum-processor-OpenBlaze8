
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
          when    2 => instruction_o <= "11"&x"0026";
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
          when   16 => instruction_o <= "10"&x"F7F0";
          when   17 => instruction_o <= "01"&x"CF01";
          when   18 => instruction_o <= "10"&x"F6F0";
          when   19 => instruction_o <= "01"&x"CF01";
          when   20 => instruction_o <= "10"&x"F5F0";
          when   21 => instruction_o <= "01"&x"CF01";
          when   22 => instruction_o <= "10"&x"F4F0";
          when   23 => instruction_o <= "01"&x"CF01";
          when   24 => instruction_o <= "00"&x"1B00";
          when   25 => instruction_o <= "00"&x"1C10";
          when   26 => instruction_o <= "00"&x"1D20";
          when   27 => instruction_o <= "00"&x"1E30";
          when   28 => instruction_o <= "11"&x"0048";
          when   29 => instruction_o <= "00"&x"10B0";
          when   30 => instruction_o <= "00"&x"11C0";
          when   31 => instruction_o <= "00"&x"12D0";
          when   32 => instruction_o <= "00"&x"13E0";
          when   33 => instruction_o <= "00"&x"1E30";
          when   34 => instruction_o <= "00"&x"1D20";
          when   35 => instruction_o <= "00"&x"1C10";
          when   36 => instruction_o <= "00"&x"1B00";
          when   37 => instruction_o <= "10"&x"A000";
          when   38 => instruction_o <= "00"&x"00CA";
          when   39 => instruction_o <= "10"&x"F0F0";
          when   40 => instruction_o <= "01"&x"CF01";
          when   41 => instruction_o <= "00"&x"00DE";
          when   42 => instruction_o <= "10"&x"F0F0";
          when   43 => instruction_o <= "01"&x"CF01";
          when   44 => instruction_o <= "00"&x"00FE";
          when   45 => instruction_o <= "10"&x"F0F0";
          when   46 => instruction_o <= "01"&x"CF01";
          when   47 => instruction_o <= "00"&x"00CA";
          when   48 => instruction_o <= "10"&x"F0F0";
          when   49 => instruction_o <= "01"&x"CF01";
          when   50 => instruction_o <= "00"&x"0BEF";
          when   51 => instruction_o <= "00"&x"0CBE";
          when   52 => instruction_o <= "00"&x"0DAD";
          when   53 => instruction_o <= "00"&x"0EDE";
          when   54 => instruction_o <= "11"&x"0004";
          when   55 => instruction_o <= "00"&x"10B0";
          when   56 => instruction_o <= "00"&x"11C0";
          when   57 => instruction_o <= "00"&x"12D0";
          when   58 => instruction_o <= "00"&x"13E0";
          when   59 => instruction_o <= "01"&x"4096";
          when   60 => instruction_o <= "11"&x"5445";
          when   61 => instruction_o <= "01"&x"41EA";
          when   62 => instruction_o <= "11"&x"5445";
          when   63 => instruction_o <= "01"&x"42CD";
          when   64 => instruction_o <= "11"&x"5445";
          when   65 => instruction_o <= "01"&x"4367";
          when   66 => instruction_o <= "11"&x"5445";
          when   67 => instruction_o <= "00"&x"00FA";
          when   68 => instruction_o <= "10"&x"C0E0";
          when   69 => instruction_o <= "00"&x"00ED";
          when   70 => instruction_o <= "10"&x"C0E0";
          when   71 => instruction_o <= "10"&x"A000";
          when   72 => instruction_o <= "01"&x"8F01";
          when   73 => instruction_o <= "00"&x"76F0";
          when   74 => instruction_o <= "01"&x"8F01";
          when   75 => instruction_o <= "00"&x"75F0";
          when   76 => instruction_o <= "01"&x"8F01";
          when   77 => instruction_o <= "00"&x"74F0";
          when   78 => instruction_o <= "01"&x"8F01";
          when   79 => instruction_o <= "00"&x"73F0";
          when   80 => instruction_o <= "00"&x"0220";
          when   81 => instruction_o <= "00"&x"0A00";
          when   82 => instruction_o <= "00"&x"0900";
          when   83 => instruction_o <= "00"&x"0800";
          when   84 => instruction_o <= "00"&x"0700";
          when   85 => instruction_o <= "01"&x"2B01";
          when   86 => instruction_o <= "11"&x"505B";
          when   87 => instruction_o <= "01"&x"9730";
          when   88 => instruction_o <= "01"&x"B840";
          when   89 => instruction_o <= "01"&x"B950";
          when   90 => instruction_o <= "01"&x"BA60";
          when   91 => instruction_o <= "10"&x"0A0E";
          when   92 => instruction_o <= "10"&x"0908";
          when   93 => instruction_o <= "10"&x"0808";
          when   94 => instruction_o <= "10"&x"0708";
          when   95 => instruction_o <= "10"&x"0E08";
          when   96 => instruction_o <= "10"&x"0D08";
          when   97 => instruction_o <= "10"&x"0C08";
          when   98 => instruction_o <= "10"&x"0B08";
          when   99 => instruction_o <= "01"&x"C201";
          when  100 => instruction_o <= "11"&x"5455";
          when  101 => instruction_o <= "10"&x"A000";

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
