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

#ifndef __CASE3_EXTERNALTRAFFICSOURCE_H_
#define __CASE3_EXTERNALTRAFFICSOURCE_H_

#include <omnetpp.h>
#include "message_structure_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class ExternalTrafficSource : public cSimpleModule
{
private:
  cMessage *sendMessageEvent;
  long lambda;
  long meanPacketLength;
  int flowIdentifier= 0;
  int flowSequenceNumber = 0;
  cHistogram packetLenStats;
  cOutVector packetLenVector;
  cHistogram randomDepartureTimeStats;
  cOutVector randomDepartureTimeVector;
  long numSent;
  double packetFlux;

public:
  ExternalTrafficSource();
  virtual ~ExternalTrafficSource();

protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
  virtual double calculateRandomDepartureTime(long lambda);
  virtual double calculateRandomPacketLen(long meanPacketLength);
  virtual MessageStructure * createPacket();
  virtual void finish();
};

#endif
