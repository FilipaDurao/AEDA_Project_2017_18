#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
namespace utilities {

    //Exception to be thrown when user wants to cancel request
    class CancelUserRequest{
    public:
        CancelUserRequest(){};
    };

    //Exception to be thrown when there are no bikes available to request
    class NoBikesAvailable{
    public:
        NoBikesAvailable(){};
    };

    //Exception to be thrown when there are no bikes available to request
    class InvalidFile{
    public:
	  InvalidFile(){};
    };

    //Exception to be thrown when there are no bikes available to scrape
    class NoBrokenBikes {
    public:
        NoBrokenBikes() {};
    };

     //Exception to be thrown when all bikes in scrapyard are scrapped
    class AllBikesScrapped {
    public:
        AllBikesScrapped() {};
    };

    unsigned int getUnsignedIntInput(string errorMsg);
    unsigned int getUnsignedIntInput(unsigned int start, unsigned int end, string errorMsg);

    bool checkFiles(const string &fileNameCompany, const string &fileNameClients, const string &fileNameBikes,
                    const string &fileNameStores, const string &fileNameBikeParts, const string &fileNameScrapyard);
};

#endif // UTILITIES_H_
