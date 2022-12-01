#include <iostream>

class Artist
{
public :
   Artist(const std::string& nume); 
   std::string toString();                    
  

private :
    std::string Numele;
    Artist(const Artist&);            //copy constructor and copy assignement are private so can not be accesed(item6)
    Artist& operator=(const Artist&);
};

std::string Artist::toString(){
    return Numele;
 }

Artist::Artist(const std::string& Nume)    //the arguments in the initialization list are used as constructor arguments(item4
   :Numele(Nume)        // this way is initialization not assignment(item4)
                         //se apeleaza astfel copy constructorul direct
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


void swap(Melodie& rhs)
{
    std::swap(this->NumeleMelodiei, rhs.NumeleMelodiei);
    std::swap(this->TrackNumber, rhs.TrackNumber);
}


/*
  Melodie& operator=(const Melodie& rhs)  //ITEM 10,l-am pus comment pt itemul11
  {

    NumeleMelodiei=rhs.NumeleMelodiei;
    TrackNumber=rhs.TrackNumber;
    
    std::cout<<"aici returnam referinta la obiect, exemplificare pentru itemul10";
     std::cout<<'\n';

    return *this;

  }
  */

Melodie& operator=(const Melodie& rhs) //ITEM 11,copy and swap self assignment
 {
   Melodie temp(rhs);
   using std::swap;

   this->swap(temp);

   std::cout<<"aici returnam referinta la obiect, exemplificare pentru ITEM11";
     std::cout<<'\n';


   return *this;

}


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


class PlayedMelodie: public Melodie { 

public:
 PlayedMelodie(const PlayedMelodie& rhs);
 PlayedMelodie& operator=(const PlayedMelodie& rhs);

 PlayedMelodie(const std::string& numemel, const int tracknumber,const int p);


std::string toString()
{
    return Melodie::toString()+"ascultata de " + std::to_string(numbers)+" ori";
}

private:
int numbers;


};

PlayedMelodie::PlayedMelodie(const std::string& numemel, const int tracknumber, const int p)
:Melodie(numemel,tracknumber),
 numbers(p)
 {}


PlayedMelodie::PlayedMelodie(const PlayedMelodie& rhs)
:Melodie(rhs), //invoke base class 
numbers(rhs.numbers)
{
   std::cout<<"PlayedMelodie copy constructor,ITEM12";
   std::cout<<'\n';
}
PlayedMelodie& PlayedMelodie::operator=(const PlayedMelodie& rhs)
{
    std::cout<<"PlayedMelodie copy assignment operator,ITEM12";
    std::cout<<'\n';
    Melodie::operator=(rhs);
    numbers=rhs.numbers;
    return *this;
}



int main() {
   
    Melodie m("Invisible String",3);
    Melodie M2("Evermore",4);
    Melodie M3("Cowboy like me",10);

    std::cout<<(m.toString());
    std::cout<<'\n';
    
    SongWritter w; //default constructor(item5)

    Melodie mel2(m); //copy constructor(item5)
    std::cout<<(mel2.toString());
    std::cout<<'\n';

    mel2=m;  //copy assignement operator(item5)
    std::cout<<(mel2.toString());
    std::cout<<'\n';

    //mel2.~Melodie();  //destructor(item5)

    M2=m=M3; //ITEM 10
    std::cout<<(M2.toString()); //acum numele melodiei M2 trebuie sa fie acelasi cu M3
    std::cout<<'\n';

    Melodie song("The moment",7);
    song=song;        //ITEM 11,self assignment

   std::cout<<(song.toString());
   std::cout<<'\n';
    
    PlayedMelodie p1=PlayedMelodie("Maroon",2,128);
    std::cout<<(p1.toString());
    std::cout<<'\n';

    PlayedMelodie p2=PlayedMelodie("Glitch",12,65);
    std::cout<<(p2.toString());
    std::cout<<'\n';

    p2=p1;  //ITEM12
    std::cout<<(p2.toString());
    std::cout<<'\n'; 



    return 0;
}