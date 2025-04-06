#include <iostream>
class MemoryLeak(){
  MemoryLeak(){
    std::cout<<"MemoryLeak created"<<std::endl;
  }
  ~MemoryLeak(){
    std::cout<<"Memoryleak destroyed"<<std::endl;
  }
};

int main(){
  for (int i=0; i<100; i++){
      MemoryLeak* leak = new MemoryLeak();
  }
  std::cout<<"program end"<<std::endl;
}
