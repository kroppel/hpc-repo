#include <cstdlib>
#include <iostream>
#include <bitset>

unsigned int instruction_asimd_compute( unsigned int  i_vec_instr,
                                        unsigned char i_vec_reg_dst,
                                        unsigned char i_vec_reg_src_0,
                                        unsigned char i_vec_reg_src_1 );

int main() {
    unsigned char l_data1  = 1;
    unsigned char l_data2  = 255;
    unsigned char l_data3  = l_data2 + 1;
    unsigned char l_data4  = 0xA1;
    unsigned char l_data5  = 0b1001011;
    unsigned char l_data6  = 'H';
            char l_data7  = -4;
    unsigned int  l_data8  = 1u << 11;
    unsigned int  l_data9 = l_data8 << 21;
    unsigned int  l_data10  = 0xFFFFFFFF >> 5;
    unsigned int  l_data11 = 0b1001 ^ 0b01111;
    unsigned int  l_data12 = ~0b1001;
    unsigned int  l_data13 = 0xF0 & 0b1010101;
    unsigned int  l_data14 = 0b001 | 0b101;
    unsigned int  l_data15 = 7743;
            int  l_data16 = -7743;

    std::cout << "l_data1: " << std::bitset<8>(l_data1) << std::endl;
    std::cout << "l_data2: " << std::bitset<8>(l_data2) << std::endl;
    std::cout << "l_data3: " << std::bitset<8>(l_data3) << std::endl;
    std::cout << "l_data4: " << std::bitset<8>(l_data4) << std::endl;
    std::cout << "l_data5: " << std::bitset<8>(l_data5) << std::endl;
    std::cout << "l_data6: " << std::bitset<8>(l_data6) << std::endl;
    std::cout << "l_data7: " << std::bitset<8>(l_data7) << std::endl;
    std::cout << "l_data8: " << std::bitset<32>(l_data8) << std::endl;
    std::cout << "l_data9: " << std::bitset<32>(l_data9) << std::endl;
    std::cout << "l_data10: " << std::bitset<32>(l_data10) << std::endl;
    std::cout << "l_data11: " << std::bitset<32>(l_data11) << std::endl;
    std::cout << "l_data12: " << std::bitset<32>(l_data12) << std::endl;
    std::cout << "l_data13: " << std::bitset<32>(l_data13) << std::endl;
    std::cout << "l_data14: " << std::bitset<32>(l_data14) << std::endl;
    std::cout << "l_data15: " << std::bitset<32>(l_data15) << std::endl;
    std::cout << "l_data16: " << std::bitset<32>(l_data16) << std::endl;


    

    unsigned int i_vec_instr = 0b01001110001000001100110000000000;
    unsigned char i_vec_reg_dst = 0b00000000;
    unsigned char i_vec_reg_src_0 = 0b00000001;
    unsigned char i_vec_reg_src_1 = 0b00000010;
    std::cout << std::bitset<32>(instruction_asimd_compute(i_vec_instr, i_vec_reg_dst, i_vec_reg_src_0, i_vec_reg_src_1)) << std::endl;


}

unsigned int instruction_asimd_compute( unsigned int  i_vec_instr,
                                        unsigned char i_vec_reg_dst,
                                        unsigned char i_vec_reg_src_0,
                                        unsigned char i_vec_reg_src_1 )
{
    // int masks for instruction register
    unsigned int mask_dest= 0xFFFFFFFF << 5; 
    unsigned int mask_src0= ~((~mask_dest) << 5); 
    unsigned int mask_src1= ~((~mask_dest) << 16);

    // char mask for 5 bit fields
    unsigned char mask_field = 0xFF >> 3; 

    // Set bits zero
    i_vec_instr = i_vec_instr & mask_dest & mask_src0 & mask_src1;
    // Set bits to desired values
    i_vec_instr = i_vec_instr | (unsigned int) (i_vec_reg_dst & mask_field);
    i_vec_instr = i_vec_instr | (((unsigned int) (i_vec_reg_src_0 & mask_field)) << 5);
    i_vec_instr = i_vec_instr | (((unsigned int) (i_vec_reg_src_1 & mask_field)) << 16);

    return i_vec_instr;
}