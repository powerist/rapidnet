/* A RapidNet application. Generated by RapidNet compiler. */

#ifndef ARP_H
#define ARP_H

#include <string>
#include <iostream>
#include "ns3/ptr.h"
#include "ns3/event-id.h"
#include "ns3/ipv4-address.h"
#include "ns3/rapidnet-header.h"
#include "ns3/relation-base.h"
#include "ns3/database.h"
#include "ns3/rapidnet-application-base.h"
#include "ns3/aggregator.h"
#include "ns3/aggwrap.h"

using namespace std;
using namespace ns3;

namespace ns3 {

class Socket;
class Packet;

namespace rapidnet {
namespace arp {

class Arp : public RapidNetApplicationBase
{
public:
  static const string ARPMAPPING;
  static const string ARPREPLY;
  static const string ARPREPLYCTL;
  static const string ARPREQCTL;
  static const string ARPREQUEST;
  static const string FLOWENTRY;
  static const string HOSTPOS;
  static const string LINKHST;
  static const string LINKSWC;
  static const string OFCONNCTL;
  static const string OFCONNSWC;
  static const string PACKET;
  static const string PACKETIN;
  static const string PACKETOUT;

  static TypeId GetTypeId (void);

  Arp ();

  virtual ~Arp ();

protected:

  virtual void DoDispose (void);

  virtual void StartApplication (void);

  virtual void StopApplication (void);

  virtual void InitDatabase (void);

  virtual void DemuxRecv (Ptr<Tuple> tuple);

  virtual void Rh1Eca0Ins (Ptr<Tuple> linkHst);

  virtual void Rh1Eca1Ins (Ptr<Tuple> arpRequest);

  virtual void Rh2_eca (Ptr<Tuple> packet);

  virtual void Rc1_eca (Ptr<Tuple> packetIn);

  virtual void Rc2_eca (Ptr<Tuple> packetIn);

  virtual void Rc3_eca (Ptr<Tuple> arpReqCtl);

  virtual void Rc4_eca (Ptr<Tuple> arpReqCtl);

  virtual void Rc6_eca (Ptr<Tuple> arpReplyCtl);

  virtual void Rs1_eca (Ptr<Tuple> packet);

  virtual void Rs2_eca (Ptr<Tuple> packetOut);

};

} // namespace arp
} // namespace rapidnet
} // namespace ns3

#endif // ARP_H
