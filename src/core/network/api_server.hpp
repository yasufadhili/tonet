/*
 * Filename: /home/yasufadhili/DEV/Tonet/tonet/src/core/network/api_server.hpp
 * Path:tonet/src/core/network
 * Created Date: Tuesday 12th November, 2024, 06:33:24 EAT
 * Author: Yasu Fadhili
 * 
 * Copyright (c) 2024 Yasu Fadhili
 */

#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace http = boost::beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

namespace net
{
  
  struct APIResponse
  {
    bool success;
    std::string message;
    boost::property_tree::ptree_data data;

    std::string toJSON() const {
        boost::property_tree::ptree root;
        root.put("success", success);
        root.put("message", message);
        root.add_child("data", data);

        std::ostringstream oss;
        boost::property_tree::write_json(oss, root);
        return oss.str();
    }
  };


  // HTTP session class to handle individual connections
  class HTTPSession : public std::enable_shared_from_this<HTTPSession> {
  public:
    explicit HTTPSession(tcp::socket socket)
        : socket_(std::move(socket))
        , buffer_(std::make_unique<boost::beast::flat_buffer>())
        , request_(std::make_unique<http::request<http::string_body>>())
        , response_(std::make_unique<http::response<http::string_body>>()) {
    }

    void start() {
        readRequest();
    }

  private:
    tcp::socket socket_;
    std::unique_ptr<boost::beast::flat_buffer> buffer_;
    std::unique_ptr<http::request<http::string_body>> request_;
    std::unique_ptr<http::response<http::string_body>> response_;

    void readRequest() {
        auto self = shared_from_this();

        http::async_read(
            socket_,
            *buffer_,
            *request_,
            [self](boost::system::error_code ec, std::size_t) {
                if (!ec) {
                    self->handleRequest();
                }
            });
    }

    void handleRequest() {
        response_->version(request_->version());
        response_->keep_alive(false);

        switch (request_->method()) {
            case http::verb::get:
                handleGet();
                break;
            case http::verb::post:
                handlePost();
                break;
            default:
                // Method not allowed
                response_->result(http::status::method_not_allowed);
                response_->set(http::field::content_type, "application/json");
                response_->body() = createErrorResponse("Method not allowed").toJSON();
                break;
        }

        writeResponse();
    }

    void handleGet() {
        response_->result(http::status::ok);
        response_->set(http::field::content_type, "application/json");

        // Example response for GET request
        APIResponse apiResponse{
            true,
            "Success",
            boost::property_tree::ptree()
        };
        apiResponse.data.put("message", "Hello from C++ API Server!");
        response_->body() = apiResponse.toJSON();
    }

    void handlePost() {
        try {
            // Parse JSON from request body
            boost::property_tree::ptree pt;
            std::stringstream ss(request_->body());
            boost::property_tree::read_json(ss, pt);

            // Process the request (example)
            APIResponse apiResponse{
                true,
                "Data received successfully",
                pt  // Echo back the received data
            };

            response_->result(http::status::ok);
            response_->set(http::field::content_type, "application/json");
            response_->body() = apiResponse.toJSON();

        } catch (const std::exception& e) {
            response_->result(http::status::bad_request);
            response_->set(http::field::content_type, "application/json");
            response_->body() = createErrorResponse("Invalid JSON format").toJSON();
        }
    }

    APIResponse createErrorResponse(const std::string& message) {
        return APIResponse{
            false,
            message,
            boost::property_tree::ptree()
        };
    }

    void writeResponse() {
        auto self = shared_from_this();

        response_->set(http::field::content_length, response_->body().size());

        http::async_write(
            socket_,
            *response_,
            [self](boost::system::error_code ec, std::size_t) {
                self->socket_.shutdown(tcp::socket::shutdown_send, ec);
            });
    }
  };



  // HTTP listener class to accept incoming connections
  class HTTPListener : public std::enable_shared_from_this<HTTPListener> {
  public:
    HTTPListener(asio::io_context& ioc, tcp::endpoint endpoint)
        : acceptor_(ioc)
        , socket_(ioc) {
        boost::system::error_code ec;

        acceptor_.open(endpoint.protocol(), ec);
        if (ec) {
            throw std::runtime_error("Failed to open acceptor: " + ec.message());
        }

        acceptor_.set_option(asio::socket_base::reuse_address(true), ec);
        if (ec) {
            throw std::runtime_error("Failed to set reuse_address option: " + ec.message());
        }

        acceptor_.bind(endpoint, ec);
        if (ec) {
            throw std::runtime_error("Failed to bind acceptor: " + ec.message());
        }

        acceptor_.listen(asio::socket_base::max_listen_connections, ec);
        if (ec) {
            throw std::runtime_error("Failed to start listening: " + ec.message());
        }
    }

    void start() {
        accept();
    }

  private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;

    void accept() {
        acceptor_.async_accept(
            socket_,
            [self = shared_from_this()](boost::system::error_code ec) {
                if (!ec) {
                    std::make_shared<HTTPSession>(std::move(self->socket_))->start();
                }
                self->accept();
            });
    }
  };
  

} // namespace net

