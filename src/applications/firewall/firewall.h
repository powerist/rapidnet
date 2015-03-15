/* A RapidNet application. Generated by RapidNet compiler. */

#ifndef FIREWALL_H
#define FIREWALL_H

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
namespace firewall {

class Firewall : public RapidNetApplicationBase
{
public:
  static const string CONTROLLERCONNECTION;
  static const string OPENCONNECTIONTOCONTROLLER;
  static const string PERFLOWRULE;
  static const string PERFLOWRULESEND;
  static const string PKTFROMSWITCH;
  static const string PKTIN;
  static const string PKTRECEIVED;
  static const string R2TRUSTEDCONTROLLERMEMORYSEND;
  static const string TRUSTEDCONTROLLERMEMORY;
  static const string TRUSTEDCONTROLLERMEMORYDELETE;
  static const string TRUSTEDCONTROLLERMEMORYSEND;

  static TypeId GetTypeId (void);

  Firewall ();

  virtual ~Firewall ();

protected:

  virtual void DoDispose (void);

  virtual void StartApplication (void);

  virtual void StopApplication (void);

  virtual void InitDatabase (void);

  virtual void DemuxRecv (Ptr<Tuple> tuple);

  virtual void R1Eca0Ins (Ptr<Tuple> pktIn);

  virtual void R2Eca0RemoteIns (Ptr<Tuple> r2trustedControllerMemorysend);

  virtual void R2Eca0RemoteDel (Ptr<Tuple> trustedControllerMemoryDelete);

  virtual void R2Eca0Ins (Ptr<Tuple> pktIn);

  virtual void R2Eca0Del (Ptr<Tuple> pktIn);

  virtual void R2Eca1Ins (Ptr<Tuple> openConnectionToController);

  virtual void R2Eca1Del (Ptr<Tuple> openConnectionToController);

  virtual void Eca0RemoteIns (Ptr<Tuple> trustedControllerMemorysend);

  virtual void Eca0Ins (Ptr<Tuple> pktIn);

  virtual void Eca1Ins (Ptr<Tuple> openConnectionToController);

  virtual void Eca0Ins (Ptr<Tuple> pktIn);

  virtual void Eca1Ins (Ptr<Tuple> perFlowRule);

  virtual void _eca (Ptr<Tuple> controllerConnection);

  virtual void ECAMat (Ptr<Tuple> perFlowRulesend);

  virtual void _eca (Ptr<Tuple> pktFromSwitch);

  virtual void Eca0Ins (Ptr<Tuple> perFlowRule);

  virtual void Eca1Ins (Ptr<Tuple> pktIn);

};

} // namespace firewall
} // namespace rapidnet
} // namespace ns3

#endif // FIREWALL_H
