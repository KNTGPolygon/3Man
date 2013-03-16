#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    int firstNumber = 0;
    int secondNumber = 0;
    int sum = 0;
 
    cout << "Enter first number" << endl;
    cin >> firstNumber;
    cout << "Enter second number" << endl;
    cin >> secondNumber;
    
    if(firstNumber > secondNumber)
    {
         cout << "First number is a maximum, it is: " << firstNumber << endl;          
    }
    else if (firstNumber == secondNumber)
    {
         cout << "They are equal! Maximum is: " << firstNumber << endl;     
    }
    else
    {
     cout << "Second number is a maximum, it is: " << secondNumber << endl;    
    }
    
    sum = firstNumber + secondNumber;
    
        cout << "Their sum is(two numbers): " << sum << endl;
        
        sum = 0;
        int number ;
        
        do
        {
            cout << "Give a number, giving 0 will end that loop and display sum" << endl << endl;
            cin >> number;
            sum += number;
         }while(number != 0);
         
         cout << "Sum of multiple numbers is: " << sum << endl;
         
         
         int height = 0;
         cout << "Give height of the pyramid" << endl;
         cin >> height;
         cout << endl << endl;
         int lastRowNumber = 2*height - 1;
         
         ostringstream pyramid ;

         
         for(int h = 1; h <= height; h++)
         {
                 pyramid << h << " ";
                 int counts = (lastRowNumber - (h*2 - 1))/2;
                 int noOfStars = lastRowNumber - counts*2;
                 
                 for(int spaces = 1; spaces <= counts; spaces ++)
                 {
                  pyramid << " ";        
                 }
                 
              
              for(int i = 1; i <= noOfStars ; i ++)
                 pyramid << "*";
                 
                 for(int spaces = 1; spaces <= counts; spaces ++)
                 {
                 pyramid << " ";        
                 }
                 
                 pyramid << "\n";
         }
    
    cout << pyramid.str();
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
