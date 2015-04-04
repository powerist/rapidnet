/*
 * 
 *                                    Host
 *                Controller            |
 *                  |\       \          |
 *                  | \       \         |
 *                  |  \       \---- Switch1 ----- Host
 *                  |   \              /           /
 *                  |    \            /           /
 *                  |     \          /           /           
 *                  |      \        /           /        
 * IncomingPacket ------- LoadBalancer ------------- Switch2 ----- Host
 *                  |               \         /
 *                  |                \       /
 *                  |                 \     /
 *                  |                  \   /
 *                  ---------------- Switch3 ----- Host
 *                                      |
 *                                      |
 *                                      |
 *                                     Host
 *
 *
 * Packets always end up on the load balancer
 * The load balancer decides which switch of the several possible ones the packet gets routed to
 * The switch the packet ends up on, does what sdn-mac-learning-bcast is to do
 */







/* ***************************** Database **************************** */

/* Database for LoadBalancer */
materialize(switchMapping, infinity, infinity, keys(2,3:int32)).

/*Database for controller*/
materialize(ofconn,infinity,infinity,keys(2)). /*Openflow connection to switch*/

/*Database for switch*/
materialize(ofconn,infinity,infinity,keys(2)). /*Openflow connection to controller*/
materialize(flowEntry,infinity,infinity,keys(2:str)). /*Flow table at switch*/
materialize(link,infinity,infinity,keys(2)). /*Neighboring relationship*/
materialize(maxPriority,infinity,1,keys(1)). /*Records the maximum priority, initial value == 0*/

/*Database for host*/
materialize(initPacket,infinity,infinity,keys(2,3:str,4:str)). /*Packet for simulation initialization*/
materialize(recvPacket,infinity,infinity,keys(2:str,3:str)). /*Packet for simulation initialization*/

/* ***************************** Database **************************** */








/* *********************** Controller program ************************ */

/*Install rules on switch*/
rc1 flowMod(@Switch, SrcMac, InPort) :-
	ofconn(@Controller, Switch),
	ofPacket(@Controller, Switch, InPort, SrcMac, DstMac).

/*Instruct the switch to send out the unmatching packet*/
rc2 broadcast(@Switch, InPort, SrcMac, DstMac) :-
	ofconn(@Controller, Switch),
	ofPacket(@Controller, Switch, InPort, SrcMac, DstMac).

/* *********************** Controller program ************************ */








/* *********************** Switch program ************************ */

/*Query the controller when receiving unknown packets */
rs1 matchingPacket(@Switch, SrcMac, DstMac, InPort, TopPriority) :-
	packet(@Switch, Nei, SrcMac, DstMac),
	link(@Switch, Nei, InPort),
	maxPriority(@Switch, TopPriority).

/*Recursively matching flow entries*/
rs2 matchingPacket(@Switch, SrcMac, DstMac, InPort, NextPriority) :-
	matchingPacket(@Switch, SrcMac, DstMac, InPort, Priority),
	flowEntry(@Switch, MacAdd, OutPort, Priority),
	Priority > 0,
	DstMac != MacAdd,
	NextPriority := Priority - 1.

/*A hit in flow table, forward the packet accordingly*/
rs3 packet(@OutNei, Switch, SrcMac, DstMac) :-
	matchingPacket(@Switch, SrcMac, DstMac, InPort, Priority),
	flowEntry(@Switch, MacAdd, OutPort, Priority),
	link(@Switch, OutNei, OutPort),
	Priority > 0,
	DstMac == MacAdd.

/*If no flow matches, send the packet to the controller*/
rs4 ofPacket(@Controller, Switch, InPort, SrcMac, DstMac) :-
	ofconn(@Switch, Controller),
	matchingPacket(@Switch, SrcMac, DstMac, InPort, Priority),
	Priority == 0.

/*Insert a flow entry into forwarding table*/
/*(TODO): We assume all flow entries are independent, which is not general*/
rs5 flowEntry(@Switch, DstMac, OutPort, Priority) :-
	flowMod(@Switch, DstMac, OutPort),
	ofconn(@Switch, Controller),
	maxPriority(@Switch, TopPriority),
	Priority := TopPriority + 1.

/*TODO: should be a_MAX<Priority> in the head tuple*/
rs6 maxPriority(@Switch, Priority) :-
	flowEntry(@Switch, DstMac, OutPort, Priority).

/*Following the controller's instruction, send out the packet as broadcast*/
rs7 packet(@OutNei, Switch, SrcMac, DstMac) :-
	broadcast(@Switch, InPort, SrcMac, DstMac),
	link(@Switch, OutNei, OutPort),
        OutPort != InPort.

/* *********************** Switch program ************************ */








/* ********************* Load Balancer program ******************* */

/* 
 * Load balancer has a packet on it
 * It hashes the mac value of the source, to decide which of several switches to send it to 
 */
lb1 randomlyObtainedSwitch(@LoadBalancer, SwitchNum, Host, SrcMac, DstMac) :- 
	lbPacket(@LoadBalancer, Host, SrcMac, DstMac),
	Value := f_hashIp(Host),
	SwitchNum := 1+f_modulo(Value, 3).

/* Get the mapping of SwitchNum to actual Switch
 * switchMapping mapst the load balancer to a switch (several of them)
 */
lb2 packet(@Switch, Host, SrcMac, DstMac) :-
	randomlyObtainedSwitch(@LoadBalancer, SwitchNum, Host, SrcMac, DstMac),
	switchMapping(@LoadBalancer, Switch, SwitchNum).

/* ********************* Load Balancer program ******************* */







/* ************************ Host program ************************* */

/* 
 * Packet initialization
 * Host with mac address SrcMac decides to send a packet to a host with mac address DstMac
 * To do so, it must send the packet to LoadBalancer first, 
 * which chooses which switch to route the packet to
 */
rh1 lbPacket(@LoadBalancer, Host, SrcMac, DstMac) :-
	initPacket(@Host, LoadBalancer, SrcMac, DstMac).

/*Receive a packet*/
rh2 recvPacket(@Host, SrcMac, DstMac) :-
	packet(@Host, Switch, SrcMac, DstMac),
	link(@Host, Switch, InPort).

/* ************************ Host program ************************* */







