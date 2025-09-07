-------------------------------------------------------------------------------
-- Title      : OpenBlaze8 Interrupt
-- Project    : OpenBlaze8
-------------------------------------------------------------------------------
-- File       : OpenBlaze8_Interrupt.vhd
-- Author     : mrosiere
-- Company    : 
-- Created    : 2014-05-22
-- Last update: 2021-10-15
-- Platform   : 
-- Standard   : VHDL'87
-------------------------------------------------------------------------------
-- Description: 
-------------------------------------------------------------------------------
-- Copyright (c) 2014 
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author  Description
-- 2014-05-22  1.0      mrosiere	Created
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
library asylum;
use asylum.math_pkg.all;

entity OpenBlaze8_Interrupt is
  -- =====[ Interfaces ]==========================
  port (
    clock_i                    : in  std_logic;
    clock_enable_i             : in  std_logic;
    reset_i                    : in  std_logic; -- synchronous reset

    -- From Clock
    cycle_phase_i              : in  std_logic;                      -- 0 = first cycle, 1 = second cycle

    interrupt_enable_i         : in  std_logic;  -- eint or reti enable
    interrupt_disable_i        : in  std_logic;  -- dint or reti disable
    
    it_en_o                    : out std_logic;  -- Have an interruption

    interrupt_i                : in  std_logic;
    interrupt_ack_o            : out std_logic    
    );
end OpenBlaze8_Interrupt;

architecture rtl of OpenBlaze8_Interrupt is

  signal it_mask_r     : std_logic;
  signal it_r          : std_logic;
  signal it_val_r_next : std_logic;
  signal it_val_r      : std_logic;
  signal it_ack_r      : std_logic;
  
begin  -- rtl
  -----------------------------------------------------------------------------
  -- Interrupt output
  -----------------------------------------------------------------------------
  transition: process (clock_i)
  begin  -- process transition
    if clock_i'event and clock_i = '1' then
      if reset_i = '1' then
        it_mask_r <= '1';
        it_r      <= '0';
        it_val_r  <= '0';
        it_ack_r  <= '0';
      elsif clock_enable_i = '1' then

        -- Capture Iterruption
        it_r        <= interrupt_i;
        it_val_r    <= it_val_r_next;
        it_ack_r    <= it_val_r;
        
        if    interrupt_disable_i = '1'
        then
          it_mask_r <= '1';
        elsif interrupt_enable_i  = '1'
        then
          it_mask_r <= '0';
        end if;

      end if;
    end if;
  end process transition;

  it_val_r_next <= cycle_phase_i and
                   not it_mask_r and
                   it_r          and
                   not it_val_r;
  
  -----------------------------------------------------------------------------
  -- Interrupt output
  -----------------------------------------------------------------------------
  it_en_o         <= it_val_r or it_ack_r;
  interrupt_ack_o <= it_ack_r;
  
end rtl;
