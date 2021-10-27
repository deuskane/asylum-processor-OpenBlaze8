
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
          when    0 => instruction_o <= "00"&x"005A";
          when    1 => instruction_o <= "00"&x"0658";
          when    2 => instruction_o <= "01"&x"200F";
          when    3 => instruction_o <= "11"&x"5021";
          when    4 => instruction_o <= "11"&x"5821";
          when    5 => instruction_o <= "01"&x"201F";
          when    6 => instruction_o <= "11"&x"5021";
          when    7 => instruction_o <= "11"&x"5C21";
          when    8 => instruction_o <= "01"&x"20FF";
          when    9 => instruction_o <= "11"&x"5021";
          when   10 => instruction_o <= "11"&x"5821";
          when   11 => instruction_o <= "01"&x"2002";
          when   12 => instruction_o <= "11"&x"5021";
          when   13 => instruction_o <= "11"&x"5C21";
          when   14 => instruction_o <= "01"&x"20A5";
          when   15 => instruction_o <= "11"&x"5421";
          when   16 => instruction_o <= "11"&x"5821";
          when   17 => instruction_o <= "01"&x"260F";
          when   18 => instruction_o <= "11"&x"5021";
          when   19 => instruction_o <= "11"&x"5C21";
          when   20 => instruction_o <= "01"&x"261F";
          when   21 => instruction_o <= "11"&x"5021";
          when   22 => instruction_o <= "11"&x"5821";
          when   23 => instruction_o <= "01"&x"26FF";
          when   24 => instruction_o <= "11"&x"5021";
          when   25 => instruction_o <= "11"&x"5C21";
          when   26 => instruction_o <= "01"&x"2602";
          when   27 => instruction_o <= "11"&x"5421";
          when   28 => instruction_o <= "11"&x"5821";
          when   29 => instruction_o <= "01"&x"26A5";
          when   30 => instruction_o <= "11"&x"5421";
          when   31 => instruction_o <= "11"&x"5821";
          when   32 => instruction_o <= "11"&x"43FC";
          when   33 => instruction_o <= "00"&x"0EED";
          when   34 => instruction_o <= "10"&x"CEE0";
          when   35 => instruction_o <= "11"&x"4021";
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

