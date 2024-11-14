# File: src/report_error.py
#!/usr/bin/env python3
import os
import smtplib
import sys
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

ERROR_TYPE_MAPPING = {
    "0": "MEMORY_ERROR",
    "1": "FILE_ACCESS_ERROR",
    "2": "DEVICE_ERROR",
    "3": "NULL_ERROR",
    "4": "UNKNOWN_ERROR"
}

def send_email(subject, body):
    # Configuration from environment variables
    SMTP_SERVER = os.getenv('SMTP_SERVER', 'smtp.gmail.com')
    SMTP_PORT = int(os.getenv('SMTP_PORT', '587'))
    SENDER_EMAIL = os.getenv('SENDER_EMAIL')
    SENDER_PASSWORD = os.getenv('SENDER_PASSWORD')
    RECIPIENT_EMAIL = os.getenv('RECIPIENT_EMAIL', 'b22cs004@iitj.ac.in')

    if not SENDER_EMAIL or not SENDER_PASSWORD:
        print("Sender email or password not set in environment variables.")
        return

    # Create the email content
    message = MIMEMultipart()
    message['From'] = SENDER_EMAIL
    message['To'] = RECIPIENT_EMAIL
    message['Subject'] = subject

    message.attach(MIMEText(body, 'plain'))

    try:
        # Connect to the SMTP server
        server = smtplib.SMTP(SMTP_SERVER, SMTP_PORT)
        server.starttls()
        server.login(SENDER_EMAIL, SENDER_PASSWORD)

        # Send the email
        server.send_message(message)
        server.quit()
        print("Email sent successfully.")
    except Exception as e:
        print(f"Failed to send email: {e}")

def main():
    if len(sys.argv) != 4:
        print("Usage: report_error.py <ERROR_TYPE> <MESSAGE> <ERROR_CODE>")
        sys.exit(1)

    error_type_num = sys.argv[1]
    message = sys.argv[2]
    error_code = sys.argv[3]

    error_type = ERROR_TYPE_MAPPING.get(error_type_num, "UNKNOWN_ERROR")

    subject = f"OS Error Report: {error_type}"
    body = f"An error of type {error_type} occurred.\nDetails: {message}\nError Code: {error_code}"

    send_email(subject, body)

if __name__ == "__main__":
    main()