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
module InputNetworkNode
{
    parameters:
        int outputLinkNumber;
        int externalTrafficGenerationLambda;
        double externalTrafficGenerationMeanPacketLength;
        int externalTrafficFlowIdentifier;
        int linkProtocolType;
        int nodeIdentifier;
        double outputLinkCapability;
        double linkPacketLossProbability;
	gates:
        inout in[];
        inout out[];  
    submodules:
        trafficExternalSource: ExternalTrafficSource {
            lambda = externalTrafficGenerationLambda;
            meanPacketLength = externalTrafficGenerationMeanPacketLength;
            flowIdentifier = externalTrafficFlowIdentifier;
        }
        
        trafficRoutingModule: TrafficRoutingModule {
            nodeIdentifier = nodeIdentifier;
        }
        
        trafficMuxModule[outputLinkNumber]: TrafficMultiplexingModule {
           linkCapability = outputLinkCapability;
        }
        
        linkTX[outputLinkNumber]: LinkTXModule {
            linkProtocol = linkProtocolType;
        }
       
  
    connections:
        
        trafficExternalSource.out --> {  delay = 0ms; } --> trafficRoutingModule.in;
        
	    for j=0..outputLinkNumber-1 {
	            trafficRoutingModule.out++ --> {  delay = 0ms; } --> trafficMuxModule[j].in++;
	    }   
	    
	    for j=0..outputLinkNumber-1 {
	             trafficMuxModule[j].out --> {  delay = 0ms; } --> linkTX[j].in;
	             linkTX[j].tx <--> {  delay = 0ms; } <--> out[j];
	    }  
	   

}
