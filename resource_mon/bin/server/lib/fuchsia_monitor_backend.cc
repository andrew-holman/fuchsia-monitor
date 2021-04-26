// // Copyright 2019 The Fuchsia Authors. All rights reserved.
// // Use of this source code is governed by a BSD-style license that can be
// // found in the LICENSE file.

// /*
// * date_proc.c - remote procedures; called by server stub.
// */
// #include <time.h>
// #include <sys/types.h>
// #include <malloc.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <pwd.h>
// #include <iostream>
// #include <fuchsia/logger/cpp/fidl.h>
// #include <zircon/syscalls/log.h>
// #include <zircon/types.h>

// #include <fuchsia/examples/cpp/fidl.h>
// #include <lib/async-loop/cpp/loop.h>
// #include <lib/async-loop/default.h>
// #include <lib/fidl/cpp/binding_set.h>
// #include <lib/sys/cpp/component_context.h>
// //#include <lib/fidl/cpp/binding.h>
// //#include <lib/gtest/real_loop_fixture.h>
// //#include <lib/sys/cpp/service_directory.h>
// //#include <lib/syslog/cpp/log_settings.h>
// //#include <lib/syslog/cpp/macros.h>
// //#include <lib/syslog/wire_format.h>

// // run "fx shell run fuchsia.com/fuchsia-monitor-backend-cpp#meta/fuchsia-monitor-backend-cpp.cmx"

// // Has sys info about boards.
// // #include <src/bringup/bin/sysinfo/sysinfo.h>

// #define MAX_LEN 1000

// char **date_menu(uint64_t option);

// // [START server]
// class Backend_MonitorImpl : public fuchsia::examples::Backend_Monitor {
//  public:
//  // I think the monitor time call back is a frontend function?
//   void MonitorTime(std::uint64_t value, MonitorTimeCallback callback) override { callback(*date_menu(value)); }
//   void SendString(std::string value) override {
//     if (event_sender_) {
//       event_sender_->OnString(value);
//     }
//   }

//   fuchsia::examples::Monitor_EventSender* event_sender_;
// };
// // [END server]

// // [START main]
// int main(int argc, const char** argv) {
//   async::Loop loop(&kAsyncLoopConfigAttachToCurrentThread);

//   Backend_MonitorImpl impl;
//   fidl::Binding<fuchsia::examples::Backend_Monitor> binding(&impl);
//   impl.event_sender_ = &binding.events();
//   fidl::InterfaceRequestHandler<fuchsia::examples::Backend_Monitor> handler =
//       [&](fidl::InterfaceRequest<fuchsia::examples::Backend_Monitor> request) {
//         binding.Bind(std::move(request));
//       };
//   auto context = sys::ComponentContext::CreateAndServeOutgoingDirectory();
//   context->outgoing()->AddPublicService(std::move(handler));

//   printf("Running monitor server\n");
//   return loop.Run();
// }
// // [END main]



// /*int main()
// {
//   long option = 1;
//   std::cout << "Hello, I'm the backend Fuchsia Monitor!\n";
//   char* response = *date_menu(&option);
//   std::cout << "Option #" << option << ": " << response << "\n";
  
//   option++;
//   response = *date_menu(&option);
//   std::cout << "Option #" << option << ": " << response << "\n";
  
//   option++;
//   response = *date_menu(&option);
//   std::cout << "Option #" << option << ": " << response << "\n";
  
  
//   return 0;
// }*/
// /*
// * Return the binary date and time.
// */
// char **date_menu(uint64_t option)
// {
//   struct tm *timeptr; /* Pointer to time structure */
//   time_t clock;       /* Clock value (in secs) */
//   static char *ptr;   /* Return string */
//   static char err[] = "Invalid Response \0";
//   static char s[MAX_LEN];
//   clock = time(0);
//   timeptr = localtime(&clock);

//   switch (option)
//   {
//   case 1:
//     strftime(s, MAX_LEN, "%A, %B %d, %Y", timeptr);
//     ptr = s;
//     break;
//   case 2:
//     strftime(s, MAX_LEN, "%T", timeptr);
//     ptr = s;
//     break;
//   case 3:
//     strftime(s, MAX_LEN, "%A, %B %d, %Y - %T", timeptr);
//     ptr = s;
//     break;
//   default:
//     ptr = err;
//     break;
//   }
//   return (&ptr);
// }

