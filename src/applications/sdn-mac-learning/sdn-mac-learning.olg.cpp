/*Database for controller*/
materialize(ofconn,infinity,infinity,keys(2)). //Openflow connection to switch
materialize(macPort,infinity,infinity,keys(2,3:int32)). //Mac-port dictionary

/*Database for switch*/
/*To account for non-matching scenario,*/
/*we assume there is always a flow entry corresponding to "default" action*/
materialize(packet,infinity,infinity,keys(2,3:str,4:str)). //Packets to be sent
materialize(ofconn,infinity,infinity,keys(2)). //Openflow connection to controller
materialize(missEntry,infinity,infinity,keys(2:str)). //For packets that match no rule
materialize(flowEntry,infinity,infinity,keys(2:str)). //Flow table at switch
materialize(inPort,infinity,infinity,keys(3:int32)). //Inport table
materialize(outPort,infinity,infinity,keys(3:int32)). //Outport table

/*Controller program*/
/*Record mac-port mapping*/
rc1 macPort(@C, Switch, InPort, SrcMac) :-
	ofconn(@C, Switch),
	ofPacket(@C, Switch, InPort, SrcMac, DstMac).
	
/*Install rules on switch*/
rc2 flowMod(@Switch, DstMac, OutPort) :-
	ofconn(@C, Switch),
	ofPacket(@C, Switch, Inport, SrcMac, DstMac),
	macPort(@C, Switch, OutPort, DstMac).

/*Switch program*/
/*Query the controller when receiving unknown packets */
rs1 ofPacket(@C, S, InPort, SrcMac, DstMac) :-
	ofconn(@S, C),
	packet(@S, Nei, SrcMac, DstMac),
	inPort(@S, Nei, InPort),
	missEntry(@S, DstMac).

/*Install rules locally per instructions from controller*/
rs2 flowEntry(@S, Mac, OutPort) :-
	flowMod(@S, Mac, OutPort).

rs3 delete missEntry(@S, Mac) :-
	flowMod(@S, Mac, OutPort).
	
/*Forward accordingly if a flow entry exists for the packet*/
/*How do we specify the sending action on port?*/
rs4 packet(@OutNei, S, SrcMac, DstMac) :-
	packet(@S, InNei, SrcMac, DstMac),
	inPort(@S, InNei, InPort),
	outPort(@S, OutNei, OutPort),	
	flowEntry(@S, DstMac, OutPort).



	
