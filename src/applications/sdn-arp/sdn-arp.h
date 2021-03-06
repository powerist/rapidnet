/* A RapidNet application. Generated by RapidNet compiler. */

#ifndef SDNARP_H
#define SDNARP_H

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
namespace sdnarp {

class SdnArp : public RapidNetApplicationBase
{
public:

  static TypeId GetTypeId (void);

  SdnArp ();

  virtual ~SdnArp ();

protected:

  virtual void DoDispose (void);

  virtual void StartApplication (void);

  virtual void StopApplication (void);

  virtual void InitDatabase (void);

  virtual void DemuxRecv (Ptr<Tuple> tuple);

};

} // namespace sdnarp
} // namespace rapidnet
} // namespace ns3

#endif // SDNARP_H
