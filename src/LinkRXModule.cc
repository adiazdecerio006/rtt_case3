//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "LinkRXModule.h"
#include <random>

Define_Module(LinkRXModule);

LinkRXModule::LinkRXModule()
{

}

LinkRXModule::~LinkRXModule()
{

}

void LinkRXModule::initialize()
{
    //Set variables
    linkProtocol = (int) par("linkProtocol");
    lossProbability = (double) par("lossProbability");
}

void LinkRXModule::handleMessage(cMessage *msg)
{


    if(!msg){
        return;
    }

    MessageStructure *message = check_and_cast<MessageStructure *> (msg);

    switch(message -> getMessageType()){
        case 1: //MESSAGE
            //Received packer will be stored in the Queue to be sent
            EV << "MESSAGE packet has been received \n";
            processInputMessage(message);

            break;
        case 2: //ACK
            //ACK will not be received
            EV << "ACK packet has been received \n";
            processACKMessage(message);
           break;
        case 3: //NACK
            //NACK will not be received
            EV << "NACK packet has been received \n";
            processNACKMessage(message);

            break;
    }
 }

 void LinkRXModule::processInputMessage( MessageStructure *message)
 {
     switch(linkProtocol){
         case 0: //No protocol
             send(message, "out");
             break;
         case 1: //Stop & Wait
         case 2: //Go Back N
             //Check if received packet contains any error
                EV << "MESSAGE packet has been received \n";
                if (isPacketErroneus()){
                    //Packet contains error
                    sendNACKBack();
                    cancelAndDelete(message);
                }else{
                    //Packet does not contain error
                    sendACKBack();
                    //Packet will be forwarded
                    message->setRetransmissionNumber(0);
                    send(message, "out");
                }

             break;
         case 3: //Selective Retransmission

             break;
     }
 }

 void LinkRXModule::processACKMessage( MessageStructure *message)
 {
     switch(linkProtocol){
             case 0: //No protocol
             {

             }
                 break;
             case 1: //Stop & Wait
             {

             }
                 break;
             case 2: //Go Back N
             {

             }
                 break;
             case 3: //Selective Retransmission
             {

             }
                 break;
         }
 }

 void LinkRXModule::processNACKMessage( MessageStructure *message)
 {
     switch(linkProtocol){
            case 0: //No protocol
            {

            }
                break;
            case 1: //Stop & Wait
            {

            }
                break;
            case 2: //Go Back N
            {

            }
                break;
            case 3: //Selective Retransmission
            {

            }
                break;
        }

 }

void LinkRXModule::sendACKBack () {
    MessageStructure *ack = new MessageStructure("ack");
    ack -> setMessageType(2);
    send(ack, "rx$o");

}

void LinkRXModule::sendNACKBack () {
    MessageStructure *nack = new MessageStructure("nack");
    nack -> setMessageType(3);
    send(nack, "rx$o");

}

bool LinkRXModule::isPacketErroneus(){
    std::uniform_real_distribution<double> uniformRandom(0.0, 1.0);
    std::default_random_engine generator(time(NULL));
    double randomResult = uniformRandom(generator);
    if(randomResult >= lossProbability){
        return false;
    }else{
        return true;
    }

}


