#include "matrix.h"
#include <iostream>
#include <memory>
#include <string>

#include <grpc/grpc.h>
#include <grpc++/grpc++.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include "main/schema.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;
using grpc::StatusCode;

using routeguide::RouteGuide;
using routeguide::MatrixRequest;
using routeguide::MatrixArr;

class RouteGuideImpl final : public RouteGuide::Service {
  Status GetMatrixAddition(ServerContext* context, 
                           const MatrixRequest* request, 
                           MatrixArr* reply) override {
    std::vector<int> mat{1,2,3,4};
    for (int i = 0; i < mat.size(); i++) {
      reply->set_data(i, mat[i]);
    }
    reply->set_rows(2);
    reply->set_cols(2);
    return Status::OK;
  }
};

void RunServer() {
  std::string address = "0.0.0.0";
  std::string port = "9001";
  std::string server_address = address + ":" + port;
  RouteGuideImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "C++ server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}