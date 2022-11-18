#include <iostream>

class Artist
{
public :
   Artist(const std::string& nume); //the arguments in the initialization list are used as constructor arguments(item4)
   std::string toString();
  

private :
    std::string Numele;
    Artist(const Artist&);            //copy constructor and copy assignement are private so can not be accesed(item6)
    Artist& operator=(const Artist&);
};

std::string Artist::toString(){
    return Numele;
 }

Artist::Artist(const std::string& Nume)
   :Numele(Nume)        // this way is initialization not assignment(item4)
 {}


Artist& a()
{
    static Artist a("Taylor Swift "); //Avoid initialization order problems replacing non-local static objects with local static objects
    return a;                          //(item4)
}



class Melodie
{
public :
  Melodie(const std::string& numemel, const int tracknumber);
  std::string toString(){
    return "Nume: "+NumeleMelodiei+" ,Artistul: "+a().toString();}

private :
    std::string NumeleMelodiei;
    int TrackNumber;
};

Melodie::Melodie(const std::string& numemel, const int tracknumber)
:NumeleMelodiei(numemel),
 TrackNumber(tracknumber)
 {}



class SongWritter
{   //default constructor(item5)
};



int main() {
   
    Melodie m("Invisible String",3);
    std::cout<<(m.toString());
    std::cout<<'\n';
    
    SongWritter w; //default constructor(item5)

    Melodie mel2(m); //copy constructor(item5)
    std::cout<<(mel2.toString());
    std::cout<<'\n';

    mel2=m;  //copy assignement operator(item5)
    std::cout<<(mel2.toString());

    mel2.~Melodie();  //destructor(item5)


    return 0;
}