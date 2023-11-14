import imaplib
import email
from email.header import decode_header
import requests
import json
import smtplib
import ssl
from bs4 import BeautifulSoup
import os

#eMail settings
smtp_server = "smtp.gmail.com"
smtp_port = 587  # for starttls
username = "caleb@summitlawncareak.com"
password = "azghzgmcbuzpgkla"

#GPT settings
key = "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"
model = "gpt-3.5-turbo"
system = "As a customer service representative for Summit Lawn Care, based in Eagle River, Alaska, your primary duty is to manage the email communications for the company. Specifically, you’ll be attending to the mailbox associated with Caleb@summitlawncareak.com. Key responsibilities include: 1.	Screening incoming emails: Not all incoming mail will be critical or relevant. Common emails from sales teams or automated notifications usually don’t require a response. These can be disregarded.2.	Handling customer communications: If an email from a customer arrives, it’s your duty to evaluate the content, decide on an appropriate response, and send it on behalf of Summit Lawn Care (SLC). The company specializes in sustainable lawn care services, so your responses should align with this expertise and business focus.3.	Managing lead generation notifications: When a lead generation platform, such as Wix, sends a notification, review the content to determine if it necessitates any action or response.While responding or taking action, you should provide reasoning in JSON format for each decision. Each action will include three components: 1.	Explanation of the decision (e.g., “I should inform Caleb about this because...”)2.	The intended recipient (e.g., “Caleb” or “SLCcustomer@example.com”) 3.	The content of the message or action to be taken (e.g., “You might be interested in this:...” or “Hello customer, I hope this email finds you well, I’m writing to you about...”) Here is an example of how you should format your actions: {'reasoning': 'I should respond to this message on behalf of SLC because the customer has an issue that needs immediat attention','recipient': 'SLCcustomer@example.com', 'message': 'Hello customer, I hope this email finds you well. I'm writing to you about the issue you've reported...' }"

class EmailClient:
    def __init__(self, username, password, smtp_server="smtp.gmail.com", smtp_port=587):
        self.username = username
        self.password = password
        self.smtp_server = smtp_server
        self.smtp_port = smtp_port

    def check_email(self):
        email_details = {}  # Initialize an empty dictionary for email details
        try:
            mail = imaplib.IMAP4_SSL("imap.gmail.com")
            mail.login(self.username, self.password)
            mail.select("inbox")

            # search mailbox
            result, data = mail.uid('search', None, "UNSEEN")
            if result == 'OK':
                email_ids = data[0].split()
                if email_ids:
                    oldest_unseen_email_id = email_ids[0]  # Get the oldest unseen email
                    result, email_data = mail.uid('fetch', oldest_unseen_email_id, '(BODY[])')  # Fetch the entire email
                    if result == 'OK':
                        raw_email = email_data[0][1].decode("utf-8")
                        email_message = email.message_from_string(raw_email)

                        from_ = email_message.get('From')
                        to_ = email_message.get('To')
                        subject_ = email_message.get('Subject')

                        body_ = None
                        if email_message.is_multipart():
                            for part in email_message.get_payload():
                                if part.get_content_type() == 'text/plain':
                                    body_ = part.get_payload(decode=True)
                                elif part.get_content_type() == 'text/html':
                                    soup = BeautifulSoup(part.get_payload(decode=True), "html.parser")
                                    body_ = soup.get_text(separator=" ")

                        if body_:
                            if isinstance(body_, bytes):
                                body_ = body_.decode('utf-8')
                            body_ = ' '.join(body_.split())

                        email_details = {
                            "from": from_,
                            "to": to_,
                            "subject": subject_,
                            "body": body_  # Now it's the cleaned up body text
                        }
        except Exception as e:
            print(f"Error: {str(e)}")
        return email_details

    def send_email(self, recipient, msg_content):
        context = ssl.create_default_context()

        try:
            server = smtplib.SMTP(self.smtp_server, self.smtp_port)
            server.ehlo()
            server.starttls(context=context)
            server.ehlo()
            server.login(self.username, self.password)
            server.sendmail(from_addr=self.username, to_addrs=recipient, msg=msg_content)
        except Exception as e:
            print(e)
        finally:
            server.quit()


class OpenAIChat:
    def __init__(self, key, model):
        self.key = key
        self.model = model
        self.url = "https://api.openai.com/v1/chat/completions"
        self.headers = {
            "Content-Type": "application/json",
            "Authorization": "Bearer " + self.key
        }
        self.system = system

    def call_api(self, msg_content):
        data = {
            "model": self.model,
            "messages": [{"role": "system", "content": self.system},
            {"role": "user", "content": msg_content}]
        }

        response = requests.post(self.url, headers=self.headers, data=json.dumps(data))

        return response.json()

    def parse_response(self, response):
        if 'choices' in response:
            assistant_message = response['choices'][0]['message']['content']
            return assistant_message
        else:
            print("Error: Invalid API response")
            return None

class DataStorage:
    def __init__(self, filename="data.json"):
        self.filename = filename

    def save_data(self, data):
        with open(self.filename, 'w') as f:
            json.dump(data, f)

    def load_data(self):
        if os.path.exists(self.filename):
            with open(self.filename, 'r') as f:
                data = json.load(f)
        else:
            data = {}
        return data
class SquareAPI:
    def __init__(self):
        self.access_token = 'EAAAEJ8jq2pSgx-qETGgkRykUaveSQ09PPJ3kqV_RYimbeJeakHdOfmWydNTMbyq'
        self.headers = {
            'Authorization': f'Bearer {access_token}',
            'Content-Type': 'application/json'
        }

    def create_customer(self, first, last, phone, email, address, city, zip):
        url = "https://connect.squareup.com/v2/customers"
        data = {
            "given_name": first,
            "family_name": last,
            "phone_number": phone,
            "email_address": email,
            "address": {
                "address_line_1": address,
                "locality": city,
                "postal_code": zip,
                "country": "US"
            }
        }
        response = requests.post(url, headers=self.headers, data=json.dumps(data))
        if response.status_code != 200:
            raise Exception(f"Failed to create customer: {response.content.decode('utf-8')}")
        customer = response.json()['customer']
        return customer['id']


"""
Usage:

1. First, import the module in your Python script:
    from email_assistant import EmailClient, OpenAIChat, DataStorage

2. Initialize the EmailClient, OpenAIChat, and DataStorage classes with the necessary parameters:
    email_client = EmailClient(username, password, smtp_server="smtp.gmail.com", smtp_port=587)
    openai_chat = OpenAIChat(key, model)
    data_storage = DataStorage(filename="data.json")

3. To check for new emails, use the EmailClient's check_email() method:
    email_details = email_client.check_email()
    # 'email_details' will contain the details of the latest unseen email.

4. To send an email, use the EmailClient's send_email() method:
    recipient_email = "recipient@example.com"
    message_content = "Hello, this is the content of the email."
    email_client.send_email(recipient_email, message_content)

5. To interact with the OpenAI model, use the OpenAIChat's call_api() method:
    user_input = "I have a question about lawn care services."
    response = openai_chat.call_api(user_input)
    # 'response' will contain the model's generated response.

6. To parse the response from the OpenAI model, use the OpenAIChat's parse_response() method:
    assistant_response = openai_chat.parse_response(response)
    # 'assistant_response' will contain the assistant's response as a string.

7. To save and load data using the DataStorage class:
    data = {"key": "value"}
    data_storage.save_data(data)  # Save data to the file specified in the constructor.
    loaded_data = data_storage.load_data()  # Load data from the file specified in the constructor.
"""