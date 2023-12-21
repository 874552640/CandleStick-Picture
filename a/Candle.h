

#ifndef Candle_h
#define Candle_h

// Include necessary libraries
using namespace std;

// Candlestick class definition
class Candlestick {
public:
    string date;        // Date
    int open;        // Opening price
    int high;        // Highest price
    int low;         // Lowest price
    int close;       // Closing price
    
    string color;       // Color

    // Constructor
    // Candlestick(string d, int o, int h, int l, int c)
    //     : date(d), open(o), high(h), low(l), close(c) {}
    
    // Constructor with default color parameter (default color is black)
    Candlestick(string d, int o, int h, int l, int c, string co = "black")
        : date(d), open(o), high(h), low(l), close(c), color(co) {}
};



#endif /* Candle_h */
