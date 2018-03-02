#include <iostream>
#include <vector>
#include <map>
using namespace std;

int search(int a){
    cout<<"this is "<<a<<" lah"<<endl;
    return 0;
}
std::map<std::string,int (*)(int)> funcMap = {
    {"search",&search},
};
int main(int argc, char** argv)
{
    /*cout << "You have entered " << argc
         << " arguments:" << "\n";
    std::string args[argc];
    for (int i = 0; i < argc; ++i){
         args[i] = argv[i] ;
        cout<<args[i]<<' ';
        
    }*/
    std::string line;
     while(std::getline(std::cin, line)) // read from std::cin
    {
        if(line.compare("exit") == 0){
            std::cout<<"Bye Bye"<<endl;
            break;
        }
        // show that it arrived
        std::cout << "Line Received: " << line << '\n';
        
       if (funcMap.find(line) != funcMap.end()) {
                funcMap[line](10);
        }
    }
    
    return 0;
}