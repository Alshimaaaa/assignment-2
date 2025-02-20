// FCAI � OOP Programming � 2023 - Assignment 2
// Program Name:				Vole machine simulator
// Last Modification Date:	    15/11/2023
// Author1 name and ID:	        Abdelrahman Ahmed Lotfy     20220474    Obidah05@gmail.com
// Author2 name and ID:	        Ahmed Hossam ElAlfy         20220016    ahalfy2005@gmail.com
// Author3 name and ID:	        Alshimaa Mohamed Abdo       20220067    mshmsh1582004@gmail.com
// Section:                     S22
// Teaching Assistant:          Eng/ Rana AbdelKader
// Purpose:                     A simulator for the vole machine using cpp classes that is able to read machine language instructions and perform operations on them

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;




string decInt_to_hexString(int no){
    string res;
    stringstream ss(res);
    //insert the hexadecimal representation of the decimal number no into the string stream.
    ss<<uppercase<<hex<<no;
    //res will have the same content as that in the string stream
    ss>>res;
    //the following is to ensure that the resulting string consists of only 2 characters;
    //and that's by including a leading zero if necessary,
    //and producing the representation of only the valid numbers with respect to the Vole Machine
    if(res.size()==1){
        res.insert(res.begin(),'0');
    }
    else{
        res= res.substr(res.size()-2,2);
    }
    return res;
}


int hexString_to_decInt (string no) {
    //copy the content of string no to the string stream, then insert it into the int no,
    // by interpreting the string as a hexadecimal representaion.
    int res;
    stringstream ss (no);
    ss >> hex >> res;
    return res;
}






//class to handle the memory by making a vector of all memory cells.
class Memory{
    private:
        vector <string> mem;
    public:
        Memory(int size = 256){//initialization
            mem.resize(size, "00");
        }

        void setSize(int size){//setting its size to the given size.
            mem.resize(size, "00");
        }

        int getSize () {
            return mem.size();
        }

        string getValue(int location){//return the value in this location.
            if (location>=0 && location<mem.size()){    //was location>0 before ???
                return mem[location];
            }
            else{
                cout<<"There is no such memory";
                return 0;
            }
        }

        void setValue(int location, string value)
        {
            if (location>=0 && location<mem.size()){    //was location>0 before ???
                mem[location] = value;
            }
            else{
                cout<<"There is no such memory";
            }
        }
};



//class to handle all the functions needed to the register (one register cell only).
class Register{
    private:
        string value;
    public:
        Register(string x = "00"){
            value = x;
        }
        void setReg(string x){
            value = x;
        }
        string getReg(){
            return value;
        }
};



//class that have all the functions
class Operation{
    public:
        static void Op1(Memory& mem, vector <Register> &reg, int regNo, int memNo){
            //The first function that load from memory to the register.
            string value = mem.getValue(memNo);
            reg[regNo].setReg(value);
        }

        static void Op2(vector <Register> &reg , int regNo,int memNo){
            //The second function that load the value to the register.
            string value = decInt_to_hexString(memNo);
            reg[regNo].setReg(value);
        }

        static void Op3(Memory& mem, vector <Register> &reg,int regNo,int memNo)
        {
            string value = reg[regNo].getReg();
            if(memNo==0){
                cout<<"The value in register "<<regNo<<" equal "<<value<<'\n';//print what is in this register.
            }
            else{
                mem.setValue(memNo, value); //save what is in this register to this memory cell.
            }
        }

        static void Op4(vector <Register> &reg,int reg1, int reg2)
        {
            //store what is in reg1 in reg2.
            string value = reg[reg1].getReg();
            reg[reg2].setReg(value);
        }

        static void Op5(vector <Register> &reg,int reg1, int reg2, int reg3){
            string x = reg[reg2].getReg(), y = reg[reg3].getReg();//S and T register values.
            int num1 = hexString_to_decInt(x),num2= hexString_to_decInt(y);//Turn them to numbers.
            if(num1>=128)num1-=256;
            if(num2>=128)num2-=256;//Turn the number to two's complement if its first bit is 1 then it's a negative number.
            int ans = num1+num2;
            string value = decInt_to_hexString(ans);
            reg[reg1].setReg(value);//Save them in the register R.
        }
        static void OpB(vector <Register> &reg, int reg1, int operand, int &counter)
        {
            string x = reg[reg1].getReg() , y = reg[0].getReg();

            if(x == y)
            {
                counter = operand;
            }

        }
};



//This class put everything together and execute the functions.
class Machine{
    private:
        Memory memory;
        vector <Register> registers;
        int programCounter;
        Register instructionRegister;


        void write_instructions_to_memory (string fileName) {
            //Open the file.
            fstream insFile;
            insFile.open(fileName, fstream::in|fstream::out);

            if(insFile.is_open()){
                //initially, we will write to the first memory cell
                int memory_location = 0;

                //Read every line from the file.
                string line;
                while(getline(insFile,line)){
                    //divide the instruction line to its data; opcode, register_index and operand.
                    char op_code = line[2];
                    char register_index = line[6];
                    string operand = line.substr(10, 2);

                    //organize those data so that they can be stored in 2 MCs
                    string content_of_first_MC, content_of_second_MC;
                    content_of_first_MC.push_back(op_code);
                    content_of_first_MC.push_back(register_index);
                    content_of_second_MC = operand;

                    //write them to the memory
                    memory.setValue(memory_location, content_of_first_MC);
                    memory.setValue(memory_location + 1, content_of_second_MC);

                    //increment the location
                    memory_location += 2;
                }

                insFile.close();
            }
            else {
                cout<<"This file doesn't exist \n";
            }
        }

        void fetch () {
            //get the current instruction from memory
            string instruction = "0x";
            instruction.append(memory.getValue(programCounter));
            instruction.append(memory.getValue(programCounter+1));

            programCounter += 2;
            instructionRegister.setReg(instruction);
        }

        int* decode () {
            string instruction = instructionRegister.getReg();

            //separate the 3 instruction's data to those 5 strings
            string op_code_string, reg1Index_string, reg2Index_string, reg3Index_string, MC_address_or_bitPattern_string;
            op_code_string = instruction[2];
            reg1Index_string = instruction[3];
            reg2Index_string = instruction[4];
            reg3Index_string = instruction[5];
            MC_address_or_bitPattern_string = reg2Index_string + reg3Index_string;

            //store those data in 5 integers, via the help of this function
            int op_code_int = hexString_to_decInt(op_code_string);
            int reg1Index_int = hexString_to_decInt(reg1Index_string);
            int reg2Index_int = hexString_to_decInt(reg2Index_string);
            int reg3Index_int = hexString_to_decInt(reg3Index_string);
            int MC_address_or_bitPattern_int = hexString_to_decInt(MC_address_or_bitPattern_string);

            //put the data in an array and return it
            int* instructionData = new int[5] {op_code_int, reg1Index_int, reg2Index_int, reg3Index_int, MC_address_or_bitPattern_int};
            return instructionData;
        }

        bool execute(int instructionData[5]){
            //instructionData consists of:                  where the instruction is in the form:
            //index0 : op-code                              op-code R1 R2 R3
            //index1 : register1 index (R1)                 OR
            //index2 : register2 index (R2)                 op-code R1 MC_index/bit_pattern
            //index3 : register3 index (R3)
            //index4 : memory cell index/bit pattern        !!use the suitable elements according to this guide!!

            //select the operation according to the op-code
            switch (instructionData[0]) {
                case 1:
                    Operation::Op1(memory, registers, instructionData[1], instructionData[4]);
                    break;
                case 2:
                    Operation::Op2(registers,instructionData[1],instructionData[4]);
                    break;
                case 3:
                    Operation::Op3(memory, registers, instructionData[1], instructionData[4]);
                    break;
                case 4:
                    Operation::Op4(registers,instructionData[2], instructionData[3]);
                    break;
                case 5:
                    Operation::Op5(registers, instructionData[1], instructionData[2], instructionData[3]);
                    break;
                case 11:
                    Operation::OpB(registers, instructionData[1], instructionData[4], programCounter);
                case 12:
                    //the machine will stop the cycle
                    return true;
                    break;
            }

            //the machine won't stop the cycle for now
            return false;
        }

    public:
        //constructor
        Machine(int memSize = 256, int regSize = 16, int initAddress = 0){
            memory.setSize(memSize);
            registers.resize(regSize);
            programCounter = initAddress;
        }

        //the whole process of the vole machine
        void run (string fileName) {
            write_instructions_to_memory(fileName);

            bool should_terminate = false;
            while (true) {
                fetch();
                int* instructionData = decode();
                should_terminate = execute(instructionData);

                if (should_terminate) {
                    break;
                }
            }

            display();
        }

        //display all the contents of the machine; program counter, instruction register, registers, and MCs.
        void display () {
            cout << endl << endl;

            string programCounter_string = "0x" + decInt_to_hexString(programCounter);
            cout << "program counter = " << programCounter_string << endl;

            cout << "instruction register = " << instructionRegister.getReg() << endl;

            cout << endl << endl;

            cout << "content of the registers from register 0x0 to register 0xF:" << endl;
            for (int i = 0; i < registers.size(); i++) {
                cout << registers[i].getReg() << endl;
            }

            cout << endl << endl;

            cout << "content of the memory cells from memory cell 0x00 to memory cell 0xFF:" << endl;
            for (int i = 0; i < memory.getSize(); i++) {
                cout << memory.getValue(i) << endl;
            }
        }
};





int main(){
    cout.setf(std::ios::hex,std::ios::basefield);

    //get the name of the file that contains the instructions
    string fileName;
    cout << "enter the name of the file that contains the instructions: ";
    cin >> fileName;
    fileName.append(".txt");
    cout << '\n' << '\n' << '\n';

    Machine machine;
    machine.run(fileName);
}
