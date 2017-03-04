#include "bstmap.h"
#include "map.h"
#include <iostream>
#include <stdio.h>


int main() {
  std::cout << "testing... \n";
  BstMap<std::string,int> * map = new BstMap<std::string,int>();
  map->add("kyle",1);
  map->add("tom",2);
  std::cout << "Added 2 items to map \n";
  
  BstMap<std::string,int> * map2 = new BstMap<std::string,int>();
  map2->add("shitty",10);
  
  *map2=*map;

  map2->remove("kyle");
  map2->remove("This does not exit");


  BstMap<int,std::string> * map3 = new BstMap<int,std::string>();  
  map3->add(1,"Prior");
  map3->add(1,"This");
  map3->add(2,"is");
  map3->add(3,"a");
  map3->add(4,"test");
  map3->add(100,"Boo");
  map3->add(101,"Right child");
  map3->add(99,"Left child");

  map3->remove(100);
  map3->remove(4);
  //map3->remove(1);

  std::cout << map3->lookup(1)  << "\n";
  // Already deleted 100, so this should cause an exception to be thrown
  //std::cout << map3->lookup(100)  << "\n";



  BstMap<int,std::string> * map4 = new BstMap<int,std::string>(); 
  map4->add(8,"one");
  map4->add(4,"one");
  map4->add(1,"one");
  map4->add(6,"one");
  map4->add(5,"one");
  map4->add(12,"one");

  map4->remove(6);

  BstMap<int,std::string> * map5 = new BstMap<int,std::string>(); 
  map5->add(1,"test");
  
  map5->remove(1);
  map5->add(2,"test2");
  
  delete map;
  delete map2;
  delete map3;
  delete map4;
  delete map5;
  return 1;
}
