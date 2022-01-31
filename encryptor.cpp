#include <iostream>
#include <fstream>
#include <string>
#include <random>

void vigenere(std::string keyFileName, std::ifstream &inputFile, std::ofstream &outputFile, bool encrypt){
    unsigned long long keySeed = 0;
    bool useGenerator = false;
    
    std::ifstream keyFile;
    keyFile.open(keyFileName.c_str(), std::ios::binary);

    if (keyFile.fail()){
        keySeed = strtoull(keyFileName.c_str(), NULL, 10);

        if(keySeed == 0){
            std::cerr << "cannot open keyfile: " << keyFileName << std::endl;
            std::cerr << "Enter a valid keyfile or a valid number" << std::endl;
            return;
        }
        useGenerator = true;
    }

    std::mt19937 key(keySeed);

    u_int8_t keyValue = 0;
    char inputValue = 0;
    int encodedBytes = 0;
    int index = 0;
    while (inputFile.read(&inputValue, 1)){

        if(useGenerator){
            keyValue = key() % 255;
        }
        else{
            if(!(keyFile >> keyValue)){
                keyFile.clear(); //reset EOF flag
                keyFile.seekg(0);
                keyFile >> keyValue;
            }
        }
        
        u_int8_t outputValue = (encrypt)? inputValue + keyValue: inputValue - keyValue;
        outputFile << outputValue;
        encodedBytes++;
    }
    (encrypt)? std::cout <<  "Encrypted: " : std::cout << "Decrypted: ";
    std::cout << encodedBytes << " bytes" << std::endl;
}

void ceasar(char key, std::ifstream &inputFile, std::ofstream &outputFile, bool encrypt){
    char letter = 'A';
    int encodedBytes = 0;

    while (inputFile.read(&letter, 1)){
        u_int8_t result = (encrypt)? letter + key: letter - key;
        outputFile << result;
        encodedBytes++;
    }
    (encrypt)? std::cout <<  "Encrypted: " : std::cout << "Decrypted: ";
    std::cout << encodedBytes << " bytes" << std::endl;
}

int main(int argc, char* argv[]){
    if (argc != 6){
        std::cerr << "Use: ./encryptor [type] [encrypt/decrypt] [plain].txt [encrypted].txt key" << std::endl;
        return 1;
    }

    std::string algorithmType = argv[1];
    std::string encryptOrDecrypt = argv[2];
    std::string inputName = argv[3];
    std::string outputName = argv[4];

    std::ifstream inputFile;
    inputFile.open(inputName, std::ios::binary);
    if(inputFile.fail()){
        std::cerr << "cannot open input: " << inputName << std::endl;
        return 2;
    }
    
    std::ofstream outputFile;
    outputFile.open(outputName, std::ios::binary);
    if(outputFile.fail()){
        std::cerr << "cannot open output: " << outputName << std::endl;
        return 3;
    }
    
    if (algorithmType == "ceasar" && encryptOrDecrypt == "encrypt"){
        ceasar(argv[5][0], inputFile, outputFile, true);
    }
    else if (algorithmType == "ceasar" && encryptOrDecrypt == "decrypt"){
        ceasar(argv[5][0], inputFile, outputFile, false);
    }
    else if (algorithmType == "vigenere" && encryptOrDecrypt == "encrypt"){
        vigenere(argv[5], inputFile, outputFile, true);
    }
    else if (algorithmType == "vigenere" && encryptOrDecrypt == "decrypt"){
        vigenere(argv[5], inputFile, outputFile, false);
    }
    else{
        std::cerr << "Use: ./encryptor [type] [encrypt/decrypt] [plain].txt [encrypted].txt key" << std::endl;
    }
    inputFile.close();
    outputFile.close();
    return 0;
}
