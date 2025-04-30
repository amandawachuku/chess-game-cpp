#include "PDFGenerator.h"
#include <hpdf.h>
#include <iostream>
#include <sstream>
#include <vector>

const float PAGE_WIDTH = 595.0f;
const float MARGIN = 50.0f;
const float MAX_LINE_WIDTH = PAGE_WIDTH - 2 * MARGIN;
const float LINE_SPACING = 16.0f;
const float START_Y = 700.0f;

void addWrappedText(HPDF_Page page, const std::string& text, float x, float& y, float fontSize, HPDF_Font font) {
    std::istringstream iss(text);
    std::string word;
    std::string line;
    
    while (iss >> word) {
        std::string testLine = line.empty() ? word : line + " " + word;
        float width = HPDF_Page_TextWidth(page, testLine.c_str());

        if (width > MAX_LINE_WIDTH) {
            // Print current line and start a new one
            HPDF_Page_BeginText(page);
            HPDF_Page_TextOut(page, x, y, line.c_str());
            HPDF_Page_EndText(page);
            y -= LINE_SPACING;
            line = word;
        } else {
            line = testLine;
        }
    }

    if (!line.empty()) {
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, x, y, line.c_str());
        HPDF_Page_EndText(page);
        y -= LINE_SPACING;
    }
}

bool PDFGenerator::generatePDF(const std::string& filename,
                               const std::string& moves,
                               const std::string& aiAnalysis) {
    HPDF_Doc pdf = HPDF_New(nullptr, nullptr);
    if (!pdf) {
        std::cerr << "❌ Failed to create PDF object.\n";
        return false;
    }

    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", nullptr);
    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetFontAndSize(page, font, 16);

    float y = 800;

    // Title
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, MARGIN, y, "Chess Game Summary");
    HPDF_Page_EndText(page);
    y -= 2 * LINE_SPACING;

    // Moves
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, MARGIN, y, "Moves Played:");
    HPDF_Page_EndText(page);
    y -= LINE_SPACING;

    addWrappedText(page, moves, MARGIN, y, 12, font);
    y -= LINE_SPACING;

    // AI Analysis
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, MARGIN, y, "AI Game Analysis:");
    HPDF_Page_EndText(page);
    y -= LINE_SPACING;

    addWrappedText(page, aiAnalysis, MARGIN, y, 12, font);

    HPDF_SaveToFile(pdf, filename.c_str());
    HPDF_Free(pdf);

    std::cout << "✅ PDF saved to " << filename << std::endl;
    return true;
}
