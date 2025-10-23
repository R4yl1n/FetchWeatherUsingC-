#include <iostream>
#include "ApiRequestWJsonAsClass.hpp"
#include <curl/curl.h>


using json = nlohmann::json;

// Callback-Funktion: schreibt die Antwort in einen std::string
size_t ApiRequestWJsonAsClass::write_to_string(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total = size * nmemb;
    std::string* out = static_cast<std::string*>(userp);
    out->append(static_cast<char*>(contents), total);
    return total;
}

std::string ApiRequestWJsonAsClass::getUserInput(){

    std::cout << "Gib eine URL für eine JSON API ein;" << std::endl << "example: https://api.open-meteo.com/v1/forecast?latitude=47.3769&longitude=8.5417&current_weather=true" << std::endl; 
    std::string user_Input;
    std::cin >> user_Input;
    return user_Input;
}

json ApiRequestWJsonAsClass::startQuery() {
    const std::string url = ApiRequestWJsonAsClass::getUserInput();

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to init CURL\n";
        exit(1);
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl error: " << curl_easy_strerror(res) << "\n";
        curl_easy_cleanup(curl);
        exit(1);
    }

    curl_easy_cleanup(curl);

    // ✅ JSON parse
    try {
        json j = json::parse(response);

        std::cout << "Erfolgreich geparst!\n";
        std::string jsonResponse = j.dump(2);   // kompaktes JSON
        return j;
        
    } catch (const std::exception& e) {
        std::cerr << " JSON parse error: " << e.what() << "\n";
         exit(1);
    }
}