// File: src/reporter.c
#include "reporter.h"
#include <stdio.h>
#include <string.h>

// Define recipient and sender email
#define RECIPIENT_EMAIL "advaitgaur2003@gmail.com"
#define SENDER_EMAIL "b22cs004@iitj.ac.in"

// Function to send email using sendmail
void send_email(const char *subject, const char *body) {
    FILE *mail = popen("/usr/sbin/sendmail -t", "w");
    if (mail == NULL) {
        // Failed to open sendmail
        return;
    }

    fprintf(mail, "To: %s\n", RECIPIENT_EMAIL);
    fprintf(mail, "From: %s\n", SENDER_EMAIL);
    fprintf(mail, "Subject: %s\n\n", subject);
    fprintf(mail, "%s\n", body);

    pclose(mail);
}

void report_error(ErrorType type, const char *message, int error_code) {
    char subject[256];
    char body[1024];

    // Convert ErrorType to string
    const char *type_str;
    switch(type) {
        case MEMORY_ERROR:
            type_str = "MEMORY_ERROR";
            break;
        case FILE_ACCESS_ERROR:
            type_str = "FILE_ACCESS_ERROR";
            break;
        case DEVICE_ERROR:
            type_str = "DEVICE_ERROR";
            break;
        default:
            type_str = "UNKNOWN_ERROR";
    }

    snprintf(subject, sizeof(subject), "OS Error Report: %s", type_str);
    snprintf(body, sizeof(body), "An error of type %s occurred.\nDetails: %s\nError Code: %d",
             type_str, message, error_code);

    send_email(subject, body);
}