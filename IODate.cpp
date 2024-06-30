#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <vector>

class Date
{
private:
    int year;
    int month;
    int day;

public:
    Date(int year, int month, int day) : year(year), month(month), day(day) {}

    void print(std::ostream& outStream) const 
    {
        outStream << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day;
    }


};

std::vector<Date> readDatesFromFile(const std::string& filePath) 
{
    std::vector<Date> dates;
    std::ifstream file(filePath);

    if (!file.is_open()) 
        throw std::runtime_error("Cannot open file: " + filePath);
    

    std::string line;
    while (std::getline(file, line)) 
    {
        std::stringstream ss(line);
        int year, month, day;
        char c = '-';

        ss >> year >> c >> month >> c >> day;
        dates.emplace_back(year, month, day);
    }

    file.close();
    return dates;
}

void saveDatesToFile(const std::vector<Date>& dates, const std::string& filePath) 
{
    std::ofstream file(filePath);

    if (!file.is_open()) 
        throw std::runtime_error("Cannot open file: " + filePath);
    

    for (const Date& date : dates) 
    {
        date.print(file);
        file << std::endl;
    }

    file.close();
}

int main() 
{
    std::string inputFilename = "dates.txt";
    std::string outputFilename = "outDates.txt";

    try 
    {
        std::vector<Date> dates = readDatesFromFile(inputFilename);

        for (const Date& date : dates) 
        {
            date.print(std::cout);
            std::cout << std::endl;
        }

        saveDatesToFile(dates, outputFilename);
    }
    catch (const std::exception& e) 
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}