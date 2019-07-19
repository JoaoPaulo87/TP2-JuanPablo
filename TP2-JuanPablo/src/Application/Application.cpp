/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved.
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <string>
#include <ComponentFactory.h>
#include <ApplicationInterface.h>
#include <ComponentInterface.h>
#include <GreeterInterface.h>
#include <MessengerInterface.h>

class Application : public ApplicationInterface, public ComponentInterface
{
    public:
        Application();
        virtual ~Application();
        int run();

        //ComponentInterface:
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        int referenceCounter;
        bool implemented;
};

Application::Application() : referenceCounter(0){}

Application::~Application(){}

int Application::run()
{
    ComponentFactory* componentFactoryObject = new ComponentFactory();
//Greeter
    componentFactoryObject->setInterfaceName("GreeterInterface");
        componentFactoryObject->setInterfaceName("MessengerInterface");


    ComponentInterface* greeterComponent = componentFactoryObject->createFrom("./Greeter");
    ComponentInterface* messageComponent = componentFactoryObject->createFrom("./Message");
    GreeterInterface* greeterObject = ( (GreeterInterface*) greeterComponent->getInstance() );
    MessengerInterface* messageObject = ( (MessengerInterface*) messageComponent->getInstance() );
    greeterObject->greet("Hello");
    greeterComponent->release();
    messageObject->say();
    messageComponent->release();
    delete componentFactoryObject;
        


//Message


    

    return 0;
}

//ComponentInterface:
bool Application::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "ApplicationInterface") ?
        implemented = true
            : implemented = false;
}

void* Application::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void Application::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new Application;
}
