#include "utils.hpp"

#include <fstream>
#include <filesystem>
#include <sstream>

namespace beast = boost::beast;
namespace http = beast::http;

http::response<http::string_body> handle_request(const http::request<http::string_body>& req) {
  http::response<http::string_body> res;

  res.version(req.version());
  res.keep_alive(false);

  res.set(http::field::server, "http-beastie");
  res.set(http::field::content_type, "text/html");

  if (req.method() == http::verb::get) {
    if (req.target() == "/") {
      try {
        res.result(http::status::ok);
        res.body() = read_file("static/index.html");
      } catch (...) {
        res.result(http::status::internal_server_error);
        res.body() = "<h1 style=\"text-align: center;\">500 Server Error</h1>";
      }
    } else if (req.target() == "/Badawy") {
      try {
        res.result(http::status::ok);
        res.body() = read_file("static/Badawy.html");
      } catch (...) {
        res.result(http::status::not_found);
        res.body() = "<h1 style=\"text-align: center;\">404 Not Found</h1>";
      }
    } else {
      res.result(http::status::not_found);
      res.body() = "<h1 style=\"text-align: center;\">404 Not Found</h1>";
    }
  } else {
    res.result(http::status::method_not_allowed);
    res.set(http::field::allow, "GET");
    res.body() = "<h1 style=\"text-align: center;\">405 Method Not Allowed</h1>";
  }

  res.prepare_payload();
  return res;
}

std::string read_file(const std::string& file_path) {
  std::ifstream file(file_path, std::ios::binary);

  if (!file.is_open()) {
    const std::filesystem::path fallback_path =
      std::filesystem::path(HTTP_BEASTIE_SOURCE_DIR) / file_path;
    file.open(fallback_path, std::ios::binary);
  }

  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file: " + file_path);
  }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
