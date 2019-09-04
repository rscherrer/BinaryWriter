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
    char height[25];
};

class BinaryData
{

private:

    char age[25];
    char first[25];
    char last[25];
    char phone[25];
    char height[25];

public:

    BinaryData(){};
    ~BinaryData(){};

    void SetData(int iAge, String strFirst, String strLast, String strPhone,
     double dHeight)
    {
        sprintf(this->age, "%d", iAge);
        sprintf(this->first, "%s", strFirst.c_str());
        sprintf(this->last, "%s", strLast.c_str());
        sprintf(this->phone, "%s", strPhone.c_str());
        sprintf(this->height, "%f", dHeight);
    }

    void Save(std::ofstream &of)
    {
        of.write((char *) &age, sizeof(age));
        of.write((char *) &first, sizeof(first));
        of.write((char *) &last, sizeof(last));
        of.write((char *) &phone, sizeof(phone));
        of.write((char *) &height, sizeof(height));
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
            binaryFile.read((char *) p.age, sizeof(p.age));
            binaryFile.read((char *) p.first, sizeof(p.first));
            binaryFile.read((char *) p.last, sizeof(p.last));
            binaryFile.read((char *) p.phone, sizeof(p.phone));
            binaryFile.read((char *) p.height, sizeof(p.height));

            std::cout << p.age << '\t'
                      << p.first << '\t'
                      << p.last << '\t'
                      << p.phone << '\t'
                      << p.height << '\n';
        }
        binaryFile.close();
    }
};

int main()
{

    String strFirst = "raph";
    String strLast = "scherrer";
    String strPhone = "666";
    int age = 25;
    double height = 172.0;

    std::unique_ptr<BinaryData> bd(new BinaryData());

    bd->SetData(age, strFirst, strLast, strPhone, height);
    bd->WriteBinaryFile("./record.dat");
    bd->ReadBinaryFile("./record.dat");

}
