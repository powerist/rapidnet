/*
 * Sources
 * -------
 * 1) Frenetic: A Network Programming Language
 *    Nate Foster 2011, Cornell
 * 
 * 2) OpenFlow-Based Server Load Balancing Gone Wild
 *    Richard Wang, Dana Butnariu, Jennifer Rexford
 * 
 * 
 * Load Balancing - Base Tuples
 * ----------------------------
 *
 * switchConnection(@Switch1, @Switch2)
 *      Switch1 has a connection and is thus able to communicate with Switch2
 *      In this case, SwitchGateway wants to connect to SwitchLoadBalancer
 * 
 * pktClient(@Switch, Client)
 *     Switch received a packet from client
 *     In this case, SwitchGateway received a packet from a client (not sure which one)
 *
 * loadBalancerConnectionToServer(@SwitchLoadBalancer, Server)
 *    load balancer connected to all available servers
 *    In this case, SwitchLoadBalancer is connected to server (not sure which one)
 *    server is a number between 0,1,2,...,(NUM_SERVERS-1)
 *
 *
 * Load Balancing - Derived Tuples
 * ----------------------------
 *
 * pktToBalance(@SwitchDst, SwitchSrc, Client)
 *     SwitchDst received a packet (originally from Client), from SwitchSrc
 *
 * pktServer(@Server, Client)
 *     Server received a packet sent by Client
 *
 * randomlyObtainedServer(@SwitchLoadBalancer, Server, Client)
 *     SwitchLoadBalancer decided to send the packet from Client to 
 *     a particular server, called Server, using its algorithm
 *
 * Numbers
 * -------
 * 1 load balancer switch
 * 1 gateway switch
 * multiple clients
 * multipler identical servers 
 * 
 */



materialize(switchConnection, infinity, infinity, keys(1,2)).
materialize(pktClient, infinity, infinity, keys(2)).
materialize(loadBalancerConnectionToServer, infinity, infinity, keys(2:int32)).
//materialize(randomlyObtainedServer, infinity, infinity, keys(2,3)).

/*
 * SwitchGateway forwards a packet originally from the client at IPclient
 * to SwitchLoadBalance 
 */
r1 pktToBalance(@SwitchLoadBalancer, SwitchGateway, Client) :- 
	pktClient(@SwitchGateway, Client),
	switchConnection(@SwitchGateway, SwitchLoadBalancer).

/*
 * SwitchGateway sends a packet to SwitchLoadBalancer (from IPclient)
 * so that SwitchLoadBalancer can decide which server to send it to.
 * 
 * SwitchLoadBalancer does this by hashing the Client's IP address
 * to get a server
 */
r2 randomlyObtainedServer(@SwitchLoadBalancer, Server, Client) :- 
	pktToBalance(@SwitchLoadBalancer, SwitchGateway, Client),
	loadBalancerConnectionToServer(@SwitchLoadBalancer, Server),
	Value := f_hashIp(Client),
	Server := 1+f_modulo(Value, 3).

/*
 * Server received packet (originaly sent by Client), from SwitchLoadBalancer
 */
r3 pktServer(@Server, Client) :- 
	randomlyObtainedServer(@SwitchLoadBalancer, Server, Client).

































