-------------------------------------------------------------------------------
-- Title      : tb_OpenBlaze8
-- Project    : OpenBlaze8
-------------------------------------------------------------------------------
-- File       : tb_OpenBlaze8.vhd
-- Author     : mrosiere
-- Company    : 
-- Created    : 2016-11-20
-- Last update: 2025-09-07
-- Platform   : 
-- Standard   : VHDL'93/02
-------------------------------------------------------------------------------
-- Description: 
-------------------------------------------------------------------------------
-- Copyright (c) 2016 
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author   Description
-- 2016-11-20  1.0      mrosiere Created
-------------------------------------------------------------------------------

library ieee;
use     ieee.std_logic_1164.all;
use     ieee.numeric_std.all;
use     ieee.std_logic_textio.all;
use     std.textio.all;

library asylum;
use     asylum.math_pkg.all;
use     asylum.OpenBlaze8_pkg.all;

entity tb_OpenBlaze8 is
  
end entity tb_OpenBlaze8;

architecture tb of tb_OpenBlaze8 is

  -- =====[ Parameters ]==========================
  constant STACK_DEPTH             : natural := 32;
  constant RAM_DEPTH               : natural := 64;
  constant DATA_WIDTH              : natural := 8;
  constant ADDR_INST_WIDTH         : natural := 10;
  constant REGFILE_DEPTH           : natural := 16;
  constant MULTI_CYCLE             : natural := 1;

  constant TB_PERIOD               : time    := 10 ns;
  constant TB_DURATION             : natural := 10000;
  
  constant TB_TEST_PORT_MISSMATCH  : natural := 1;
  constant TB_IT_PORT_ID           : std_logic_vector(DATA_WIDTH -1 downto 0) := X"FF";
  constant TB_LED_PORT_ID          : std_logic_vector(DATA_WIDTH -1 downto 0) := X"20";
  constant TB_SWITCH_PORT_ID       : std_logic_vector(DATA_WIDTH -1 downto 0) := X"00";
  constant TB_WATCH0_PORT_ID       : std_logic_vector(DATA_WIDTH -1 downto 0) := X"C0";
  constant TB_WATCH1_PORT_ID       : std_logic_vector(DATA_WIDTH -1 downto 0) := X"C1";
  constant TB_WATCH2_PORT_ID       : std_logic_vector(DATA_WIDTH -1 downto 0) := X"C2";
  constant TB_WATCH3_PORT_ID       : std_logic_vector(DATA_WIDTH -1 downto 0) := X"C3";
  constant TB_EXPECTED_PORT_ID     : std_logic_vector(DATA_WIDTH -1 downto 0) := X"E0";
  constant TB_EXPECTED_OUT_PORT_OK : std_logic_vector(DATA_WIDTH -1 downto 0) := X"FA";
  constant TB_EXPECTED_OUT_PORT_KO : std_logic_vector(DATA_WIDTH -1 downto 0) := X"ED";
  
  -- =====[ Signals ]=============================
  signal dut_clock_i           : std_logic := '0';
  signal dut_clock_enable_i    : std_logic;
  signal dut_reset_i           : std_logic := '0';
  signal dut_address_o         : std_logic_vector(ADDR_INST_WIDTH -1 downto 0);
  signal dut_instruction_i     : std_logic_vector(18 -1 downto 0);
  signal dut_port_id_o         : std_logic_vector(DATA_WIDTH -1 downto 0);
  signal dut_in_port_i         : std_logic_vector(DATA_WIDTH -1 downto 0);
  signal dut_out_port_o        : std_logic_vector(DATA_WIDTH -1 downto 0);
  signal dut_read_strobe_o     : std_logic;
  signal dut_write_strobe_o    : std_logic;
  signal dut_interrupt_i       : std_logic;
  signal dut_interrupt_ack_o   : std_logic;

  signal ref_clock_i           : std_logic := '0';
--signal ref_clock_enable_i    : std_logic;
  signal ref_reset_i           : std_logic := '0';
  signal ref_address_o         : std_logic_vector(10 -1 downto 0);
  signal ref_instruction_i     : std_logic_vector(18 -1 downto 0);
  signal ref_port_id_o         : std_logic_vector(8 -1 downto 0);
  signal ref_in_port_i         : std_logic_vector(8 -1 downto 0);
  signal ref_out_port_o        : std_logic_vector(8 -1 downto 0);
  signal ref_read_strobe_o     : std_logic;
  signal ref_write_strobe_o    : std_logic;
  signal ref_interrupt_i       : std_logic;
  signal ref_interrupt_ack_o   : std_logic;

  type mem_t is array (0 to 2**8-1) of std_logic_vector(8 -1 downto 0);
  signal mem                   : mem_t;
  signal mem_rdata             : std_logic_vector(8-1 downto 0);
 
  signal it_r                  : std_logic := '0';
  signal it_cnt_r              : unsigned(8-1 downto 0);
  
-----------------------------------------------------
  -- Test signals
  -----------------------------------------------------
  signal   test_done : std_logic := '0';
  signal   test_ok   : std_logic := '0';

  signal   watch32b  : std_logic_vector(32-1 downto 0);

  function to_hstring(vec : std_logic_vector) return string is
    constant hex_chars : string := "0123456789ABCDEF";
    variable result    : string(1 to (vec'length + 3) / 4);
    variable nibble    : std_logic_vector(3 downto 0);
    variable i         : integer;
begin
    for idx in 0 to result'length - 1 loop
        i := vec'length - 1 - idx * 4;
        if i < 3 then
            nibble := (others => '0');
            for j in 0 to i loop
                nibble(3 - j) := vec(j);
            end loop;
        else
            nibble := vec(i downto i - 3);
        end if;
        result(idx + 1) := hex_chars(to_integer(unsigned(nibble)) + 1);
    end loop;
    return result;
end function;

  
  
begin  -- architecture tb

  -----------------------------------------------------------------------------
  -- DUT
  -----------------------------------------------------------------------------

  dut : OpenBlaze8
    generic map
    (STACK_DEPTH     => STACK_DEPTH    
    ,RAM_DEPTH       => RAM_DEPTH      
    ,DATA_WIDTH      => DATA_WIDTH     
    ,ADDR_INST_WIDTH => ADDR_INST_WIDTH
    ,REGFILE_DEPTH   => REGFILE_DEPTH  
    ,MULTI_CYCLE     => MULTI_CYCLE    
    )
    port map
    (clock_i           => dut_clock_i        
    ,clock_enable_i    => dut_clock_enable_i 
    ,reset_i           => dut_reset_i        
    ,address_o         => dut_address_o      
    ,instruction_i     => dut_instruction_i  
    ,port_id_o         => dut_port_id_o      
    ,in_port_i         => dut_in_port_i      
    ,out_port_o        => dut_out_port_o     
    ,read_strobe_o     => dut_read_strobe_o  
    ,write_strobe_o    => dut_write_strobe_o 
    ,interrupt_i       => dut_interrupt_i    
    ,interrupt_ack_o   => dut_interrupt_ack_o
     );

  -----------------------------------------------------------------------------
  -- Reference
  -----------------------------------------------------------------------------
  ref : entity work.kcpsm3(low_level_definition)
    port map
    (clk           => ref_clock_i
    ,reset         => ref_reset_i
    ,address       => ref_address_o
    ,instruction   => ref_instruction_i
    ,port_id       => ref_port_id_o
    ,in_port       => ref_in_port_i
    ,out_port      => ref_out_port_o
    ,read_strobe   => ref_read_strobe_o
    ,write_strobe  => ref_write_strobe_o
    ,interrupt     => ref_interrupt_i
    ,interrupt_ack => ref_interrupt_ack_o
    );

  -----------------------------------------------------------------------------
  -- ROM
  -----------------------------------------------------------------------------
  dut_rom : entity work.OpenBlaze8_ROM(rtl)
    port map
    (clk_i             => ref_clock_i
    ,cke_i             => '1'
    ,address_i         => ref_address_o
    ,instruction_o     => ref_instruction_i
     );

  -----------------------------------------------------------------------------
  -- Ref Clock
  -----------------------------------------------------------------------------
  ref_clock_i            <= not test_done and not ref_clock_i after TB_PERIOD/2;

  dut_clock_i            <= ref_clock_i;
  dut_clock_enable_i     <= '1';
  
  -----------------------------------------------------------------------------
  -- Ref Reset
  -----------------------------------------------------------------------------
  -- purpose: Reset
  -- type   : combinational
  -- inputs : 
  -- outputs: dut_reset_i, ref_reset_i
  l_reset: process is
  begin  -- process l_reset

    dut_reset_i <= '1';
    ref_reset_i <= '1';

    wait for 5*TB_PERIOD;
    ref_reset_i <= '0';
    wait for 2*TB_PERIOD;
    dut_reset_i <= '0';

    -- end of process
    wait;
  end process l_reset;

  -----------------------------------------------------------------------------
  -- Ref others input
  -----------------------------------------------------------------------------
  p_mem: process (ref_clock_i) is
  begin  -- process p_mem
    if ref_clock_i'event and ref_clock_i = '1'
    then  -- rising clock edge

      if ref_write_strobe_o = '1'
      then
        mem(to_integer(unsigned(ref_port_id_o))) <= ref_out_port_o;
      end if;

      -- In all tb, switch = ~led
      if ref_port_id_o = TB_SWITCH_PORT_ID
      then
        mem_rdata <= not mem(to_integer(unsigned(TB_LED_PORT_ID)));
      else
        mem_rdata <=     mem(to_integer(unsigned(ref_port_id_o)));
      end if;
            
    end if;
  end process p_mem;
  
  ref_in_port_i     <= mem_rdata when ref_read_strobe_o = '1' else
                       (others => 'U');
  
  dut_instruction_i <= ref_instruction_i;
  dut_in_port_i     <= ref_in_port_i    ;

  -----------------------------------------------------------------------------
  -- Interruption
  -----------------------------------------------------------------------------
  p_it: process (ref_clock_i) is
  begin  -- process p_it
    if ref_clock_i'event and ref_clock_i = '1'
    then  -- rising clock edge

      -- Write in IT generatro
      if ref_write_strobe_o = '1' and ref_port_id_o = TB_IT_PORT_ID
      then
        it_cnt_r <= unsigned(ref_out_port_o);
      end if;

      -- throw interruption
      if it_cnt_r = 1
      then
        it_r <= '1';
      end if;

      if it_cnt_r > 0 then

        it_cnt_r <= it_cnt_r -1;


      end if;

      -- Clear interruption
      if (ref_interrupt_ack_o = '1')
      then
        it_r <= '0';
      end if;
      
    end if;
  end process p_it;

  ref_interrupt_i   <= it_r;
  dut_interrupt_i   <= ref_interrupt_i  ;
  
  
  -----------------------------------------------------------------------------
  -- Testbench Limit
  -----------------------------------------------------------------------------
  l_tb_limit: process is
  begin  -- process l_tb_limit
    wait for TB_DURATION*TB_PERIOD;

    assert (test_done = '1') report "[TESTBENCH] Test KO : Maximum cycle is reached" severity failure;

    -- end of process
    wait;
  end process l_tb_limit;

  -----------------------------------------------------------------------------
  -- Testbench verification
  -----------------------------------------------------------------------------

  l_tb_verif: process (ref_clock_i) is
    variable var_watch32b  : std_logic_vector(32-1 downto 0);

  begin  -- process l_tb_verif
    if (ref_clock_i'event and ref_clock_i = '0')
    then  -- falling clock edge

      -- Test only no reset
      if ((dut_reset_i='0') and (ref_reset_i='0'))
      then

        if (TB_TEST_PORT_MISSMATCH = 1)
        then
          assert (dut_address_o       = ref_address_o      ) report "[TESTBENCH] Test KO : Missmatch with reference for the port address"       severity failure;
          assert (dut_interrupt_ack_o = ref_interrupt_ack_o) report "[TESTBENCH] Test KO : Missmatch with reference for the port interrupt_ack" severity failure;
          assert (dut_read_strobe_o   = ref_read_strobe_o  ) report "[TESTBENCH] Test KO : Missmatch with reference for the port read_strobe"   severity failure;
          assert (dut_write_strobe_o  = ref_write_strobe_o ) report "[TESTBENCH] Test KO : Missmatch with reference for the port write_strobe"  severity failure;

          if ((dut_write_strobe_o = '1') or (dut_read_strobe_o = '1'))
          then
          assert (dut_port_id_o       = ref_port_id_o      ) report "[TESTBENCH] Test KO : Missmatch with reference for the port port_id"       severity failure;
          end if;
        
          if (dut_write_strobe_o = '1')
          then
            if (dut_out_port_o      /= ref_out_port_o     )
            then
              report "[TESTBENCH] Test KO : Missmatch with reference for the port out_port";
              test_done <= '1';
            end if;
          end if;        
        end if;

        var_watch32b := watch32b;
        if (dut_write_strobe_o = '1') and (dut_port_id_o = TB_WATCH0_PORT_ID) then
          var_watch32b(8-1  downto  0) := dut_out_port_o;
        end if;
        if (dut_write_strobe_o = '1') and (dut_port_id_o = TB_WATCH1_PORT_ID) then
          var_watch32b(16-1 downto  8) := dut_out_port_o;
        end if;
        if (dut_write_strobe_o = '1') and (dut_port_id_o = TB_WATCH2_PORT_ID) then
          var_watch32b(24-1 downto 16) := dut_out_port_o;
        end if;
        if (dut_write_strobe_o = '1') and (dut_port_id_o = TB_WATCH3_PORT_ID) then
          var_watch32b(32-1 downto 24) := dut_out_port_o;
          report "[TESTBENCH] Watch   : " & to_hstring(var_watch32b);
        end if;
        watch32b <= var_watch32b;
        
        if (dut_write_strobe_o = '1') and (dut_port_id_o = TB_EXPECTED_PORT_ID) then
          case dut_out_port_o is
            when TB_EXPECTED_OUT_PORT_OK => report "[TESTBENCH] Test OK : Trigger OK detected"      ; test_done <= '1';

            when TB_EXPECTED_OUT_PORT_KO => report "[TESTBENCH] Test KO : Trigger KO detected"      severity failure;
            when others                  => report "[TESTBENCH] Test KO : Invalid trigger detected" severity failure;
          end case;
        end if;
      end if;
    end if;
  end process l_tb_verif;
  
end architecture tb;
