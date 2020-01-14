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
    void print(){
    	cout << "Artist: " << artist << endl << "Title: " << title << endl
        << "Year: " << year << endl;
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
        // checks to make sure the Artwork is the same before checking the buyer information
        bool are_equal = Artwork::operator==(target) && customer_name == target.customer_name;
        are_equal = are_equal && customer_address == target.customer_address;
        are_equal = are_equal && sale_amount == target.sale_amount;
        return are_equal;
    }

    void print(){
		Artwork::print();
		cout << "Buyer Name: "<< customer_name << endl <<"Buyer Address: "<< customer_address << endl
        <<"Sale Amount: "<< sale_amount << endl;
	}
};

class ArtCollection 
{
    vector <Artwork> have;
    vector <SoldArtwork> sold;

    public:
    // Size of both Artwork and SoldArtwork vectors
    int size() 
    {
    	cout<< "have: " <<have.size() <<"  sold: "<<sold.size()<<endl;
        return have.size() + sold.size();
    }

    bool insert_artwork(const Artwork& other){
        bool dupe = false;
        for(vector<Artwork>::iterator my_it=have.begin();my_it!=have.end();my_it++){
            if (other == *my_it){
                dupe = true;
            }
		}
        if (!dupe){
            have.push_back(other);
            cout << "Artwork added!" << endl;
            return true;
        }
		else{
            cout << "Insert failed. Duplicate artwork." << endl;
            return false;
        }
    }

    bool sell_artwork(const SoldArtwork& other){
        static_cast<Artwork>(other);
        for (int index = 0; index < have.size(); index++){
            if (have[index] == other){
                sold.push_back(other);
                have.erase(have.begin()+index);
                index--;
                cout << "Sold!" << endl;
                return true;
            }
        }
        cout << "Did not sell." << endl;
        return false;
    }
	
    bool operator==(const ArtCollection& other) const
    {
        int count = 0;
        if (have.size() != other.have.size() ||
			 sold.size() != other.sold.size()){
			return false;
			}
	        
        for(int art1 = 0; art1 < have.size(); art1++){
            for (int art2 = 0; art2 < have.size(); art2++){
                if (have[art1] == other.have[art2])
                    count++;                    
            }           
        }
        if (count == have.size()){
            //check operator
            count = 0;
            for(int art1 = 0; art1 < sold.size(); art1++){
                for (int art2 = 0; art2 < sold.size(); art2++){
                    if (sold[art1] == other.sold[art2])
                    count++;
                }
            }
            if (count == sold.size())
                return true;
        }


        return false;
	}

    friend ArtCollection operator+(ArtCollection& original, ArtCollection& other);
};	


ArtCollection operator+(ArtCollection& original, ArtCollection& other) 
{
    ArtCollection temp;
    temp.have.insert(temp.have.end(),original.have.begin(),original.have.end());
    temp.have.insert(temp.have.end(),other.have.begin(),other.have.end());

    temp.sold.insert(temp.sold.end(),original.sold.begin(),original.sold.end());
    temp.sold.insert(temp.sold.end(),other.sold.begin(),other.sold.end());

    return temp;
}


bool test_insert_artwork(ArtCollection & collection,Artwork art){
    if(collection.insert_artwork(art)){
    	return true;
	}
	return false;
}

bool test_sell_artwork(ArtCollection & gallery, SoldArtwork sell){
    //sell an artwork   
    
    if(gallery.sell_artwork(sell)){
    	return true;
	}
	return false;
}

bool test_compare(Artwork one, Artwork two){
	return (one==two);
}
int main()
{
	ArtCollection museum;
	Artwork a1("Jeremy", "number 1", 2020);
	
	//insertion
	test_insert_artwork(museum, a1);
	test_insert_artwork(museum, a1);
	Artwork a2("Evan", "bikes", 1996);
	test_insert_artwork(museum, a2);
	Artwork a3("Keiquang", "integrals", 2020);
	
	// sell artwork, selling the same artwork, selling an artwork that doesn't exist
	SoldArtwork s1(a2, "bob", "bob's house", 20);
	SoldArtwork s2(a3, "joe", "joe's house", 0);
	test_sell_artwork(museum, s1);
	test_sell_artwork(museum, s1);
	test_sell_artwork(museum, s2);
	
	// operator== test for Artwork and SoldArtwork
	cout << test_compare(a1,a1) << endl;
	cout << test_compare(a1,a2) << endl;
	cout << test_compare(s1,s1) << endl;
	cout << test_compare(s1,s2) << endl;
	
	//test_insert_artwork(museum, a2);
	
	//test_sell_artwork(museum,a1,"mike", "UW", 17.99);
	
	//Artwork art("Evan", "planes", 2016);
		
	/*
   //sell an artwork
    SoldArtwork s1(a1,"mike","mike's house", 10);
    ac1.sell_artwork(s1);
    s1.print();
    
    //second collection
    ArtCollection ac2;

	Artwork a4("Evan", "planes", 2016);	
    ac2.insert_artwork(a4);
    //inserts a fresh artwork
    Artwork b1("Bob", "bob's building", 10);
    ac2.insert_artwork(b1);
    
    //combines
    ArtCollection ac3;
    ac3 = ac3 + ac1;
    ac3 = ac3 + ac2;
    cout << ac3.size() << endl;
    */
}

