# OpenBlaze8 - 8-bit Microprocessor Core

## Table of Contents

1. [Introduction](#introduction)
2. [Module Documentation](#module-documentation)
   - [Top-Level Module (OpenBlaze8)](#top-level-module-openblaze8)
   - [ALU Module](#alu-module)
   - [Clock Module](#clock-module)
   - [Control Module](#control-module)
   - [Decode Module](#decode-module)
   - [Flags Module](#flags-module)
   - [Interrupt Module](#interrupt-module)
   - [Load/Store Module](#loadstore-module)
   - [Operand Module](#operand-module)
   - [Program Counter Module](#program-counter-module)
   - [RegFile Module](#regfile-module)
   - [Result Module](#result-module)
   - [Stack Module](#stack-module)
   - [RAM Module](#ram-module)
3. [Verification](#verification)
4. [Build and Simulation](#build-and-simulation)

---

## Introduction

OpenBlaze8 is a configurable 8-bit microprocessor core design in VHDL targeting embedded systems and FPGA implementations. The core implements a PicoBlaze-like architecture with support for:

- **8-bit data operations** with configurable data width
- **Stack-based architecture** for function calls and returns
- **Interrupt handling** with interrupt acknowledgment
- **Configurable register file** (16 registers by default)
- **Internal RAM** for data storage
- **Multi-cycle operation** support for resource-constrained designs

### Key Features

- **Modular Design**: Clear separation of concerns with dedicated modules for ALU, control, decoding, and memory management
- **Configurable Parameters**: Stack depth, RAM depth, register file size, and instruction address width are all configurable
- **Synchronous/Asynchronous Register File**: Support for both synchronous and asynchronous reads
- **Flag Management**: Carry and Zero flags with interrupt context save/restore
- **I/O Subsystem**: Read and write strobes for external I/O communication

### Design Philosophy

The architecture follows a classic 5-stage pipeline approach with clear module boundaries:
1. **Clock Module** - Clock distribution and timing control
2. **Program Counter** - Instruction address generation
3. **Decode** - Instruction decoding
4. **Control** - Sequencing and control signal generation
5. **Execution** - ALU, memory access, and result management

---

## Module Documentation

### Top-Level Module (OpenBlaze8)

The OpenBlaze8 entity is the top-level module that instantiates all sub-modules and manages their interconnections.

**File**: `hdl/OpenBlaze8.vhd`

#### Generics

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `STACK_DEPTH` | natural | 32 | Depth of the call stack for function calls and returns |
| `RAM_DEPTH` | natural | 64 | Size of the internal RAM in bytes |
| `DATA_WIDTH` | natural | 8 | Width of data operands in bits |
| `ADDR_INST_WIDTH` | natural | 10 | Width of instruction address bus in bits |
| `REGFILE_DEPTH` | natural | 16 | Number of general-purpose registers |
| `REGFILE_SYNC_READ` | boolean | true | Enable synchronous (true) or asynchronous (false) register file reads |
| `MULTI_CYCLE` | natural | 1 | Multi-cycle operation support (0-N cycles) |

#### Ports

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | System clock |
| `clock_enable_i` | in | 1 | Clock enable signal for gated clocking |
| `reset_i` | in | 1 | Synchronous active-high reset |
| `address_o` | out | ADDR_INST_WIDTH | Instruction address for ROM |
| `instruction_i` | in | 18 | Instruction word from ROM |
| `port_id_o` | out | DATA_WIDTH | I/O port identifier for reads/writes |
| `in_port_i` | in | DATA_WIDTH | Input data from external ports |
| `out_port_o` | out | DATA_WIDTH | Output data to external ports |
| `read_strobe_o` | out | 1 | Read strobe for I/O operations |
| `write_strobe_o` | out | 1 | Write strobe for I/O operations |
| `interrupt_i` | in | 1 | External interrupt request signal |
| `interrupt_ack_o` | out | 1 | Interrupt acknowledgment signal |

#### Functionality

The top-level module:
- Coordinates all submodules through internal signal routing
- Manages instruction fetching and execution
- Handles external I/O communication
- Processes interrupt requests and saves/restores processor state
- Implements the main instruction pipeline

---

### ALU Module

The Arithmetic and Logic Unit performs all arithmetic, logical, and shift operations.

**File**: `hdl/OpenBlaze8_ALU.vhd`

#### Generics

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `size_data` | natural | 8 | Width of data operands |

#### Ports

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | System clock |
| `clock_enable_i` | in | 1 | Clock enable signal |
| `reset_i` | in | 1 | Synchronous reset |
| `alu_op_arith_cy_i` | in | 1 | High for ADDCY/SUBCY instructions |
| `alu_op_arith_i` | in | 1 | Arithmetic operation type (0=Add, 1=Sub) |
| `alu_op_logic_i` | in | 2 | Logic operation select (AND, OR, XOR) |
| `alu_op_rotate_shift_right_i` | in | 1 | Direction of rotate/shift (1=right) |
| `alu_op_rotate_shift_i` | in | 2 | Rotate/shift source of inserted bits |
| `alu_op_rotate_shift_cst_i` | in | 1 | Rotate/shift insert constant value |
| `alu_op_type_i` | in | 2 | Operation type (00=Load, 01=Rotate/Shift, 10=Logic, 11=Arith) |
| `alu_op_flag_c_i` | in | 2 | Carry flag operation mode |
| `alu_op1_i` | in | size_data | First operand |
| `alu_op2_i` | in | size_data | Second operand |
| `flag_c_i` | in | 1 | Carry flag input |
| `flag_z_i` | in | 1 | Zero flag input |
| `alu_res_o` | out | size_data | ALU result |
| `flag_c_o` | out | 1 | Carry flag output |
| `flag_z_o` | out | 1 | Zero flag output |

#### Functionality

Implements:
- **Arithmetic Operations**: ADD, ADDC, SUB, SUBC with carry propagation
- **Logical Operations**: AND, OR, XOR
- **Rotate/Shift Operations**: Rotate Left (RL), Rotate Right (RR), Shift operations with multiple insertion modes
- **Flag Updates**: Updates carry and zero flags based on result

---

### Clock Module

Manages clock distribution and cycle phase tracking for multi-cycle operations.

**File**: `hdl/OpenBlaze8_Clock.vhd`

#### Generics

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `multi_cycle` | natural | 1 | Multi-cycle mode configuration |

#### Ports

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | Input system clock |
| `clock_enable_i` | in | 1 | Clock enable input |
| `reset_i` | in | 1 | Synchronous reset |
| `reset_o` | out | 1 | Internal reset output |
| `clock_o` | out | 1 | Output clock signal |
| `cycle_phase_o` | out | 1 | Cycle phase indicator (0=first, 1=second) |

#### Functionality

- Distributes clock to all modules
- Generates cycle phase signal for multi-cycle operations
- Provides synchronous reset distribution
- Supports clock division for reduced frequency operation

---

### Control Module

Generates control signals for ALU, register file, and program counter based on decoded instructions.

**File**: `hdl/OpenBlaze8_Control.vhd`

#### Generics

None

#### Ports (Selected Important Ports)

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | System clock |
| `clock_enable_i` | in | 1 | Clock enable |
| `reset_i` | in | 1 | Synchronous reset |
| `cycle_phase_i` | in | 1 | Cycle phase from Clock module |
| `decode_opcode1_i` | in | 5 | Instruction type opcode |
| `decode_opcode2_i` | in | 4 | Instruction operation opcode |
| `decode_operand_mux_i` | in | 1 | Select immediate or register operand |
| `decode_branch_cond_i` | in | 3 | Branch condition flags to evaluate |
| `decode_inhib_o` | out | 1 | Inhibit instruction during interrupt |
| `pc_write_en_o` | out | 1 | Program counter write enable |
| `pc_next_mux_o` | out | 3 | Program counter source select |
| `stack_push_val_o` | out | 1 | Stack push enable |
| `stack_pop_ack_o` | out | 1 | Stack pop acknowledge |
| `regx_read_en_o` | out | 1 | Register X read enable |
| `regx_write_en_o` | out | 1 | Register X write enable |
| `regy_read_en_o` | out | 1 | Register Y read enable |
| `alu_op_arith_cy_o` | out | 1 | Arithmetic with carry signal |
| `alu_op_arith_o` | out | 1 | Arithmetic operation select |
| `alu_op_logic_o` | out | 2 | Logic operation select |
| `alu_op_type_o` | out | 2 | ALU operation type |
| `flag_write_c_o` | out | 1 | Carry flag write enable |
| `flag_write_z_o` | out | 1 | Zero flag write enable |

#### Functionality

Decodes instruction types and generates appropriate control signals:
- ALU control signals for arithmetic, logic, and shift operations
- Register file access control
- Program counter selection for branches, calls, and returns
- Stack control for function calls
- Flag update controls
- Interrupt inhibition during critical operations

---

### Decode Module

Decodes the 18-bit instruction word into control signals.

**File**: `hdl/OpenBlaze8_Decode.vhd`

#### Generics

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `multi_cycle` | natural | 1 | Multi-cycle configuration |

#### Ports

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | System clock |
| `clock_enable_i` | in | 1 | Clock enable |
| `reset_i` | in | 1 | Synchronous reset |
| `instruction_i` | in | 18 | Instruction word from ROM |
| `decode_opcode1_o` | out | 5 | Primary opcode |
| `decode_opcode2_o` | out | 4 | Secondary opcode |
| `decode_operand_mux_o` | out | 1 | Operand select (0=imm, 1=reg) |
| `decode_branch_cond_o` | out | 3 | Branch condition select |
| `decode_num_regx_o` | out | 4 | Register X address |
| `decode_num_regy_o` | out | 4 | Register Y address |
| `decode_imm_o` | out | 10 | 10-bit immediate value |
| `decode_inhib_i` | in | 1 | Inhibit signal from control |

#### Instruction Format

The 18-bit instruction is formatted as:
```
[17:14] - opcode1 (Primary instruction type)
[13]    - operand_mux or branch_cond[2]
[12:9]  - Register X address
[8:5]   - Register Y address
[4:1]   - opcode2 (Secondary instruction type)
[10:1]  - 10-bit immediate value
```

#### Functionality

- Extracts opcode fields from instruction word
- Identifies register operands
- Extracts immediate values for immediate mode operations
- Detects branch conditions
- Modifies decoded instruction during interrupt (nop behavior)

---

### Flags Module

Manages processor flags (Carry and Zero) with context saving for interrupt handling.

**File**: `hdl/OpenBlaze8_Flags.vhd`

#### Generics

None

#### Ports

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | System clock |
| `clock_enable_i` | in | 1 | Clock enable |
| `reset_i` | in | 1 | Synchronous reset |
| `flag_c_o` | out | 1 | Carry flag output |
| `flag_z_o` | out | 1 | Zero flag output |
| `flag_c_i` | in | 1 | Carry flag input (from ALU) |
| `flag_z_i` | in | 1 | Zero flag input (from ALU) |
| `flag_write_c_i` | in | 1 | Write carry flag enable |
| `flag_write_z_i` | in | 1 | Write zero flag enable |
| `flag_save_i` | in | 1 | Save flags on interrupt |
| `flag_restore_i` | in | 1 | Restore flags on RETI |

#### Functionality

- Maintains two flags: Carry (C) and Zero (Z)
- Updates flags from ALU results when enabled
- Saves flag state on interrupt entry
- Restores flag state on interrupt return (RETI)
- Provides flags to control unit for conditional branching

---

### Interrupt Module

Handles external interrupt requests and masking.

**File**: `hdl/OpenBlaze8_Interrupt.vhd`

#### Generics

None

#### Ports

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | System clock |
| `clock_enable_i` | in | 1 | Clock enable |
| `reset_i` | in | 1 | Synchronous reset |
| `cycle_phase_i` | in | 1 | Cycle phase input |
| `interrupt_enable_i` | in | 1 | Enable interrupt (EINT) |
| `interrupt_disable_i` | in | 1 | Disable interrupt (DINT) |
| `it_en_o` | out | 1 | Interrupt pending output |
| `interrupt_i` | in | 1 | External interrupt input |
| `interrupt_ack_o` | out | 1 | Interrupt acknowledgment output |

#### Functionality

- Captures external interrupt signals
- Maintains interrupt enable mask (EINT/DINT instructions)
- Generates interrupt pending signal when interrupt is detected and enabled
- Provides interrupt acknowledgment signal
- Synchronizes interrupt with cycle phase

---

### Load/Store Module

Handles I/O read and write operations.

**File**: `hdl/OpenBlaze8_LoadStore.vhd`

#### Generics

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `size_data` | natural | 8 | Width of data operands |

#### Ports

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | System clock |
| `clock_enable_i` | in | 1 | Clock enable |
| `reset_i` | in | 1 | Synchronous reset |
| `io_access_en_i` | in | 1 | I/O access enable |
| `io_read_en_i` | in | 1 | I/O read strobe |
| `io_write_en_i` | in | 1 | I/O write strobe |
| `io_addr_i` | in | size_data | I/O port address |
| `io_data_read_o` | out | size_data | I/O data read output |
| `io_data_write_i` | in | size_data | I/O data to write |
| `port_id_o` | out | size_data | Port ID to external interface |
| `in_port_i` | in | size_data | Input port data from external interface |
| `out_port_o` | out | size_data | Output port data to external interface |
| `read_strobe_o` | out | 1 | Read strobe to external interface |
| `write_strobe_o` | out | 1 | Write strobe to external interface |

#### Functionality

- Passes through I/O port IDs and data
- Generates read and write strobes for external peripherals
- Routes input data from external ports to result path
- Routes output data to external ports

---

### Operand Module

Selects between immediate and register operands for ALU operations.

**File**: `hdl/OpenBlaze8_Operand.vhd`

#### Generics

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `size_data` | natural | 8 | Width of operands |

#### Ports

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | System clock |
| `clock_enable_i` | in | 1 | Clock enable |
| `reset_i` | in | 1 | Synchronous reset |
| `decode_operand_mux_i` | in | 1 | Operand select (0=reg, 1=imm) |
| `decode_imm_i` | in | size_data | Immediate value |
| `reg_op1_i` | in | size_data | Register operand 1 |
| `reg_op2_i` | in | size_data | Register operand 2 |
| `operand_op1_o` | out | size_data | ALU operand 1 |
| `operand_op2_o` | out | size_data | ALU operand 2 |

#### Functionality

- Always passes register operand 1 to ALU
- Multiplexes register operand 2 or immediate value to ALU operand 2
- Implements immediate mode encoding with proper bit widths

---

### Program Counter Module

Manages instruction address generation and control flow.

**File**: `hdl/OpenBlaze8_Program_Counter.vhd`

#### Generics

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `size_addr_inst` | natural | 10 | Width of instruction address |

#### Ports

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | System clock |
| `clock_enable_i` | in | 1 | Clock enable |
| `reset_i` | in | 1 | Synchronous reset |
| `pc_write_en_i` | in | 1 | Program counter write enable |
| `pc_next_mux_i` | in | 3 | PC source select |
| `decode_address_i` | in | size_addr_inst | Jump/call target address |
| `stack_push_data_o` | out | size_addr_inst | PC value for stack push |
| `stack_pop_data_i` | in | size_addr_inst | Return address from stack |
| `inst_address_o` | out | size_addr_inst | Current instruction address |

#### PC Source Selection (pc_next_mux_i)

| Value | Function |
|-------|----------|
| 001 | PC + 1 (normal sequence) |
| 010 | Stack return (RETI) |
| 011 | Stack return (RET) |
| 100 | Jump/Call target (from decode_address_i) |
| 110 | Interrupt service routine entry (all 1s) |

#### Functionality

- Maintains program counter register
- Provides instruction address to ROM
- Implements branch/jump/call/return address selection
- Supports interrupt vector at maximum address
- Increments PC for sequential execution

---

### RegFile Module

Register file with dual-read, single-write architecture.

**File**: `hdl/OpenBlaze8_RegFile.vhd`

#### Generics

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `size_data` | natural | 8 | Width of register data |
| `nb_reg` | natural | 16 | Number of registers |
| `SYNC_READ` | boolean | false | Synchronous (true) vs asynchronous (false) reads |

#### Ports

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | System clock |
| `clock_enable_i` | in | 1 | Clock enable |
| `reset_i` | in | 1 | Synchronous reset |
| `regx_read_en_i` | in | 1 | Register X read enable |
| `regx_write_en_i` | in | 1 | Register X write enable |
| `regx_addr_i` | in | log2(nb_reg) | Register X address |
| `regx_data_i` | in | size_data | Register X write data |
| `regx_data_o` | out | size_data | Register X read data |
| `regy_read_en_i` | in | 1 | Register Y read enable |
| `regy_addr_i` | in | log2(nb_reg) | Register Y address |
| `regy_data_o` | out | size_data | Register Y read data |

#### Functionality

- Implements dual-read single-write register file
- Two independent read ports (X and Y)
- Single write port targeting register X
- Configurable synchronous or asynchronous reads
- Built using RAM primitives from asylum library

---

### Result Module

Multiplexes result sources (ALU, RAM, or I/O) for register writeback.

**File**: `hdl/OpenBlaze8_Result.vhd`

#### Generics

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `size_data` | natural | 8 | Width of result data |

#### Ports

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | System clock |
| `clock_enable_i` | in | 1 | Clock enable |
| `reset_i` | in | 1 | Synchronous reset |
| `result_mux_i` | in | 2 | Result source select |
| `alu_res_i` | in | size_data | ALU result |
| `ram_fetch_data_i` | in | size_data | RAM read data |
| `io_input_data_i` | in | size_data | I/O input data |
| `res_o` | out | size_data | Final result output |

#### Result Multiplexing

| result_mux_i[2] | result_mux_i[1] | Source |
|-----------------|-----------------|--------|
| 0 | 0 | I/O Input Data |
| 0 | 1 | RAM Data |
| 1 | X | ALU Result |

#### Functionality

- Selects result from ALU, RAM, or I/O
- Drives the selected result to register file writeback
- Enables different instruction types (arithmetic, memory, I/O) in same pipeline

---

### Stack Module

Call stack for function returns and interrupt handling.

**File**: `hdl/OpenBlaze8_Stack.vhd`

#### Generics

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `size_stack` | natural | 32 | Stack depth (number of entries) |
| `size_addr_inst` | natural | 10 | Width of instruction addresses |

#### Ports

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | System clock |
| `clock_enable_i` | in | 1 | Clock enable |
| `reset_i` | in | 1 | Synchronous reset |
| `stack_push_val_i` | in | 1 | Push request (valid) |
| `stack_push_data_i` | in | size_addr_inst | Data to push |
| `stack_pop_ack_i` | in | 1 | Pop acknowledge request |
| `stack_pop_data_o` | out | size_addr_inst | Popped data |

#### Functionality

- Manages call stack for CALL/RET instructions
- Saves return addresses on function calls
- Restores return addresses on function returns
- Uses LIFO (Last-In-First-Out) discipline
- Based on asylum library stack primitive
- Configurable depth for different application requirements
- Overflow behavior: overwrites oldest entries (OVERWRITE=1)

---

### RAM Module

Internal data RAM for variable storage.

**File**: `hdl/OpenBlaze8_RAM.vhd`

#### Generics

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `size_data` | natural | 8 | Width of data words |
| `size_ram` | natural | 64 | Size of RAM in bytes |

#### Ports

| Port Name | Direction | Width | Description |
|-----------|-----------|-------|-------------|
| `clock_i` | in | 1 | System clock |
| `clock_enable_i` | in | 1 | Clock enable |
| `reset_i` | in | 1 | Synchronous reset |
| `ram_read_en_i` | in | 1 | Read enable |
| `ram_write_en_i` | in | 1 | Write enable |
| `ram_addr_i` | in | log2(size_ram) | Read/write address |
| `ram_read_data_o` | out | size_data | Read data output |
| `ram_write_data_i` | in | size_data | Write data input |

#### Functionality

- Single-port RAM with simultaneous read-write capability
- Asynchronous read operations
- Synchronous write operations
- Supports FETCH and STORE instructions
- Built using asylum library RAM primitives

---

## Verification

The OpenBlaze8 design includes comprehensive verification components for validating core functionality.

### Testbench

**File**: `sim/tb_OpenBlaze8.vhd`

The testbench (`tb_OpenBlaze8.vhd`) provides a complete simulation environment for the OpenBlaze8 processor:

#### Key Features

- **Configuration Constants**:
  - Stack Depth: 32 entries
  - RAM Depth: 64 bytes
  - Data Width: 8 bits
  - Instruction Address Width: 10 bits
  - Register File Depth: 16 registers
  - Simulation Period: 10 ns

- **Port Simulation**:
  - `TB_LED_PORT_ID` (0x20): LED output control
  - `TB_SWITCH_PORT_ID` (0x00): Switch input reading
  - `TB_WATCH_PORT_ID[0:3]` (0xC0-0xC3): Debug watch registers
  - `TB_IT_PORT_ID` (0xFF): Interrupt test port
  - `TB_EXPECTED_PORT_ID` (0xE0): Expected result verification

- **Test Signals**:
  - Memory simulation for ROM access
  - Interrupt generation and acknowledgment tracking
  - Test completion and pass/fail status

#### Test Execution

The testbench runs for 10,000 clock cycles with 10 ns period (100 MHz equivalent).

### Assembly Tests

The `sim/testbench-asm/` directory contains 41 assembly test programs written in PicoBlaze assembly (`.psm` files). These tests verify:

#### Test Categories

| Test File | Functionality |
|-----------|---------------|
| `test_000_default.psm` | Processor initialization and default state |
| `test_001_test_ok.psm` | Basic test framework validation |
| `test_002_jump.psm` | Unconditional jump instruction |
| `test_003_jump.psm` | Jump with different addresses |
| `test_004_comp.psm` | Compare instruction |
| `test_005_comp.psm` | Compare with immediate |
| `test_006_and.psm` | Bitwise AND operation |
| `test_007_or.psm` | Bitwise OR operation |
| `test_008_xor.psm` | Bitwise XOR operation |
| `test_009_andi.psm` | AND with immediate |
| `test_010_ori.psm` | OR with immediate |
| `test_011_xori.psm` | XOR with immediate |
| `test_012_add.psm` | Addition without carry |
| `test_013_addi.psm` | Add immediate |
| `test_014_sub.psm` | Subtraction without borrow |
| `test_015_subi.psm` | Subtract immediate |
| `test_016_comp.psm` | Compare variations |
| `test_017_compi.psm` | Compare immediate |
| `test_018_rl.psm` | Rotate left |
| `test_019_rr.psm` | Rotate right |
| `test_020_sl0.psm` | Shift left insert 0 |
| `test_021_sl1.psm` | Shift left insert 1 |
| `test_022_sla.psm` | Shift left arithmetic |
| `test_023_slx.psm` | Shift left exchange |
| `test_024_sr.psm` | Shift right |
| `test_025_call.psm` | Function call instruction |
| `test_026_call_ret.psm` | Call and return pair |
| `test_027_call_ret.psm` | Nested call and return |
| `test_028_call_ret_cond.psm` | Conditional call and return |
| `test_029_fetch_store.psm` | Fetch from RAM |
| `test_030_fetch_store.psm` | Store to RAM |
| `test_031_fetch_store.psm` | RAM read/write combinations |
| `test_032_stack_depth.psm` | Stack overflow/underflow |
| `test_033_mul.psm` | Unsigned multiplication (16-bit) |
| `test_034_div.psm` | Unsigned division (16-bit) |
| `test_035_test.psm` | Test instruction (AND without result storage) |
| `test_036_test.psm` | Test variations |
| `test_037_in_out.psm` | Input from I/O port |
| `test_038_in_out.psm` | Output to I/O port |
| `test_039_eint_reti.psm` | Enable interrupt and return |
| `test_040_eint_reti.psm` | Interrupt service routine |
| `test_041_eint_reti.psm` | Complex interrupt scenarios |

#### Test Framework

Each assembly test:
1. Performs specific functionality tests
2. Uses I/O ports to communicate results
3. Writes test status to port 0xE0 (expected result port)
4. Signals pass/fail through output ports

### C Language Tests

The `sim/testbench-c/` directory contains C language test utilities:

**Files**:
- `test_uadd16.c` - 16-bit unsigned addition test
- `test_udiv16.c` - 16-bit unsigned division test
- `test_umul16.c` - 16-bit unsigned multiplication test
- `testbench.h` - Common testbench definitions and utilities

These tests may be used for reference implementations or extended verification beyond VHDL simulation.

### Test Execution Flow

1. **Setup Phase**: Testbench initializes processor state, memory, and I/O
2. **Instruction Fetch**: Processor requests instructions from simulated ROM
3. **Execution**: Testbench monitors execution and tracks results
4. **Verification**: Tests write results to designated I/O ports
5. **Status Check**: Testbench validates test completion and pass/fail signals

---

## Build and Simulation

### Project Structure

The project uses **FuseSoC** for design and simulation management.

**Files**:
- `OpenBlaze8.core` - FuseSoC core file with design configuration
- `Makefile` - Build automation for simulation and synthesis
- `mk/defs.mk` - Build variable definitions
- `mk/targets.txt` - Available build targets

### FuseSoC Configuration

The `OpenBlaze8.core` file defines:
- Project metadata (name, version, author)
- Design files and modules
- Testbench configurations
- Generator configurations for assembly test compilation
- Simulation targets

**Current Version**: 1.3.0 (includes SBI wrapper support)

### Build Targets

Common targets include:
- **Simulation targets** (sim_*): Run VHDL simulations
- **Emulation targets** (emu_*): FPGA emulation
- **Lint targets** (lint_*): Static code analysis


## Additional Notes

### Design Dependencies

The OpenBlaze8 design depends on the **asylum library** for:
- `math_pkg` - Mathematical utilities and functions
- `ram_pkg` - RAM primitive components
- `stack_pkg` - Stack primitive components
- `sbi_pkg` - System Bus Interface definitions

### Customization

All major parameters are configurable via VHDL generics:
- Data width (8-bit default, configurable)
- Memory sizes (stack, RAM, register file)
- Instruction address width
- Register file read mode (sync/async)
- Multi-cycle operation support

### Instruction Set

The processor implements a PicoBlaze-compatible instruction set including:
- Arithmetic: ADD, ADDC, SUB, SUBC
- Logic: AND, OR, XOR
- Shift/Rotate: RL, RR, SL0, SL1, SRA, SRX
- Memory: FETCH, STORE
- I/O: INPUT, OUTPUT
- Control: CALL, RETURN, JUMP (conditional/unconditional)
- Special: COMPARE, TEST, EINT, DINT, RETI

