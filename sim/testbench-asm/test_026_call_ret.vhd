
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
          when    0 => instruction_o <= "00"&x"0000";
          when    1 => instruction_o <= "11"&x"0100";
          when    2 => instruction_o <= "11"&x"0103";
          when    3 => instruction_o <= "11"&x"0106";
          when    4 => instruction_o <= "01"&x"4089";
          when    5 => instruction_o <= "11"&x"5509";
          when    6 => instruction_o <= "11"&x"43FC";
          when  256 => instruction_o <= "00"&x"C001";
          when  257 => instruction_o <= "10"&x"A000";
          when  258 => instruction_o <= "11"&x"4109";
          when  259 => instruction_o <= "00"&x"C008";
          when  260 => instruction_o <= "10"&x"A000";
          when  261 => instruction_o <= "11"&x"4109";
          when  262 => instruction_o <= "00"&x"C080";
          when  263 => instruction_o <= "10"&x"A000";
          when  264 => instruction_o <= "11"&x"4109";
          when  265 => instruction_o <= "00"&x"0EED";
          when  266 => instruction_o <= "10"&x"CEE0";
          when  267 => instruction_o <= "11"&x"4109";
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
