#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

#include "teeth.hpp"

int main (int argc, char* argv[]) {

    std::string file = "input.txt";
    std::ofstream outFile ("output.txt");

    std::fstream fileStream;
    fileStream.open(file, std::ios::in); //Opening file
    if (!fileStream) {
        throw("Invalid File");
    }

    bool debug = false;
    ParseArg(debug, "debug", argv);

    //Parsing file
    while (fileStream.peek() != EOF) {
        int topArrSize = 0;
        int botArrSize = 0;
        std::vector<int> topArr;
        std::vector<int> botArr;

        ReadInData(fileStream, 
            topArrSize, topArr, 
            botArrSize, botArr
        );

        //Break since EOF will still evaluate false even when reaching end of file
        if (topArr.size() == 0 || botArr.size() == 0) {
            break;
        }

        //New arrays to be created
        std::vector<int> newTopArr;
        std::vector<int> newBotArr;
        newTopArr.reserve(topArr.size() * 2);
        newBotArr.reserve(botArr.size() * 2);

        std::cout << "Initial Arrays: " << "\n";
        PrintArr(topArr);
        PrintArr(botArr);
        std::cout << "\n";
        
        //The edges matching creates a nice lower bound that prevents some calculations
        int minHeight = std::max(
            std::max(
                topArr.front() + botArr.front(), 
                topArr.back() + botArr.back()
            ),
            std::min(
                MaxArray(topArr) + MinArray(botArr),
                MaxArray(botArr) + MinArray(topArr)
            )
        );
        

        int ti = 0;
        int bi = 0;
        while ((ti < topArrSize - 1) || (bi < botArrSize - 1)) {

            //Lots of preventing out of bounds errors
            ti = std::min(ti, topArrSize - 1);
            bi = std::min(bi, botArrSize - 1);
            int ti1 = std::min(ti + 1, topArrSize - 1);
            int bi1 = std::min(bi + 1, botArrSize - 1);
            int ti2 = std::min(ti + 2, topArrSize - 1);
            int bi2 = std::min(bi + 2, botArrSize - 1);

            //Convience vars
            int currTop = topArr[ti];
            int currBot = botArr[bi];
            int nextTop = topArr[ti1];
            int nextBot = botArr[bi1];

            //Creating the new arrays
            newTopArr.push_back(topArr[ti]);
            newBotArr.push_back(botArr[bi]);

            //Debug output to see arrays built
            if (debug) {
                std::cout << "MinHeight: " << minHeight << "\n";
                PrintArr(newTopArr);
                PrintArr(newBotArr);
                std::cout << "\n";
            }

            //Checking for new min height
            int newMin = std::min(
                std::min(currBot + nextTop, currTop + nextBot),
                nextTop + nextBot
            );

            int upper = MinPairSum(nextBot, topArr, ti);
            int lower = MinPairSum(nextTop, botArr, bi);
            if (upper > minHeight) {
                minHeight = upper;
            }
            if (lower > minHeight) {
                minHeight = lower;
            }
            if (newMin > minHeight) {
                minHeight = newMin;
            }

            if ((nextBot + nextTop) <= minHeight && (MinPairSum(botArr[bi2], topArr, ti1) <= minHeight) && (MinPairSum(topArr[ti2], botArr, bi1) <= minHeight)) {
                ti++;
                bi++; 
            } else if ((nextTop + currBot) <= minHeight) {
                ti++;
            } else if ((currTop + nextBot) <= minHeight) {
                bi++;
            }
        }
        
        //Outputting the last value
        ti = std::min(ti, topArrSize - 1);
        bi = std::min(bi, botArrSize - 1);
        newTopArr.push_back(topArr[ti]);
        newBotArr.push_back(botArr[bi]);

        std::cout << "Final Arrays: " << "\n";
        PrintArr(newTopArr);
        PrintArr(newBotArr);
        std::cout << "Height: " << minHeight << "\n";
        std::cout << "-----------------------------------------------------" << "\n\n";

        //Outputting To File
        outFile << minHeight << "\n";
        for (int i = 0; i < newTopArr.size(); i++) {
            outFile << newTopArr[i] << " " << newBotArr[i] << "\n";
        }
    }
    outFile.close();
    fileStream.close(); //Closing file

    return 0;
}