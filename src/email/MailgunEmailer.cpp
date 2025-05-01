#include "email/MailgunEmailer.h"
#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <vector>

bool MailgunEmailer::sendEmailWithAttachment(const std::vector<std::string>& recipientEmails, const std::string& pdfPath) {
    for (const std::string& recipient : recipientEmails) {
        CURL* curl;
        CURLcode res = CURLE_OK;
        struct curl_slist* recipients = NULL;
        struct curl_mime* mime;
        struct curl_mimepart* part;

        const char* smtp_url = "smtp://mail.smtp2go.com:587";
        const char* username = "chessapp_user";
        const char* password = "QnYpXGLZeKI63iIF";

        curl = curl_easy_init();
        if (!curl) {
            std::cerr << "❌ Failed to initialize curl.\n";
            return false;
        }

        curl_easy_setopt(curl, CURLOPT_USERNAME, username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_URL, smtp_url);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // For development
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "awachuku@smu.edu");

        std::string formattedRecipient = "<" + recipient + ">";
        recipients = curl_slist_append(recipients, formattedRecipient.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        // === MIME message ===
        mime = curl_mime_init(curl);

        // Email body part (simple message)
        part = curl_mime_addpart(mime);
        curl_mime_data(part, "Attached is your personalized chess game analysis report.", CURL_ZERO_TERMINATED);
        curl_mime_type(part, "text/plain");

        // PDF attachment part
        part = curl_mime_addpart(mime);
        curl_mime_filedata(part, pdfPath.c_str());
        curl_mime_filename(part, "chess_report.pdf");
        curl_mime_type(part, "application/pdf");

        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "❌ Failed to send to " << recipient << ": " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "✅ Sent email to: " << recipient << std::endl;
        }

        // Cleanup for this recipient
        curl_slist_free_all(recipients);
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
    }

    return true;
}
