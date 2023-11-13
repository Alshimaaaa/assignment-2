#include<bits/stdc++.h>
using namespace std;
class Memory{//class to handle the memory by making a vector of all the memories.
private:
    vector<int>mem;
public:
    Memory(int size=0){//initialization
        mem.resize(size,0);
    }
    void setSize(int size){//setting its size to the given size.
        mem.resize(size,0);
    }
    int getValue(int location){//return the value in this location.
        if (location>0 && location<mem.size()){
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
    void setValue(int location, int value)
    {
        if (location>0 && location<mem.size()){
            mem[location] = value;
        }
        else{
            cout<<"There is no such memory";
        }
    }
};
 class Register{//class to handle all the functions needed to the register.
 private:
     int value;
 public:
     Register(int x=0){
         value=x;
     }
     int setReg(int x){
         value=x;
     }
     int getReg(){
         return value;
     }
};
class Operation{//class that have all the functions
public:
    static void Op1(Register& reg ,Memory& mem, int location){
        //The first function that load from memory to the register.
        int value =mem.getValue(location);
        reg.setReg(value);
        cout<<value<<'\n';
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
class Machine{//This class put everything together and execute the functions.
private:
    Memory m;
    vector<Register>r;
    int count;
public:
    Machine(int memSize=0, int regSize=0, int x=0){
        m.setSize(memSize);
        r.resize(regSize,0);
        count=x;
    }
    void execute(vector<vector<int>>& instructions){
        for(count;count<instructions.size();count++){
            int op_code=instructions[count][0];//The first part of the instruction.
            int regIndex = instructions[count][1];//The second part of the instruction.
            int operand = instructions[count][2];//The third part of the instruction.
            if(op_code == 1){
                Operation::Op1(r[regIndex],m,operand);
            }
            else if(op_code == 2){
                Operation::Op2(r[regIndex],operand);
            }
            else if(op_code == 3)
            {
                Operation::Op3(r[regIndex], m, operand);
            }
        }
    }
};
int main(){
    cout.setf(std::ios::hex,std::ios::basefield);
    fstream file;//Open the file.
    file.open("f.txt",fstream::in|fstream::out);
    vector<vector<int>>instructions;
    Machine machine(256,8);//Assumption for both memory size and register size.
    if(file.is_open()){
        string line;
        //Read every line from the file.
        while(getline(file,line)){
            //divide the instruction line to opcode, register and operand then put them all in vector v;
            istringstream iss(line);
            int value;
            vector<int>v;
            while(iss>>hex>>value){
                v.push_back(value);
            }
            instructions.push_back(v);//Then put every vector of them in the instructions vector.
        }
        file.close();
        machine.execute(instructions);//Execute all the given instructions.
    }
    else{
        cout<<"This file doesn't exist\n";
    }
}

