library IEEE;
use     IEEE.STD_LOGIC_1164.ALL;
use     IEEE.NUMERIC_STD.ALL;
library work;
use     work.math_pkg.all;

package OpenBlaze8_pkg is
-- [COMPONENT_INSERT][BEGIN]
component OpenBlaze8 is
  -- =====[ Parameters ]==========================
  generic (
     STACK_DEPTH     : natural := 32;
     RAM_DEPTH       : natural := 64;
     DATA_WIDTH      : natural := 8;
     ADDR_INST_WIDTH : natural := 10;
     REGFILE_DEPTH   : natural := 16;
     MULTI_CYCLE     : natural := 1);
  -- =====[ Interfaces ]==========================
  port (
    clock_i           : in  std_logic;
    clock_enable_i    : in  std_logic;
    reset_i           : in  std_logic;
    address_o         : out std_logic_vector(ADDR_INST_WIDTH downto 1);
    instruction_i     : in  std_logic_vector(18 downto 1);
    port_id_o         : out std_logic_vector(DATA_WIDTH downto 1);
    in_port_i         : in  std_logic_vector(DATA_WIDTH downto 1);
    out_port_o        : out std_logic_vector(DATA_WIDTH downto 1);
    read_strobe_o     : out std_logic;
    write_strobe_o    : out std_logic;
    interrupt_i       : in  std_logic;
    interrupt_ack_o   : out std_logic
    );
end component OpenBlaze8;

component OpenBlaze8_ALU is
  -- =====[ Parameters ]==========================
  generic (
     size_data      : natural := 8);
  -- =====[ Interfaces ]==========================
  port (
    clock_i              : in  std_logic;
    clock_enable_i       : in  std_logic;
    reset_i              : in  std_logic; -- synchronous reset

    -- From Control
    alu_op_arith_cy_i    : in  std_logic;
    alu_op_arith_i       : in  std_logic;                      -- Arithmetic instructions
    alu_op_logic_i       : in  std_logic_vector( 2 downto 1);          -- Logic instructions

    alu_op_rotate_shift_right_i : in  std_logic;  -- Rotate or shift is right
    alu_op_rotate_shift_i       : in  std_logic_vector( 2 downto 1);  -- Rotate or shift operation :
                                                  -- 00 : insert the flag C (sla,sra)
                                                  -- 01 : insert the data msb (rl,srx)
                                                  -- 10 : insert the data lsb (rr,slx)
                                                  -- 11 : insert a constant   (sl0, sl1, sr0, sr1)

    alu_op_rotate_shift_cst_i   : in   std_logic;  -- Rotate or shift is right

    alu_op_type_i               : in   std_logic_vector( 2 downto 1);         -- Operation type
                                                                      -- 00 Load
                                                                      -- 01 Rotate/Shift
                                                                      -- 11 Arith
                                                                      -- 10 Logic

--  alu_op_flag_z_i             : in  std_logic;                      -- Operation on flag z
--                                                                    -- 1 opx is nul
--                                                                    -- 0 res is nul

    alu_op_flag_c_i             : in  std_logic_vector( 2 downto 1);  -- Operation on flag c
                                                                      -- 01 res MSB (arith or compare)
                                                                      -- 00 0 (logic)
                                                                      -- 10 bit out (rotate/shift)
                                                                      -- 11 odd (test)
    

    -- From Operand
    alu_op1_i            : in  std_logic_vector(size_data downto 1);
    alu_op2_i            : in  std_logic_vector(size_data downto 1);

    -- From Flag
    flag_c_i             : in  std_logic;
    flag_z_i             : in  std_logic;

    -- To result
    alu_res_o            : out std_logic_vector(size_data downto 1);

    -- To flag
    flag_c_o             : out std_logic;
    flag_z_o             : out std_logic
    );
end component OpenBlaze8_ALU;

component OpenBlaze8_Clock is
  -- =====[ Parameters ]==========================
  generic (
     multi_cycle    : natural := 1);
  -- =====[ Interfaces ]==========================
  port (
    clock_i              : in  std_logic;
    clock_enable_i       : in  std_logic;
    reset_i              : in  std_logic; -- synchronous clock
    reset_o              : out std_logic; -- synchronous clock

    clock_o              : out std_logic;
    cycle_phase_o        : out std_logic  -- 0 = first cycle, 1 = second cycle

  );
end component OpenBlaze8_Clock;

component OpenBlaze8_Control is
  -- =====[ Interfaces ]==========================
  port (
    clock_i              : in  std_logic;
    clock_enable_i       : in  std_logic;
    reset_i              : in  std_logic; -- synchronous reset

    -- From Clock
    cycle_phase_i        : in  std_logic;                      -- 0 = first cycle, 1 = second cycle

    -- From Decode
    decode_opcode1_i            : in  std_logic_vector( 5 downto 1);  -- Instruction type (add, shift, ...)
    decode_opcode2_i            : in  std_logic_vector( 4 downto 1);  -- Instruction operation (rl, rr, ...)        
    decode_operand_mux_i        : in  std_logic                    ;  -- Use immediat (0) or register (1)
    decode_branch_cond_i        : in  std_logic_vector( 3 downto 1);  -- The flag used by the branchment (C,NC,Z,NZ)

    -- To Decode
    decode_inhib_o              : out std_logic;                      -- Need inhibit the instruction
    
    -- To Program Counter
    pc_write_en_o               : out std_logic;                      -- PC must be modify
    pc_next_mux_o               : out std_logic_vector( 3 downto 1);  -- Next Program Counter Source
                                                                      -- 001 pc+1
                                                                      -- 110 Interrupt Go to ISR
                                                                      -- 100 call/jump (use immediat)
                                                                      -- 011 ret  (use stack+1)
                                                                      -- 010 reti (use stack)

    -- To Stack
    stack_push_val_o            : out std_logic;                      -- Stack Push enable
    stack_pop_ack_o             : out std_logic;                      -- Stack Pop  enable
                                
    -- To RegFile               
    regx_read_en_o              : out std_logic;                      -- First  register (x) read  enable
    regx_write_en_o             : out std_logic;                      -- First  register (x) write enable
    regy_read_en_o              : out std_logic;                      -- Second register (y) read  enable
                                
    -- To ALU                   
    alu_op_arith_cy_o           : out std_logic;                      -- '1' when instruction is addcy / subcy
    alu_op_arith_o              : out std_logic;                      -- Arithmetic instructions
                                                                      -- 0 Add/Addcy
                                                                      -- 1 sub/subcy
                                
    alu_op_logic_o              : out std_logic_vector( 2 downto 1);  -- Logic instructions
                                                                      -- 0x and
                                                                      -- 10 or
                                                                      -- 11 xor

    alu_op_rotate_shift_right_o : out std_logic;                      -- Rotate or shift is right
    alu_op_rotate_shift_o       : out std_logic_vector( 2 downto 1);  -- Rotate or shift operation :
                                                                      -- 00 : insert the flag C (sla,sra)
                                                                      -- 01 : insert the data msb (rl,srx)
                                                                      -- 10 : insert the data lsb (rr,slx)
                                                                      -- 11 : insert a constant   (sl0, sl1, sr0, sr1)

    alu_op_rotate_shift_cst_o   : out std_logic;                      -- Rotate or shift is right

    alu_op_type_o               : out std_logic_vector( 2 downto 1);  -- Operation type
                                                                      -- 00 Load
                                                                      -- 01 Rotate/Shift
                                                                      -- 11 Arith
                                                                      -- 10 Logic

--  alu_op_flag_z_o             : out std_logic;                      -- Operation on flag z
--                                                                    -- 1 opx is nul
--                                                                    -- 0 res is nul

    alu_op_flag_c_o             : out std_logic_vector( 2 downto 1);  -- Operation on flag c
                                                                      -- 00 0          (logic)
                                                                      -- 01 result MSB (arith/compare)
                                                                      -- 10 bit out    (rotate/shift)
                                                                      -- 11 odd       (test)

    -- To Result
    result_mux_o                : out std_logic_vector(2 downto 1);   -- Result source :
                                                                      -- 1x : alu
                                                                      -- 01 : RAM
                                                                      -- 00 : io
    
    -- To LoadStore
    io_access_en_o              : out std_logic;                       -- Have input or output instructions
    io_read_en_o                : out std_logic;                       -- 1 on the second cycle of input  instruction
    io_write_en_o               : out std_logic;                       -- 1 on the second cycle of output instruction

    -- To RAM
    ram_read_en_o               : out std_logic;                       -- 1 on                     fetch instruction
    ram_write_en_o              : out std_logic;                       -- 1 on the second cycle of store instruction
    
    -- From Flag
    flag_c_i                    : in  std_logic;                      -- Flag Carry
    flag_z_i                    : in  std_logic;                      -- Flag Zero

    -- To Flag
    flag_write_c_o              : out std_logic;  -- Flag write carry
    flag_write_z_o              : out std_logic;  -- Flag write zero
                                
    flag_save_o                 : out std_logic;  -- Interruption
    flag_restore_o              : out std_logic;  -- RETI

    -- From Interrupt
    it_en_i                     : in  std_logic;  -- Have an unmasked interruption
    
    -- To Interrupt
    interrupt_enable_o          : out std_logic;  -- eint or reti enable
    interrupt_disable_o         : out std_logic   -- dint or reti disable
    );
end component OpenBlaze8_Control;

component OpenBlaze8_Decode is
  -- =====[ Parameters ]==========================
  generic (
     multi_cycle    : natural := 1);
  -- =====[ Interfaces ]==========================
  port (
    clock_i              : in  std_logic;
    clock_enable_i       : in  std_logic;
    reset_i              : in  std_logic; -- synchronous reset

    instruction_i        : in  std_logic_vector(18 downto 1); -- Instruction from the ROM

    decode_opcode1_o     : out std_logic_vector( 5 downto 1);
    decode_opcode2_o     : out std_logic_vector( 4 downto 1);
    decode_operand_mux_o : out std_logic                    ;
    decode_branch_cond_o : out std_logic_vector( 3 downto 1);
    decode_num_regx_o    : out std_logic_vector( 4 downto 1);
    decode_num_regy_o    : out std_logic_vector( 4 downto 1);
    decode_imm_o         : out std_logic_vector(10 downto 1);

    decode_inhib_i       : in  std_logic                      -- Need inhibit the instruction
    
  );
end component OpenBlaze8_Decode;

component OpenBlaze8_Flags is
  -- =====[ Interfaces ]==========================
  port (
    clock_i              : in  std_logic;
    clock_enable_i       : in  std_logic;
    reset_i              : in  std_logic; -- synchronous reset
    
    -- read flags
    flag_c_o             : out std_logic;  -- Flag Carry
    flag_z_o             : out std_logic;  -- Flag Zero

    -- write flags
    flag_c_i             : in  std_logic;  -- Flag Carry
    flag_z_i             : in  std_logic;  -- Flag Zero

    -- control 
    flag_write_c_i       : in  std_logic;
    flag_write_z_i       : in  std_logic;

    flag_save_i          : in  std_logic;  -- Interruption
    flag_restore_i       : in  std_logic   -- RETI
    );
end component OpenBlaze8_Flags;

component OpenBlaze8_Interrupt is
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
end component OpenBlaze8_Interrupt;

component OpenBlaze8_LoadStore is
  -- =====[ Parameters ]==========================
  generic (
     size_data      : natural := 8);
  -- =====[ Interfaces ]==========================
  port (
    clock_i              : in  std_logic;
    clock_enable_i       : in  std_logic;
    reset_i              : in  std_logic; -- synchronous reset

--  cycle_phase_i        : in  std_logic;                      -- 0 = first cycle, 1 = second cycle
    
    io_access_en_i       : in  std_logic;
    io_read_en_i         : in  std_logic;
    io_write_en_i        : in  std_logic;
    io_addr_i            : in  std_logic_vector(size_data downto 1);
    io_data_read_o       : out std_logic_vector(size_data downto 1);
    io_data_write_i      : in  std_logic_vector(size_data downto 1);

    port_id_o            : out std_logic_vector(size_data downto 1);
    in_port_i            : in  std_logic_vector(size_data downto 1);
    out_port_o           : out std_logic_vector(size_data downto 1);
    read_strobe_o        : out std_logic;
    write_strobe_o       : out std_logic
    );
end component OpenBlaze8_LoadStore;

component OpenBlaze8_Operand is
  -- =====[ Parameters ]==========================
  generic (
     size_data      : natural := 8);
  -- =====[ Interfaces ]==========================
  port (
    clock_i              : in  std_logic;
    clock_enable_i       : in  std_logic;
    reset_i              : in  std_logic; -- synchronous reset

    decode_operand_mux_i : in  std_logic;  -- 0 : register, 1 immediat
    decode_imm_i         : in  std_logic_vector(size_data downto 1);

    reg_op1_i            : in  std_logic_vector(size_data downto 1);
    reg_op2_i            : in  std_logic_vector(size_data downto 1);
    
    operand_op1_o        : out std_logic_vector(size_data downto 1);
    operand_op2_o        : out std_logic_vector(size_data downto 1)
    );
end component OpenBlaze8_Operand;

component OpenBlaze8_Program_Counter is
  -- =====[ Parameters ]==========================
  generic (
     size_addr_inst : natural := 10);
  -- =====[ Interfaces ]==========================
  port (
    clock_i              : in  std_logic;
    clock_enable_i       : in  std_logic;
    reset_i              : in  std_logic;

    pc_write_en_i        : in  std_logic;                                  --write in PC

    pc_next_mux_i        : in  std_logic_vector( 3 downto 1);              -- Next Program Counter Source
                                                                      -- 001 pc+1
                                                                      -- 110 Interrupt Go to ISR
                                                                      -- 100 call/jump (use immediat)
                                                                      -- 011 ret  (use stack+1)
                                                                      -- 010 reti (use stack)

    decode_address_i     : in  std_logic_vector(size_addr_inst downto 1);  -- Decoded branch condition

    stack_push_data_o    : out std_logic_vector(size_addr_inst downto 1);  -- Stack push data
    stack_pop_data_i     : in  std_logic_vector(size_addr_inst downto 1);  -- Stack push data

    inst_address_o       : out std_logic_vector(size_addr_inst downto 1)   -- Instruction Address

    );
end component OpenBlaze8_Program_Counter;

component OpenBlaze8_RAM is
  -- =====[ Parameters ]==========================
  generic (
     size_data      : natural := 8;
     size_ram       : natural := 64
   );
  -- =====[ Interfaces ]==========================
  port (
    clock_i              : in  std_logic;
    clock_enable_i       : in  std_logic;
    reset_i              : in  std_logic; -- synchronous reset

    ram_read_en_i       : in  std_logic;
    ram_write_en_i      : in  std_logic;
    ram_addr_i          : in  std_logic_vector(log2(size_ram) downto 1);
    ram_read_data_o     : out std_logic_vector(size_data downto 1);
    ram_write_data_i    : in  std_logic_vector(size_data downto 1)
    );
end component OpenBlaze8_RAM;

component OpenBlaze8_Result is
  -- =====[ Parameters ]==========================
  generic (
     size_data      : natural := 8);
  -- =====[ Interfaces ]==========================
  port (
    clock_i              : in  std_logic;
    clock_enable_i       : in  std_logic;
    reset_i              : in  std_logic; -- synchronous reset

    result_mux_i         : in  std_logic_vector(2 downto 1); -- 00 : io, 01 ram, else alu

    alu_res_i            : in  std_logic_vector(size_data downto 1);
    ram_fetch_data_i     : in  std_logic_vector(size_data downto 1);
    io_input_data_i      : in  std_logic_vector(size_data downto 1);

    res_o                : out std_logic_vector(size_data downto 1)
    );
end component OpenBlaze8_Result;

component OpenBlaze8_Stack is
  -- =====[ Parameters ]==========================
  generic (
     size_stack     : natural := 32;
     size_addr_inst : natural := 10
   );
  -- =====[ Interfaces ]==========================
  port (
    clock_i              : in  std_logic;
    clock_enable_i       : in  std_logic;
    reset_i              : in  std_logic; -- synchronous reset

    stack_push_val_i     : in  std_logic;
    stack_push_data_i    : in  std_logic_vector(size_addr_inst downto 1);  -- Stack push data

    stack_pop_ack_i      : in  std_logic;
    stack_pop_data_o     : out std_logic_vector(size_addr_inst downto 1)  -- Stack push data
    );
end component OpenBlaze8_Stack;

component OpenBlaze8_RegFile is
  -- =====[ Parameters ]==========================
  generic (
     size_data      : natural := 8;
     nb_reg         : natural := 16
   );
  -- =====[ Interfaces ]==========================
  port (
    clock_i              : in  std_logic;
    clock_enable_i       : in  std_logic;
    reset_i              : in  std_logic; -- synchronous reset

    regx_read_en_i       : in  std_logic;
    regx_write_en_i      : in  std_logic;
    regx_addr_i          : in  std_logic_vector(log2(nb_reg) downto 1);
    regx_data_i          : in  std_logic_vector(size_data downto 1);
    regx_data_o          : out std_logic_vector(size_data downto 1);

    regy_read_en_i       : in  std_logic;
    regy_addr_i          : in  std_logic_vector(log2(nb_reg) downto 1);
    regy_data_o          : out std_logic_vector(size_data downto 1)
    );
end component OpenBlaze8_RegFile;

-- [COMPONENT_INSERT][END]

end OpenBlaze8_pkg;
