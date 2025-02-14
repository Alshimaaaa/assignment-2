#include<bits/stdc++.h>

using namespace std;

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
    int getMem(int location){//return the location itself(memory)
        if (location>0 && location<mem.size()){
            return location;
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
        Register(string x = "0"){
            value = x;
        }
        int setReg(string x){
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
    static void Op2(Register& reg , int value){
        //The second function that load the value to the register.
        reg.setReg(value);
        cout<<value<<'\n';
    }
    static void Op3(Register& reg, Memory& mem, int location)
    {
        int x = reg.getReg();
        mem.setValue(location, x);
    }
    static void Op4(Register& reg1, Register& reg2)
    {
        int x = reg1.getReg();
        reg2.setReg(x);
    }

};



//This class put everything together and execute the functions.
class Machine{
private:
    Memory memory;
    vector <Register> registers;
    int programCounter;
    Register instructionRegister;
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
        while (true) {
            fetch();
            int* instructionData = decode();
            execute(instructionData);
        }
        display();
    }

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

        //separate the 3 instruction's data to those 3 strings
        string op_code_string, regIndex_string, operand_string;
        op_code_string = instruction[2];
        regIndex_string = instruction[3];
        operand_string = instruction.substr(4, 2);

        //store those data in 3 integers, by reading from the corresponding string and interpreting the number as hexadecimal
        int op_code_int, regIndex_int, operand_int;

        istringstream iss1(op_code_string);
        iss1 >> hex >> op_code_int;

        istringstream iss2(regIndex_string);
        iss2 >> hex >> regIndex_int;

        istringstream iss3(operand_string);
        iss3 >> hex >> operand_int;

        //put the data in an array and return it
        int* instructionData = new int[3] {op_code_int, regIndex_int, operand_int};
        return instructionData;
    }

    void execute(int instructionData[3]){
        //instructionData consists of:
        //index0 : op code
        //index1 : register index
        //index2 : operand
        
        //select the operation according to the op-code
        switch (instructionData[0]) {
            case 1:
                Operation::Op1(memory, registers, instructionData[1], instructionData[2]);
                break;
            case 2:
                Operation::Op2(r[regIndex],operand);
                break;
            case 3:
                Operation::Op3(r[regIndex], m, operand);
                break;
        }
    }

    //display all the contents of the machine; program counter, instruction register, registers, and MCs.
    void display () {
        cout << "program counter = " << programCounter << endl;

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

    Machine machine;
    machine.run(fileName);
}
