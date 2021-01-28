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

simple Txc1
{
    gates:
        input in;
}
//
// Two instances (tic and toc) of Txc1 connected both ways.
// Tic and toc will pass messages to one another.
//
network Scenario
{
    @display("bgb=630,557");
    submodules:
        trafficExternalSource: ExternalTrafficSource {
            lambda = 20;
            meanPacketLength = 1000;
            flowIdentifier = 1;
            @display("p=402,34");
        }
        trafficExternalSource2: ExternalTrafficSource {
            lambda = 20;
            meanPacketLength = 1000;
            flowIdentifier = 1;
            @display("p=104,26");
        }
        trafficMuxModule: TrafficMultiplexingModule {
            linkCapability = 1000000;
            @display("p=264,215");
        }
        trafficMuxModule2: TrafficMultiplexingModule {
            linkCapability = 1000000;
            @display("p=104,215");
        }
        trafficMuxModule3: TrafficMultiplexingModule {
            linkCapability = 1000000;
            @display("p=449,223");
        }
        toc1: Txc1 {
            @display("p=264,502");
        }
        toc2: Txc1 {
            @display("p=104,502");
        }
        toc3: Txc1 {
            @display("p=449,502");
        }
        trafficRoutingModule: TrafficRoutingModule {
            @display("p=402,134");
            nodeIdentifier = 1;
        }
        trafficRoutingModule2: TrafficRoutingModule {
            @display("p=104,126");
            nodeIdentifier = 1;
        }
        linkTX: LinkTXModule {
            linkProtocol = 0;
            @display("p=263,309");
        }
        linkTX2: LinkTXModule {
            linkProtocol = 0;
            @display("p=104,310");
        }
        linkTX3: LinkTXModule {
            linkProtocol = 0;
            @display("p=452,312");
        }
        linkRX: LinkRXModule {
            linkProtocol = 0;
            lossProbability = 0.33;
            @display("p=264,392");
        }
        linkRX2: LinkRXModule {
            linkProtocol = 0;
            lossProbability = 0.5;
            @display("p=104,392");
        }
        linkRX3: LinkRXModule {
            linkProtocol = 0;
            lossProbability = 0.66;
            @display("p=449,392");
        }
    connections:
        trafficExternalSource.out --> {  delay = 0ms; } --> trafficRoutingModule.in;
        trafficExternalSource2.out --> {  delay = 0ms; } --> trafficRoutingModule2.in;
        trafficRoutingModule.out++ --> {  delay = 0ms; } --> trafficMuxModule.in++;
        trafficRoutingModule.out++ --> {  delay = 0ms; } --> trafficMuxModule2.in++;
        trafficRoutingModule.out++ --> {  delay = 0ms; } --> trafficMuxModule3.in++;
        trafficRoutingModule2.out++ --> {  delay = 0ms; } --> trafficMuxModule.in++;
        trafficRoutingModule2.out++ --> {  delay = 0ms; } --> trafficMuxModule2.in++;
        trafficRoutingModule2.out++ --> {  delay = 0ms; } --> trafficMuxModule3.in++;
        //divisor1.out++ --> {  delay = 0ms; } --> toc1.in;
        //divisor1.out++ --> {  delay = 0ms; } --> toc2.in;
        //divisor1.out++ --> {  delay = 0ms; } --> toc3.in;
        trafficMuxModule.out --> {  delay = 0ms; } --> linkTX.in;
        trafficMuxModule2.out --> {  delay = 0ms; } --> linkTX2.in;
        trafficMuxModule3.out --> {  delay = 0ms; } --> linkTX3.in;
        linkTX.tx <--> {  delay = 10ms; } <--> linkRX.rx;
        linkTX2.tx <--> {  delay = 10ms; } <--> linkRX2.rx;
        linkTX3.tx <--> {  delay = 10ms; } <--> linkRX3.rx;
        linkRX.out --> {  delay = 0ms; } --> toc1.in;
        linkRX2.out --> {  delay = 0ms; } --> toc2.in;
        linkRX3.out --> {  delay = 0ms; } --> toc3.in;

}
