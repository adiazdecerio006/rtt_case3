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
network NetworkNodeExample
{
    @display("bgb=630,557");
    submodules:
        trafficExternalSource: ExternalTrafficSource {
            lambda = 20;
            meanPacketLength = 1000;
            flowIdentifier = 1;
            @display("p=14.586,21.318");
        }
        trafficMuxModule: TrafficMultiplexingModule {
            linkCapability = 1000000;
            @display("p=209.81401,310.794");
        }
        trafficMuxModule2: TrafficMultiplexingModule {
            linkCapability = 1000000;
            @display("p=415.14,306.306");
        }
        trafficRoutingModule: TrafficRoutingModule {
            @display("p=1.122,116.688");
            nodeIdentifier = 1;
        }
        trafficRoutingModule2: TrafficRoutingModule {
            @display("p=304.062,169.42201");
            nodeIdentifier = 1;
        }
        trafficRoutingModule3: TrafficRoutingModule {
            @display("p=605.88,46.002003");
            nodeIdentifier = 1;
        }
        linkTX: LinkTXModule {
            linkProtocol = 0;
            @display("p=205.326,410.652");
        }
        linkTX2: LinkTXModule {
            linkProtocol = 0;
            @display("p=417.384,415.14");
        }
        linkRX: LinkRXModule {
            linkProtocol = 0;
            lossProbability = 0.33;
            @display("p=304.062,54.978");
        }
        linkRX2: LinkRXModule {
            linkProtocol = 0;
            lossProbability = 0.5;
            @display("p=627.198,139.128");
        }
    connections:
        trafficExternalSource.out --> {  delay = 0ms; } --> trafficRoutingModule.in;
        linkRX.out --> {  delay = 0ms; } --> trafficRoutingModule2.in;
        linkRX2.out --> {  delay = 0ms; } --> trafficRoutingModule3.in;
        trafficRoutingModule2.out++ --> {  delay = 0ms; } --> trafficMuxModule.in++;
        trafficRoutingModule2.out++ --> {  delay = 0ms; } --> trafficMuxModule2.in++;
        trafficMuxModule.out --> {  delay = 0ms; } --> linkTX.in;
        trafficMuxModule2.out --> {  delay = 0ms; } --> linkTX2.in;
}
