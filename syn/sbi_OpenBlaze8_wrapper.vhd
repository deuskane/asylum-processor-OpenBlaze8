-------------------------------------------------------------------------------
-- Title      : sbi_OpenBlaze8_wrapper
-- Project    : Asylum
-------------------------------------------------------------------------------
-- File       : sbi_OpenBlaze8_wrapper.vhd
-- Author     : Mathieu Rosiere
-------------------------------------------------------------------------------
-- Description:
-- Wrapper (lint_ghdl, lint_ghdl_synth_sbi_*, syn_sbi_*) : sbi_OpenBlaze8
-- with flat and constrained SBI ports (sbi_OpenBlaze8 has unconstrained SBI
-- ports and cannot be a synthesis top). The SBI address / data width is
-- DATA_WIDTH (PORT_ID / OUT_PORT / IN_PORT). The generics and their defaults
-- are those of sbi_OpenBlaze8. The core OpenBlaze8 has constrained ports :
-- it is the top of lint_ghdl_synth_core_* / syn_core_* (no wrapper).
-------------------------------------------------------------------------------
-- Copyright (c) 2026
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author   Description
-- 2026-10-20  1.0      mrosiere Created
-- 2026-10-24  1.1      mrosiere Was OpenBlaze8_synth_top, library asylum
-- 2026-11-20  2.0      mrosiere Was OpenBlaze8_wrapper : sbi_OpenBlaze8 only,
--                               the core is synthesized without wrapper
-------------------------------------------------------------------------------

library ieee;
use     ieee.std_logic_1164.all;
library asylum;
use     asylum.sbi_pkg.all;

entity sbi_OpenBlaze8_wrapper is
  generic (
    STACK_DEPTH            : natural := 32;
    RAM_DEPTH              : natural := 64;
    DATA_WIDTH             : natural := 8;
    ADDR_INST_WIDTH        : natural := 10;
    REGFILE_DEPTH          : natural := 16;
    REGFILE_SYNC_READ      : boolean := false
  );
  port (
    clk_i                  : in  std_logic;
    cke_i                  : in  std_logic;
    arstn_i                : in  std_logic;
    ics_o                  : out std_logic;
    iaddr_o                : out std_logic_vector(ADDR_INST_WIDTH-1 downto 0);
    idata_i                : in  std_logic_vector(18-1 downto 0);
    sbi_cs_o               : out std_logic;
    sbi_re_o               : out std_logic;
    sbi_we_o               : out std_logic;
    sbi_addr_o             : out std_logic_vector(DATA_WIDTH-1 downto 0);
    sbi_wdata_o            : out std_logic_vector(DATA_WIDTH-1 downto 0);
    sbi_ready_i            : in  std_logic;
    sbi_rdata_i            : in  std_logic_vector(DATA_WIDTH-1 downto 0);
    interrupt_i            : in  std_logic;
    interrupt_ack_o        : out std_logic
  );
end entity sbi_OpenBlaze8_wrapper;

architecture rtl of sbi_OpenBlaze8_wrapper is

  signal sbi_ini           : sbi_ini_t(addr (DATA_WIDTH-1 downto 0),
                                       wdata(DATA_WIDTH-1 downto 0));
  signal sbi_tgt           : sbi_tgt_t(rdata(DATA_WIDTH-1 downto 0));

begin

  -----------------------------------------------------------------------------
  -- sbi_OpenBlaze8
  -----------------------------------------------------------------------------
  sbi_cs_o                 <= sbi_ini.cs;
  sbi_re_o                 <= sbi_ini.re;
  sbi_we_o                 <= sbi_ini.we;
  sbi_addr_o               <= sbi_ini.addr;
  sbi_wdata_o              <= sbi_ini.wdata;
  sbi_tgt.ready            <= sbi_ready_i;
  sbi_tgt.rdata            <= sbi_rdata_i;
  sbi_tgt.info.name        <= (others => ' ');

  ins_sbi_OpenBlaze8 : entity asylum.sbi_OpenBlaze8
    generic map (
      STACK_DEPTH          => STACK_DEPTH,
      RAM_DEPTH            => RAM_DEPTH,
      DATA_WIDTH           => DATA_WIDTH,
      ADDR_INST_WIDTH      => ADDR_INST_WIDTH,
      REGFILE_DEPTH        => REGFILE_DEPTH,
      REGFILE_SYNC_READ    => REGFILE_SYNC_READ
    )
    port map (
      clk_i                => clk_i,
      cke_i                => cke_i,
      arstn_i              => arstn_i,
      ics_o                => ics_o,
      iaddr_o              => iaddr_o,
      idata_i              => idata_i,
      sbi_ini_o            => sbi_ini,
      sbi_tgt_i            => sbi_tgt,
      interrupt_i          => interrupt_i,
      interrupt_ack_o      => interrupt_ack_o
    );

end architecture rtl;
