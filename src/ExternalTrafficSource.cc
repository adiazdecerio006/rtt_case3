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

#include "ExternalTrafficSource.h"
#include <random>
#include <chrono>

Define_Module(ExternalTrafficSource);

ExternalTrafficSource::ExternalTrafficSource()
{
    sendMessageEvent = nullptr;
}

ExternalTrafficSource::~ExternalTrafficSource()
{
    cancelAndDelete(sendMessageEvent);
}

void ExternalTrafficSource::initialize()
{
    //Set variables
    meanPacketLength = (double) par("meanPacketLength");
    flowIdentifier = (double) par("flowIdentifier");
    lambda = (double) par("lambda");
    sendMessageEvent = new cMessage("sendMessageEvent");
    numSent = 0;
    packetFlux = 0;
    WATCH(numSent);
    WATCH(packetFlux);
    packetLenStats.setName("packetLenStats");
    packetLenVector.setName("packetLenVector");
    randomDepartureTimeStats.setName("randomDepartureTimeStats");
    randomDepartureTimeVector.setName("randomDepartureTimeVector");
    EV << "Initializing Source with flow identifier: " << flowIdentifier << "\n";
    double nextDepartureTime = calculateRandomDepartureTime(lambda);
    EV << "Next departure Time: " << nextDepartureTime << "\n";
    scheduleAt(simTime()+nextDepartureTime, sendMessageEvent);

}

void ExternalTrafficSource::handleMessage(cMessage *msg)
{
    ASSERT(msg == sendMessageEvent);

    MessageStructure *job = createPacket();
    numSent++;
    packetFlux = (numSent / simTime())*1000;
    send(job, "out");
    EV << "Departure Time: `" << simTime() << "\n";
    scheduleAt(simTime()+calculateRandomDepartureTime(lambda), sendMessageEvent);
}


double ExternalTrafficSource::calculateRandomDepartureTime(long lambda)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_real_distribution<double> uniformRandom(0.0, 1.0);
    double time = -(1000/lambda) * log(uniformRandom(generator));
    randomDepartureTimeVector.record(time);
    randomDepartureTimeStats.collect(time);
    //TODO Truncation!!
    return time;
}

//Packet length will be truncated to octet value
double ExternalTrafficSource::calculateRandomPacketLen(long meanPacketLength)
{
    //std::default_random_engine generator;
    //std::exponential_distribution<double> distribution(1/meanPacketLength); distribution(generator);
    //return distribution(generator);
    std::uniform_real_distribution<double> uniformRandom(0.0, 1.0);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);

    double meanPacket = -(meanPacketLength) * log(uniformRandom(generator)); // Logarithm always gives negative values
    packetLenVector.record(meanPacket);
    packetLenStats.collect(meanPacket);

    return meanPacket;
}

MessageStructure * ExternalTrafficSource::createPacket()
{
    MessageStructure * packet = new MessageStructure();
    double packetLen = calculateRandomPacketLen(meanPacketLength);
    packet->setPacketLength(packetLen);
    EV << "Generated Packet Length : " << packetLen << "\n";
    packet->setFlowIdentifier(flowIdentifier);
    packet->setFlowSequenceIdentifier(++flowSequenceNumber);
    packet->setMessageType(1); //1 refers to normal message type, 2 to ACK message type and 3 to NACK message type
    packet->setRetransmissionNumber(0);
    return packet;
}

void ExternalTrafficSource::finish()
{

    EV << "Packet len , min:    " << packetLenStats.getMin() << endl;
    EV << "Packet len, max:    " << packetLenStats.getMax() << endl;
    EV << "Packet len, mean:   " << packetLenStats.getMean() << endl;
    EV << "Packet len, stddev: " << packetLenStats.getStddev() << endl;

    packetLenStats.recordAs("Packet len count");

}

