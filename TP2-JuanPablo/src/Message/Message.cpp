/**
* Copyright (c) 2015 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <string>
#include <GreeterInterface.h>
#include <ComponentInterface.h>

class Message : public GreeterInterface, public ComponentInterface
{
    public:
        Message();
        virtual ~Message();
        void sendMessage(std::string word);
        std::string word;


        //ComponentInterface:
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        int referenceCounter;
        bool implemented;
};

Message::Message() : referenceCounter(0){}

Message::~Message(){}

void Message::sendMessage(std::string word)
{
    std::cout << "I am a message and the message is: " << word << std::endl;
}

//ComponentInterface:
bool Message::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "GreeterInterface") ?
        implemented = true
            : implemented = false;
}

void* Message::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void Message::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new Message();
}
//object of abstract class type "Message" is not allowed: -- pure virtual function "GreeterInterface::greet" has no overrider
