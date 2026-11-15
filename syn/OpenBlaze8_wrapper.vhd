-------------------------------------------------------------------------------
-- Title      : OpenBlaze8_wrapper
-- Project    : Asylum
-------------------------------------------------------------------------------
-- File       : OpenBlaze8_wrapper.vhd
-- Author     : Mathieu Rosiere
-------------------------------------------------------------------------------
-- Description:
-- Wrapper (lint_ghdl, lint_ghdl_synth_*) : one instance of
-- OpenBlaze8 (core_* ports) and one instance of sbi_OpenBlaze8 (sbi_* ports)
-- with flat and constrained SBI ports (sbi_OpenBlaze8 has unconstrained SBI
-- ports and cannot be a synthesis top). The SBI address / data width is
-- DATA_WIDTH (PORT_ID / OUT_PORT / IN_PORT). The generics are forwarded to
-- both instances, defaults of OpenBlaze8 (REGFILE_SYNC_READ = true).
-------------------------------------------------------------------------------
-- Copyright (c) 2026
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author   Description
-- 2026-10-20  1.0      mrosiere Created
-- 2026-10-24  1.1      mrosiere Was OpenBlaze8_synth_top, library asylum
-------------------------------------------------------------------------------

library ieee;
use     ieee.std_logic_1164.all;
library asylum;
use     asylum.sbi_pkg.all;

entity OpenBlaze8_wrapper is
  generic (
    STACK_DEPTH            : natural := 32;
    RAM_DEPTH              : natural := 64;
    DATA_WIDTH             : natural := 8;
    ADDR_INST_WIDTH        : natural := 10;
    REGFILE_DEPTH          : natural := 16;
    REGFILE_SYNC_READ      : boolean := true
  );
  port (
    -- OpenBlaze8
    core_clock_i           : in  std_logic;
    core_clock_enable_i    : in  std_logic;
    core_reset_i           : in  std_logic;
    core_address_o         : out std_logic_vector(ADDR_INST_WIDTH downto 1);
    core_instruction_i     : in  std_logic_vector(18 downto 1);
    core_port_id_o         : out std_logic_vector(DATA_WIDTH downto 1);
    core_in_port_i         : in  std_logic_vector(DATA_WIDTH downto 1);
    core_out_port_o        : out std_logic_vector(DATA_WIDTH downto 1);
    core_read_strobe_o     : out std_logic;
    core_write_strobe_o    : out std_logic;
    core_interrupt_i       : in  std_logic;
    core_interrupt_ack_o   : out std_logic;

    -- sbi_OpenBlaze8
    sbi_clk_i              : in  std_logic;
    sbi_cke_i              : in  std_logic;
    sbi_arstn_i            : in  std_logic;
    sbi_ics_o              : out std_logic;
    sbi_iaddr_o            : out std_logic_vector(ADDR_INST_WIDTH-1 downto 0);
    sbi_idata_i            : in  std_logic_vector(18-1 downto 0);
    sbi_cs_o               : out std_logic;
    sbi_re_o               : out std_logic;
    sbi_we_o               : out std_logic;
    sbi_addr_o             : out std_logic_vector(DATA_WIDTH-1 downto 0);
    sbi_wdata_o            : out std_logic_vector(DATA_WIDTH-1 downto 0);
    sbi_ready_i            : in  std_logic;
    sbi_rdata_i            : in  std_logic_vector(DATA_WIDTH-1 downto 0);
    sbi_interrupt_i        : in  std_logic;
    sbi_interrupt_ack_o    : out std_logic
  );
end entity OpenBlaze8_wrapper;

architecture rtl of OpenBlaze8_wrapper is

  signal sbi_ini           : sbi_ini_t(addr (DATA_WIDTH-1 downto 0),
                                       wdata(DATA_WIDTH-1 downto 0));
  signal sbi_tgt           : sbi_tgt_t(rdata(DATA_WIDTH-1 downto 0));

begin

  -----------------------------------------------------------------------------
  -- OpenBlaze8
  -----------------------------------------------------------------------------
  ins_OpenBlaze8 : entity asylum.OpenBlaze8
    generic map (
      STACK_DEPTH          => STACK_DEPTH,
      RAM_DEPTH            => RAM_DEPTH,
      DATA_WIDTH           => DATA_WIDTH,
      ADDR_INST_WIDTH      => ADDR_INST_WIDTH,
      REGFILE_DEPTH        => REGFILE_DEPTH,
      REGFILE_SYNC_READ    => REGFILE_SYNC_READ
    )
    port map (
      clock_i              => core_clock_i,
      clock_enable_i       => core_clock_enable_i,
      reset_i              => core_reset_i,
      address_o            => core_address_o,
      instruction_i        => core_instruction_i,
      port_id_o            => core_port_id_o,
      in_port_i            => core_in_port_i,
      out_port_o           => core_out_port_o,
      read_strobe_o        => core_read_strobe_o,
      write_strobe_o       => core_write_strobe_o,
      interrupt_i          => core_interrupt_i,
      interrupt_ack_o      => core_interrupt_ack_o
    );

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
      clk_i                => sbi_clk_i,
      cke_i                => sbi_cke_i,
      arstn_i              => sbi_arstn_i,
      ics_o                => sbi_ics_o,
      iaddr_o              => sbi_iaddr_o,
      idata_i              => sbi_idata_i,
      sbi_ini_o            => sbi_ini,
      sbi_tgt_i            => sbi_tgt,
      interrupt_i          => sbi_interrupt_i,
      interrupt_ack_o      => sbi_interrupt_ack_o
    );

end architecture rtl;
