// Practice Exercise 1

#include <iostream>
#include <vector>
using namespace std;

class Artwork
{
    private:
    string artist, title;
    unsigned int year;

    public:
    // default constructor
    Artwork() : year(0) {}

    // parametric constructor
    Artwork(string new_artist, string new_title, unsigned int new_year) : 
    artist(new_artist), title(new_title), year(new_year) {}

    string get_artist()
    {
        return artist;
    }

    string get_title()
    {
        return title;
    }

    unsigned int get_year()
    {
        return year;
    }

    bool operator==(const Artwork & target) const
    {
        //fragmented for readability
        bool are_equal = artist == target.artist;
        are_equal = are_equal && title == target.title;
        are_equal = are_equal && year == target.year;
        return are_equal;
    }
};

class SoldArtwork : public Artwork
{
    private:
    string customer_name, customer_address;
    double sale_amount;

    public:
    // default constructor
    SoldArtwork() : sale_amount(0) {}

    // Parametric constructor
    SoldArtwork(Artwork old, string new_name, string new_address, double new_amount) :
    Artwork(old), customer_name(new_name), customer_address(new_address), sale_amount(new_amount) {}

    bool operator==(const SoldArtwork & target) const
    {
        bool are_equal = Artwork::operator==(target) && customer_name == target.customer_name;
        are_equal = are_equal && customer_address == target.customer_address;
        are_equal = are_equal && sale_amount == target.sale_amount;
        return are_equal;
    }
};

class ArtCollection 
{
    vector <Artwork> have;
    vector <SoldArtwork> sold;

    public:
    int size() 
    {
        return have.size();
    }

    bool insert_artwork(const Artwork& other){
        bool dupe = false;
        for(int i = 0; i<have.size();i++){
            if (other == have[i])
                dupe = true;
        }
        if (!dupe){
            have.push_back(other);
            return true;
        }else{
            return false;
        }
    }

    bool sell_artwork(const SoldArtwork& other){
        static_cast<Artwork>(other);
        for (int i =0; i < have.size(); i++){
            if (have[i]==other){
                sold.push_back(other);
                have.erase(have.begin()+i);
                //i--;
                return true;
            }
        }
        return false;
    }
};

int main(){
    ArtCollection museum;
    Artwork a1("Jeremy", "number 1", 2020);
    Artwork a2("Evan", "bikes", 1996);
    museum.insert_artwork(a1);
    museum.insert_artwork(a2);
    cout << museum.size();
    SoldArtwork s1(a1,"mike","mike's house", 10);
    museum.sell_artwork(s1);
    cout <<museum.size();
}
