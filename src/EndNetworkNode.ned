package case3;
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
simple Txc2
{
    parameters:
        int nodeIdentifier;
    gates:
        input in;
}
//
// Two instances (tic and toc) of Txc1 connected both ways.
// Tic and toc will pass messages to one another.
//
module EndNetworkNode
{
    parameters:
        int inputLinkNumber;
        int linkProtocolType;
        double linkPacketLossProbability;
        int nodeIdentifier;
        
	gates:
        inout in[];
    submodules:
        linkRX[inputLinkNumber]: LinkRXModule {
            linkProtocol = linkProtocolType;
            lossProbability = linkPacketLossProbability;
        }
        tx2[inputLinkNumber]: Txc2 {
            nodeIdentifier = nodeIdentifier;
        }
  
    connections:
        
        for i=0..inputLinkNumber-1 {
	            in[i] <--> {  delay = 0ms; } <--> linkRX[i].rx;
	            linkRX[i].out --> {  delay = 0ms; } -->tx2[i].in;
    
	    }
}
