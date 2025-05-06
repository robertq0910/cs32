#include <iostream>
#include <string>
using namespace std;

enum CallType {
    VOICE, TEXT
};

//Your declarations and implementations would go here
class Medium {
public: 
    Medium(string id) {
        m_id = id;
    }
        // Constructor
    virtual ~Medium() {}  // Destructor, can be empty inside
    virtual string connect() const = 0;
    virtual string transmit(string msg) const = 0;
    string id() const {
        return m_id;
    }  
private:
    string m_id;
};

class XAccount: public Medium {
public: 
    XAccount(string id): Medium(id) {    // Pass id to medium with INITIALIZATION LIST to access Medium's private member variable
        // To construct a derived object you have to define the base object
    }
    virtual ~XAccount() {};
    virtual string connect() const{     // Also has to be const if Medium's pure virtual function is const!
        return "Post to X ";
    }
    virtual string transmit(string msg) const {
        return "text: " + msg;
    }
};

class Phone : public Medium {
public:
    Phone(string id, CallType type) : Medium(id), m_type(type) {}
    virtual ~Phone() {};
    virtual string connect() const {
        return "Call ";
    }
    virtual string transmit(string msg) const {
        if (m_type == VOICE) {
            return "voice: " + msg;
        }
        else if (m_type == TEXT) {
            return "text: " + msg;
        }
    }
private: 
    // need data member for voice or text
    CallType m_type;
};
class EmailAccount : public Medium {
public:
    EmailAccount(string id) : Medium(id) {}
    virtual ~EmailAccount() {};
    virtual string connect() const {
        return "Email ";
    }
    virtual string transmit(string msg) const {
        return "text: " + msg;
    }
};

void send(const Medium* m, string msg)
{
    cout << m->connect() << " using id " << m->id()
        << ", sending " << m->transmit(msg) << endl;
}

int main()
{
    Medium* media[4];
    media[0] = new XAccount("UCLABruinAlert");
    // Phone users may prefer messages to be left as voice or text.
    media[1] = new Phone("(310) 825 3894", VOICE);
    media[2] = new Phone("(213) 389 9060", TEXT);
    media[3] = new EmailAccount("jbroon@ucla.edu");

    cout << "Send the message." << endl;
    for (int k = 0; k < 4; k++)
        send(media[k], "Major power outage in West L.A.");

    // Clean up the media before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete media[k];
}