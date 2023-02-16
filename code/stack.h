#pragma once

template <class T>
class Stack
{
public:



    //Add the element (does not matter where)
    void push(const T &val);{
        list.add_to_head(val);
    }


     //Remove and return the most recently added element
    //Last In First Out Abstract Data Type (LIFO) 
    //First In Last Out (FILO) the first element added
    T pop(){
        T temp = list.head.val();
        List.remove_head();
        return temp;
        //if is empty it will throw we can catch it and throw it again but we can also leave it liek this
    }

  //returns the most recently added element //active record //stack frame
     T top() const{
         return list.head.val();
     }
    bool is_empty(){
        return list.is_empty();
    }
    void clear(){
        while(!list.is_empty())
            list.remove_head();
    }

//we will use a single linked list to implement the operations
private:
    List<T> list;
}



//we use it for 
//memory managment
//managing functions calls 
//conversion of recursive code to irerative code

//ex
// Stack <int> s;
// s.push(5);
// s.push(10);
// s.push(11);
// s.pop();
// s.push(7);
// s.pop();
// s.pop();

//The element that remains is 5

//function calls operate the same way as this in dellocation 
/*
f1(){
    f2();
}

f2(){
    f3();
}

f3(){
    f4();
}

main(){
    f1();
}

*/

//Example of stack frame as well is destructors 


//EXAMPLE:UNDO REDO
/*
two stacks
when you pop from one stack it is put into another stack for redo
*/
