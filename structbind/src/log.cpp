#include "log.h"

Log::Log(std::string sender, int priority, std::array<char, 3> code, std::string message)
    : _sender(sender), _priority(priority), _code(code), _message(message) {}

std::string& Log::sender() { return _sender; }
int& Log::priority() { return _priority; }
std::array<char, 3>& Log::code() { return _code; }
std::string& Log::message() { return _message; }

const std::string& Log::sender() const { return _sender; }
int Log::priority() const { return _priority; }
const std::array<char, 3>& Log::code() const { return _code; }
const std::string& Log::message() const { return _message; }


void setPriority(Log& log, int newPriority) {
    log.priority() = newPriority;
}


