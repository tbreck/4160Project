//        Data-Driven Object oriented Game Construction
#include "engine.h"
#include "BoardManager.h"

RenderContext* RenderContext::instance = NULL;

int main(int, char*[]) {
   try {
      Engine engine(10);
      engine.play();
      delete RenderContext::getInstance();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
