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

#include "TrafficRoutingModule.h"
#include <random>
#include <chrono>


Define_Module(TrafficRoutingModule);

TrafficRoutingModule::TrafficRoutingModule()
{

}

TrafficRoutingModule::~TrafficRoutingModule()
{

}

void TrafficRoutingModule::initialize()
{
    nodeIdentifier = (int) par("nodeIdentifier");

    switch(nodeIdentifier){
    case 1:
        routingList =  new routingWeigths[2];
            routingList[0].linkIdentifier = 0;
            routingList[0].probability = 0.25;
            routingList[1].linkIdentifier = 1;
            routingList[1].probability = 0.75;
        break;
    case 2:
        routingList =  new routingWeigths[2];
            routingList[0].linkIdentifier = 0;
            routingList[0].probability = 0.3333333;
            routingList[1].linkIdentifier = 1;
            routingList[1].probability = 0.6666667;
        break;
    case 5:
        routingList =  new routingWeigths[2];
            routingList[0].linkIdentifier = 0;
            routingList[0].probability = 0.5;
            routingList[1].linkIdentifier = 1;
            routingList[1].probability = 0.5;
        break;
    }
    //Set variables
    gateIDStats.setName("gateIDStats");
    gateIDVector.setName("gateIDVector");
    randomNumberStats.setName("randomNumberStats");
    randomNumberVector.setName("randomNumberVector");

}

void TrafficRoutingModule::handleMessage(cMessage *msg)
{
    EV <<"TrafficRoutingModule handling Message \n";
    MessageStructure *message= check_and_cast<MessageStructure *> (msg);
    insertPackingTracingData(message);
    send(message,"out",calculateOutputGateId());
}

int TrafficRoutingModule::calculateOutputGateId()
{

    std::uniform_real_distribution<double> uniformRandom(0.0, 1.0);
    // construct a trivial random generator engine from a time-based seed:
     unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
     std::default_random_engine generator (seed);

    double randomResult = uniformRandom(generator);

    EV <<"TrafficRoutingModule: " << nodeIdentifier <<" RandomResult: " << randomResult << "\n";

    int i = 0;
    float accumulatedRoutingWeigth = 0;
    int gateId = 0;

    do{
        accumulatedRoutingWeigth += routingList[i].probability;
        gateId = routingList[i++].linkIdentifier;
    }while(randomResult > accumulatedRoutingWeigth);

    EV <<"Gate id: " << gateId << " nodeIdentifier: " << nodeIdentifier  << "\n";
    gateIDVector.record(gateId);
    gateIDStats.collect(gateId);
    randomNumberVector.record(randomResult);
    randomNumberStats.collect(randomResult);



    return gateId;
}

void TrafficRoutingModule::insertPackingTracingData( MessageStructure *message)
{
    int currentSize = message->getPacketHopTrackingArraySize();

    message->setPacketHopTrackingArraySize(currentSize+1);
    message->setPacketTimingTrackingArraySize(currentSize+1);
    message->setPacketHopTracking(currentSize,nodeIdentifier);
    message->setPacketTimingTracking(currentSize,simTime());

}

void TrafficRoutingModule::finish()
{

    EV << "Gate ID , min:    " << gateIDStats.getMin() << endl;
    EV << "Gate ID, max:    " << gateIDStats.getMax() << endl;
    EV << "Gate ID, mean:   " << gateIDStats.getMean() << endl;
    EV << "Gate ID, stddev: " << gateIDStats.getStddev() << endl;

    EV << "random Number , min:    " << randomNumberStats.getMin() << endl;
    EV << "random Number, max:    " << randomNumberStats.getMax() << endl;
    EV << "random Number, mean:   " << randomNumberStats.getMean() << endl;
    EV << "random Number, stddev: " << randomNumberStats.getStddev() << endl;

    randomNumberStats.recordAs("GAte ID count");
    gateIDStats.recordAs("Number count");

}
