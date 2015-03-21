/* 
 *  ===============
 * ||   SDN ARP   ||
 *  ===============
 * Controller serves as ARP agent
 *
 * Base Tuples
 * -----------
 * 
 * arpRequest(@Host, SrcIp, SrcMac, DstIp, DstMac)
 * 
 * linkHst(@Host, Switch, Port)
 * 
 * Derived Tuples
 * --------------
 * packet(@Switch, Host, Dst, PktLoad)
 *     Switch Received packet sent from Host, to be forwarded to Dst. 
 *     DstMac, DstIp, SrcMac, SrcIp, ARP_REQUEST, ARP_TYPE
 */

/*Constants*/









/*Database for controller*/
materialize(ofconnCtl,infinity,infinity,keys(2)). //Openflow connection to switches
/*Arguments: (controller, switch)*/
materialize(arpMapping,infinity,infinity,keys(2)). //Ip=>MAC mapping
/*Arguments: (controller, ip, mac)*/
materialize(hostPos,infinity,infinity,keys(2)). //Position of host
/*Arguments: (controller, host, switch, port)*/

/*Database for switch*/
materialize(ofconnSwc,infinity,infinity,keys(2)). //Openflow connection to controller
/*Arguments: (switch, controller)*/
materialize(linkSwc,infinity,infinity,keys(3:int32)). //Inter-switch and switch-host connections
/*Arguments: (switch, switch/host, port)*/
materialize(flowEntry,infinity,infinity,keys(2:str)). //Flow table at switch
/*Arguments: (switch, match, priority, action)*/

/*Database for host*/
materialize(linkHst,infinity,infinity,keys(3:int32)). //Host-switch connection
/*Arguments: (host, switch, port)*/
materialize(arpRequest,infinity,infinity,keys(2,3:str,4,5:str)). //ARP requests
/*Arguments: (host, src_ip, src_mac, dst_ip, dst_mac)*/
materialize(arpReply,infinity,infinity,keys(2,3:str,4,5:str)). //ARP replys
/*Arguments: (host, src_ip, src_mac, dst_ip, dst_mac)*/

/*Non-materialized tuple:*/
/*packet(@Nexthop, Src, Dst, Packet_load)*/
/*packetOut(@Switch, Controller, Port, Packet)*/
/*packetIn(@Controller, Switch, InPort, Pkt)*/


/*Host program*/
/*Send ARP request to directly connected switch*/
rh1 packet(@Switch, Host, Dst, DstMac, DstIp, SrcMac, SrcIp, Req, Type) :-
	linkHst(@Host, Switch, Port),
	arpRequest(@Host, SrcIp, SrcMac, DstIp, DstMac),
	Req := 1,
	Type := "ARP",
	Dst := "ff:ff:ff:ff:ff".







