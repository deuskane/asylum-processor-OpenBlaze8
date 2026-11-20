-------------------------------------------------------------------------------
-- Title      : tb_OpenBlaze8_bfm_pkg
-- Project    : OpenBlaze8
-------------------------------------------------------------------------------
-- File       : tb_OpenBlaze8_bfm_pkg.vhd
-- Author     : mrosiere
-------------------------------------------------------------------------------
-- Description: Helpers of the tb_OpenBlaze8 scenarios : IO map of the test
--              programs (sim/testbench-asm, sim/testbench-c/testbench.h),
--              IO model, reset pulse, run of a program until its OK trigger
-------------------------------------------------------------------------------
-- Copyright (c) 2026
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author   Description
-- 2026-11-20  1.0      mrosiere Created (split of tb_OpenBlaze8)
-------------------------------------------------------------------------------

library ieee;
use     ieee.std_logic_1164.all;
use     ieee.numeric_std.all;

library uvvm_util;
context uvvm_util.uvvm_util_context;

package tb_OpenBlaze8_bfm_pkg is

  constant C_TB_SCOPE        : string  := "TB_OpenBlaze8";
  constant C_PERIOD          : time    := 10 ns;

  -- Maximum number of cycles of a program, from the reset release to its
  -- OK trigger (without stall)
  constant C_TIMEOUT_CYCLES  : natural := 10000;

  -- IO map of the test programs
  constant C_SWITCH_PORT_ID  : std_logic_vector(8-1 downto 0) := x"00"; -- reads not led
  constant C_LED_PORT_ID     : std_logic_vector(8-1 downto 0) := x"20";
  constant C_WATCH0_PORT_ID  : std_logic_vector(8-1 downto 0) := x"C0"; -- 32-bit watch, LSB
  constant C_WATCH3_PORT_ID  : std_logic_vector(8-1 downto 0) := x"C3"; -- 32-bit watch, MSB
  constant C_TEST_PORT_ID    : std_logic_vector(8-1 downto 0) := x"E0"; -- trigger
  constant C_IT_PORT_ID      : std_logic_vector(8-1 downto 0) := x"FF"; -- interrupt after n cycles
  constant C_TEST_OK         : std_logic_vector(8-1 downto 0) := x"FA";
  constant C_TEST_KO         : std_logic_vector(8-1 downto 0) := x"ED";

  -- IO model : 256 ports, written by OUTPUT, read back by INPUT
  type io_mem_t is array (0 to 2**8-1) of std_logic_vector(8-1 downto 0);

  -- IO read : the switch port reads the inverse of the led port
  function io_read
    (constant mem      : in    io_mem_t
    ;constant port_id  : in    std_logic_vector
    ) return std_logic_vector;

  -- Reset pulse of 5 cycles, released on a falling edge
  procedure do_reset
    (signal   clk      : in    std_logic
    ;signal   rst      : out   std_logic
    );

  -- Wait the OK trigger of the program (port C_TEST_PORT_ID), at most
  -- timeout cycles after the reset release
  procedure run_program
    (constant name     : in    string
    ;constant timeout  : in    natural
    ;signal   clk      : in    std_logic
    ;signal   prog_ok  : in    std_logic
    );

end package tb_OpenBlaze8_bfm_pkg;

package body tb_OpenBlaze8_bfm_pkg is

  function io_read
    (constant mem      : in    io_mem_t
    ;constant port_id  : in    std_logic_vector
    ) return std_logic_vector is
  begin
    if is_x(port_id)
    then
      return (8-1 downto 0 => 'X');
    elsif port_id = C_SWITCH_PORT_ID
    then
      return not mem(to_integer(unsigned(C_LED_PORT_ID)));
    else
      return     mem(to_integer(unsigned(port_id)));
    end if;
  end function io_read;

  procedure do_reset
    (signal   clk      : in    std_logic
    ;signal   rst      : out   std_logic
    ) is
  begin
    rst <= '1';
    for i in 1 to 5
    loop
      wait until rising_edge(clk);
    end loop;
    wait until falling_edge(clk);
    rst <= '0';
  end procedure do_reset;

  procedure run_program
    (constant name     : in    string
    ;constant timeout  : in    natural
    ;signal   clk      : in    std_logic
    ;signal   prog_ok  : in    std_logic
    ) is
    variable v_start   : time;
  begin
    v_start := now;
    if prog_ok /= '1'
    then
      wait until prog_ok = '1' for timeout * C_PERIOD;
    end if;
    check_value(prog_ok, '1', ERROR, "Program " & name & " : OK trigger within " & integer'image(timeout) & " cycles", C_TB_SCOPE);
    log(ID_SEQUENCER, "Program " & name & " : OK trigger " & integer'image((now - v_start) / C_PERIOD) & " cycles after the reset release", C_TB_SCOPE);
  end procedure run_program;

end package body tb_OpenBlaze8_bfm_pkg;
