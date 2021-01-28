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


//
// Two instances (tic and toc) of Txc1 connected both ways.
// Tic and toc will pass messages to one another.
//
network Case3Scenario
{
    parameters:
        int linkProtocol;
        double linkPacketLossProbability;
        double meanPacketLength;
        int lambda;
        double linkCapability;
        double linkdelay @unit(s);
        @display("bgb=564,395");
    submodules:
        networkNode1: InputNetworkNode {
            outputLinkNumber = 2;
            externalTrafficGenerationLambda = lambda;
            externalTrafficGenerationMeanPacketLength = meanPacketLength;
            externalTrafficFlowIdentifier = 1;
            linkProtocolType = linkProtocol;
            nodeIdentifier = 1;
            outputLinkCapability = linkCapability;
            linkPacketLossProbability = linkPacketLossProbability;
            @display("p=54,135");
        }
        networkNode2: NetworkNode2Input {

            inputLinkNumber = 2;
            outputLinkNumber = 2;
            externalTrafficGenerationLambda = lambda;
            externalTrafficGenerationMeanPacketLength = meanPacketLength;
            externalTrafficFlowIdentifier = 2;
            linkProtocolType = linkProtocol;
            nodeIdentifier = 2;
            outputLinkCapability = linkCapability;
            linkPacketLossProbability = linkPacketLossProbability;
            @display("p=183,74");
        }
        networkNode5: NetworkNode {
            inputLinkNumber = 1;
            outputLinkNumber = 2;
            externalTrafficGenerationLambda = lambda;
            externalTrafficGenerationMeanPacketLength = meanPacketLength;
            externalTrafficFlowIdentifier = 5;
            linkProtocolType = linkProtocol;
            nodeIdentifier = 5;
            outputLinkCapability = linkCapability;
            linkPacketLossProbability = linkPacketLossProbability;
            @display("p=167,193");
        }
        toc3: EndNetworkNode {
            @display("p=382,91");
            inputLinkNumber = 1;
            linkProtocolType = linkProtocol;
            linkPacketLossProbability = linkPacketLossProbability;
            nodeIdentifier = 3;
        }
        toc4: EndNetworkNode {
            @display("p=340,202");
            inputLinkNumber = 2;
            linkProtocolType = linkProtocol;
            linkPacketLossProbability = linkPacketLossProbability;
            nodeIdentifier = 4;
        }
    connections:
        networkNode1.out++ <--> {  delay = linkdelay; } <--> networkNode5.in++;
        networkNode1.out++ <--> {  delay = linkdelay; } <--> networkNode2.in++;
        networkNode5.out++ <--> {  delay = linkdelay; } <--> networkNode2.in++;
        networkNode5.out++ <--> {  delay = linkdelay; } <--> toc4.in++;
        networkNode2.out++ <--> {  delay = linkdelay; } <--> toc4.in++;
        networkNode2.out++ <--> {  delay = linkdelay; } <--> toc3.in++;


}
