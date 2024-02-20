#pragma once

#include <coroutine>
#include <cstddef>  // za std::byte
#include <string>
#include <utility> // za std::exchange()
#include <optional>
#include <cassert>


class Parser{
    // Čekanje na sljedeći oktet.
    struct Awaiter{
     // Kodirati Awaiter koji čeka na sljedeći oktet i vraća
     // ga u korutinu kad ga dočeka. Ako oktet još nije spreman
     // suspendira korutinu.

      //---------------------
      // std::coroutine_handle<> coro;  NIJE POTREBNA
      std::optional<std::byte> & recieveByte; // REFERANCA 

      bool await_ready() const{ return recieveByte.has_value();}
      // SAMO SUSPENDIRA
      void await_suspend(std::coroutine_handle<> /* handle */) noexcept {/* coro = handle;*/}

      std::byte await_resume() noexcept{
          assert(recieveByte.has_value());
          auto result = recieveByte.value();
          recieveByte.reset();
          //std::byte result = std::exchange(*recieveByte, std::byte{}); ZBOG NEKOG RAZLOGA PRAVI PROBLEME
          return result;
      }
    };

     struct Promise
     {
         std::optional<std::byte> current_byte;
         std::string current_frame;

         // Detalji Promise objekta
         //----------------------

         auto initial_suspend() const noexcept{  return std::suspend_always{}; }

         auto final_suspend() const noexcept{ return std::suspend_always{}; }

         void unhandled_exception() { std::terminate();}

         void return_void() noexcept { }
        // Vraća Parser objekt iz Promise-a
        auto get_return_object() noexcept{
            return Parser{std::coroutine_handle<Promise>::from_promise(*this)};
        }

        std::suspend_always yield_value(std::string frame){
            current_frame = std::move(frame);
            return {};
        }

        Awaiter await_transform(std::byte /* byte */){
           // current_byte = byte;  TO SE RADI U set_byte() METODI
            //return Awaiter{nullptr, current_byte};
            return Awaiter{current_byte};
        }

        std::string get_frame(){ // TO JE MOGLO BITI U PARSER KLASI
            std::string frame = std::move(current_frame);
            current_frame.clear();
            return frame;
        }
      };

     std::coroutine_handle<Promise> cHandle;

public:
     using promise_type = Promise;
     // Javne metode klase Parser.

     Parser(std::coroutine_handle<Promise> handle): cHandle(handle) { }

     ~Parser() {
         if (cHandle) {
             cHandle.destroy();
         }
     }

     // nije dopusteno
     Parser(Parser const &) = delete;
     Parser & operator=(Parser const &) = delete;

     // vraća true ako korutina nije gotova, inače false
     bool resume() const{
         if(!cHandle || cHandle.done())
             return false;
         cHandle.resume();
         return !cHandle.done();
     }
     //vraća pripadajući Awaiter
     //Awaiter set_byte(std::byte byte) const{
     void set_byte(std::byte byte) const{
        // return cHandle.promise().await_transform(byte); ČEMU await_transform?
         cHandle.promise().current_byte = byte;
         if(!cHandle.done())
            cHandle.resume();
     }
     // trenutni okvir iz Promise objekta
     std::string get_frame() const{
         return cHandle.promise().get_frame();
     }

};
