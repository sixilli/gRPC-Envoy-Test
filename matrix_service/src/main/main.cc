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

    int arrays_count = request->data_size();
    auto arr = request->data(0);

    std::vector<std::unique_ptr<Matrix<int32_t>>> matrices;
    matrices.reserve(arrays_count);

    for (int i = 0; i < arrays_count; i++) {
      auto arr_msg = request->data(i);
      std::vector<int32_t> vec(arr_msg.array().begin(), arr_msg.array().end());
      matrices.push_back(
        std::make_unique<Matrix<int32_t>>(vec, arr_msg.rows(), arr_msg.cols())
      );
    }

    auto result = std::make_unique<Matrix<int32_t>>(arr.rows(), arr.cols());

    for (int i = 0; i < arrays_count; i++) {
      result->add_inplace(*matrices[i]);
    }

    auto mat_data = result->ravel();
    reply->mutable_array()->Add(mat_data.begin(), mat_data.end());
    reply->set_rows(result->rows);
    reply->set_cols(result->columns);
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