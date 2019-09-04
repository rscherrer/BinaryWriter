#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>

typedef std::string String;

struct Person
{
	char age[25];
    char first[25];
    char last[25];
    char phone[25];
};

class BinaryData
{
private:
    char age[25];
    char first[25];
    char last[25];
    char phone[25];
public:
    BinaryData(){};
    ~BinaryData(){};

    void SetData(int iAge, String strFirst, String strLast, String strPhone)
    {
        sprintf(this->age, "%d", iAge);
        sprintf(this->first, "%s", strFirst.c_str());
        sprintf(this->last, "%s", strLast.c_str());
        sprintf(this->phone, "%s", strPhone.c_str());
    }

    void Save(std::ofstream &of)
    {
        of.write((char *) &age, sizeof(age));
        of.write((char *) &first, sizeof(first));
        of.write((char *) &last, sizeof(last));
        of.write((char *) &phone, sizeof(phone));
    }

    void WriteBinaryFile(String strFile)
    {
        std::ofstream fs;
        fs.open(strFile, std::ios::binary);
        if(!fs.is_open()) {
            std::cout << "cannot open file " << strFile << '\n';
        }
        else {
            this->Save(fs);
        }
        fs.close();
    }

    void ReadBinaryFile(String strFile)
    {
        Person p;
        std::ifstream binaryFile;
        int size = 0;
        binaryFile.open(strFile, std::ios::binary);
        binaryFile.seekg(0, std::ios::end);
        size = (int) binaryFile.tellg();
        binaryFile.seekg(0, std::ios::beg);

        while(binaryFile.tellg() < size)
        {
            binaryFile.read((char*) p.age, sizeof(p.age));
            binaryFile.read((char*) p.first, sizeof(p.first));
            binaryFile.read((char*) p.last, sizeof(p.last));
            binaryFile.read((char*) p.phone, sizeof(p.phone));

            std::cout << p.age << '\t' << p.first << '\t' << p.last << '\t' << p.phone << '\n';
        }
        binaryFile.close();
    }
};

int main()
{

    String strFirst, strLast, strPhone;
    int age;

    std::unique_ptr<BinaryData> bd(new BinaryData());

    std::cout << "enter age:";
    std::cin >> age;
    std::cout << "enter first name:";
    std::cin >> strFirst;
    std::cout << "enter last name:";
    std::cin >> strLast;
    std::cout << "enter phone number:";
    std::cin >> strPhone;

    bd->SetData(age, strFirst, strLast, strPhone);
    bd->WriteBinaryFile("./record.dat");
    bd->ReadBinaryFile("./record.dat");

}
