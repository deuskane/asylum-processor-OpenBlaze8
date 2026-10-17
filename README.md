<!--
  README GENERATION INSTRUCTIONS (for the next regeneration run)
  ----------------------------------------------------------------
  This README follows the common Asylum IP model. Regenerate it from the
  sources, never from the previous README text alone.

  Sources of truth (in priority order):
    1. hdl/*.vhd            : entities, generics, ports, packages
    2. hdl/csr/*.hjson      : register map (regtool); *_csr.md/.h are generated
    3. <IP>.core            : VLNV (name), filesets, targets, depends, revisions
    4. mk/targets.txt       : target list shown by `make help`; mk/defs.mk
    5. sim/, syn/, esw/, boards/ : testbenches, constraints, software
  Section order (keep it, same headings in every IP):
    CI badge / Title + one-line description + VLNV / Table of Contents /
    Introduction (Key Features) / Block Diagram / Top-Level (Parameters,
    Ports, Instantiation Example) / HDL Modules / Register Map /
    Verification / Synthesis / Design Notes (optional) /
    Directory Structure / Dependencies
  Rules:
    - Language: English. Tables: Parameters = Name|Type|Default|Description,
      Ports = Name|Direction|Type|Description (grouped by interface).
    - Register Map: link to the generated hdl/csr/<X>_csr.md (plus the
      .hjson source and _csr.h header); never copy register tables here.
    - Top-Level = sbi_* wrapper if present, else the entity used by the
      `default` target, else the main entity (libraries: list packages).
    - Write "This IP has no software-visible registers." / "No dedicated
      synthesis target ..." instead of removing a section.
    - Keep still-accurate hand-written content (ISA tables, results,
      images) in "Design Notes"; drop anything not backed by the sources.
    - Block diagram: doc/<NAME>.drawio (NAME = 4th field of the VLNV),
      top entity box with generics on top, inputs left, outputs right,
      bus interfaces as bold arrows, internal blocks colour-coded
      (CSR yellow, FIFO/memory green, core logic blue, external grey).
      Update it whenever ports/generics/sub-blocks change.
    - Do not edit generated files (hdl/csr/*_csr.*) or the CI badge URL.
-->
[![CI](https://github.com/deuskane/asylum-processor-OpenBlaze8/actions/workflows/ci.yml/badge.svg)](https://github.com/deuskane/asylum-processor-OpenBlaze8/actions/workflows/ci.yml)

# asylum-processor-OpenBlaze8

**8-bit soft processor, cycle-accurate clone of the Xilinx PicoBlaze-3 (KCPSM3), written in portable RTL with an SBI bus wrapper.**

VLNV: `asylum:processor:OpenBlaze8:1.3.2`

## Table of Contents

1. [Introduction](#introduction)
2. [Block Diagram](#block-diagram)
3. [Top-Level](#top-level)
4. [HDL Modules](#hdl-modules)
5. [Register Map](#register-map)
6. [Verification](#verification)
7. [Synthesis](#synthesis)
8. [Design Notes](#design-notes)
9. [Directory Structure](#directory-structure)
10. [Dependencies](#dependencies)

## Introduction

OpenBlaze8 re-implements the KCPSM3 (PicoBlaze-3) micro-controller of Xilinx without any vendor primitive: it executes the same 18-bit instruction set with the same timing (two clock cycles per instruction) and the same port / interrupt behaviour, so programs written for KCPSM3 (`.psm`, kcpsm3 or pBlazIDE syntax) or compiled with the PicoBlaze port of SDCC run unchanged. The core is split into small modules (decode, control, ALU, register file, stack, scratch-pad RAM...) and its memories use the generic `asylum:component:ram` / `asylum:component:stack` cores.

The `sbi_OpenBlaze8` wrapper maps the PicoBlaze IO port interface onto the Asylum SBI bus (`port_id` = address, `out_port` = write data, `in_port` = read data) and stalls the core while the addressed target is not ready. It is the OpenBlaze8 CPU option of the PicoSoC (`cpu_wrapper`, `CPU_MODEL = "OpenBlaze8"`).

### Key Features

- PicoBlaze-3 compatible instruction set: LOAD, logic, arithmetic with carry, COMPARE / TEST, 10 shift / rotate operations, INPUT / OUTPUT, FETCH / STORE, JUMP / CALL / RETURN (conditional on Z / NZ / C / NC), RETURNI, ENABLE / DISABLE INTERRUPT
- Two clock cycles per instruction, global clock enable (`clock_enable_i` / `cke_i`)
- Configurable register file depth (`REGFILE_DEPTH`, 16 by default) with synchronous or asynchronous read (`REGFILE_SYNC_READ`)
- Configurable scratch-pad RAM (`RAM_DEPTH`, 64 bytes by default) and CALL/RETURN stack (`STACK_DEPTH`, 32 by default, oldest entry overwritten on overflow)
- ZERO and CARRY flags, saved on interrupt entry and restored by RETURNI
- One interrupt input, vector at the last program address (all ones), `interrupt_ack` output
- 256 IO ports, mapped on the SBI bus by `sbi_OpenBlaze8` (8-bit address, 8-bit data, wait states through `sbi_tgt_i.ready`)
- Verified in lock-step against the original Xilinx `kcpsm3` netlist with 42 assembler and 3 C test programs

## Block Diagram

Diagram: [doc/OpenBlaze8.drawio](doc/OpenBlaze8.drawio) (open with diagrams.net or the VS Code Draw.io extension).

- `sbi_OpenBlaze8` inverts `arstn_i` into the core reset, gates the core clock enable with the SBI handshake (`cke = cke_i and (not cs or ready)`) and outputs it as `ics_o` (instruction fetch enable).
- `OpenBlaze8_Decode` splits the instruction into opcodes, register numbers and the 10-bit immediate; `OpenBlaze8_Control` decodes the opcode into the enables of every other block, phased by `OpenBlaze8_Clock` (`cycle_phase`).
- `OpenBlaze8_Program_Counter` selects PC+1, the jump / call target, the stack top (+1 for RETURN, as-is for RETURNI) or the interrupt vector; `OpenBlaze8_Stack` holds the return addresses.
- `OpenBlaze8_RegFile` provides `sX` / `sY`, `OpenBlaze8_Operand` selects `sY` or the constant `kk`, `OpenBlaze8_ALU` computes the result and the next C / Z flags stored in `OpenBlaze8_Flags`.
- `OpenBlaze8_Result` writes back the ALU result, the scratch-pad data (`OpenBlaze8_RAM`, FETCH) or the input port (`OpenBlaze8_LoadStore`, INPUT) into `sX`. `OpenBlaze8_Interrupt` masks, samples and acknowledges `interrupt_i`.

## Top-Level

Top-level entity: **`sbi_OpenBlaze8`** ([hdl/sbi_OpenBlaze8.vhd](hdl/sbi_OpenBlaze8.vhd)), library `asylum`, component declared in `asylum.OpenBlaze8_pkg`. The `default` target of the core uses the bare core `OpenBlaze8` as toplevel (see [HDL Modules](#hdl-modules)).

### Parameters

| Name | Type | Default | Description |
|------|------|---------|-------------|
| `STACK_DEPTH` | natural | `32` | Number of entries of the CALL/RETURN stack |
| `RAM_DEPTH` | natural | `64` | Size of the scratch-pad RAM in bytes (FETCH / STORE) |
| `DATA_WIDTH` | natural | `8` | Data path width (the ALU shift logic and the instruction format assume 8) |
| `ADDR_INST_WIDTH` | natural | `10` | Program address width (at most 10, the immediate field width) |
| `REGFILE_DEPTH` | natural | `16` | Number of registers (at most 16, 4-bit register fields) |
| `REGFILE_SYNC_READ` | boolean | `false` | Register file read mode: `true` synchronous, `false` asynchronous (note: the default of the bare `OpenBlaze8` is `true`) |

### Ports

#### Clock & Reset

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `clk_i` | in | std_logic | Clock |
| `cke_i` | in | std_logic | Clock enable |
| `arstn_i` | in | std_logic | Reset, active low (inverted and used as the core `reset_i`) |

#### Instruction

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `ics_o` | out | std_logic | Instruction memory enable (internal clock enable, low while the SBI access is stalled) |
| `iaddr_o` | out | std_logic_vector(ADDR_INST_WIDTH-1 downto 0) | Program counter (instruction address) |
| `idata_i` | in | std_logic_vector(17 downto 0) | Instruction |

#### Bus (SBI)

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `sbi_ini_o` | out | sbi_ini_t | SBI request: `cs` = `re` or `we`, `re` = READ_STROBE, `we` = WRITE_STROBE, `addr` = PORT_ID, `wdata` = OUT_PORT (both `DATA_WIDTH` bits) |
| `sbi_tgt_i` | in | sbi_tgt_t | SBI response: `rdata` = IN_PORT, `ready` (core stalled while `cs = 1` and `ready = 0`) |

#### Interrupts

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `interrupt_i` | in | std_logic | Interrupt request (level, sampled when interrupts are enabled) |
| `interrupt_ack_o` | out | std_logic | Interrupt acknowledge (one cycle) |

### Instantiation Example

```vhdl
library asylum;
use     asylum.sbi_pkg.all;
use     asylum.OpenBlaze8_pkg.all;

  ins_cpu : entity asylum.sbi_OpenBlaze8
    generic map
    ( STACK_DEPTH       => 32
     ,RAM_DEPTH         => 256
     ,DATA_WIDTH        => 8
     ,ADDR_INST_WIDTH   => 10
     ,REGFILE_DEPTH     => 16
     ,REGFILE_SYNC_READ => true
    )
    port map
    ( clk_i           => clk
     ,cke_i           => '1'
     ,arstn_i         => arst_b
     ,ics_o           => inst_cs
     ,iaddr_o         => inst_addr        -- (9 downto 0)
     ,idata_i         => inst_data        -- (17 downto 0)
     ,sbi_ini_o       => sbi_ini          -- sbi_ini_t(addr(7 downto 0), wdata(7 downto 0))
     ,sbi_tgt_i       => sbi_tgt          -- sbi_tgt_t(rdata(7 downto 0))
     ,interrupt_i     => it
     ,interrupt_ack_o => it_ack
    );
```

The program ROM is generated from a `.psm` or `.c` file by the `pbcc_gen` generator of `asylum:utils:generators` (default entity `OpenBlaze8_ROM`, ports `clk_i`, `cke_i`, `address_i`, `instruction_o`).

## HDL Modules

| File | Unit | Kind | Role |
|------|------|------|------|
| [hdl/OpenBlaze8_pkg.vhd](hdl/OpenBlaze8_pkg.vhd) | `OpenBlaze8_pkg` | package | Component declarations of all OpenBlaze8 entities and of `sbi_OpenBlaze8` |
| [hdl/OpenBlaze8.vhd](hdl/OpenBlaze8.vhd) | `OpenBlaze8` | entity | Processor core (KCPSM3 compatible interface), toplevel of the `default` target |
| [hdl/sbi_OpenBlaze8.vhd](hdl/sbi_OpenBlaze8.vhd) | `sbi_OpenBlaze8` | entity | Top-level: SBI wrapper around `OpenBlaze8` |
| [hdl/OpenBlaze8_Clock.vhd](hdl/OpenBlaze8_Clock.vhd) | `OpenBlaze8_Clock` | entity | Cycle phase toggle, clock / reset pass-through |
| [hdl/OpenBlaze8_Decode.vhd](hdl/OpenBlaze8_Decode.vhd) | `OpenBlaze8_Decode` | entity | Instruction field extraction, instruction replaced by `LOAD sX, sX` on interrupt |
| [hdl/OpenBlaze8_Control.vhd](hdl/OpenBlaze8_Control.vhd) | `OpenBlaze8_Control` | entity | Opcode decoder: PC / stack / register / ALU / flags / IO / RAM / interrupt controls |
| [hdl/OpenBlaze8_Program_Counter.vhd](hdl/OpenBlaze8_Program_Counter.vhd) | `OpenBlaze8_Program_Counter` | entity | Program counter and next-PC multiplexer |
| [hdl/OpenBlaze8_Stack.vhd](hdl/OpenBlaze8_Stack.vhd) | `OpenBlaze8_Stack` | entity | CALL/RETURN stack (`stack`, `OVERWRITE = 1`) |
| [hdl/OpenBlaze8_RegFile.vhd](hdl/OpenBlaze8_RegFile.vhd) | `OpenBlaze8_RegFile` | entity | Register file, two `ram_1r1w` written in parallel (ports X and Y) |
| [hdl/OpenBlaze8_Operand.vhd](hdl/OpenBlaze8_Operand.vhd) | `OpenBlaze8_Operand` | entity | Second operand multiplexer (`sY` or constant) |
| [hdl/OpenBlaze8_ALU.vhd](hdl/OpenBlaze8_ALU.vhd) | `OpenBlaze8_ALU` | entity | Arithmetic, logic, shift / rotate, load; next C / Z flags |
| [hdl/OpenBlaze8_Flags.vhd](hdl/OpenBlaze8_Flags.vhd) | `OpenBlaze8_Flags` | entity | C / Z flags and their interrupt copies |
| [hdl/OpenBlaze8_RAM.vhd](hdl/OpenBlaze8_RAM.vhd) | `OpenBlaze8_RAM` | entity | Scratch-pad RAM (`ram_1r1w`, asynchronous read) |
| [hdl/OpenBlaze8_LoadStore.vhd](hdl/OpenBlaze8_LoadStore.vhd) | `OpenBlaze8_LoadStore` | entity | IO port interface (`port_id`, `out_port`, `in_port`, strobes) |
| [hdl/OpenBlaze8_Result.vhd](hdl/OpenBlaze8_Result.vhd) | `OpenBlaze8_Result` | entity | Write-back multiplexer (ALU / RAM / IO) |
| [hdl/OpenBlaze8_Interrupt.vhd](hdl/OpenBlaze8_Interrupt.vhd) | `OpenBlaze8_Interrupt` | entity | Interrupt mask, sampling and acknowledge |

All sub-modules have `clock_i`, `clock_enable_i` and `reset_i` (active high) ports, omitted from the tables below. Vector ports of the core use `(N downto 1)` ranges.

### OpenBlaze8

Processor core with the KCPSM3 port list (plus clock enable). Generics are those of `sbi_OpenBlaze8` (same names and defaults, except `REGFILE_SYNC_READ := true`).

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `clock_i` | in | std_logic | Clock |
| `clock_enable_i` | in | std_logic | Clock enable |
| `reset_i` | in | std_logic | Reset, active high (synchronous for most registers, asynchronous for the cycle phase and the stack) |
| `address_o` | out | std_logic_vector(ADDR_INST_WIDTH downto 1) | Instruction address |
| `instruction_i` | in | std_logic_vector(18 downto 1) | Instruction |
| `port_id_o` | out | std_logic_vector(DATA_WIDTH downto 1) | IO port address |
| `in_port_i` | in | std_logic_vector(DATA_WIDTH downto 1) | IO input data |
| `out_port_o` | out | std_logic_vector(DATA_WIDTH downto 1) | IO output data |
| `read_strobe_o` | out | std_logic | INPUT strobe |
| `write_strobe_o` | out | std_logic | OUTPUT strobe |
| `interrupt_i` | in | std_logic | Interrupt request |
| `interrupt_ack_o` | out | std_logic | Interrupt acknowledge |

### OpenBlaze8_Clock

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `reset_o` | out | std_logic | Internal reset (= `reset_i`) |
| `clock_o` | out | std_logic | Internal clock (= `clock_i`) |
| `cycle_phase_o` | out | std_logic | 0 = first cycle, 1 = second cycle of the instruction (toggles when `clock_enable_i = 1`) |

### OpenBlaze8_Decode

Generic `multi_cycle : natural := 1` (unused).

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `instruction_i` | in | std_logic_vector(18 downto 1) | Instruction |
| `decode_opcode1_o` | out | std_logic_vector(5 downto 1) | Instruction type, `instruction[17:13]` (forced to LOAD on interrupt) |
| `decode_opcode2_o` | out | std_logic_vector(4 downto 1) | Shift / rotate operation, `instruction[3:0]` |
| `decode_operand_mux_o` | out | std_logic | `instruction[12]`: 1 = register `sY`, 0 = constant |
| `decode_branch_cond_o` | out | std_logic_vector(3 downto 1) | `instruction[12:10]`: conditional flag, Z/C select, NZ/NC select |
| `decode_num_regx_o` | out | std_logic_vector(4 downto 1) | `sX`, `instruction[11:8]` |
| `decode_num_regy_o` | out | std_logic_vector(4 downto 1) | `sY`, `instruction[7:4]` (= `sX` on interrupt) |
| `decode_imm_o` | out | std_logic_vector(10 downto 1) | Immediate / address, `instruction[9:0]` |
| `decode_inhib_i` | in | std_logic | Interrupt in progress: inhibit the current instruction |

### OpenBlaze8_Control

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `cycle_phase_i` | in | std_logic | Cycle phase |
| `decode_opcode1_i`, `decode_opcode2_i`, `decode_operand_mux_i`, `decode_branch_cond_i` | in | std_logic_vector / std_logic | Decoded fields |
| `decode_inhib_o` | out | std_logic | Inhibit decode (= `it_en_i`) |
| `pc_write_en_o` | out | std_logic | PC write (first cycle) |
| `pc_next_mux_o` | out | std_logic_vector(3 downto 1) | Next PC source (see `OpenBlaze8_Program_Counter`) |
| `stack_push_val_o` / `stack_pop_ack_o` | out | std_logic | Stack push (CALL taken, interrupt) / pop (RETURN taken, RETURNI) |
| `regx_read_en_o`, `regx_write_en_o`, `regy_read_en_o` | out | std_logic | Register file enables (write in second cycle) |
| `alu_op_arith_cy_o`, `alu_op_arith_o`, `alu_op_logic_o`, `alu_op_rotate_shift_right_o`, `alu_op_rotate_shift_o`, `alu_op_rotate_shift_cst_o`, `alu_op_type_o`, `alu_op_flag_c_o` | out | std_logic / std_logic_vector(2 downto 1) | ALU operation |
| `result_mux_o` | out | std_logic_vector(2 downto 1) | Write-back source |
| `io_access_en_o`, `io_read_en_o`, `io_write_en_o` | out | std_logic | IO controls (strobes registered at the end of the first cycle, asserted during the second cycle) |
| `ram_read_en_o`, `ram_write_en_o` | out | std_logic | Scratch-pad controls |
| `flag_c_i`, `flag_z_i` | in | std_logic | Current flags (branch condition) |
| `flag_write_c_o`, `flag_write_z_o`, `flag_save_o`, `flag_restore_o` | out | std_logic | Flag write, save (interrupt), restore (RETURNI) |
| `interrupt_enable_o`, `interrupt_disable_o` | out | std_logic | ENABLE / DISABLE INTERRUPT, RETURNI ENABLE / DISABLE, disable on interrupt entry |
| `it_en_i` | in | std_logic | Interrupt in progress |

### OpenBlaze8_Program_Counter

Generic `size_addr_inst : natural := 10`.

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `pc_write_en_i` | in | std_logic | PC write enable |
| `pc_next_mux_i` | in | std_logic_vector(3 downto 1) | `001` PC+1, `100` CALL / JUMP target, `011` RETURN (stack + 1), `010` RETURNI (stack), `110` interrupt vector (all ones) |
| `decode_address_i` | in | std_logic_vector(size_addr_inst downto 1) | Branch target |
| `stack_push_data_o` | out | std_logic_vector(size_addr_inst downto 1) | Current PC, pushed on CALL / interrupt |
| `stack_pop_data_i` | in | std_logic_vector(size_addr_inst downto 1) | Stack top |
| `inst_address_o` | out | std_logic_vector(size_addr_inst downto 1) | Instruction address |

### OpenBlaze8_Stack

Generics `size_stack : natural := 32`, `size_addr_inst : natural := 10`.

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `stack_push_val_i` | in | std_logic | Push |
| `stack_push_data_i` | in | std_logic_vector(size_addr_inst downto 1) | Pushed address |
| `stack_pop_ack_i` | in | std_logic | Pop |
| `stack_pop_data_o` | out | std_logic_vector(size_addr_inst downto 1) | Stack top |

### OpenBlaze8_RegFile

Generics `size_data : natural := 8`, `nb_reg : natural := 16`, `SYNC_READ : boolean := false`.

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `regx_read_en_i`, `regx_write_en_i` | in | std_logic | Port X read / write enable |
| `regx_addr_i` | in | std_logic_vector(log2(nb_reg) downto 1) | Port X address (`sX`) |
| `regx_data_i` | in | std_logic_vector(size_data downto 1) | Write data |
| `regx_data_o` | out | std_logic_vector(size_data downto 1) | `sX` |
| `regy_read_en_i` | in | std_logic | Port Y read enable |
| `regy_addr_i` | in | std_logic_vector(log2(nb_reg) downto 1) | Port Y address (`sY`) |
| `regy_data_o` | out | std_logic_vector(size_data downto 1) | `sY` |

### OpenBlaze8_ALU

Generic `size_data : natural := 8`.

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `alu_op_arith_cy_i` | in | std_logic | 1: ADDCY / SUBCY |
| `alu_op_arith_i` | in | std_logic | 0: add, 1: subtract |
| `alu_op_logic_i` | in | std_logic_vector(2 downto 1) | `0x` AND, `10` OR, `11` XOR |
| `alu_op_rotate_shift_right_i` | in | std_logic | 1: right |
| `alu_op_rotate_shift_i` | in | std_logic_vector(2 downto 1) | Inserted bit: `00` carry, `01` MSB, `10` LSB, `11` constant |
| `alu_op_rotate_shift_cst_i` | in | std_logic | Constant inserted bit |
| `alu_op_type_i` | in | std_logic_vector(2 downto 1) | `00` load, `01` rotate / shift, `10` logic, `11` arithmetic |
| `alu_op_flag_c_i` | in | std_logic_vector(2 downto 1) | Carry source: `00` 0, `01` arithmetic carry, `10` shifted-out bit, `11` odd parity (TEST) |
| `alu_op1_i`, `alu_op2_i` | in | std_logic_vector(size_data downto 1) | Operands |
| `flag_c_i`, `flag_z_i` | in | std_logic | Current flags |
| `alu_res_o` | out | std_logic_vector(size_data downto 1) | Result |
| `flag_c_o`, `flag_z_o` | out | std_logic | Next flags (Z = result is zero) |

### OpenBlaze8_Flags

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `flag_c_o`, `flag_z_o` | out | std_logic | Current flags |
| `flag_c_i`, `flag_z_i` | in | std_logic | Next flags |
| `flag_write_c_i`, `flag_write_z_i` | in | std_logic | Write enables |
| `flag_save_i` | in | std_logic | Copy flags (interrupt entry) |
| `flag_restore_i` | in | std_logic | Restore copies (RETURNI) |

### OpenBlaze8_RAM

Generics `size_data : natural := 8`, `size_ram : natural := 64`.

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `ram_read_en_i`, `ram_write_en_i` | in | std_logic | FETCH / STORE |
| `ram_addr_i` | in | std_logic_vector(log2(size_ram) downto 1) | Address (second operand) |
| `ram_read_data_o` | out | std_logic_vector(size_data downto 1) | Read data |
| `ram_write_data_i` | in | std_logic_vector(size_data downto 1) | Write data (`sX`) |

### OpenBlaze8_LoadStore, OpenBlaze8_Operand, OpenBlaze8_Result

Combinational multiplexers, generic `size_data : natural := 8`.

| Entity | Ports | Function |
|--------|-------|----------|
| `OpenBlaze8_LoadStore` | `io_access_en_i`, `io_read_en_i`, `io_write_en_i`, `io_addr_i`, `io_data_write_i`, `io_data_read_o`, `port_id_o`, `in_port_i`, `out_port_o`, `read_strobe_o`, `write_strobe_o` | `port_id = io_addr` (second operand), `out_port = sX`, strobes = read / write enables, `io_data_read = in_port` |
| `OpenBlaze8_Operand` | `decode_operand_mux_i`, `decode_imm_i`, `reg_op1_i`, `reg_op2_i`, `operand_op1_o`, `operand_op2_o` | `op1 = sX`; `op2 = sY` when `decode_operand_mux_i = 1`, else the constant |
| `OpenBlaze8_Result` | `result_mux_i`, `alu_res_i`, `ram_fetch_data_i`, `io_input_data_i`, `res_o` | `1x`: ALU, `01`: RAM, `00`: IO |

### OpenBlaze8_Interrupt

| Name | Direction | Type | Description |
|------|-----------|------|-------------|
| `cycle_phase_i` | in | std_logic | Cycle phase |
| `interrupt_enable_i` | in | std_logic | Unmask (ENABLE INTERRUPT, RETURNI ENABLE) |
| `interrupt_disable_i` | in | std_logic | Mask (DISABLE INTERRUPT, RETURNI DISABLE, interrupt entry) |
| `it_en_o` | out | std_logic | Interrupt in progress (2 cycles) |
| `interrupt_i` | in | std_logic | Interrupt request (registered) |
| `interrupt_ack_o` | out | std_logic | Acknowledge |

## Register Map

This IP has no software-visible registers.

Programmer-visible state: `REGFILE_DEPTH` 8-bit registers `s0`..`sF`, the ZERO and CARRY flags (plus their interrupt copies), the interrupt enable flag (disabled at reset), the program counter, the CALL/RETURN stack (`STACK_DEPTH`) and the scratch-pad RAM (`RAM_DEPTH` bytes). IO ports are addressed on the SBI bus by `sbi_OpenBlaze8`. See [Design Notes](#design-notes).

## Verification

### Testbenches

| File | DUT | Description |
|------|-----|-------------|
| [sim/tb_OpenBlaze8.vhd](sim/tb_OpenBlaze8.vhd) | `OpenBlaze8` | Lock-step comparison with the Xilinx reference `kcpsm3` (`xilinx:processor:kcpsm`) running the same generated ROM (`OpenBlaze8_ROM`). On every falling edge it checks `address`, `interrupt_ack`, `read_strobe`, `write_strobe`, `port_id` and `out_port`. A 256-byte IO memory models the ports (SWITCH `0x00` reads back `not LED 0x20`), writing `n` to port `0xFF` raises an interrupt after `n` cycles, ports `0xC0`..`0xC3` form a 32-bit watch value printed in the log, and port `0xE0` ends the test (`0xFA` = Test OK, `0xED` = Test KO). Timeout 10000 cycles of 10 ns |

Test programs:

- [sim/testbench-asm/](sim/testbench-asm/): 42 assembler tests `test_000_default.psm` .. `test_041_eint_reti.psm` (pBlazIDE syntax): jumps, COMPARE, AND / OR / XOR, ADD / SUB (register and immediate), RL / RR / SL0 / SL1 / SLA / SLX / SR, CALL / RETURN (conditional), FETCH / STORE, stack depth, 16-bit multiplication / division, TEST, INPUT / OUTPUT, ENABLE INTERRUPT / RETURNI.
- [sim/testbench-c/](sim/testbench-c/): 3 C tests (`test_uadd16.c`, `test_udiv16.c`, `test_umul16.c`) using [testbench.h](sim/testbench-c/testbench.h) (`PORT_WR` / `PORT_RD`, `TEST_OK` / `TEST_KO`, `watch32b`), compiled with `--verbose --all-callee-saves`.

### Targets

| Target | Toplevel | Description |
|--------|----------|-------------|
| `default` | `OpenBlaze8` | HDL fileset only (not a simulation) |
| `sim` | `tb_OpenBlaze8` | Base of the simulation targets (GHDL options `-Wall -fsynopsys -frelaxed`, `--ieee-asserts=disable`); no test program |
| `sim_asm_test_<NNN>_<name>` (42 targets) | `tb_OpenBlaze8` | One target per `sim/testbench-asm/test_<NNN>_<name>.psm` (generator `gen_asm_test_<NNN>_<name>`, type `pblazeide`): `000_default`, `001_test_ok`, `002_jump`, `003_jump`, `004_comp`, `005_comp`, `006_and`, `007_or`, `008_xor`, `009_andi`, `010_ori`, `011_xori`, `012_add`, `013_addi`, `014_sub`, `015_subi`, `016_comp`, `017_compi`, `018_rl`, `019_rr`, `020_sl0`, `021_sl1`, `022_sla`, `023_slx`, `024_sr`, `025_call`, `026_call_ret`, `027_call_ret`, `028_call_ret_cond`, `029_fetch_store`, `030_fetch_store`, `031_fetch_store`, `032_stack_depth`, `033_mul`, `034_div`, `035_test`, `036_test`, `037_in_out`, `038_in_out`, `039_eint_reti`, `040_eint_reti`, `041_eint_reti` |
| `sim_c_test_<name>` (3 targets) | `tb_OpenBlaze8` | One target per `sim/testbench-c/test_<name>.c` (generator type `c`): `uadd16`, `udiv16`, `umul16` |

### How to Run

The default tool is GHDL (`mk/defs.mk`: `TOOL ?= ghdl`, `TARGET ?= sim_c_test_umul16`).

```bash
make help                          # variables, rules and target list (mk/targets.txt)
make sim_asm_test_012_add          # run one target (log in log/)
make nonreg_sim                    # run every sim_* target
make TARGETS_FILTER=^sim_c nonreg_sim   # run a filtered subset
make clean                         # remove build/ and log/
```

Equivalent FuseSoC command:

```bash
fusesoc --cores-root . run --build-root build --target sim_asm_test_012_add asylum:processor:OpenBlaze8:1.3.2
```

Prerequisites: the test programs are converted into `OpenBlaze8_ROM` by the `pbcc_gen` generator (`asylum:utils:generators`), which needs `PICOASM_HOME` (picoasm assembler, `bin/picoasm` and the `ROM_form.vhd` templates) and, for the C tests, `PBCC_HOME` (SDCC with the PicoBlaze back-end, `bin/sdcc`). Outside CI, GHDL writes a waveform `dut.fst`.

## Synthesis

No dedicated synthesis target. The `files_hdl` sources are plain RTL (no vendor primitive, no simulation-only code); the register file and scratch pad are `ram_1r1w` instances (distributed RAM when `REGFILE_SYNC_READ = false` / asynchronous read) and the stack an `asylum:component:stack` instance. The core is synthesized as part of the PicoSoC emulation and lint targets (`asylum:soc:PicoSoC`, NanoXplore / Digilent boards).

## Design Notes

### Instruction Set

Instructions are 18 bits. `opcode1 = instruction[17:13]`, `instruction[12]` selects the second operand (`1` = register `sY = instruction[7:4]`, `0` = constant `kk = instruction[7:0]`), `sX = instruction[11:8]`, `aaa = instruction[9:0]`. Encodings are those of KCPSM3.

| opcode1 | Mnemonic | Operation | Flags |
|---------|----------|-----------|-------|
| `00000` | `LOAD sX, kk / sY` | sX = op2 | - |
| `00010` | `INPUT sX, pp / (sY)` | sX = IN_PORT, PORT_ID = op2, READ_STROBE | - |
| `00011` | `FETCH sX, ss / (sY)` | sX = RAM[op2] | - |
| `00101` | `AND sX, kk / sY` | sX = sX and op2 | C = 0, Z |
| `00110` | `OR sX, kk / sY` | sX = sX or op2 | C = 0, Z |
| `00111` | `XOR sX, kk / sY` | sX = sX xor op2 | C = 0, Z |
| `01001` | `TEST sX, kk / sY` | sX and op2, no write-back | C = odd parity, Z |
| `01010` | `COMPARE sX, kk / sY` | sX - op2, no write-back | C = borrow, Z |
| `01100` | `ADD sX, kk / sY` | sX = sX + op2 | C, Z |
| `01101` | `ADDCY sX, kk / sY` | sX = sX + op2 + C | C, Z |
| `01110` | `SUB sX, kk / sY` | sX = sX - op2 | C = borrow, Z |
| `01111` | `SUBCY sX, kk / sY` | sX = sX - op2 - C | C = borrow, Z |
| `10000` | shift / rotate `sX` | see below (`instruction[3:0]`) | C = bit out, Z |
| `10101` | `RETURN [Z/NZ/C/NC]` | PC = pop + 1 | - |
| `10110` | `OUTPUT sX, pp / (sY)` | OUT_PORT = sX, PORT_ID = op2, WRITE_STROBE | - |
| `10111` | `STORE sX, ss / (sY)` | RAM[op2] = sX | - |
| `11000` | `CALL [Z/NZ/C/NC,] aaa` | push PC, PC = aaa | - |
| `11010` | `JUMP [Z/NZ/C/NC,] aaa` | PC = aaa | - |
| `11100` | `RETURNI ENABLE / DISABLE` | PC = pop, flags restored, interrupt enable = `instruction[0]` | restored |
| `11110` | `ENABLE / DISABLE INTERRUPT` | interrupt enable = `instruction[0]` | - |

Conditions (`instruction[12:10]`): `0xx` always, `100` Z, `101` NZ, `110` C, `111` NC.

| `instruction[3:0]` | Mnemonic | Inserted bit | `instruction[3:0]` | Mnemonic | Inserted bit |
|--------------------|----------|--------------|--------------------|----------|--------------|
| `0110` | `SL0` | 0 | `1110` | `SR0` | 0 |
| `0111` | `SL1` | 1 | `1111` | `SR1` | 1 |
| `0100` | `SLX` | LSB | `1010` | `SRX` | MSB |
| `0000` | `SLA` | C | `1000` | `SRA` | C |
| `0010` | `RL` | MSB | `1100` | `RR` | LSB |

### Micro-architecture

- Each instruction takes two enabled clock cycles (`cycle_phase` 0 then 1). The PC is updated in the first cycle; register, flag, RAM writes and IO strobes happen in the second cycle.
- The register file is two `ram_1r1w` (port X, port Y) sharing the write port, which gives two read ports and one write port.
- Interrupt: when enabled, `interrupt_i` is registered and taken in the second cycle; during the next two cycles (`it_en`) the current instruction is replaced by `LOAD sX, sX`, the PC is pushed, the flags are saved, interrupts are disabled and the PC jumps to the last address (`0x3FF` with `ADDR_INST_WIDTH = 10`); `interrupt_ack` is asserted for one cycle. RETURNI pops the address without increment, so the inhibited instruction is re-executed.
- The stack is an `asylum:component:stack` with `OVERWRITE = 1`: a push on a full stack overwrites the oldest entry.
- `sbi_OpenBlaze8` freezes the whole core (clock enable low) while an IO access is waiting for `sbi_tgt_i.ready`; `ics_o` follows the same enable so that a synchronous instruction ROM is frozen too.
- Width limits as coded: the left shift uses bits `7 downto 1` (8-bit data), the immediate / address field is 10 bits (`ADDR_INST_WIDTH <= 10`), register fields are 4 bits (`REGFILE_DEPTH <= 16`) and the RAM address is taken from the 8-bit second operand.

## Directory Structure

```
asylum-processor-OpenBlaze8/
├── OpenBlaze8.core             # FuseSoC core (asylum:processor:OpenBlaze8)
├── Makefile                    # Common Asylum Makefile (FuseSoC wrapper)
├── mk/
│   ├── defs.mk                 # FILE_CORE, default TARGET and TOOL
│   └── targets.txt             # Target list (generated from the .core)
├── doc/
│   └── OpenBlaze8.drawio       # Block diagram
├── hdl/
│   ├── OpenBlaze8_pkg.vhd
│   ├── OpenBlaze8.vhd
│   ├── sbi_OpenBlaze8.vhd
│   └── OpenBlaze8_<Module>.vhd # ALU, Clock, Control, Decode, Flags, Interrupt, LoadStore,
│                               # Operand, Program_Counter, RAM, RegFile, Result, Stack
└── sim/
    ├── tb_OpenBlaze8.vhd       # Lock-step testbench (DUT vs kcpsm3)
    ├── testbench-asm/          # 42 assembler tests test_000 .. test_041 (*.psm)
    └── testbench-c/            # testbench.h + test_uadd16.c, test_udiv16.c, test_umul16.c
```

## Dependencies

| Core | Used by (fileset) | Purpose |
|------|-------------------|---------|
| `asylum:utils:pkg` | `files_hdl` | Common packages (`sbi_pkg`, `math_pkg`) |
| `asylum:component:ram` (`>=1.0.0`) | `files_hdl` | `ram_1r1w` for the register file and the scratch-pad RAM |
| `asylum:component:stack` (`>=1.0.0`) | `files_hdl` | `stack` for the CALL/RETURN stack |
| `xilinx:processor:kcpsm` (`>=1.30`) | `files_sim` | Reference model `kcpsm3` of the testbench |
| `xilinx:primitive:unisim` (`>=11.1`) | `files_sim` | Xilinx primitives used by `kcpsm3` |
| `asylum:utils:generators` | `pbcc_dep` | `pbcc_gen` generator (assembler / C to `OpenBlaze8_ROM`) |
