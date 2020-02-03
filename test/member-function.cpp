#include <ArduinoUnitTests.h>
#include "../src/aWOT.h"
#include "./mocks/MockStream.h"

class Handler {
 public:
  Handler() {};
  ~Handler() {}

  void handle(Request & req, Response & res) {
    res.set("Content-Type", "text/plain");
    res.print("test");
  }
};

unittest(member_function) {
  char const *request =
    "GET / HTTP/1.0" CRLF
    CRLF;

  char const *expected =
    "HTTP/1.1 200 OK" CRLF
    "Content-Type: text/plain" CRLF
    "Connection: close" CRLF
    CRLF
    "test";

  MockStream stream(request);
  Application app;
  Handler handler;

  app.get("/", std::bind(&Handler::handle, handler, std::placeholders::_1, std::placeholders::_2));
  app.process(&stream);

  assertEqual(expected, stream.response());
}

unittest_main()
