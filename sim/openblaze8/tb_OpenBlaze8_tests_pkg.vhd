-------------------------------------------------------------------------------
-- Title      : tb_OpenBlaze8_tests_pkg
-- Project    : OpenBlaze8
-------------------------------------------------------------------------------
-- File       : tb_OpenBlaze8_tests_pkg.vhd
-- Author     : mrosiere
-------------------------------------------------------------------------------
-- Description: Scenarios of tb_OpenBlaze8 : names (valid items of TESTS_LIST)
--              and dispatch (run_test). A scenario is a test program
--              (sim/testbench-asm/<name>.psm, sim/testbench-c/<name>.c),
--              compiled by pbcc_gen into the ROM tb_OpenBlaze8_rom selects
--              (index of the name in C_TESTS) : the program is the code of
--              the scenario, the checks are the lock-step comparison with
--              kcpsm3 and the OK trigger of the program.
-------------------------------------------------------------------------------
-- Copyright (c) 2026
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author   Description
-- 2026-11-20  1.0      mrosiere Created (split of tb_OpenBlaze8)
-------------------------------------------------------------------------------

library ieee;
use     ieee.std_logic_1164.all;

library uvvm_util;
context uvvm_util.uvvm_util_context;

library asylum;
use     asylum.string_pkg.all;

library work;
use     work.tb_OpenBlaze8_bfm_pkg.all;

package tb_OpenBlaze8_tests_pkg is

  -- Names of the scenarios (valid items of TESTS_LIST), in the order of the
  -- ROMs of tb_OpenBlaze8_rom
  constant C_TESTS : string := "test_000_default,test_001_test_ok,test_002_jump,"
                             & "test_003_jump,test_004_comp,test_005_comp,test_006_and,"
                             & "test_007_or,test_008_xor,test_009_andi,test_010_ori,"
                             & "test_011_xori,test_012_add,test_013_addi,test_014_sub,"
                             & "test_015_subi,test_016_comp,test_017_compi,test_018_rl,"
                             & "test_019_rr,test_020_sl0,test_021_sl1,test_022_sla,"
                             & "test_023_slx,test_024_sr,test_025_call,test_026_call_ret,"
                             & "test_027_call_ret,test_028_call_ret_cond,"
                             & "test_029_fetch_store,test_030_fetch_store,"
                             & "test_031_fetch_store,test_032_stack_depth,test_033_mul,"
                             & "test_034_div,test_035_test,test_036_test,test_037_in_out,"
                             & "test_038_in_out,test_039_eint_reti,test_040_eint_reti,"
                             & "test_041_eint_reti,test_042_in_out_indirect,test_043_carry,"
                             & "test_044_reti_flags,test_045_int_reset,test_uadd16,"
                             & "test_udiv16,test_umul16";

  -- Index of the program name in C_TESTS (ROM of tb_OpenBlaze8_rom)
  function test_index
    (constant name     : in    string
    ) return natural;

  -- Run the scenario name : the program selected before the reset runs until
  -- its OK trigger
  procedure run_test
    (constant name     : in    string
    ;constant timeout  : in    natural
    ;signal   clk      : in    std_logic
    ;signal   prog_ok  : in    std_logic
    );

end package tb_OpenBlaze8_tests_pkg;

package body tb_OpenBlaze8_tests_pkg is

  function test_index
    (constant name     : in    string
    ) return natural is
  begin
    for i in 1 to list_length(C_TESTS)
    loop
      if string_eq(list_item(C_TESTS, i), name)
      then
        return i;
      end if;
    end loop;
    return 0;
  end function test_index;

  procedure run_test
    (constant name     : in    string
    ;constant timeout  : in    natural
    ;signal   clk      : in    std_logic
    ;signal   prog_ok  : in    std_logic
    ) is
  begin
    if list_contains(C_TESTS, name)
    then
      run_program(name, timeout, clk, prog_ok);
    else
      alert(TB_ERROR, "Unknown test " & name, C_TB_SCOPE);
    end if;
  end procedure run_test;

end package body tb_OpenBlaze8_tests_pkg;
