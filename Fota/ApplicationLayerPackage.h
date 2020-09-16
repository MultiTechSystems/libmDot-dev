

#ifndef APPLICATION_LAYER_PACKAGE_H_
#define APPLICATION_LAYER_PACKAGE_H_

#include <vector>

#include "mDot.h"

#define DEFAULT_RETRY_DELAY   (5000)

enum ApplicationPackagePort {
   APP_PORT_MULTICAST      = 200,
   APP_PORT_FRAGMENTATION  = 201,
   APP_PORT_CLOCK_SYNC     = 202
};

struct ApplicationMessage {
   bool pending;
   bool is_request;
   uint8_t port;
   int16_t attempts;
   uint32_t delay;
   std::vector<uint8_t> payload;

   void reset()
   {
      payload.clear();
      attempts = 1;
      delay = 0;
      is_request = false;
      pending = false;
   }
};

class ApplicationLayerPackage
{
public:
   ApplicationLayerPackage(mDot* dot) : _dot(dot) { }
   virtual ~ApplicationLayerPackage() { }

   virtual uint8_t getPort() = 0;

   virtual void processCmd(ApplicationMessage& recv, ApplicationMessage& resp) = 0;

protected:
   mDot* _dot;
};

#endif // APPLICATION_LAYER_PACKAGE_H_