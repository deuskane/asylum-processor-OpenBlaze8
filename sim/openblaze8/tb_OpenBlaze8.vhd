-------------------------------------------------------------------------------
-- Title      : tb_OpenBlaze8
-- Project    : OpenBlaze8
-------------------------------------------------------------------------------
-- File       : tb_OpenBlaze8.vhd
-- Author     : mrosiere
-- Company    :
-- Created    : 2016-11-20
-- Last update: 2026-11-20
-- Platform   :
-- Standard   : VHDL'2008
-------------------------------------------------------------------------------
-- Description: Self-checking testbench of OpenBlaze8 : the DUT and the
--              reference Xilinx kcpsm3 run the same program in lock-step and
--              their ports are compared at every cycle.
--              TESTS_LIST        : programs run in sequence, separated by ','
--                                  (tb_OpenBlaze8_tests_pkg), each one after
--                                  a reset pulse ; "" : build only
--              MODEL             : "core" : OpenBlaze8, clock_enable_i = '1'
--                                  "sbi"  : sbi_OpenBlaze8, random cke_i and
--                                  ready (stalls), kcpsm3 clock gated by the
--                                  expected clock enable
--              REGFILE_SYNC_READ : generic of the DUT
-------------------------------------------------------------------------------
-- Copyright (c) 2016
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author   Description
-- 2016-11-20  1.0      mrosiere Created
-- 2026-11-20  2.0      mrosiere UVVM, TESTS_LIST (one program per scenario,
--                               ROM bank tb_OpenBlaze8_rom), reset pulse
--                               before each scenario, MODEL "sbi" with
--                               stalls, one DUT per run
-------------------------------------------------------------------------------

library ieee;
use     ieee.std_logic_1164.all;
use     ieee.numeric_std.all;
use     ieee.math_real.all;

library uvvm_util;
context uvvm_util.uvvm_util_context;

library asylum;
use     asylum.sbi_pkg.all;
use     asylum.string_pkg.all;
use     asylum.OpenBlaze8_pkg.all;

library work;
use     work.tb_OpenBlaze8_bfm_pkg.all;
use     work.tb_OpenBlaze8_tests_pkg.all;

entity tb_OpenBlaze8 is
  generic (
    TESTS_LIST        : string  := ""      -- Scenarios, e.g. "test_002_jump,test_umul16"
   ;MODEL             : string  := "core"  -- "core" or "sbi"
   ;REGFILE_SYNC_READ : boolean := false
  );
end entity tb_OpenBlaze8;

architecture sim of tb_OpenBlaze8 is

  constant C_SCOPE           : string  := C_TB_SCOPE;

  -- Configuration of the KCPSM3 reference
  constant STACK_DEPTH       : natural := 32;
  constant RAM_DEPTH         : natural := 64;
  constant DATA_WIDTH        : natural := 8;
  constant ADDR_INST_WIDTH   : natural := 10;
  constant REGFILE_DEPTH     : natural := 16;

  -- KCPSM3 timing (port_id / out_port valid during the 2 cycles of
  -- INPUT / OUTPUT) : the core with an asynchronous register file
  constant C_IO_FIRST_CYCLE  : boolean := not REGFILE_SYNC_READ;
  -- in_port registered from port_id (allowed by KCPSM3) for the core with an
  -- asynchronous register file, decoded combinationally otherwise
  constant C_IN_PORT_REG     : boolean := (MODEL = "core") and not REGFILE_SYNC_READ;
  -- Stalls (MODEL "sbi") : timeout x4
  constant C_TIMEOUT         : natural := C_TIMEOUT_CYCLES * (1 + 3 * boolean'pos(MODEL = "sbi"));

  -- Clock, reset, program
  signal   clk               : std_logic := '0';
  signal   clk_ena           : boolean   := true;
  signal   rst               : std_logic := '1';
  signal   rom_sel           : natural   := 0;
  signal   prog_ok           : std_logic := '0';

  -- DUT (ports of OpenBlaze8, or sbi_OpenBlaze8 mapped on them)
  signal   cke               : std_logic := '1';  -- cke_i of sbi_OpenBlaze8
  signal   ready             : std_logic := '1';  -- SBI ready of the target
  signal   dut_ics           : std_logic;         -- ics_o of sbi_OpenBlaze8
  signal   dut_address       : std_logic_vector(ADDR_INST_WIDTH-1 downto 0);
  signal   dut_port_id       : std_logic_vector(DATA_WIDTH-1 downto 0);
  signal   dut_in_port       : std_logic_vector(DATA_WIDTH-1 downto 0);
  signal   dut_out_port      : std_logic_vector(DATA_WIDTH-1 downto 0);
  signal   dut_read_strobe   : std_logic;
  signal   dut_write_strobe  : std_logic;
  signal   dut_cs            : std_logic;
  signal   dut_interrupt_ack : std_logic;

  -- Reference
  signal   ref_clk           : std_logic;
  signal   ref_cke           : std_logic;         -- expected clock enable of the DUT
  signal   ref_cke_r         : std_logic := '1';  -- ref_cke on the falling edge
  signal   ref_address       : std_logic_vector(10-1 downto 0);
  signal   ref_instruction   : std_logic_vector(18-1 downto 0);
  signal   ref_port_id       : std_logic_vector(8-1 downto 0);
  signal   ref_in_port       : std_logic_vector(8-1 downto 0);
  signal   ref_out_port      : std_logic_vector(8-1 downto 0);
  signal   ref_read_strobe   : std_logic;
  signal   ref_write_strobe  : std_logic;
  signal   ref_interrupt_ack : std_logic;

  -- IO model, interrupt generator
  signal   mem               : io_mem_t;
  signal   ref_mem_rdata     : std_logic_vector(8-1 downto 0);
  signal   dut_mem_rdata     : std_logic_vector(8-1 downto 0);
  signal   interrupt         : std_logic;
  signal   it_cnt_r          : unsigned(8-1 downto 0);

begin  -- architecture sim

  clock_generator(clk, clk_ena, C_PERIOD, "TB Clock");

  -----------------------------------------------------------------------------
  -- DUT
  -----------------------------------------------------------------------------
  gen_core: if MODEL = "core"
  generate
    dut : OpenBlaze8
      generic map
      (STACK_DEPTH       => STACK_DEPTH
      ,RAM_DEPTH         => RAM_DEPTH
      ,DATA_WIDTH        => DATA_WIDTH
      ,ADDR_INST_WIDTH   => ADDR_INST_WIDTH
      ,REGFILE_DEPTH     => REGFILE_DEPTH
      ,REGFILE_SYNC_READ => REGFILE_SYNC_READ
      )
      port map
      (clock_i           => clk
      ,clock_enable_i    => '1'
      ,reset_i           => rst
      ,address_o         => dut_address
      ,instruction_i     => ref_instruction
      ,port_id_o         => dut_port_id
      ,in_port_i         => dut_in_port
      ,out_port_o        => dut_out_port
      ,read_strobe_o     => dut_read_strobe
      ,write_strobe_o    => dut_write_strobe
      ,interrupt_i       => interrupt
      ,interrupt_ack_o   => dut_interrupt_ack
      );

    dut_ics <= '1';
    dut_cs  <= dut_read_strobe or dut_write_strobe;
  end generate gen_core;

  gen_sbi: if MODEL = "sbi"
  generate
    signal   arstn           : std_logic;
    signal   sbi_ini         : sbi_ini_t(addr (DATA_WIDTH-1 downto 0),
                                         wdata(DATA_WIDTH-1 downto 0));
    signal   sbi_tgt         : sbi_tgt_t(rdata(DATA_WIDTH-1 downto 0));
  begin
    arstn <= not rst;

    dut : sbi_OpenBlaze8
      generic map
      (STACK_DEPTH       => STACK_DEPTH
      ,RAM_DEPTH         => RAM_DEPTH
      ,DATA_WIDTH        => DATA_WIDTH
      ,ADDR_INST_WIDTH   => ADDR_INST_WIDTH
      ,REGFILE_DEPTH     => REGFILE_DEPTH
      ,REGFILE_SYNC_READ => REGFILE_SYNC_READ
      )
      port map
      (clk_i             => clk
      ,cke_i             => cke
      ,arstn_i           => arstn
      ,ics_o             => dut_ics
      ,iaddr_o           => dut_address
      ,idata_i           => ref_instruction
      ,sbi_ini_o         => sbi_ini
      ,sbi_tgt_i         => sbi_tgt
      ,interrupt_i       => interrupt
      ,interrupt_ack_o   => dut_interrupt_ack
      );

    dut_cs            <= sbi_ini.cs;
    dut_read_strobe   <= sbi_ini.re;
    dut_write_strobe  <= sbi_ini.we;
    dut_port_id       <= sbi_ini.addr;
    dut_out_port      <= sbi_ini.wdata;
    sbi_tgt.ready     <= ready;
    sbi_tgt.rdata     <= dut_in_port;
    sbi_tgt.info.name <= (others => ' ');

    -----------------------------------------------------------------------------
    -- Stalls : cke_i and ready drawn on the rising edge, the
    -- same seeds in each scenario. None during the reset and the 3 cycles
    -- after it : the internal reset of the DUT and of the reference is
    -- released 2 clock edges after reset_i, enabled or not.
    -----------------------------------------------------------------------------
    p_stall: process (clk) is
      variable v_seed1 : positive;
      variable v_seed2 : positive;
      variable v_cnt   : natural;
      variable v_rand  : real;
    begin
      if rising_edge(clk)
      then
        if rst = '1'
        then
          v_seed1   := 1;
          v_seed2   := 1;
          v_cnt     := 0;
          cke   <= '1';
          ready <= '1';
        elsif v_cnt < 3
        then
          v_cnt     := v_cnt + 1;
        else
          uniform(v_seed1, v_seed2, v_rand);
          cke   <= '0' when v_rand < 0.25 else '1';
          uniform(v_seed1, v_seed2, v_rand);
          ready <= '0' when v_rand < 0.5  else '1';
        end if;
      end if;
    end process p_stall;
  end generate gen_sbi;

  -----------------------------------------------------------------------------
  -- Reference : kcpsm3, clock gated by the expected clock enable of the DUT
  -- (from the strobes of the reference), latched on the falling edge
  -----------------------------------------------------------------------------
  ref_cke <= cke and (not (ref_read_strobe or ref_write_strobe) or ready);

  p_ref_cke: process (clk) is
  begin
    if falling_edge(clk)
    then
      ref_cke_r <= ref_cke;
    end if;
  end process p_ref_cke;

  ref_clk <= clk and ref_cke_r;

  ref : entity work.kcpsm3(low_level_definition)
    port map
    (clk           => ref_clk
    ,reset         => rst
    ,address       => ref_address
    ,instruction   => ref_instruction
    ,port_id       => ref_port_id
    ,in_port       => ref_in_port
    ,out_port      => ref_out_port
    ,read_strobe   => ref_read_strobe
    ,write_strobe  => ref_write_strobe
    ,interrupt     => interrupt
    ,interrupt_ack => ref_interrupt_ack
    );

  -----------------------------------------------------------------------------
  -- Program ROM (fetched with the address of the reference, the DUT address
  -- is compared to it at every cycle)
  -----------------------------------------------------------------------------
  ins_rom : entity work.tb_OpenBlaze8_rom
    port map
    (clk_i         => ref_clk
    ,sel_i         => rom_sel
    ,address_i     => ref_address
    ,instruction_o => ref_instruction
    );

  -----------------------------------------------------------------------------
  -- IO model : written by the reference, switch = not led
  -----------------------------------------------------------------------------
  p_mem: process (ref_clk) is
  begin
    if rising_edge(ref_clk)
    then
      if rst = '1'
      then
        mem <= (others => (others => 'U'));
      elsif ref_write_strobe = '1'
      then
        mem(to_integer(unsigned(ref_port_id))) <= ref_out_port;
      end if;

      -- Read data registered on port_id at each clock edge (pipelined
      -- in_port mux, allowed by KCPSM3 : port_id valid during 2 cycles)
      ref_mem_rdata <= io_read(mem, ref_port_id);
      dut_mem_rdata <= io_read(mem, dut_port_id);
    end if;
  end process p_mem;

  ref_in_port <= ref_mem_rdata when ref_read_strobe = '1' else
                 (others => 'U');

  -- SBI : read data only valid with ready
  dut_in_port <= (others => 'U')            when dut_read_strobe /= '1' else
                 (others => 'X')            when ready /= '1'           else
                 dut_mem_rdata              when C_IN_PORT_REG          else
                 io_read(mem, dut_port_id);

  -----------------------------------------------------------------------------
  -- Interrupt generator : OUTPUT n to port C_IT_PORT_ID raises the interrupt
  -- n cycles later, cleared by interrupt_ack of the reference
  -----------------------------------------------------------------------------
  p_it: process (ref_clk) is
  begin
    if rising_edge(ref_clk)
    then
      if rst = '1'
      then
        interrupt <= '0';
        it_cnt_r  <= (others => '0');
      else
        if ref_write_strobe = '1' and ref_port_id = C_IT_PORT_ID
        then
          it_cnt_r <= unsigned(ref_out_port);
        elsif it_cnt_r > 0
        then
          it_cnt_r <= it_cnt_r - 1;
        end if;

        if it_cnt_r = 1
        then
          interrupt <= '1';
        end if;

        if ref_interrupt_ack = '1'
        then
          interrupt <= '0';
        end if;
      end if;
    end if;
  end process p_it;

  -----------------------------------------------------------------------------
  -- Lock-step comparison with the reference, on the falling edge, out of
  -- reset. Every cycle (not logged) : address, strobes, interrupt_ack,
  -- port_id / out_port during an access, in the first cycle of an access
  -- (KCPSM3 timing), cs and ics (sbi). Logged (=> OK), once per access (the
  -- cycle ending with an enabled edge) : port_id / out_port of each OUTPUT,
  -- port_id of each INPUT, each interrupt_ack.
  -----------------------------------------------------------------------------
  p_monitor: process (clk) is
    variable v_port_id_d  : std_logic_vector(DATA_WIDTH-1 downto 0);
    variable v_ref_id_d   : std_logic_vector(DATA_WIDTH-1 downto 0);
    variable v_out_port_d : std_logic_vector(DATA_WIDTH-1 downto 0);
    variable v_ref_out_d  : std_logic_vector(DATA_WIDTH-1 downto 0);
    variable v_watch      : std_logic_vector(32-1 downto 0);
    variable v_byte       : natural;
  begin
    if falling_edge(clk)
    then
      if rst = '1'
      then
        prog_ok <= '0';
        v_watch := (others => '0');
      else
        check_value(dut_address      , ref_address      , ERROR, "address = reference"      , C_SCOPE, msg_id => ID_NEVER);
        check_value(dut_read_strobe  , ref_read_strobe  , ERROR, "read_strobe = reference"  , C_SCOPE, msg_id => ID_NEVER);
        check_value(dut_write_strobe , ref_write_strobe , ERROR, "write_strobe = reference" , C_SCOPE, msg_id => ID_NEVER);
        check_value(dut_interrupt_ack, ref_interrupt_ack, ERROR, "interrupt_ack = reference", C_SCOPE, msg_id => ID_NEVER);
        if MODEL = "sbi"
        then
          check_value(dut_cs         , ref_read_strobe or ref_write_strobe, ERROR, "cs = read_strobe or write_strobe", C_SCOPE, msg_id => ID_NEVER);
          check_value(dut_ics        , ref_cke          , ERROR, "ics = cke_i and (not cs or ready)", C_SCOPE, msg_id => ID_NEVER);
        end if;

        -- INPUT / OUTPUT : port_id
        if (ref_write_strobe = '1') or (ref_read_strobe = '1')
        then
          if ref_cke = '1'
          then
            check_value(dut_port_id, ref_port_id, ERROR, "port_id = reference", C_SCOPE);
            if C_IO_FIRST_CYCLE
            then
              check_value(v_port_id_d, v_ref_id_d, ERROR, "port_id = reference in the first cycle of INPUT / OUTPUT", C_SCOPE, msg_id => ID_NEVER);
            end if;
          else
            check_value(dut_port_id, ref_port_id, ERROR, "port_id = reference (stall)", C_SCOPE, msg_id => ID_NEVER);
          end if;
        end if;

        -- OUTPUT : out_port
        if ref_write_strobe = '1'
        then
          if ref_cke = '1'
          then
            check_value(dut_out_port, ref_out_port, ERROR, "out_port = reference", C_SCOPE);
            if C_IO_FIRST_CYCLE
            then
              check_value(v_out_port_d, v_ref_out_d, ERROR, "out_port = reference in the first cycle of OUTPUT", C_SCOPE, msg_id => ID_NEVER);
            end if;
          else
            check_value(dut_out_port, ref_out_port, ERROR, "out_port = reference (stall)", C_SCOPE, msg_id => ID_NEVER);
          end if;
        end if;

        if (ref_interrupt_ack = '1') and (ref_cke = '1')
        then
          check_value(dut_interrupt_ack, '1', ERROR, "interrupt_ack with the reference", C_SCOPE);
        end if;

        -- Program trigger and 32-bit watch (C programs), once per access
        if (dut_write_strobe = '1') and (ref_cke = '1')
        then
          if dut_port_id = C_TEST_PORT_ID
          then
            if dut_out_port = C_TEST_OK
            then
              prog_ok <= '1';
            elsif dut_out_port = C_TEST_KO
            then
              alert(ERROR, "KO trigger of the program", C_SCOPE);
            else
              alert(ERROR, "Invalid trigger 0x" & to_string(dut_out_port, HEX), C_SCOPE);
            end if;
          end if;

          if (unsigned(dut_port_id) >= unsigned(C_WATCH0_PORT_ID)) and
             (unsigned(dut_port_id) <= unsigned(C_WATCH3_PORT_ID))
          then
            v_byte := to_integer(unsigned(dut_port_id(1 downto 0)));
            v_watch(8*v_byte+7 downto 8*v_byte) := dut_out_port;
            if dut_port_id = C_WATCH3_PORT_ID
            then
              log(ID_SEQUENCER, "Watch : 0x" & to_string(v_watch, HEX), C_SCOPE);
            end if;
          end if;
        end if;
      end if;

      -- Values of the last cycle ending with an enabled edge
      if ref_cke = '1'
      then
        v_port_id_d  := dut_port_id;
        v_ref_id_d   := ref_port_id;
        v_out_port_d := dut_out_port;
        v_ref_out_d  := ref_out_port;
      end if;
    end if;
  end process p_monitor;

  -----------------------------------------------------------------------------
  -- Sequencer
  -----------------------------------------------------------------------------
  p_sequencer : process
  begin
    log(ID_LOG_HDR, "MODEL = " & MODEL & ", REGFILE_SYNC_READ = " & boolean'image(REGFILE_SYNC_READ) & ", TESTS_LIST : " & TESTS_LIST, C_SCOPE);

    -- Every name is checked before the first scenario
    for i in 1 to list_length(TESTS_LIST)
    loop
      if not list_contains(C_TESTS, list_item(TESTS_LIST, i))
      then
        alert(TB_ERROR, "Unknown test """ & list_item(TESTS_LIST, i) & """ (tests : " & C_TESTS & ")", C_SCOPE);
      end if;
    end loop;

    for i in 1 to list_length(TESTS_LIST)
    loop
      -- Program selected, reset pulse : each scenario starts from reset (the
      -- IO model and the interrupt generator too)
      rom_sel <= test_index(list_item(TESTS_LIST, i));
      do_reset(clk, rst);

      log(ID_LOG_HDR, "TEST " & integer'image(i) & "/" & integer'image(list_length(TESTS_LIST)) & " : " & list_item(TESTS_LIST, i), C_SCOPE);
      run_test(list_item(TESTS_LIST, i), C_TIMEOUT, clk, prog_ok);
    end loop;

    report_alert_counters(FINAL);
    std.env.stop;
    wait;
  end process p_sequencer;

end architecture sim;
