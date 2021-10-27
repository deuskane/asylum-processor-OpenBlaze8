
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
          when    2 => instruction_o <= "00"&x"0201";
          when    3 => instruction_o <= "00"&x"030F";
          when    4 => instruction_o <= "00"&x"0410";
          when    5 => instruction_o <= "00"&x"05FF";
          when    6 => instruction_o <= "00"&x"065A";
          when    7 => instruction_o <= "00"&x"1A00";
          when    8 => instruction_o <= "01"&x"CA00";
          when    9 => instruction_o <= "11"&x"5C0B";
          when   10 => instruction_o <= "11"&x"4050";
          when   11 => instruction_o <= "11"&x"540D";
          when   12 => instruction_o <= "11"&x"4050";
          when   13 => instruction_o <= "01"&x"4AA5";
          when   14 => instruction_o <= "11"&x"5010";
          when   15 => instruction_o <= "11"&x"4050";
          when   16 => instruction_o <= "00"&x"1A00";
          when   17 => instruction_o <= "01"&x"CA01";
          when   18 => instruction_o <= "11"&x"5C14";
          when   19 => instruction_o <= "11"&x"4050";
          when   20 => instruction_o <= "11"&x"5416";
          when   21 => instruction_o <= "11"&x"4050";
          when   22 => instruction_o <= "01"&x"4AA4";
          when   23 => instruction_o <= "11"&x"5019";
          when   24 => instruction_o <= "11"&x"4050";
          when   25 => instruction_o <= "00"&x"1A00";
          when   26 => instruction_o <= "01"&x"CA0F";
          when   27 => instruction_o <= "11"&x"5C1D";
          when   28 => instruction_o <= "11"&x"4050";
          when   29 => instruction_o <= "11"&x"541F";
          when   30 => instruction_o <= "11"&x"4050";
          when   31 => instruction_o <= "01"&x"4A96";
          when   32 => instruction_o <= "11"&x"5022";
          when   33 => instruction_o <= "11"&x"4050";
          when   34 => instruction_o <= "00"&x"1A00";
          when   35 => instruction_o <= "01"&x"CA10";
          when   36 => instruction_o <= "11"&x"5C26";
          when   37 => instruction_o <= "11"&x"4050";
          when   38 => instruction_o <= "11"&x"5428";
          when   39 => instruction_o <= "11"&x"4050";
          when   40 => instruction_o <= "01"&x"4A95";
          when   41 => instruction_o <= "11"&x"502B";
          when   42 => instruction_o <= "11"&x"4050";
          when   43 => instruction_o <= "00"&x"1A00";
          when   44 => instruction_o <= "01"&x"CAFF";
          when   45 => instruction_o <= "11"&x"582F";
          when   46 => instruction_o <= "11"&x"4050";
          when   47 => instruction_o <= "11"&x"5431";
          when   48 => instruction_o <= "11"&x"4050";
          when   49 => instruction_o <= "01"&x"4AA6";
          when   50 => instruction_o <= "11"&x"5034";
          when   51 => instruction_o <= "11"&x"4050";
          when   52 => instruction_o <= "00"&x"1A00";
          when   53 => instruction_o <= "01"&x"CA5A";
          when   54 => instruction_o <= "11"&x"5C38";
          when   55 => instruction_o <= "11"&x"4050";
          when   56 => instruction_o <= "11"&x"543A";
          when   57 => instruction_o <= "11"&x"4050";
          when   58 => instruction_o <= "01"&x"4A4B";
          when   59 => instruction_o <= "11"&x"503D";
          when   60 => instruction_o <= "11"&x"4050";
          when   61 => instruction_o <= "00"&x"1A10";
          when   62 => instruction_o <= "01"&x"CA00";
          when   63 => instruction_o <= "11"&x"5C41";
          when   64 => instruction_o <= "11"&x"4050";
          when   65 => instruction_o <= "11"&x"5043";
          when   66 => instruction_o <= "11"&x"4050";
          when   67 => instruction_o <= "01"&x"4A00";
          when   68 => instruction_o <= "11"&x"5046";
          when   69 => instruction_o <= "11"&x"4050";
          when   70 => instruction_o <= "00"&x"1A60";
          when   71 => instruction_o <= "01"&x"CAA5";
          when   72 => instruction_o <= "11"&x"584A";
          when   73 => instruction_o <= "11"&x"4050";
          when   74 => instruction_o <= "11"&x"544C";
          when   75 => instruction_o <= "11"&x"4050";
          when   76 => instruction_o <= "01"&x"4AB5";
          when   77 => instruction_o <= "11"&x"504F";
          when   78 => instruction_o <= "11"&x"4050";
          when   79 => instruction_o <= "11"&x"43FC";
          when   80 => instruction_o <= "00"&x"0EED";
          when   81 => instruction_o <= "10"&x"CEE0";
          when   82 => instruction_o <= "11"&x"4050";
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
