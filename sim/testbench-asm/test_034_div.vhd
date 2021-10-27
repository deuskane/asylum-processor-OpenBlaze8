
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
          when    0 => instruction_o <= "00"&x"00D5";
          when    1 => instruction_o <= "00"&x"0111";
          when    2 => instruction_o <= "00"&x"050C";
          when    3 => instruction_o <= "00"&x"0609";
          when    4 => instruction_o <= "11"&x"001C";
          when    5 => instruction_o <= "01"&x"5630";
          when    6 => instruction_o <= "11"&x"5428";
          when    7 => instruction_o <= "01"&x"5520";
          when    8 => instruction_o <= "11"&x"5428";
          when    9 => instruction_o <= "00"&x"0011";
          when   10 => instruction_o <= "00"&x"01D5";
          when   11 => instruction_o <= "00"&x"0500";
          when   12 => instruction_o <= "00"&x"0611";
          when   13 => instruction_o <= "11"&x"001C";
          when   14 => instruction_o <= "01"&x"5630";
          when   15 => instruction_o <= "11"&x"5428";
          when   16 => instruction_o <= "01"&x"5520";
          when   17 => instruction_o <= "11"&x"5428";
          when   18 => instruction_o <= "00"&x"0081";
          when   19 => instruction_o <= "00"&x"0125";
          when   20 => instruction_o <= "00"&x"0503";
          when   21 => instruction_o <= "00"&x"0612";
          when   22 => instruction_o <= "11"&x"001C";
          when   23 => instruction_o <= "01"&x"5630";
          when   24 => instruction_o <= "11"&x"5428";
          when   25 => instruction_o <= "01"&x"5520";
          when   26 => instruction_o <= "11"&x"5428";
          when   27 => instruction_o <= "11"&x"43FC";
          when   28 => instruction_o <= "00"&x"0300";
          when   29 => instruction_o <= "00"&x"0480";
          when   30 => instruction_o <= "01"&x"3040";
          when   31 => instruction_o <= "10"&x"0300";
          when   32 => instruction_o <= "10"&x"0206";
          when   33 => instruction_o <= "01"&x"5310";
          when   34 => instruction_o <= "11"&x"5825";
          when   35 => instruction_o <= "01"&x"D310";
          when   36 => instruction_o <= "01"&x"8201";
          when   37 => instruction_o <= "10"&x"040E";
          when   38 => instruction_o <= "11"&x"541E";
          when   39 => instruction_o <= "10"&x"A000";
          when   40 => instruction_o <= "00"&x"0EED";
          when   41 => instruction_o <= "10"&x"CEE0";
          when   42 => instruction_o <= "11"&x"4028";
          when 1020 => instruction_o <= "00"&x"0EFA";
          when 1021 => instruction_o <= "10"&x"CEE0";
          when 1022 => instruction_o <= "11"&x"43FC";
          when 1023 => instruction_o <= "00"&x"7FFE";

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

