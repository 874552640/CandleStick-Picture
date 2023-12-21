#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Candle.h"
#include "Tokenizer.h"

using namespace std;

// Function to tokenize a string based on a separator
vector<string> tokenize(string csvLine, char sep);

// Function to print candlestick data
void printCandlestickData(vector<Candlestick> data);

// Function to print the candlestick plot
void printCandlePlot(vector<Candlestick> data);

int main(){
    
//    ifstream inputFile("/Users/yuan/Desktop/data.csv");
    ifstream inputFile("data.csv");
    
    // Check if the file is successfully opened
    if (!inputFile.is_open()) {
        cerr << "Error opening file!" << std::endl;
        return 1;
    }
    
    vector<Candlestick> dataVector;
    string line;
    getline(inputFile, line);
    
    while (getline(inputFile, line)) {
        // Tokenize the line and extract data using string stream
        vector<string> word_list = tokenize(line, ',');
        // Store the extracted data in the Candlestick struct and add it to the vector
        dataVector.push_back(Candlestick(word_list[0], stoi(word_list[1]), stoi(word_list[2]), stoi(word_list[3]), stoi(word_list[4])));
    }

    // Close the file
    inputFile.close();

    // Print the candlestick plot
    printCandlePlot(dataVector);
    
    return 0;
}

// Function to print candlestick data
void printCandlestickData(vector<Candlestick> data){
    cout << "Date" << "        " << "Open" << "  " << "High" << "  " << "Low" << "  " << "Close" << endl;
    for(Candlestick candle : data){
        cout << candle.date << "  " << candle.open << "   " << candle.high << "   " << candle.low << "   " << candle.close << endl;
    }
}

// Function to print the candlestick plot
void printCandlePlot(vector<Candlestick> data){
    vector<string> lines;
    
    lines.push_back("price");
    
    for(int j = 0; j < data.size(); j++){
        // Adjusting open and close values if open is greater than close
        if(data[j].open > data[j].close){
            int x = data[j].open;
            data[j].open = data[j].close;
            data[j].close = x;
            //change the color
            data[j].color = "red";
        }
    }
    
    // Print the coordinate system
    for (int i = 140; i >= 65; i = i - 5){
        string line = "";
        if(i % 20 == 0 and i != 80){
            line.append(to_string(i) + "|");
        } else if (i == 80){
            line.append(" 80|");
        } else {
            line.append("   |");
        }
        
        
        for(int j = 0; j < data.size(); j++){
            if(i > data[j].close and i <= data[j].high){
                // Print stalk
                line.append("          |          ");
            } else if(i == data[j].close){
                // Determine the color of the candlestick
                if(data[j].color == "red"){
                    // Print upper part
                    line.append("     .....|....      ");
                } else {
                    line.append("     __________      ");
                }
            } else if(i > data[j].open and i < data[j].close){
                // Print middle part
                line.append("    |          |     ");
            } else if(i == data[j].open){
                // Print lower part
                line.append("     ▔▔▔▔▔|▔▔▔▔      ");
            } else if(i >= data[j].low and i < data[j].open){
                // Print stalk
                line.append("          |          ");
            } else {
                line.append("                     ");
            }
        }
        
        lines.push_back(line);
        
    }
    // Print the lower part of the coordinate system
    lines.push_back("   |___________________________________________________________________________________________________________");
    
    string end = " ";
    for(int i = 0; i < data.size(); i++){
        end.append("      ");
        end.append(data[i].date);
        end.append("      ");
    }
    end.append("date");
    lines.push_back(end);
    
    for(string &line : lines){
        cout << line << endl;
    }
}


