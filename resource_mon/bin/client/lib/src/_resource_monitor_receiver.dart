import 'package:fidl/fidl.dart';
import 'package:fidl_fuchsia_services_examples/fidl_async.dart';

class ResourceMonitorRecieverImp extends ResourceMonitorFrontend {
  static const String serviceName = ResourceMonitorFrontend.$serviceName;
  final _binding = ResourceMonitorFrontendBinding();
  void bind(InterfaceRequest<ResourceMonitorFrontend> request) =>
      _binding.bind(this, request);
}
