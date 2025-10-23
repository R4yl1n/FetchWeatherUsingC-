#include "ApiRequestWJsonAsClass.hpp"
#include <iostream>

using namespace std;

int main() {
    json result = ApiRequestWJsonAsClass::startQuery();
    cout << "Returned JSON:\n" << result << std::endl;

    if (result.contains("current_weather")){
    cout << "das momentane Wetter beträgt " << result["current_weather"]["temperature"] << " °C" << endl;
    } else {
        cout << "Unkown API no weather Data displayed" << endl;
    }
    
    if (result.is_null()) {
        cerr << "No valid JSON returned." << endl;
        return 1;
    }

    return 0;
}