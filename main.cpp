#include "data.hpp"

using namespace std;

#define windowWidth 1365
#define windowLength 1024
#define loopDelay 50


int main(){
    Window *window = new Window(windowWidth, windowLength, "RSDL Demo");
    Data* data = new Data();
    preprocess(window, data);
    int counter = 0;
    int newWaveDelayTime = 0;
    auto lastProcessTime = chrono::steady_clock::now();
    while(true){
        counter++;
        int loopDuration = (chrono::steady_clock::now() - lastProcessTime).count()/1000000;
        lastProcessTime = chrono::steady_clock::now();
        process(window, data, loopDuration, counter, newWaveDelayTime);
        update(window, data, loopDuration);
        delay(loopDelay);
    }
}
