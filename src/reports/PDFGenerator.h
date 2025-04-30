// PDFGenerator.h
#ifndef PDF_GENERATOR_H
#define PDF_GENERATOR_H

#include <string>

class PDFGenerator {
public:
    // Generates a PDF summary of the chess game
    // @param filename: Path to the output PDF file
    // @param moves: String containing formatted moves (e.g., "1. e4 e5 2. Nf3 Nc6")
    // @param aiAnalysis: Full text of the AI-generated commentary
    // @return true if the PDF is successfully created, false otherwise
    static bool generatePDF(const std::string& filename,
                            const std::string& moves,
                            const std::string& aiAnalysis);
};

#endif // PDF_GENERATOR_H
