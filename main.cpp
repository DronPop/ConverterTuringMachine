#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <tuple>
#include <iomanip>

enum Direction {
    Left = -1,
    Right = +1,
    None = 0,
};

void convert(std::istream& in_, std::ostream& out_);

bool isComment(const std::string& string_);

bool isEmpty(const std::string& string_);

void removeSpace(std::string& string_);

char convertChar(const char c_);

std::pair<char, std::string> parseLeftPart(std::string leftPart_);

std::tuple<char, std::string, Direction> parseRightPart(std::string rightPart_);

int main(int argc_, char** argv_) {
    std::string inputFileName;
    std::cout << "input filename: ";
    std::cin >> inputFileName;
    
    std::string outputFilename;
    std::cout << "output filename: ";
    std::cin >> outputFilename;
    
    std::ifstream in(inputFileName);
    if (!in.is_open()) {
        std::cout << "incorect input filename!\n";
        return 0;
    }
    
    std::ofstream out(outputFilename);
    if (!out.is_open()) {
        std::cout << "incorect output filename!\n";
        return 0;
    }
    
    convert(in, out);
    
    return EXIT_SUCCESS;
}

void convert(std::istream& in_, std::ostream& out_) {
    std::string str;
    while (std::getline(in_, str)) {
        if (isComment(str)) {
            out_ << str << '\n';
        } else if (isEmpty(str)) {
            out_ << str << '\n';
        } else {
            const size_t midIndex = str.find("->");
            const std::string leftPartOfRule = str.substr(0, midIndex);
            const std::string rightPartOfRule = str.substr(midIndex + 2);
            char inC, outC;
            Direction direction;
            std::string inState, outState;
            std::tie(inC, inState) = parseLeftPart(leftPartOfRule);
            std::tie(outC, outState, direction) = parseRightPart(rightPartOfRule);
            out_ << inState << ", " << inC << " -> " << outState << ", " << outC << ", ";
            if (direction == Right) {
                out_ << std::showpos << direction << '\n';
            } else {
                out_ << direction << '\n';
            }
        }
    }
}

bool isComment(const std::string& string_) {
    return string_.find("//") == 0;
}

bool isEmpty(const std::string& string_) {
    for (const char& c: string_) {
        if (c != ' ')
            return false;
    }
    return true;
}

void removeSpace(std::string& string_) {
    int index = 0;
    while ((index = string_.find(' ')) != std::string::npos)
        string_.erase(index);
}

char convertChar(const char c_) {
    if (c_ == 'B') {
        return '^';
    }
    return c_;
}

std::pair<char, std::string> parseLeftPart(std::string leftPart_) {
    removeSpace(leftPart_);
    return {convertChar(leftPart_.front()), leftPart_.substr(1) };
}

std::tuple<char, std::string, Direction> parseRightPart(std::string rightPart_) {
    removeSpace(rightPart_);
    const char last = rightPart_.back();
    Direction direction = None;
    if (last == 'L') {
        direction = Left;
    } else {
        direction = Right;
    }
    return std::make_tuple(convertChar(rightPart_.front()),
                           rightPart_.substr(1, rightPart_.size() - 2),
                           direction);
}


