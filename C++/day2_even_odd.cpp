#include<iostream>
#include<string>

int main(){

	int num; int mark;
	std::cout<<"enter a number"<<std::endl;
	std::cin>>num;
	
	std::cout<<"This is an "<<(num % 2 == 0 ? "even" : "odd") << " number .\n";
	std::cout<<"This is a "<<(num < 0 ? "negative" : "postive") << " number .\n";
        std::cout<<"This number is  "<<( num % 3 == 0 && num % 5 == 0 ? "divisible" : "not divisible") << " by 3 and 5 .\n";


	std::cout<<"*********************** \n";
	std::cout<<"##**Marks emulator**## \n";
	
	std::cout<<"Please enter your score (0 - 100%)\n";
	std::cin>>mark;

	if(mark >= 90) {
		std::cout<< "Your Grade = A, excellent! \n";
	}
	else if (mark >=80){
                std::cout<< "Your Grade = B, good job! \n";
	}
	else if (mark >= 70){
                std::cout<< "Your Grade = C, good! \n";
	}
	else if (mark >= 60){
                std::cout<< "Your Grade = D, fair! \n";
        }
	else if(mark >= 45){
                std::cout<< "Your Grade = E, work harder! \n";
        }
	else if(mark >=0)
		std::cout<< "Your Grade = F, Redo the exam! \n";
	else 
		std::cout<< "enter a valid score \n";   
	return 0;
/*
	if (num < 0 ){
		std::cout<<num; 
		std::cout <<" is negative"<<std::endl;
	}
	else{
		std::cout<<num; 
		std::cout <<" is postive"<<std::endl;
	}
	if (num % 3 == 0 && num % 5 == 0){
		std::cout<<num; 
		std::cout <<" divisible by both 3 and 5"<<std::endl;
	}
	else{
		std::cout<<num;
                std::cout <<" not divisible by both 3 and 5"<<std::endl;
	}
*/

}

