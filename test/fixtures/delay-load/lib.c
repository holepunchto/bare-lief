#include <windows.h>

__declspec(dllexport) int
foo() {
  return GetSystemMetrics(SM_CXSCREEN);
}
