//
//  INTERFACE.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 02/12/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "INTERFACE.hpp"
namespace itf {
/*int Answer(const std::string alt[], int n)
{
    int answer;
    std::string prompt = Choice;
    std::cout << "\nWhat do you want to do:" << std::endl;
    for(int i = 0; i < n; i++)
        std::cout << alt[i].c_str() << std::endl;
    do{
        std::cout << prompt.c_str() << ": -> ";
        prompt = Msg;
        std::cin >> answer;
        if (!std::cin.good()){
            std::cout << "Error when number of choice was entered; \nRepeat, please." << std::endl;
            std::cin.ignore(80, '\n');
            std::cin.clear();
        }
    } while (answer < 0 || answer >= n);
    std::cin.ignore(80, '\n');
    return answer;
}*/
    int Add(Descatalog *view)
    {
        string id;
        std::cout << "Enter name object" << std::endl;
        std::cin >> id;
        if (!std::cin.good())
            throw std::invalid_argument("Error when a name was entered");
        view->add_object(id);
        
        return 0;
    }
    int Find(Descatalog *view)
    {
        std::string name;
        std::cout << "Enter a object name: --> ";
        std::cin >> name;
        if (!std::cin.good())
            throw std::invalid_argument("Error when a shape name was entered");
        view->find(name);
    
        return 0;
    }
    int Remove(Descatalog*view)
    {
        std::string name;
        std::cout << "Enter a shape name: --> ";
        std::cin >> name;
        if (!std::cin.good())
            throw std::invalid_argument("Error when a shape name was entered");
        if (view->remove(name))
            std::cout << "Ok" << std::endl;
        else
            std::cout << "The Shape with Name \"" << name << "\" is absent in container"
            << std::endl;
        return 0;
    }
    int ShowAll(Descatalog *view){
        std::cout << *view;
        return 0;
    }
    
    int NextC(Descatalog *view){
        return 0;
    }
    
    int OpenF(Descatalog *view){
        return 0;
    }
    
    int BackC(Descatalog *view){
        return 0;
    }
}
