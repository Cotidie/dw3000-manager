#pragma once

#include <Arduino.h>

enum class ResponseState {
    SUCCESS, ERROR
};

class Response {
public:
    virtual ResponseState getStatus() = 0;
    int getResponseCode() { return this->responseCode; }
    String getError() { return this->error; }

protected:
    int responseCode;
    String error;
};

class SuccessResponse: public Response {
public:
    SuccessResponse(int code) {this->responseCode = code;}
    ResponseState getStatus() { return ResponseState::SUCCESS; } 
};

class ErrorResponse: public Response {
public:
    ErrorResponse(String error = "") { this->error = error; }
    ResponseState getStatus() { return ResponseState::ERROR; } 
};