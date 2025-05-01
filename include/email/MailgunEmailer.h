#include <vector>
#include <string>

class MailgunEmailer {
public:
    static bool sendEmailWithAttachment(const std::vector<std::string>& recipientEmails, const std::string& pdfPath);
};

