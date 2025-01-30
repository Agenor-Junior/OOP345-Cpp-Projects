#include "order.h"
#include <iostream>


int main(int argc, char** argv)
{   
    std::cout <<"Arguments is:"<<std::endl;

    for(int i=0; i< argc;i++){
        std::cout << argv[i]<<std::endl;
    }



    return 0;
}
