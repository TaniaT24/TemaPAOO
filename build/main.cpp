#include <iostream>
#include <tr1/memory>

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



private :
    std::string NumeleMelodiei;
    int TrackNumber;
};


Melodie::Melodie(const std::string& numemel, const int tracknumber)
:NumeleMelodiei(numemel),
 TrackNumber(tracknumber)
 {}


Melodie* createMelodie()
{
  Melodie *melNew = new Melodie("Forever Winter",13);  //ITEM 13
   std::cout<<"S-a creat un nou obiect de tip melodie";
   std::cout<<'\n';

  return melNew;

}

void f()
{
                                      //ITEM13
std::tr1::shared_ptr<Melodie> 
pInv1(createMelodie());     //apelam functia creata pt noul obiect
std::tr1::shared_ptr<Melodie> 
pInv2(pInv1); 
pInv1 = pInv2; 

}

class MelodyOnlyOnYoutube{    //ITEM14

    private:
        std::string name;
        bool yt=false;      //initial melodia e si pe Spotify

    public:
    MelodyOnlyOnYoutube(std::string NumeMel){
        this->name = NumeMel;
        
    }

    MelodyOnlyOnYoutube(const MelodyOnlyOnYoutube &m){
        this->name = m.name;
        this->yt = m.yt;
    }

    ~MelodyOnlyOnYoutube(){
        std::cout<<"Destructorul a fost apelat,Melodia care era doar pe Youtube si pe Spotify nu, a fost stearsa";   //destructor
        std::cout<<'\n';  
    }


    void setarePeYtsauNU(bool yt){
        this->yt = yt;
    }

    void isOnlyOnYTorNot(){
        if(this->yt == false) 
           { std::cout<<"Melodia "<< this->name <<" este si pe Spotify,nu doar pe Youtube";
            std::cout<<'\n';}
        else
           { std::cout<<"Melodia "<<this->name <<" este doar pe Youtube,nu si pe Spotify";
             std::cout<<'\n';
           }
    }

};


void onlyOnYT(MelodyOnlyOnYoutube &m){
    m.setarePeYtsauNU(true);            //functia care seteaza melodia sa fie doar pe yt
}

void AlsoOnSpotify(MelodyOnlyOnYoutube &m){
    m.setarePeYtsauNU(false);               //functia care seteaza melodia sa fie si pe Spotify
} 

class OwnerMelody{    //ITEM14
    private:
        MelodyOnlyOnYoutube &mel;

    public:
    OwnerMelody(MelodyOnlyOnYoutube &m):
    mel(m){ 
        onlyOnYT(mel);  //seteaza sa fie doar pe yt
    }
    ~OwnerMelody(){
        AlsoOnSpotify(mel);    //pune melodia si pe Spotify
         std::cout<<"Destructorul a fost apelat pt clasa Owner";   
        std::cout<<'\n';  
    }
};



int main() {
   
    Melodie m("Invisible String",3);
    Melodie M2("Evermore",4);
    Melodie M3("Cowboy like me",10);

    std::cout<<(m.toString());
    std::cout<<'\n';
    
     f();   //ITEM13
  
    MelodyOnlyOnYoutube melodieyt("Blonde");  //ITEM 14
    melodieyt.isOnlyOnYTorNot();                  //initial bool este pe false deci melodia e si pe Spotify
    std::cout<<"\n";

    OwnerMelody OWNm(melodieyt);          
    melodieyt.isOnlyOnYTorNot();  //melodia a fost acum setata doar pe yt de catre owner
    std::cout<<"\n";



    return 0;
}