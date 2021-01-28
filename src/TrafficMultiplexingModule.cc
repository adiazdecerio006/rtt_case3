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

#include "TrafficMultiplexingModule.h"
#include <random>

Define_Module(TrafficMultiplexingModule);

using namespace omnetpp;

simtime_t TrafficMultiplexingModule::startService(cMessage *msg)
{
    //Calculate the service time of each message
    MessageStructure* packet = check_and_cast<MessageStructure *> (msg);
    simtime_t service_time = (packet->getPacketLength() / (double) par("linkCapability"));

    EV << "Starting service of " << msg->getName() << " with service time:  "<< service_time << endl;

    return service_time;
}

void TrafficMultiplexingModule::endService(cMessage *msg)
{
    EV << "Completed service of " << msg->getName() << endl;
    send(msg, "out");
}

