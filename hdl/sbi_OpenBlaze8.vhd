-------------------------------------------------------------------------------
-- Title      : sbi_OpenBlaze8
-- Project    : 
-------------------------------------------------------------------------------
-- File       : sbi_OpenBlaze8.vhd
-- Author     : Mathieu Rosiere
-- Company    : 
-- Created    : 2017-03-30
-- Last update: 2025-11-22
-- Platform   : 
-- Standard   : VHDL'93/02
-------------------------------------------------------------------------------
-- Description: 
-------------------------------------------------------------------------------
-- Copyright (c) 2017 
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author   Description
-- 2017-03-30  1.0      mrosiere Created
-- 2025-01-21  1.1      mrosiere Fix busy usage
-- 2025-03-09  1.2      mrosiere Use unconstrainted sbi
-- 2025-03-15  1.3      mrosiere Stall idata_i when cke desasserted
-- 2025-04-14  1.4      mrosiere Add output ics_o
-- 2025-05-08  1.5      mrosiere data cs depend of re and we
-- 2025-11-05  1.6      mrosiere Add parameter for sync/async regfile
-------------------------------------------------------------------------------

library IEEE;
use     IEEE.STD_LOGIC_1164.ALL;
use     IEEE.numeric_std.ALL;
library asylum;
library asylum;
use     asylum.sbi_pkg.all;
use     asylum.OpenBlaze8_pkg.all;

entity sbi_OpenBlaze8 is
  generic (
     STACK_DEPTH       : natural := 32;
     RAM_DEPTH         : natural := 64;
     DATA_WIDTH        : natural := 8;
     ADDR_INST_WIDTH   : natural := 10;
     REGFILE_DEPTH     : natural := 16;
     REGFILE_SYNC_READ : boolean := false;
     MULTI_CYCLE       : natural := 1);
  port   (
    clk_i            : in    std_logic;
    cke_i            : in    std_logic;
    arstn_i          : in    std_logic; -- asynchronous reset

    -- Instructions
    ics_o            : out std_logic;
    iaddr_o          : out std_logic_vector(ADDR_INST_WIDTH-1 downto 0);
    idata_i          : in  std_logic_vector(18-1 downto 0);
    
    -- Bus
    sbi_ini_o        : out   sbi_ini_t;
    sbi_tgt_i        : in    sbi_tgt_t;

    -- To/From IT Ctrl
    interrupt_i      : in    std_logic;
    interrupt_ack_o  : out   std_logic
    );
  
end entity sbi_OpenBlaze8;

architecture rtl of sbi_OpenBlaze8 is
  signal dre     : std_logic;
  signal dwe     : std_logic;
  signal cke     : std_logic;
  signal arst    : std_logic;
begin  -- architecture rtl

  arst    <= not arstn_i;
  cke     <= cke_i and sbi_tgt_i.ready;
  ics_o   <= cke;
  
  ins_OpenBlaze8 : OpenBlaze8
  generic map(
     STACK_DEPTH       => STACK_DEPTH      ,
     RAM_DEPTH         => RAM_DEPTH        ,
     DATA_WIDTH        => DATA_WIDTH       ,
     ADDR_INST_WIDTH   => ADDR_INST_WIDTH  ,
     REGFILE_DEPTH     => REGFILE_DEPTH    ,
     REGFILE_SYNC_READ => REGFILE_SYNC_READ,
     MULTI_CYCLE       => MULTI_CYCLE    
     )
  port map(
    clock_i           => clk_i          ,
    clock_enable_i    => cke            ,
    reset_i           => arst           ,
    address_o         => iaddr_o        ,
    instruction_i     => idata_i        ,
    port_id_o         => sbi_ini_o.addr ,
    in_port_i         => sbi_tgt_i.rdata,
    out_port_o        => sbi_ini_o.wdata,
    read_strobe_o     => dre            ,
    write_strobe_o    => dwe            ,
    interrupt_i       => interrupt_i    ,
    interrupt_ack_o   => interrupt_ack_o
    );

  sbi_ini_o.cs <= dre or dwe;
  sbi_ini_o.re <= dre;
  sbi_ini_o.we <= dwe;
  
end architecture rtl;
