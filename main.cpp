#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstdlib>

class Track
{
private:
    std::string name;
    std::tm creationDate;
    std::time_t duration;
public:
    Track(std::string name, std::tm creationDate, std::time_t duration)
    {
        this->name=name;
        this->creationDate=creationDate;
        this->duration=duration;
    }

    Track()
    {
        name="None";
        duration=std::time(nullptr);
        creationDate=*std::localtime(&duration);
        duration=0;
    }

    std::string getTrackname()
    {
        return name;
    }

    std::string getCreationDate()
    {
        std::ostringstream temp;
        temp << std::put_time(&creationDate, "%d/%m/%Y");
        return temp.str();
    }

    std::time_t getDuration()
    {
        return duration;
    }
};

class Player
{
private:
    int qty=0, currentSong=0;
    int storageCapacity=8;
    Track* songs=new Track[storageCapacity];
    bool isPaused=false, isStopped=true;
public:
    Player(Track* songs, int qty)
    {
        this->qty=qty;
        this->songs=new Track[qty];

        for(int i=0;i<this->qty;i++)
            *(this->songs+i) = *(songs+i);
    }

    Player()
    {

    }

    ~Player()
    {
        delete[] songs;
    }

    void add(Track song)
    {
        if(qty<storageCapacity)
        {
            *(songs+qty)=song;
            qty++;
        }
        else
        {
            storageCapacity=storageCapacity*2;
            Track* temp=new Track[storageCapacity];
            for(int i=0;i<8;i++)
            {
                *(temp+i)=*(songs+i);
            }

            delete[] songs;
            songs=temp;
            *(songs+qty)=song;
            qty++;
        }
    }

    void play()
    {
        if(isPaused)
        {
            isPaused = false;
            std::cout << (songs + currentSong)->getTrackname() << " resumed\n";
        }
        else if(qty!=0&&isStopped)
        {
            currentSong = rand()%qty;
            std::cout << (songs + currentSong)->getTrackname() << " " << (songs + currentSong)->getCreationDate() << std::endl;
            isStopped=false;
        }
    }

    void pause()
    {
        if(!isPaused&&qty!=0)
        {
            isPaused=true;
            std::cout << (songs + currentSong)->getTrackname() << " paused\n";
        }
    }

    void next()
    {
        if(isPaused||isStopped)
        {
            isPaused = false;
            isStopped = true;
        }

        this->play();
    }

    void stop()
    {
        if(!isStopped&&qty!=0)
        {
            std::cout << (songs+currentSong)->getTrackname() << " stopped\n";
        }
    }

};

int main()
{
    //std::time_t t=std::time(nullptr);
    //std::tm today= *std::localtime(&t);
    std::tm date = {1,1,1,1,1,70,0,0,0};

    std::srand(std::time(nullptr));
    Track songs[10];

    std::string songNames[10]={"Lovely song",
                        "Best ever song",
                        "Lovely song",
                        "Great song",
                        "Bad song",
                        "Girls song",
                        "Boys song",
                        "Dizzy song",
                        "Kids song",
                        "Deutschland uber alles song"};

    std::tm songdate=date;

    for(int i=0;i<10;i++)
    {
        songdate.tm_year=date.tm_year+(rand()%50);
        songdate.tm_mon=date.tm_mon+(rand()%12);
        songdate.tm_mday=date.tm_mday+(rand()%30);
        songs[i]=Track (songNames[i], songdate, 240+rand()%120);
    }

    Player sony;
    for(int i=0;i<10;i++)
        sony.add(songs[i]);

    std::string input;
    do
    {
        std::cout << "Input command: ";
        std::cin >> input;
        if(input=="play")
            sony.play();
        else if (input=="pause")
            sony.pause();
        else if(input=="next")
            sony.next();
        else if(input=="stop")
            sony.stop();
    }
    while(input!="exit");

    return 0;
}
