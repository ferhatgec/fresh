#include <fescript/modules/fescript_os.hpp>
#include <freshengine.hpp>
#include <iostream>

#ifdef _WIN32
#   include <Windows.h>
#   include <conio.h>
#else
#   include <unistd.h>
#   include <termios.h>
#endif

#define SIZE 128

namespace fescript {
__idk_nodiscard Object FescriptOSPlatform::call(Interpreter &interpreter, std::vector<Object> arguments) {
#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
  return "win32";
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
  return "darwin";
#elif defined(__linux__) || defined(linux) || defined(__linux) || defined(__gnu_linux__)
  return "linux";
#elif defined(__ANDROID__)
  return "android";
#elif (defined(__FreeBSD_kernel__) && defined(__GLIBC__)) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
  return "freebsd";
#elif defined(__DragonFly__)
  return "dragonfly";
#elif defined(__OpenBSD__)
  return "openbsd";
#elif defined(__NetBSD__)
  return "netbsd";
#else
  return "";
#endif
}

__idk_nodiscard Object FescriptOSExec::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_STRING("OS_exec()", 1)
  char buffer[SIZE];
  std::string result;
  FILE* file = popen(std::get<StringIndex>(arguments.front()).data(), "r");
  if(!file)
    return "";
  while(!feof(file))
    if(fgets(buffer, SIZE, file) != nullptr)
      result += buffer;
  pclose(file);
  return result;
}

__idk_nodiscard Object FescriptOSArch::call(Interpreter &interpreter, std::vector<Object> arguments) {
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_AMD64)
  return "amd64";
#elif defined(__arm__) || defined(_M_ARM) || defined(_M_ARMT)
  return "arm";
#elif defined(__aarch64__)
  return "arm64";
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(__X86__) || defined(_M_IX86) || defined(_M_I86)
  return "x86";
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__)
  return "powerpc";
#elif defined(__sparc__) || defined(__sparc)
  return "sparc";
#else
  return "";
#endif
}

// output: string
__idk_nodiscard Object FescriptOSGetClipboardText::call(fescript::Interpreter& interpreter, std::vector <Object> arguments) {
  return std::string(fresh::Engine::get_instance()->get_clipboard_resource().get_clipboard_data().data());
}

// output: nil
__idk_nodiscard Object FescriptOSSetClipboardText::call(fescript::Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("OS_set_clipboard_text", 1)
  fresh::Engine::get_instance()->get_clipboard_resource().get_clipboard_data() = std::get<StringIndex>(arguments.front()).data();
  fresh::Engine::get_instance()->get_clipboard_resource().sync_clipboard_data();
  return nullptr;
}
}