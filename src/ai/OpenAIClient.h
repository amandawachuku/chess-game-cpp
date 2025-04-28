// OpenAIClient.h
#pragma once

#include <string>

class OpenAIClient {
private:
    std::string apiKey;

public:
    OpenAIClient(const std::string& key);
    std::string analyzeGame(const std::string& gameMoves);
};
