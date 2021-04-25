import 'dart:async';

import 'package:fidl/fidl.dart';
import 'package:fidl_fuchsia_services_examples/fidl_async.dart';

class ResourceMonitorRecieverImp extends ResourceMonitor {
  final _binding = ResourceMonitorBinding();
  void bind(InterfaceRequest<ResourceMonitor> request) =>
      _binding.bind(this, request);
}
