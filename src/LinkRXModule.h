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
class LinkRXModule : public cSimpleModule
{
  private:
    int linkProtocol; // Assumed to be always Stop & Wait
    double lossProbability;
  public:
    LinkRXModule();
    virtual ~LinkRXModule();
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void sendACKBack ();
    virtual void sendNACKBack ();
    virtual bool isPacketErroneus();
    virtual void processInputMessage( MessageStructure *message);
    virtual void processACKMessage( MessageStructure *message);
    virtual void processNACKMessage( MessageStructure *message);
};



#endif
