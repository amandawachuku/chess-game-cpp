// OpenAIClient.cpp
#include "OpenAIClient.h"
#include <curl/curl.h>
#include <iostream>

OpenAIClient::OpenAIClient(const std::string& key) : apiKey(key) {}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string OpenAIClient::analyzeGame(const std::string& gameMoves) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://api.openai.com/v1/chat/completions";

        std::string jsonData = 
            "{\"model\": \"gpt-4.1-nano\","
            "\"messages\": [{\"role\": \"system\", \"content\": \"You are a chess coach.\"},"
            "{\"role\": \"user\", \"content\": \"Analyze this chess game: " + gameMoves + "\"}]}";

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        //Temorparily disable SSL Checks for testing purposes
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "❌ curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return readBuffer;
}
