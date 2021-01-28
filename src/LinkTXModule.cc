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

#include "LinkTXModule.h"
#include <random>

Define_Module(LinkTXModule);

LinkTXModule::LinkTXModule()
{

}

LinkTXModule::~LinkTXModule()
{

}

void LinkTXModule::initialize()
{
    queue = new cQueue("queue");
    sentQueue = new cQueue("sentQueue");
    freeLinkEvent = new cMessage("freeLinkEvent");
    linkProtocol = (int) par("linkProtocol");
    // Initialize variables
    numSent = 0;
    packetFlux = 0;
    numReceived = 0;
    numACKSent = 0;
    numNACKSent = 0;
    goBackNModule = 0;
    WATCH(numSent);
    WATCH(numReceived);
    WATCH(numACKSent);
    WATCH(numNACKSent);
    WATCH(packetFlux);
}

void LinkTXModule::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(),"freeLinkEvent") == 0){
        processFreeLinkEvent();
    }else{

        MessageStructure *message= check_and_cast<MessageStructure *> (msg);

       switch(message -> getMessageType()){
           case 1: //MESSAGE
               //Received packer will be stored in the Queue to be sent
               EV << "MESSAGE packet has been received \n";
               processInputMessage(message);
               numReceived++;
               packetFlux = (numSent / simTime())*1000;
               break;
           case 2: //ACK
               //Last packet reception has been confirmed, in case any packet is waiting in the queue it will be sent
               EV << "ACK packet has been received \n";
               processACKMessage(message);
               numACKSent++;
              break;
           case 3: //NACK
               //Last packet reception has not been confirmed, it will be retransmitted again
               EV << "NACK packet has been received \n";
               processNACKMessage(message);
               numNACKSent++;
               break;
       }
    }
}

void LinkTXModule::sendPacketCopy (MessageStructure *pkt) {

    MessageStructure *pktCpy = check_and_cast<MessageStructure *> (pkt -> dup());
    numSent++;
    simtime_t service_time = (pktCpy->getPacketLength() / (double) par("linkCapability"));
    send(pktCpy, "tx$o");
    busyLink = 1;
    goBackNModule++;
    cancelEvent(freeLinkEvent);
    scheduleAt(simTime()+service_time, freeLinkEvent);

}

void LinkTXModule::processInputMessage( MessageStructure *message)
{
    switch(linkProtocol){
        case 0: //No protocol
            sendPacketCopy(message);
            cancelAndDelete(message);
            break;
        case 1: //Stop & Wait
            //If queue is empty it will be automatically sent, otherwise it will be stored
            if (queue -> isEmpty()) {
               EV << "MESSAGE packet will be automatically sent \n";
               // Even if the queue is empty the packet will be stored , just in case it needs to be retransmitted
               queue -> insert(message);
               //Once the packet is stored only a copy can be sent, the reference of the original packet is already enqueued
               sendPacketCopy(message);
            } else {
               EV << "MESSAGE packet will be enqueued\n";
               queue -> insert(message);
            }
            break;
        case 2: //Go Back N
            //If queue is empty it will be automatically sent, otherwise it will be stored
            if (queue -> isEmpty()) {
               EV << "MESSAGE packet will be automatically sent \n";
               // Even if the queue is empty the packet will be stored , just in case it needs to be retransmitted
               sentQueue -> insert(message);
               //Once the packet is stored only a copy can be sent, the reference of the original packet is already enqueued
               sendPacketCopy(message);
            } else {
               EV << "MESSAGE packet will be enqueued\n";
               queue -> insert(message);
            }
            break;
        case 3: //Selective Retransmission

            break;
    }
}

void LinkTXModule::processACKMessage( MessageStructure *message)
{
    switch(linkProtocol){
        case 0: //No protocol

            break;
        case 1: //Stop & Wait
            cancelAndDelete(message);
               if (queue -> isEmpty())
                   EV << "ACK packet arrived , but queue is empty so next packet cannot be sent \n";
               else {
                  //Confirmed packet will be deleted from the queue and next packet will be sent
                   MessageStructure *pkt = check_and_cast<MessageStructure *> ( queue -> pop());
                   cancelAndDelete(pkt);
                  if (!queue -> isEmpty()){
                      MessageStructure *pkt = check_and_cast<MessageStructure *> (queue -> front()); //Front extracts the packet w/o removing it , just in case it needs to be retransmitted
                      sendPacketCopy(pkt);
                  }else{
                      EV << "ACK packet arrived , but queue is empty so next packet cannot be sent \n";
                  }

               }
            break;
        case 2: //Go Back N
            cancelAndDelete(message);
               if (sentQueue -> isEmpty())
                   EV << "ACK packet arrived , but queue is empty so next packet cannot be sent \n";
               else {
                  //Confirmed packet will be deleted from the queue
                   MessageStructure *pkt = check_and_cast<MessageStructure *> (sentQueue -> pop());
                   cancelAndDelete(pkt);
                  if (!queue -> isEmpty() && busyLink == 0){
                      MessageStructure *pkt = check_and_cast<MessageStructure *> (queue -> pop()); //Front extracts the packet w/o removing it , just in case it needs to be retransmitted
                      sentQueue -> insert(pkt);
                      sendPacketCopy(pkt);
                  }else{
                      EV << "ACK packet arrived , but queue is empty so next packet cannot be sent \n";
                  }

               }
            break;
        case 3: //Selective Retransmission

            break;
    }
}

void LinkTXModule::processNACKMessage( MessageStructure *message)
{
    switch(linkProtocol){
           case 0: //No protocol
           {

           }
               break;
           case 1: //Stop & Wait
           {
               cancelAndDelete(message);
               MessageStructure *pkt = check_and_cast<MessageStructure *> (queue -> front()); //Front extracts the packet w/o removing it , just in case it needs to be retransmitted
               //Retransmission number will be increased
               pkt->setRetransmissionNumber(pkt->getRetransmissionNumber()+1);
               sendPacketCopy(pkt);
           }
               break;
           case 2: //Go Back N
           {
              cancelAndDelete(message);
              if (sentQueue -> isEmpty())
                  EV << "NACK packet arrived , but queue is empty so next packet cannot be sent \n";
              else {
                  //Messages
                  goBackretransmitting = 1;
                  goBackNModule = 0;
                  MessageStructure *pkt = check_and_cast<MessageStructure *> (sentQueue -> front()); //Front extracts the packet w/o removing it , just in case it needs to be retransmitted
                  sendPacketCopy(pkt);
              }
           }
               break;
           case 3: //Selective Retransmission
           {

           }
               break;
       }

}

void LinkTXModule::processFreeLinkEvent()
{
    busyLink = 0;

    switch(linkProtocol){
        case 0: //No protocol
            break;
        case 1: //Stop & Wait
            break;
        case 2: //Go Back N
            //If queue is empty it will be automatically sent, otherwise it will be stored
            if(goBackretransmitting && sentQueue -> getLength() > 1 ){
                MessageStructure *pkt = check_and_cast<MessageStructure *> (sentQueue -> get(goBackNModule-1) ); //Front extracts the packet w/o removing it , just in case it needs to be retransmitted
                sendPacketCopy(pkt);
            }else {
                if (!queue -> isEmpty() && goBackNModule < goBackNModuleMax) {
                   EV << "MESSAGE packet will be automatically sent \n";
                   MessageStructure *pkt = check_and_cast<MessageStructure *> (queue -> pop());
                   // Even if the queue is empty the packet will be stored , just in case it needs to be retransmitted
                   sentQueue -> insert(pkt);
                   //Once the packet is stored only a copy can be sent, the reference of the original packet is already enqueued
                   sendPacketCopy(pkt);
                }
                else if (goBackNModule == goBackNModuleMax){
                    EV << "Go back N module reached its maximum \n";
                }
            }



            break;
        case 3: //Selective Retransmission

            break;
    }
}


