#define DECLARE_MESSAGE(msg) static UINT msg = ::RegisterWindowMessage(msg##_MSG);
