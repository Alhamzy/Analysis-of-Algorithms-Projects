#ifndef MAIN_HPP
#define MAIN_HPP

int MinPairSum(int pair, std::vector<int>& arr, int index) {
    if (index >= arr.size() - 1) {
        return arr.back() + pair;
    }
    int minVal = INT32_MAX;
    for (int i = index; i < (arr.size()); i++) {
        minVal = ((arr[i] + pair) < minVal) ? (arr[i] + pair) : minVal;
    }
    return minVal;
}

int MinArray(std::vector<int>& arr) {
    if (arr.size() == 0) {
        return 0;
    }
    int min = INT32_MAX;
    for (int i = 0; i < arr.size(); i++) {
        min = (arr[i] < min) ? arr[i] : min;
    }
    return min;
}

int MaxArray(std::vector<int>& arr) {
    if (arr.size() == 0) {
        return 0;
    }
    int max = 0;
    for (int i = 0; i < arr.size(); i++) {
        max = (arr[i] > max) ? arr[i] : max;
    }
    return max;
}

void PrintArr(std::vector<int>& arr) {
    for (auto &i : arr) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

void ParseArg(bool& ref, std::string target, char* args[]) {
    int i = 1;
    while(args[i] != nullptr) {
        std::string arg;
        arg = args[i];
        std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
        if (arg.compare(target) == 0) {
            ref = true;
        }
        i++;
    }
}

void ReadInData(
    std::fstream& file, 
    int& topArrSize, std::vector<int>& topArr, 
    int& botArrSize, std::vector<int>& botArr
) {
    
    file >> topArrSize;
    file >> botArrSize;
    
    for (int i = 0; i < topArrSize; i++) {
        int temp;
        file >> temp;
        topArr.push_back(temp);
    }

    for (int i = 0; i < botArrSize; i++) {
        int temp;
        file >> temp;
        botArr.push_back(temp);
    }
}

#endif