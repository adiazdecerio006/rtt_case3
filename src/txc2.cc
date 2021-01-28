//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <string.h>
#include <omnetpp.h>
#include "message_structure_m.h"


using namespace omnetpp;

/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
class Txc2 : public cSimpleModule
{
  protected:
    // The following redefined virtual function holds the algorithm.
    int nodeIdentifier;
    cHistogram circuit15Stats;
    cOutVector circuit15Vector;
    cHistogram circuit52Stats;
    cOutVector circuit52Vector;
    cHistogram circuit24Stats;
    cOutVector circuit24Vector;
    cHistogram circuit1524Stats;
    cOutVector circuit1524Vector;
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void insertPackingTracingData( MessageStructure *message);
    virtual void getDelayFromVC (MessageStructure *message,int* vc);
    virtual void getDataFromMessage (MessageStructure *message);
};

// The module class needs to be registered with OMNeT++
Define_Module(Txc2);

void Txc2::initialize()
{
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be `tic'.
    nodeIdentifier = (int) par("nodeIdentifier");
    circuit15Stats.setName("circuit15Stats");
    circuit15Vector.setName("circuit15Vector");
    circuit52Stats.setName("circuit52Stats");
    circuit52Vector.setName("circuit52Vector");
    circuit24Stats.setName("circuit24Stats");
    circuit24Vector.setName("circuit24Vector");
    circuit1524Stats.setName("circuit1524Stats");
    circuit1524Vector.setName("circuit1524Vector");

}

void Txc2::handleMessage(cMessage *msg)
{
    MessageStructure *message= check_and_cast<MessageStructure *> (msg);
    insertPackingTracingData(message);

    int * vc = new int [4];
    vc[0] = 1;
    vc[1] = 5;
    vc[2] = 2;
    vc[3] = 4;
    getDelayFromVC(message,vc);

    cancelAndDelete(msg);
}

void Txc2::insertPackingTracingData( MessageStructure *message)
{
    int currentSize = message->getPacketHopTrackingArraySize();

    message->setPacketHopTrackingArraySize(currentSize+1);
    message->setPacketTimingTrackingArraySize(currentSize+1);
    message->setPacketHopTracking(currentSize,nodeIdentifier);
    message->setPacketTimingTracking(currentSize,simTime());

}

void Txc2::getDelayFromVC (MessageStructure *message, int* vc)
{
    int currentSize = message->getPacketHopTrackingArraySize();

    bool fromVC = false;

    if(currentSize == 4){
        fromVC = true;
        for(int i=0;currentSize < i;i++){
           if(!message->getPacketHopTracking(i) == vc[i]){
               fromVC = false;
               break;
           }
        }
    }

    if(fromVC){
        getDataFromMessage(message);
    }

}

void Txc2::getDataFromMessage (MessageStructure *message)
{
    simtime_t vc15 = message->getPacketTimingTracking(1) - message->getPacketTimingTracking(0);
    simtime_t vc52 = message->getPacketTimingTracking(2) - message->getPacketTimingTracking(1);
    simtime_t vc24 = message->getPacketTimingTracking(3) - message->getPacketTimingTracking(2);
    simtime_t vc1524 = message->getPacketTimingTracking(3) - message->getPacketTimingTracking(0);


    circuit15Stats.collect(vc15.dbl());
    circuit15Vector.record(vc15.dbl());
    circuit52Stats.collect(vc52.dbl());
    circuit52Vector.record(vc52.dbl());
    circuit24Stats.collect(vc24.dbl());
    circuit24Vector.record(vc24.dbl());
    circuit1524Stats.collect(vc1524.dbl());
    circuit1524Vector.record(vc1524.dbl());
}



